#ifndef MMC_H_
#define MMC_H_

#include <math.h>
#include <rmatrix.hpp>
#include <vector>

#include <Computation.h>

#include "basicio.hpp"
#include "data/Trace.h"
#include "frames.hpp"
#include "ssmp.hpp"
#include "mathe.hpp"

using cxsc::rvector;
using cxsc::_double;
using std::vector;
using ivk::Trace;

namespace IvkModeling{
	class MMC : public ivk::Computation{
		public:
			MMC(rvector data);
			MMC(vector<double> data);
			MMC(const char* filename,int gopSize);
			~MMC();
			
			void setW(int w);
			void setMA(int mA);
			void setMS(int mS);
			
			int getW();
			int getMA();
			int getMS();
			
			rvector getXi();
			rvector getXi_();
			
			virtual void compute();
			
		private:
			rvector* xi;
			rvector* xi_;
			rvector* mSi;
			rvector* mAi;
			rmatrix* transMat;
			int w;
			int mA;
			int mS;
			
			void calcXi_();
			void calcStateSpace();
			void calcTransitionMatrix();
	};
}
#endif
