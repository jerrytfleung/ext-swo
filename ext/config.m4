dnl config.m4 for extension swo

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([swo],
dnl   [for swo support],
dnl   [AS_HELP_STRING([--with-swo],
dnl     [Include swo support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([swo],
  [whether to enable swo support],
  [AS_HELP_STRING([--enable-swo],
    [Enable swo support])],
  [no])

if test "$PHP_SWO" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, SWO_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-swo -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/swo.h"  # you most likely want to change this
  dnl if test -r $PHP_SWO/$SEARCH_FOR; then # path given as parameter
  dnl   SWO_DIR=$PHP_SWO
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for swo files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SWO_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SWO_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the swo distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-swo -> add include path
  dnl PHP_ADD_INCLUDE($SWO_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-swo -> check for lib and symbol presence
  dnl LIBNAME=SWO # you may want to change this
  dnl LIBSYMBOL=SWO # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_SWO_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your swo library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SWO_DIR/$PHP_LIBDIR, SWO_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SWO_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your swo library.])
  dnl ],[
  dnl   -L$SWO_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SWO_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_SWO, 1, [ Have swo support ])

  dnl Enable C++
  PHP_REQUIRE_CXX()

  dnl Check for libcurl dependency
  PKG_CHECK_MODULES([CURL], [libcurl >= 7.61.0])
    PKG_CHECK_VAR([CURL_FEATURES], [libcurl], [supported_features])

    PHP_EVAL_LIBLINE([$CURL_LIBS], [CURL_SHARED_LIBADD])
    PHP_EVAL_INCLINE([$CURL_CFLAGS])

    AC_MSG_CHECKING([for SSL support in libcurl])
    AS_CASE([$CURL_FEATURES], [*SSL*], [CURL_SSL=yes], [CURL_SSL=no])
    AC_MSG_RESULT([$CURL_SSL])

    AS_IF([test "x$PHP_THREAD_SAFETY" = xyes && test "x$CURL_SSL" = xyes],
      [AC_CACHE_CHECK([whether libcurl is linked against a supported OpenSSL version],
        [php_cv_lib_curl_ssl_supported], [
        save_LIBS=$LIBS
        save_CFLAGS=$CFLAGS
        LIBS="$LIBS $CURL_SHARED_LIBADD"
        CFLAGS="$CFLAGS $CURL_CFLAGS"

        AC_RUN_IFELSE([AC_LANG_PROGRAM([
  #include <stdio.h>
  #include <strings.h>
  #include <curl/curl.h>
  ], [
    curl_version_info_data *data = curl_version_info(CURLVERSION_NOW);

    if (data && data->ssl_version && *data->ssl_version) {
      const char *ptr = data->ssl_version;

      while(*ptr == ' ') ++ptr;
      int major, minor;
      if (sscanf(ptr, "OpenSSL/%d.%d", &major, &minor) == 2) {
        /* Check for 1.1.1+ (including 1.1.1a, 1.1.1b, etc.) */
        if ((major > 1) || (major == 1 && minor == 1 && strncmp(ptr + 12, "1", 1) == 0)) {
          /* OpenSSL 1.1.1+ - supported */
          return 3;
        }
        /* OpenSSL 1.1.0 and earlier - unsupported */
        return 0;
      }
      if (strncasecmp(ptr, "OpenSSL", sizeof("OpenSSL")-1) == 0) {
        /* Old OpenSSL version */
        return 0;
      }
      /* Different SSL library */
      return 2;
    }
    /* No SSL support */
    return 1;
  ])],
        [php_cv_lib_curl_ssl_supported=no],
        [php_cv_lib_curl_ssl_supported=yes],
        [php_cv_lib_curl_ssl_supported=yes])
        LIBS=$save_LIBS
        CFLAGS=$save_CFLAGS
      ])

      AS_VAR_IF([php_cv_lib_curl_ssl_supported], [no], [
        AC_MSG_ERROR([libcurl is linked against an unsupported OpenSSL version. OpenSSL 1.1.1 or later is required.])
      ])
    ])
  PHP_CHECK_LIBRARY([curl],
    [curl_easy_perform],
    [AC_DEFINE([HAVE_CURL], [1],
      [Define to 1 if the PHP extension 'curl' is available.])],
    [AC_MSG_FAILURE([The libcurl check failed.])],
    [$CURL_LIBS])

  PHP_SUBST([CURL_SHARED_LIBADD])
  PHP_NEW_EXTENSION(swo, swo.c service.cpp setting_service.cpp setting_service_c_wrapper.cpp, $ext_shared,, "-Wall -Wextra -Werror -Wno-unused-parameter",cxx)
fi
