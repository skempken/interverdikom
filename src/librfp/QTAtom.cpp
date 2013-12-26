#include "QTAtom.h"

QTAtom::QTAtom(unsigned int size, std::string& name, int filePos)
{
	// Init fields
	this->size = size;
	this->name = name;
	this->filePos = filePos;
}

QTAtom::~QTAtom() {}
