AC_PREREQ(2.60)
AC_INIT([paxos],
        [1.0],
        [julien.clement@epita.fr],
        [paxos])

AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([
                  foreign
                  -Wall
                  -Werror
                  silent-rules
                  subdir-objects
])


PKG_CHECK_MODULES([CRITERION], [criterion],
[HAVE_CRITERION=1], [HAVE_CRITERION=0])
AM_CONDITIONAL([USING_CRITERION], [test $HAVE_CRITERION -eq 1])

AM_PROG_AR
AX_CXX_COMPILE_STDCXX_17([noext], [mandatory])

AX_CHECK_COMPILE_FLAG([-pedantic],
                      [AM_CXXFLAGS="$AM_CXXFLAGS -pedantic"])

AX_COMPILER_FLAGS

LT_INIT([
         disable-shared
         pic-only
 ])

AX_BOOST_BASE

AM_SILENT_RULES([yes])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
