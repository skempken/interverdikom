#include "DiagonalizationTest.h"

// Standard C Library
#include <assert.h>

// libIVK includes
#include <Trace.h>
#include <SSMProcess.h>
#include <SimpleMCModeler.h>
#include <ComputationParameters.h>
#include <RealUtils.h>
#include <Logging.hpp>

using namespace ivk;

// Local includes
#include "FileImport.h"

DiagonalizationTest::DiagonalizationTest()
{
}

DiagonalizationTest::~DiagonalizationTest()
{
}

void DiagonalizationTest::runTest()
{
	// Parameters
	const char* filename = "/home/kempken/workspace/InterVerdiKom/testdata/horizon.data";
	const int goplength = 12;
	const int dSteps = 50;
	const int states = 5;
	const int N = 100;
	
	// Create SMP Model from trace
	rvector _trace = FileImport::importGops(filename,goplength);
	Trace trace(_trace);
	rvector autoTrace = trace.getAutocorrelation(N);
	
	ComputationParameters param_m;
	param_m.setInt(SimpleMCModeler::PARAM_NUMDSTEPS, dSteps);
	param_m.setInt(SimpleMCModeler::PARAM_NUMSTATES, states);
		
	SimpleMCModeler _smcm(&trace, param_m);
	SSMProcess* _model = _smcm.compute();
	
	rvector autoModel = _model->getAutocorrelation(N);
	
	// Compute error function for some Betas and print
	for(real beta = 0.0; beta <=1.0; beta += 0.1)
	{
		Logging::log(Logging::Debug, "beta", errorFunction(autoTrace, autoModel, beta));
	}
}

real DiagonalizationTest::errorFunction(rvector autoTrace, rvector autoModel, real beta)
{
	assert(Lb(autoTrace) == Lb(autoModel));
	assert(Ub(autoTrace) == Ub(autoModel));
	
	real tmp, bin;
	real result = 0.0;
	for(int n = Lb(autoTrace); n <= Ub(autoTrace); n++){
		tmp = 0.0;
		
		for(int l = 0; l <= n; l++){
			bin = 1.0;
			for(int b = 1; b <= l; b ++){
				bin *= ( n+1-b ) / b;
			}
			tmp = bin;
			tmp *= RealUtils::rPow( beta, n-l );
			tmp *= RealUtils::rPow( ( 1 - beta ), l );
			tmp *= autoModel[l];
		}
		result += (autoTrace[n] - tmp)*(autoTrace[n] - tmp);
	}
	
	return result;
}

real DiagonalizationTest::binomial(const int n, const int k)
{
	real bin = 1.0;
	for(int b = 1; b <= k; b ++){
		bin *= ( n+1-b ) / b;
	}
	return bin;
}
