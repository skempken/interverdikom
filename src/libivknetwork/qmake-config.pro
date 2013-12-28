TEMPLATE = app
CONFIG = staticlib qt
QT = xml core

INCLUDEPATH += $$CXSC_LOC/include
LIBS = -L$$CXSC_LOC/lib \
	-L../../lib \
	-lcxsc

OBJECTS_DIR = ../../tmp/libivknetwork

DESTDIR = ../../bin
TARGET = ivknetwork
