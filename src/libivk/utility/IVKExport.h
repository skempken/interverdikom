#ifndef IVKEXPORT_H_
#define IVKEXPORT_H_

#include "data/SSMProcess.h"
#include "data/GIProcess.h"

namespace ivk
{

class IVKExport
{
private:
	IVKExport();
	virtual ~IVKExport();

public:
	static void writeToIVKFile(const char* filename, const SSMProcess &arrival, const GIProcess &service);
	static void intervalPolynomialMatrixExport(const char* filename, const SSMProcess &model);
};

}

#endif /*IVKEXPORT_H_*/
