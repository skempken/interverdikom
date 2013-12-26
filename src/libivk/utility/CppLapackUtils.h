#ifndef CPPLAPACKUTILS_H_
#define CPPLAPACKUTILS_H_

#include "cpplapack/cpplapack.h"

#include <cmatrix.hpp>
#include <iostream>

using namespace cxsc;
using namespace CPPL;
using namespace std;

namespace ivk {

class CppLapackUtils
{
public:
	static zgematrix toZgematrix(const cmatrix & originalMatrix);
	
	static cmatrix toCmatrix(const zgematrix & originalMatrix);
	
	static cmatrix solveLss(const cmatrix & A, const cmatrix & B);
};

}

#endif /*CPPLAPACKUTILS_H_*/
