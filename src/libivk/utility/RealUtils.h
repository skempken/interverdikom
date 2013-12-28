#ifndef REALUTILS_H_
#define REALUTILS_H_

#include<real.hpp>
#include<rvector.hpp>
#include<math.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<sstream>
#include<vector>

using cxsc::real;
using cxsc::rvector;
using namespace std;

namespace ivk{
	class RealUtils{
		public:
		static cxsc::real machEps;
		static cxsc::real rPow(cxsc::real base, int exp);
		static cxsc::real meth(rvector autocSequence, rvector autocModel,cxsc::real beta);
		static cxsc::real getMachEps();
	};
}

#endif // REALUTILS_H_
