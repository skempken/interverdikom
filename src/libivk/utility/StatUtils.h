#ifndef STATUTILS_H_
#define STATUTILS_H_

#include "interval.hpp"
#include <stdexcept>

using namespace cxsc;

namespace ivk{
	/**\class StatUtils
	\brief StatUtils is used as utilityclass for statistic methods*/
	class StatUtils{
		public:
			/**Method to compute the confidence_interval for an unknown probability
			\param n the size of the samplerange
			\param r_n the relative frequency
			\param the number of decimal places for the quantile
			\return the confidence_interval for the value r_n*/
			static interval confidence(int n, real r_n, int quantile);
	};
}
#endif
