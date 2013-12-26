#ifndef MATLABEXPORT_H_
#define MATLABEXPORT_H_

#include <string>
#include <iostream>
#include <sstream>

#include <real.hpp>
#include <interval.hpp>
#include <complex.hpp>
#include <cinterval.hpp>

#include <rmatrix.hpp>
#include <imatrix.hpp>
#include <cmatrix.hpp>
#include <cimatrix.hpp>

#include "utility/MatrixPolynomial.hpp"

namespace ivk {

class MatlabExport {
public:
	static std::string toString(const cxsc::real &u);
	static std::string toString(const cxsc::interval &u);
	static std::string toString(const cxsc::complex &u);
	static std::string toString(const cxsc::cinterval &u);
	
	static std::string toString(const cxsc::rmatrix &u);
	static std::string toString(const cxsc::imatrix &u);
	static std::string toString(const cxsc::cmatrix &u);
	static std::string toString(const cxsc::cimatrix &u);
	
	template<class M, class V, class P>
	static std::string toString(const MatrixPolynomial<M,V,P> & value) {
		int offset = 0;
		std::stringstream s;
		for (int i = value.lowerBound(); i <= value.upperBound(); i++) {
			s << "P" << offset++ << " = " << toString(value.at(i)) << endl;
		}
		return s.str();
	}
};

}

#endif /*MATLABEXPORT_H_*/
