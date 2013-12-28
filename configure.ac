AC_INIT(interverdikom,version-0.1)

DEFAULT_CXSC_LOC=/opt/cxsc-2.2
DEFAULT_QWT_LOC=/usr/local/qwt

AC_PATH_PROGS(qmake_loc,[qmake-qt4 qmake],[false])

if test $qmake_loc == "false"
then
	AC_MSG_ERROR(QMake could not be found!)
fi

echo -n "Please specify location of libcxsc: [[$DEFAULT_CXSC_LOC]] "

read usrinput <&AS_ORIGINAL_STDIN_FD
libcxsc_loc=${usrinput:-$DEFAULT_CXSC_LOC}
AC_SUBST(libcxsc_loc)

if ! `test  -d $libcxsc_loc`
then
	AC_MSG_ERROR([Directory $libcxsc_loc does not exist.])
fi

AC_CHECK_PROG(have_ccache,ccache,yes,no)
if test "$have_ccache" == 'no' ; then
	cpp_call="g++"
else
	cpp_call="ccache g++"
fi

AC_SUBST(cpp_call)

AC_CONFIG_FILES(qmake-config.pro)
AC_CONFIG_FILES([build],[chmod u+x build])
AC_OUTPUT
