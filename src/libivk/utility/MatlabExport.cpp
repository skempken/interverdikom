#include "MatlabExport.h"

using namespace cxsc;

using std::string;
using std::stringstream;

namespace ivk {


string MatlabExport::toString(const real & value) {
	stringstream s;
	s << value;
	return s.str();
}

string MatlabExport::toString(const interval & value) {
	stringstream s;
	s << "infsup(" << Inf(value) << "," << Sup(value) << ")";
	return s.str();
}

string MatlabExport::toString(const complex & value) {
	stringstream s;
	s << "complex(" << Re(value) << "," << Im(value) << ")";
	return s.str();
}

string MatlabExport::toString(const cinterval & value) {
	stringstream s;
	s << "infsup(" << toString(Inf(value)) << "," << toString(Sup(value)) << ")";
	return s.str();
}

template<class T>
string matrixToString(const T & matrix) {
	stringstream s;
	s << "[";
	for (int i = Lb(matrix,1); i <= Ub(matrix,1); i++) {
		for (int j = Lb(matrix,2); j <= Ub(matrix,2); j++) {
			s << MatlabExport::toString(matrix[i][j]);
			s << " ";
		}

		s << ";";
	}

	s << "]";

	return s.str();
}

string MatlabExport::toString(const rmatrix & value) {
	return matrixToString(value);
}

string MatlabExport::toString(const imatrix & value) {
	return matrixToString(value);
}

string MatlabExport::toString(const cmatrix & value) {
	return matrixToString(value);
}

string MatlabExport::toString(const cxsc::cimatrix & value) {
	return matrixToString(value);
}


}
