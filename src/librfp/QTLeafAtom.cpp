#include "QTLeafAtom.h"

#include <fstream>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

QTLeafAtom::QTLeafAtom(unsigned int size, std::string& name, int filePos, std::istream& file)
	: QTAtom(size,name,filePos)
{
	// DEBUG REMOVEME
	// cout << filePos << "::LEAF::" << name << " - " << size << endl;

	// Calculate size of data and read it in
	dataSize = size - 8;
	data = malloc(dataSize);
	file.seekg(filePos);
	file.read((char*)data,dataSize);
}

QTLeafAtom::~QTLeafAtom()
{
	free(data);
}
