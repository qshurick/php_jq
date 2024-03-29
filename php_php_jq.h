/* php_jq extension for PHP */

#ifndef PHP_PHP_JQ_H
# define PHP_PHP_JQ_H

extern zend_module_entry php_jq_module_entry;
# define phpext_php_jq_ptr &php_jq_module_entry

# define PHP_PHP_JQ_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_PHP_JQ)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_PHP_JQ_H */
