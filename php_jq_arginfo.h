/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 7952faf85c569cc487ca1f84670b32b195926803 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Qshurick_Jq_Jq___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Qshurick_Jq_Jq_transform, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, jsonString, IS_STRING, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(Qshurick_Jq_Jq, __construct);
ZEND_METHOD(Qshurick_Jq_Jq, transform);


static const zend_function_entry class_Qshurick_Jq_Jq_methods[] = {
	ZEND_ME(Qshurick_Jq_Jq, __construct, arginfo_class_Qshurick_Jq_Jq___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Qshurick_Jq_Jq, transform, arginfo_class_Qshurick_Jq_Jq_transform, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Qshurick_Jq_InvalidProgramException_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Qshurick_Jq_InvalidJsonStringException_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Qshurick_Jq_UnableTransformException_methods[] = {
	ZEND_FE_END
};

static zend_class_entry *register_class_Qshurick_Jq_Jq(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Qshurick\\Jq", "Jq", class_Qshurick_Jq_Jq_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Qshurick_Jq_InvalidProgramException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Qshurick\\Jq", "InvalidProgramException", class_Qshurick_Jq_InvalidProgramException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Qshurick_Jq_InvalidJsonStringException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Qshurick\\Jq", "InvalidJsonStringException", class_Qshurick_Jq_InvalidJsonStringException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}

static zend_class_entry *register_class_Qshurick_Jq_UnableTransformException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Qshurick\\Jq", "UnableTransformException", class_Qshurick_Jq_UnableTransformException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;

	return class_entry;
}
