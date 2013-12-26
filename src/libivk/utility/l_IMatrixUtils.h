#ifndef L_IMATRIXUTILS_H_
#define L_IMATRIXUTILS_H_

#include "MatrixUtils.hpp"

#include <l_imatrix.hpp>
#include <l_ivector.hpp>
#include <l_interval.hpp>
#include <l_real.hpp>

using cxsc::l_imatrix;
using cxsc::l_ivector;
using cxsc::l_interval;
using cxsc::l_real;

namespace ivk
{

class l_IMatrixUtils : public MatrixUtils<l_imatrix, l_ivector, l_interval>
{
public:
	static l_imatrix zeros(const int lb1, const int ub1, const int lb2, const int ub2);
	static l_imatrix identity(const int lb, const int ub);
	static l_real maxDiam(const l_imatrix &matrix);
	static l_imatrix invert(const l_imatrix &matrix);
};

}

#endif /*L_IMATRIXUTILS_H_*/
