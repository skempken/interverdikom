/*
 * CVectorUtils.h
 *
 *  Created on: 28.08.2008
 *      Author: kempken
 */

#ifndef CPOLYNOMIALUTILS_H_
#define CVPOLYNOMIALUTILS_H_

#include <cvector.hpp>
#include <cmatrix.hpp>

using cxsc::cvector;
using cxsc::cmatrix;
using cxsc::complex;

namespace ivk {

class CPolynomialUtils {
private:
	CPolynomialUtils();
	virtual ~CPolynomialUtils();

public:
	static cvector roots(const cvector &polynomial);
};

}

#endif /* CPOLYNOMIALUTILS_H_ */
