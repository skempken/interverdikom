#include "l_IMatrixUtils.h"

#include <stdexcept>

#include "Logging.hpp"

namespace ivk
{

l_imatrix l_IMatrixUtils::zeros(const int lb1, const int ub1, const int lb2, const int ub2)
{
	l_imatrix B(lb1, ub1, lb2, ub2);

	for(int r = Lb(B,1); r<=Ub(B,1); ++r)
	{
		for(int c = Lb(B,2); c <=Ub(B,2); ++c)
		{
			B[r][c] = l_interval(0.0,0.0);
		}
	}
	return B;
}

l_imatrix l_IMatrixUtils::identity(const int lb, const int ub)
{
	l_imatrix ret = zeros(lb,ub,lb,ub);
	for(int i = lb; i<=ub; ++i)
		ret[i][i] = l_interval(1.0,1.0);
	return ret;
}

l_real l_IMatrixUtils::maxDiam(const l_imatrix &a)
{
	l_real diam(0.0);
	for(int i = Lb(a,1); i<=Ub(a,1); ++i)
		for(int j = Lb(a,2); j<=Ub(a,2); ++j)
			diam = std::max<l_real>(diam, Sup(a[i][j]) - Inf(a[i][j]));
	return diam;
}

l_imatrix l_IMatrixUtils::invert(const l_imatrix &matrix)
{
	if(!((Lb(matrix,1) == Lb(matrix,2)) && (Ub(matrix,1) == Ub(matrix,2))))
		throw new std::invalid_argument("Matrix bounds do not match.");

	const int size = Ub(matrix,1) - Lb(matrix,1)+1;
	l_imatrix ret(Lb(matrix,1), Ub(matrix,1), Lb(matrix,2), Ub(matrix,2));
	l_interval det;

	switch(size)
	{
	case 1:
		ret[Lb(matrix,1)][Lb(matrix,2)] = l_interval(1.0,1.0) / matrix[Lb(matrix,1)][Lb(matrix,2)];
		break;
	case 2:
        det = matrix[Lb(matrix,1)][Lb(matrix,2)] * matrix[Ub(matrix,1)][Ub(matrix,2)]
              - matrix[Lb(matrix,1)][Ub(matrix,2)] * matrix[Ub(matrix,1)][Lb(matrix,2)];
        ret[Lb(matrix,1)][Lb(matrix,2)] = matrix[Ub(matrix,1)][Ub(matrix,2)] / det;
        ret[Lb(matrix,1)][Ub(matrix,2)] = - matrix[Lb(matrix,1)][Ub(matrix,2)] / det;
        ret[Ub(matrix,1)][Lb(matrix,2)] = - matrix[Ub(matrix,1)][Lb(matrix,2)] / det;
        ret[Ub(matrix,1)][Ub(matrix,1)] = matrix[Lb(matrix,1)][Lb(matrix,2)] / det;
        break;
	case 3:
		det = matrix[Lb(matrix,1)][Lb(matrix,2)]*matrix[Lb(matrix,1)+1][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+2]
		    + matrix[Lb(matrix,1)][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+1][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+2][Lb(matrix,2)]
		    + matrix[Lb(matrix,1)][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+1][Lb(matrix,2)]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+1]
		    - matrix[Lb(matrix,1)][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+1][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+2][Lb(matrix,2)]
		    - matrix[Lb(matrix,1)][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+1][Lb(matrix,2)]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+2]
		    - matrix[Lb(matrix,1)][Lb(matrix,2)]*matrix[Lb(matrix,1)+1][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+1];

		ret[Lb(matrix,1)][Lb(matrix,2)] = (matrix[Lb(matrix,1)+1][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+2] - matrix[Lb(matrix,1)+1][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+1])/det;
		ret[Lb(matrix,1)][Lb(matrix,2)+1] = (matrix[Lb(matrix,1)][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+1] - matrix[Lb(matrix,1)][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+2])/det;
		ret[Lb(matrix,1)][Lb(matrix,2)+2] = (matrix[Lb(matrix,1)][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+1][Lb(matrix,2)+2] - matrix[Lb(matrix,1)][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+1][Lb(matrix,2)+1])/det;

		ret[Lb(matrix,1)+1][Lb(matrix,2)] = (matrix[Lb(matrix,1)+1][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+2][Lb(matrix,2)] - matrix[Lb(matrix,1)+1][Lb(matrix,2)]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+2])/det;
		ret[Lb(matrix,1)+1][Lb(matrix,2)+1] = (matrix[Lb(matrix,1)][Lb(matrix,2)]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+2] - matrix[Lb(matrix,1)][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+2][Lb(matrix,2)])/det;
		ret[Lb(matrix,1)+1][Lb(matrix,2)+2] = (matrix[Lb(matrix,1)][Lb(matrix,2)+2]*matrix[Lb(matrix,1)+1][Lb(matrix,2)] - matrix[Lb(matrix,1)][Lb(matrix,2)]*matrix[Lb(matrix,1)+1][Lb(matrix,2)+2])/det;

		ret[Lb(matrix,1)+2][Lb(matrix,2)] = (matrix[Lb(matrix,1)+1][Lb(matrix,2)]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+1] - matrix[Lb(matrix,1)+1][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+2][Lb(matrix,2)])/det;
		ret[Lb(matrix,1)+2][Lb(matrix,2)+1] = (matrix[Lb(matrix,1)][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+2][Lb(matrix,2)] - matrix[Lb(matrix,1)][Lb(matrix,2)]*matrix[Lb(matrix,1)+2][Lb(matrix,2)+1])/det;
		ret[Lb(matrix,1)+2][Lb(matrix,2)+2] = (matrix[Lb(matrix,1)][Lb(matrix,2)]*matrix[Lb(matrix,1)+1][Lb(matrix,2)+1] - matrix[Lb(matrix,1)][Lb(matrix,2)+1]*matrix[Lb(matrix,1)+1][Lb(matrix,2)])/det;
		break;
		// ...
	default:
	    // TODO: Some nice inversion algorithm here

		throw new std::logic_error("Not yet implemented.");
		break;
	}
	return ret;
}

}
