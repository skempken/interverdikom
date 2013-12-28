#ifndef INTMATRIXUTILS_H_
#define INTMATRIXUTILS_H_

#include <intvector.hpp>
#include <intmatrix.hpp>

#include "MatrixUtils.hpp"

using cxsc::intmatrix;
using cxsc::intvector;

namespace ivk
{

class IntMatrixUtils : public MatrixUtils<intmatrix, intvector, int>
{

};

}

#endif /*INTMATRIXUTILS_H_*/
