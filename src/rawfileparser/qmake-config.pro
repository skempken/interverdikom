TEMPLATE = app
CONFIG -= qt
OBJECTS_DIR = ../../tmp/rawfileparser
INCLUDEPATH += ../librfp
LIBS += -L../../lib \
    -lrfp
DESTDIR = ../../bin
TARGET = rawfileparser
POST_TARGETDEPS += ../../lib/librfp.a

win32 {
	CONFIG += console
}