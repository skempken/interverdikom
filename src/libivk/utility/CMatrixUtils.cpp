#include "CMatrixUtils.h"

namespace ivk {

cmatrix CMatrixUtils::invert(const cmatrix & matrix) {
	return mid(CIMatrixUtils::invert(cimatrix(matrix)));
}

}
