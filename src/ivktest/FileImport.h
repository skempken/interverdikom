#ifndef FILEIMPORT_H_
#define FILEIMPORT_H_

// C Standard Library
#include <iostream>
#include <fstream>

// C-XSC
#include <real.hpp>
#include <rvector.hpp>

using cxsc::real;
using cxsc::rvector;

class FileImport
{
public:
	static rvector loadData(const char* filename);
	static rvector frame2gop(rvector data, const int gopsize);
	static rvector importGops(const char* filename, const int goplength);
};

#endif /*FILEIMPORT_H_*/
