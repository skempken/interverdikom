TEMPLATE = app
QT += xml
OBJECTS_DIR = ../../tmp/gui
MOC_DIR = ../../tmp/gui
UI_DIR = ./ui_base
LIBS += -L../../lib \
    -lrfp \
    -livk \
    -lqwt-qt4 \
    -lcxsc \
    -lblas \
    -L$$CXSC_LOC/lib \
	-llapack \
	-lgfortran \
    -lfftw3
INCLUDEPATH += ../librfp \
    ../libivk \
    $$CXSC_LOC/include
POST_TARGETDEPS += ../../lib/libivk.a \
    ../../lib/librfp.a
DESTDIR = ../../bin
TARGET = ivkapp
CONFIG -= rtti
