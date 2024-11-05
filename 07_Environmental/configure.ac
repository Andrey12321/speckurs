#                                               -*- Autoconf -*-
# Используйте этот файл с autoconf для создания скрипта configure.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0], [support@example.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Проверки программ.
AC_PROG_CC

# Проверки библиотек.
PKG_CHECK_MODULES([RHASH], [librhash >= 1.3.0],, [AC_MSG_ERROR([Требуется библиотека librhash.])])

AC_ARG_ENABLE([readline],
  [AS_HELP_STRING([--enable-readline], [включить поддержку readline (по умолчанию: да)])],
  [], [enable_readline=yes])

USE_READLINE=no
AM_CONDITIONAL([USE_READLINE], [test "x$enable_readline" = "xyes"])
if test "x$enable_readline" = "xyes"; then
  PKG_CHECK_MODULES([READLINE], [readline], [
    USE_READLINE=yes
    AC_DEFINE([HAVE_READLINE], [1], [Определите, если используется readline])],
    [AC_MSG_NOTICE([readline не найден, продолжаем без него])])
fi

# Проверки заголовочных файлов.

# Проверки typedefs, структур и характеристик компилятора.
AC_TYPE_SIZE_T

# Проверки функций библиотеки.
AC_CHECK_FUNCS([strcasecmp strcspn])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
