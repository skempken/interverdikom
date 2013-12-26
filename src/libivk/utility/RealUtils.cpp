#include "RealUtils.h"

namespace ivk{
	real RealUtils::machEps = 0.0;
	
	real RealUtils::rPow(real base, int exp){
		assert( exp >= 0 );
		real ret = 1.0;
		real x = base;
		int b = 1;
		
		if(exp != 0){
			for(int i = 0; i <= 31; i++){
				if(exp & b){
					ret *= x;
				}
				x = x*x;
				b = b << 1;
			}
		}
		return ret;
	}
	
	real RealUtils::meth(rvector autocSequence, rvector autocModel,real beta){
		int m = ( Ub( autocSequence ) - Lb( autocSequence ) + 1 ) / 2;
		
		real tmp,bin;
		real result = 0.0;
		for(int n = 1; n < m; n++){
			result += autocSequence[n];
			tmp = 0.0;
			
			for(int l = 0; l <= n; l++){
				bin = 1.0;
				for(int b = 1; b <= l; b ++){
					bin *= ( n+1-b ) / b;
				}
				tmp = bin;
				tmp *= rPow( beta, n-l );
				tmp *= rPow( ( 1 - beta ), l );
				tmp *= autocModel[l];
			}
			result -= tmp;
		}
		
		return result;
	}
	
	real RealUtils::getMachEps(){
		if(RealUtils::machEps == 0.0)
		{
			double temp1 = 1.0;
			double temp2 = 0.0;
			
			do
			{
				RealUtils::machEps = temp1;
				temp1 /= 2.0;
				temp2 = 1.0 + temp1;
			}
			while (temp2 > 1.0);
			
		}
		
		return RealUtils::machEps;
	}
}
