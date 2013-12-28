#ifndef MMCMODELER_H_
#define MMCMODELER_H_

#include "AbstractDiscreteSSMPModeler.h"

namespace ivk
{

class MMCModeler : public AbstractDiscreteSSMPModeler
{
public:			
	static const char* PARAM_W;
	static const char* PARAM_MA;
	static const char* PARAM_MS;
	
	MMCModeler(const Trace * ptrData, const ComputationParameters &parameters);
	virtual ~MMCModeler();
	
	void setXi(const Trace * ptrData);
	rvector getXi() const;
	
	void setW(const int value);
	int getW() const;
	
	void setNumMS(const int value);
	int setNumMS() const;
	
	void setNumMA(const int value);
	int setNumMA() const;
	
	void setParameters(const ComputationParameters &parameters);
	
	ComputationParameters getParameters();
	
	virtual SSMProcess* compute();
		
private:
	int w;
	int mA;
	int mS;
	
	rvector xi;
	rvector xi_;
	intvector mSi;
	intvector mAi;
	
	void calcXi_();
	void calcStateSpace();
	SSMProcess* calcGlobalTransitionMatrix();
};

}

#endif /*MMCMODELER_H_*/
