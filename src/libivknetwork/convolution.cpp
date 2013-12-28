#include "convolution.h"

#include <idot.hpp>

#include <algorithm>

using cxsc::idotprecision;
using cxsc::interval;

namespace ivk
{

ivector convAdd(const ivector &a, const ivector &b)
{
	ivector ret(Lb(a)+Lb(b), Ub(a)+Ub(b));
	for(int i = Lb(ret); i<=Ub(ret); ++i)
	{
		ret[i] = 0.0;
	}
	
	for(int k=Lb(ret); k<=Ub(ret); ++k)
	{
		idotprecision _accu;
		_accu = interval(0.0);
		for(int i = std::max<int>(Lb(a), k-Ub(b)); i<=std::min<int>(Ub(a), k-Lb(b)); ++i)
			accumulate(_accu, a[i], b[k-i]);
		ret[k] = rnd(_accu);
	}
	return ret;
}

}
