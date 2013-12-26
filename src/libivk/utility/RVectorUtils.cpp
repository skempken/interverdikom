#include "RVectorUtils.h"
#include <utility>
#include <algorithm>
#include "real.hpp"

namespace ivk{
	std::vector< std::pair< int , cxsc::real > > RVectorUtils::sortWithIndex(rvector &vec){
		std::vector< std::pair< int , cxsc::real > > data;
		
		for(int i = Lb( vec ) ; i <= Ub( vec ) ; i++){
			data.push_back( std::make_pair( i , vec[i] ) );
		}
		
		std::sort( data.begin() , data.end() , RVectorUtils::testPairs );
		
		
		return data;
	}
	
	bool RVectorUtils::testPairs( std::pair< int , cxsc::real > x, std::pair< int , cxsc::real > y){
		return ( x.second < y.second );
	}

	bool RVectorUtils::test2LayerPairs(pair<pair<int,int>,real> a , pair<pair<int,int>,real> b){
		return (a.second < b.second);
	}
}
