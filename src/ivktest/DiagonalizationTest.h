#ifndef DIAGONALIZATIONTEST_H_
#define DIAGONALIZATIONTEST_H_

// C-XSC includes
#include <real.hpp>
#include <rvector.hpp>

using cxsc::real;
using cxsc::rvector;

class DiagonalizationTest
{
public:
	DiagonalizationTest();
	virtual ~DiagonalizationTest();
	
	void runTest();
	real errorFunction(rvector autoTrace, rvector autoModel, real beta);
	real binomial(const int n, const int k);
};

#endif /*DIAGONALIZATIONTEST_H_*/
