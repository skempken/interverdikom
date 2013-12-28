#ifndef SCENEPARTITIONER_H_
#define SCENEPARTITIONER_H_

#include "AbstractComputation.hpp"
#include "data/Trace.h"
#include <vector>
#include "intvector.hpp"

using namespace std;
using namespace cxsc;

namespace ivk
{

class ScenePartitioner : public AbstractComputation<Trace, vector<Trace> >
{
public:
	static const char* PARAM_EPSILON;
	
	ScenePartitioner(const Trace* data, const ComputationParameters &parameters);
	virtual ~ScenePartitioner();
	
	virtual void setEpsilon(const real value);
	virtual real getEpsilon() const;
	
	virtual void setParameters(const ComputationParameters &parameters);
	
	virtual vector<Trace>* compute();
		
private:
	
	real m_epsilon;
};

}

#endif /*SCENEPARTITIONER_H_*/
