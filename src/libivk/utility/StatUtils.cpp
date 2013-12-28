#include "StatUtils.h"

namespace ivk{
	interval StatUtils::confidence(int n, real r_n, int quantile){
		interval ret(0,0);
		real 	x = n * r_n * (1 - r_n);
		if(x >= 9){
			real c = 0.0;
			switch(quantile){
				case 1:
					c = 1.282;
				break;
				
				case 2:
					c = 2.326;
				break;
				
				case 3:
					c = 3.090;
				break;
				
				case 4:
					c = 3.719;
				break;
				
				case 5:
					c = 4.265;
				break;
				
				case 6:
					c = 4.753;
				break;
				
				/* Quantil für 0.95
				case 7:
					c = 1.645;
				break;
				*/
			}
			
			real b = c * sqrt( (r_n * ( 1 - r_n )) / n);
			ret = interval( r_n-b , r_n+b );
		}
		else{
			throw std::runtime_error("samplerange to small (N < 9)");
		}
		return ret;
	}
}
