TEMPLATE = app
CONFIG -= qt
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
OBJECTS_DIR = ../../tmp/ivktest
LIBS += -L../../lib \
    -livk \
    -lcxsc \
    -lblas \
    -lfftw3 \
	-llapack \
	-lgfortran \
    -L$$CXSC_LOC/lib
INCLUDEPATH += ../libivk \
	../libivk/computation \
	../libivk/data \
	../libivk/exception \
	../libivk/utility \
    $$CXSC_LOC/include
POST_TARGETDEPS += ../../lib/libivk.a
DESTDIR = ../../bin
TARGET = ivktest
