#ifndef RVECTORUTILS_H_
#define RVECTORUTILS_H_

#include "rvector.hpp"
#include <vector>

using cxsc::rvector;
using cxsc::real;
using std::pair;
using std::vector;

namespace ivk{
	class RVectorUtils{
	public:
		static std::vector< std::pair< int , cxsc::real > > sortWithIndex(rvector &vec);
		static bool testPairs( std::pair< int , cxsc::real > x , std::pair< int , cxsc::real > y );
		static bool test2LayerPairs( pair<pair<int,int>,real> a , pair<pair<int,int>,real> b);
		
	};
}

#endif /*RVECTORUTILS_H_*/
