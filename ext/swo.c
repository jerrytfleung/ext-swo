/* swo extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_swo.h"
// #include "setting_service_c_wrapper.h"
#include "swo_arginfo.h"
#ifndef _WIN32
#include <pthread.h>
#endif
#include <time.h>

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()                                           \
  ZEND_PARSE_PARAMETERS_START(0, 0)                                            \
  ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_DECLARE_MODULE_GLOBALS(swo)

PHP_INI_BEGIN()
STD_PHP_INI_ENTRY("swo.collector", "apm.collector.na-01.cloud.solarwinds.com",
                  PHP_INI_ALL, OnUpdateString, collector, zend_swo_globals,
                  swo_globals)
STD_PHP_INI_ENTRY("swo.service_key", "", PHP_INI_ALL, OnUpdateString,
                  service_key, zend_swo_globals, swo_globals)
PHP_INI_END()

/* {{{ void Solarwinds\\Sampler\\setting() */
PHP_FUNCTION(Solarwinds_Sampler_setting) {
  ZEND_PARSE_PARAMETERS_NONE();
  char setting[1024] = {0};
  // Setting_Service_Get_Setting(SWO_G(setting_service), setting);
  RETURN_STRING(setting);
}
/* }}} */

#ifndef _WIN32
void prefork() {
  // Setting_Service_Free(SWO_G(setting_service));
}

void postfork() {
  // SWO_G(setting_service) = Setting_Service_Allocate(SWO_G(collector), SWO_G(service_key));
}
#endif

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(swo) {
#if defined(ZTS) && defined(COMPILE_DL_SWO)
  ZEND_TSRMLS_CACHE_UPDATE();
#endif
  REGISTER_INI_ENTRIES();

  // SWO_G(setting_service) = Setting_Service_Allocate(SWO_G(collector), SWO_G(service_key));

#ifndef _WIN32
  pthread_atfork(prefork, postfork, postfork);
#endif

  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(swo) {
  // Setting_Service_Free(SWO_G(setting_service));

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
PHP_GINIT_FUNCTION(swo) { ZEND_SECURE_ZERO(swo_globals, sizeof(*swo_globals)); }
/* }}} */

/* {{{ swo_module_entry */
zend_module_entry swo_module_entry = {
    STANDARD_MODULE_HEADER,
    "swo",              /* Extension name */
    ext_functions,      /* zend_function_entry */
    PHP_MINIT(swo),     /* PHP_MINIT - Module initialization */
    PHP_MSHUTDOWN(swo), /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(swo),     /* PHP_RINIT - Request initialization */
    NULL,               /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(swo),     /* PHP_MINFO - Module info */
    PHP_SWO_VERSION,    /* Version */
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
