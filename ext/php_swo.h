/* swo extension for PHP */

#ifndef PHP_SWO_H
#define PHP_SWO_H

extern zend_module_entry swo_module_entry;
#define phpext_swo_ptr &swo_module_entry

#define PHP_SWO_VERSION "0.1.0"

#if defined(ZTS) && defined(COMPILE_DL_SWO)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif /* PHP_SWO_H */
