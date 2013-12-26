/*
 * DFTTest.h
 *
 *  Created on: 29.07.2008
 *      Author: kempken
 */

#ifndef DFTTEST_H_
#define DFTTEST_H_

#include <civector.hpp>
#include <l_interval.hpp>
#include <l_ivector.hpp>

using namespace cxsc;

class DFTTest {
public:
	DFTTest();
	virtual ~DFTTest();

	static civector dft0(civector a);
	static civector dft1(civector a);
	static civector dft2(civector a);
	static civector dft3(civector a);
	static void l_dft3(civector a);
	static civector idft3(civector a);


	static l_real getMaxDiam(const l_ivector &values);
	static real getMaxDiam(const civector &values);
};

#endif /* DFTTEST_H_ */
