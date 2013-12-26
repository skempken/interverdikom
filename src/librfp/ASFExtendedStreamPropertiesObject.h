#ifndef ASFEXTENDEDSTREAMPROPERTIESOBJECT_H_
#define ASFEXTENDEDSTREAMPROPERTIESOBJECT_H_

#include "ASFObject.h"

/// Header object containing advanced stream property information
class ASFExtendedStreamPropertiesObject : public ASFObject
{
public:
	ASFExtendedStreamPropertiesObject(const GUID guid, const QWORD size);
	virtual ~ASFExtendedStreamPropertiesObject();
	
protected:
	virtual void getDataFromFile(std::ifstream &file);
	
private:
	unsigned short int streamNumber;
	unsigned short int streamNameCount;
	unsigned short int payloadExtensionCount; 
};

#endif /*ASFEXTENDEDSTREAMPROPERTIESOBJECT_H_*/
