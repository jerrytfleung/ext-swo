/* swo extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_swo.h"
#include "swo_arginfo.h"
#include "setting_service_c_wrapper.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()                                           \
  ZEND_PARSE_PARAMETERS_START(0, 0)                                            \
  ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_DECLARE_MODULE_GLOBALS(swo)

PHP_INI_BEGIN()
STD_PHP_INI_ENTRY("swo.collector", "", PHP_INI_ALL, OnUpdateString,
                  collector, zend_swo_globals, swo_globals)
STD_PHP_INI_ENTRY("swo.service_key", "", PHP_INI_ALL, OnUpdateString,
                  service_key, zend_swo_globals, swo_globals)
PHP_INI_END()

/* {{{ void test1() */
PHP_FUNCTION(test1) {
  ZEND_PARSE_PARAMETERS_NONE();

  php_printf("The extension %s is loaded and working!\r\n", "swo");
}
/* }}} */

/* {{{ string test2( [ string $var ] ) */
PHP_FUNCTION(test2) {
  char *var = "World";
  size_t var_len = sizeof("World") - 1;
  zend_string *retval;

  ZEND_PARSE_PARAMETERS_START(0, 1)
  Z_PARAM_OPTIONAL
  Z_PARAM_STRING(var, var_len)
  ZEND_PARSE_PARAMETERS_END();

  retval = strpprintf(0, "Hello %s", var);

  RETURN_STR(retval);
}
/* }}}*/

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(swo) {
#if defined(ZTS) && defined(COMPILE_DL_SWO)
  ZEND_TSRMLS_CACHE_UPDATE();
#endif
  REGISTER_INI_ENTRIES();

  SWO_G(setting_service) = Setting_Service_Allocate();

  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(swo) {
  Setting_Service_Free(SWO_G(setting_service));

  UNREGISTER_INI_ENTRIES();

  return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(swo) {
#if defined(ZTS) && defined(COMPILE_DL_SWO)
  ZEND_TSRMLS_CACHE_UPDATE();
#endif

  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(swo) {
  php_info_print_table_start();
  php_info_print_table_header(2, "swo support", "enabled");
  php_info_print_table_end();
  DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ PHP_GINIT_FUNCTION */
PHP_GINIT_FUNCTION(swo) {
  ZEND_SECURE_ZERO(swo_globals, sizeof(*swo_globals));
}
/* }}} */

/* {{{ swo_module_entry */
zend_module_entry swo_module_entry = {
    STANDARD_MODULE_HEADER,
    "swo",           /* Extension name */
    ext_functions,   /* zend_function_entry */
    PHP_MINIT(swo),  /* PHP_MINIT - Module initialization */
    PHP_MSHUTDOWN(swo), /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(swo),  /* PHP_RINIT - Request initialization */
    NULL,            /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(swo),  /* PHP_MINFO - Module info */
    PHP_SWO_VERSION, /* Version */
    PHP_MODULE_GLOBALS(swo),
    PHP_GINIT(swo),
    NULL,
    NULL,
    STANDARD_MODULE_PROPERTIES_EX};
/* }}} */

#ifdef COMPILE_DL_SWO
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(swo)
#endif
