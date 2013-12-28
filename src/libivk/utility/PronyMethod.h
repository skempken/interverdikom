#ifndef PRONYMETHOD_H_
#define PRONYMETHOD_H_

#include<rvector.hpp>
#include<imatrix.hpp>
#include<cvector.hpp>

#include "solvers/ILinSys.hpp"
#include "roots/RootFinder.h"
#include "RealUtils.h"
#include "RMatrixUtils.h"
#include "data/SSMProcess.h"
#include "Determinant.h"

using std::cout;
using std::endl;

using cxsc::imatrix;
using cxsc::rvector;
using cxsc::ivector;
using cxsc::interval;

using ivk::RealUtils;

namespace ivk{
	class PronyMethod{
		public:
			PronyMethod(SSMProcess* smp);
			~PronyMethod();
			
			void setN(int n);
			int getN();
			
			interval compute();
			interval computeAutocorrelation(int x);
			
		private:
			//autocorrelation with (Ub-Lb+1)/2 states
			rvector* a;
			//number of states calculated by the dimension of a
			int states;
			//err from ILinSolve
			int err;
			//result of rootfinding
			rvector* mu;
			//MyMatrix for solvin 2nd system of equations
			imatrix* imat;
			//coefficient to calculate autocorrelations
			ivector* coeff;
			//SMProcess that provides the class with all necessary values
			SMProcess* smp_;
			//integer that is used as parameter for computeAutocorrelation method
			int n;
		
			void verifyResult();
			void setMuMatrix();
			
	};
}

#endif // PRONYMETHOD_H_
