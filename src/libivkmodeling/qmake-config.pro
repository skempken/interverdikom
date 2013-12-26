TEMPLATE = app
CONFIG += qt
QT = xml

INCLUDEPATH += $$CXSC_LOC/include \
	../libivk
LIBS = -L$$CXSC_LOC/lib \
	-L../../lib \
	-lcxsc \
	-livk

OBJECTS_DIR = ../../tmp/libivkmodeling

POST_TARGETDEPS += ../../lib/libivk.a

DESTDIR = ../../bin
TARGET = ivkmodeling
