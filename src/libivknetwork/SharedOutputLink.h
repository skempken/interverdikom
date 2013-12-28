#ifndef SHAREDOUTPUTLINK_H_
#define SHAREDOUTPUTLINK_H_

#include "BaseOutputLink.h"

namespace ivk
{

class SharedOutputLink : public BaseOutputLink
{
public:
	SharedOutputLink(const int bufferSize, const ivector &capacity);
	virtual ~SharedOutputLink();
	
	virtual void tick();
};

}

#endif /*SHAREDOUTPUTLINK_H_*/
