#include "QTPlaceholderAtom.h"

#include "QTContainerAtom.h"
#include "QTLeafAtom.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;

QTPlaceholderAtom::QTPlaceholderAtom(unsigned int size, std::string& name, int filePos)
	: QTAtom(size,name,filePos)
{
	// cout << filePos << "::" << name << " - " << size << endl;
}

QTPlaceholderAtom::~QTPlaceholderAtom() {}

QTContainerAtom* QTPlaceholderAtom::makeContainerAtom(std::istream& file)
{
	return new QTContainerAtom(size,name,filePos,file);
}

QTLeafAtom* QTPlaceholderAtom::makeLeafAtom(std::istream& file)
{
	return new QTLeafAtom(size,name,filePos,file);
}
