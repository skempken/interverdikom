#include "data/GIProcess.h"
#include "utility/RMatrixUtils.h"
#include "utility/IMatrixUtils.h"

namespace ivk
{

GIProcess::GIProcess(const rvector &_distribution)
: SSMProcess(RMatrixUtils::zeros(1,1,1,1), RMatrixUtils::zeros(1,1,0,0), false)
{
	// Construct transition matrix.
	rmatrix _trans(1,1,1,1);
	_trans[1][1] = 1.0;
	
	setTransitionMatrix(_trans);
	setDistribution(_distribution);
}

GIProcess::GIProcess(const ivector &_distribution)
: SSMProcess(IMatrixUtils::zeros(1,1,1,1), IMatrixUtils::zeros(1,1,0,0), false)
{
	// Construct transition matrix.
	imatrix _trans(1,1,1,1);
	_trans[1][1] = interval(1.0,1.0);
	
	setTransitionMatrix(_trans);
	setDistribution(_distribution);
}

GIProcess::~GIProcess()
{
}

void GIProcess::setDistribution(const rvector &_distribution)
{
	// Construct distribution matrix.
	rmatrix _dist(1,1,Lb(_distribution), Ub(_distribution));
	_dist[1] = _distribution;
	setDistributions(_dist);
}

void GIProcess::setDistribution(const ivector &_distribution)
{
	// Construct distribution matrix.
	imatrix _dist(1,1,Lb(_distribution), Ub(_distribution));
	_dist[1] = _distribution;
	setDistributions(_dist);
}

ivector GIProcess::getDistribution() const
{
	imatrix dists = this->getDistributions();
	ivector ret = dists[Lb(dists,1)];
	return ret;
}

GIProcess operator-(const GIProcess &A, const GIProcess &B)
{
	return GIProcess(SSMProcess::subDists(A.getDistribution(), B.getDistribution()));
}

GIProcess operator+(const GIProcess &A, const GIProcess &B)
{
	return GIProcess(SSMProcess::addDists(A.getDistribution(), B.getDistribution()));
}

}
