# Granule configure.ac

# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.67])
AC_INIT([gofu], [0.0], [kiwitargetgranule@gmail.com])
AC_CONFIG_SRCDIR([src/gofu.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
PKG_CHECK_MODULES(PANGOCAIRO, pangocairo >= 1.24.5)

# Checks for header files.
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt])

AM_INIT_AUTOMAKE([-Wall -Werror 1.10.2])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
