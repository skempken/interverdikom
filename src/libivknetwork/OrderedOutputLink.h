#ifndef ORDEREDOUTPUTLINK_H_
#define ORDEREDOUTPUTLINK_H_

#include "BaseOutputLink.h"

namespace ivk
{

class OrderedOutputLink : public BaseOutputLink
{
public:
	OrderedOutputLink(const int bufferSize, const ivector &capacity);
	virtual ~OrderedOutputLink();
	
	virtual void tick();
};

}

#endif /*ORDEREDOUTPUTLINK_H_*/
