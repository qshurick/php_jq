/* php_jq extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
#include "php_php_jq.h"
#include "php_jq_arginfo.h"
#include "jq.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

zend_class_entry *invalid_program_exception;
zend_class_entry *invalid_json_exception;
zend_class_entry *unable_transform_exception;

enum {
  PHP_JQ_INIT_ERROR = 1,
  PHP_JQ_PROGRAM_ERROR = 2,
  PHP_JQ_INPUT_ERROR = 3,
  PHP_JQ_TRANSFORM_ERROS = 4
};

typedef struct {
  unsigned char last_error;
  jv result;
} php_jq_result;

/**
  * Preven JQ to write into stderr, tho now need a way to get the message and
  * share it in corresponding exception
  */
static void stub_err_cb(void *data, jv msg)
{
}

void transform_json(php_jq_result* ret, const char* program, const char* json_string)
{
  jq_state *jq = NULL;

  ret->last_error = 0;

  jq = jq_init();
  if (jq == NULL) {
    ret->last_error = PHP_JQ_INIT_ERROR;
    return;
  }

  jq_set_error_cb(jq, stub_err_cb, NULL);

  jv program_arguments = jv_object();
  int compiled = jq_compile_args(jq, program, jv_copy(program_arguments));
  if (!compiled) {
    ret->last_error = PHP_JQ_PROGRAM_ERROR;
    goto safe_out;
  }

  jv data = jv_parse(json_string);
  if (jv_get_kind(data) == JV_KIND_INVALID) {
    ret->last_error = PHP_JQ_INPUT_ERROR;
    jv_free(data);
    goto safe_out;
  }

  jq_start(jq, data, 0);
  jv result;
  if (!jv_is_valid(result = jq_next(jq))) {
    ret->last_error = PHP_JQ_TRANSFORM_ERROS;
    goto safe_out;
  }
  ret->result = result;

safe_out:
  
  jv_free(program_arguments);
  jq_teardown(&jq);
}

PHP_METHOD(Qshurick_Jq_Jq, __construct)
{
}

PHP_METHOD(Qshurick_Jq_Jq, transform)
{
  zend_string *program;
  zend_string *json;

  ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STR(program);
    Z_PARAM_STR(json);
  ZEND_PARSE_PARAMETERS_END();

  php_jq_result *const result = (php_jq_result *) emalloc(sizeof(php_jq_result));
  transform_json(result, ZSTR_VAL(program), ZSTR_VAL(json));

  if (result->last_error != 0) {
    switch (result->last_error) {
      case PHP_JQ_PROGRAM_ERROR:
        zend_throw_exception(invalid_program_exception, "Jq program has errors", 0);
        break;
      case PHP_JQ_INPUT_ERROR:
        zend_throw_exception(invalid_json_exception, "Invalid JSON string", 0);
        break;
      case PHP_JQ_INIT_ERROR:
      case PHP_JQ_TRANSFORM_ERROS:
      default:
        zend_throw_exception(unable_transform_exception, "Unable to perform transformation", 0);
    }
    efree(result);
    RETURN_THROWS();
  }

  jv jv_json_string = jv_dump_string(result->result, 0);
  const char *str = jv_string_value(jv_json_string);
  zend_string *ret = zend_string_init(str, strlen(str), 0);

  efree(result);
  jv_free(jv_json_string);

  RETURN_STR(ret);
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(php_jq)
{
#if defined(ZTS) && defined(COMPILE_DL_QSHURICK)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

    register_class_Qshurick_Jq_Jq();
    invalid_program_exception = register_class_Qshurick_Jq_InvalidProgramException(spl_ce_RuntimeException);
    invalid_json_exception = register_class_Qshurick_Jq_InvalidJsonStringException(spl_ce_RuntimeException);
    unable_transform_exception = register_class_Qshurick_Jq_UnableTransformException(spl_ce_RuntimeException);

	return SUCCESS;
}

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(php_jq)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "php_jq support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ php_jq_module_entry */
zend_module_entry php_jq_module_entry = {
	STANDARD_MODULE_HEADER,
	"php_jq",
	NULL,
	PHP_MINIT(php_jq),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(php_jq),
	PHP_PHP_JQ_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHP_JQ
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(php_jq)
#endif
