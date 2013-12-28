TEMPLATE = lib
CONFIG = staticlib 
CONFIG += debug

INCLUDEPATH += $$CXSC_LOC/include
LIBS = -L$$CXSC_LOC/lib \
	-L../../lib \
	-lcxsc \
	-llapack \
	-lgfortran \
	-lfftw3

OBJECTS_DIR = ../../tmp/libivk

DESTDIR = ../../lib
TARGET = ivk
