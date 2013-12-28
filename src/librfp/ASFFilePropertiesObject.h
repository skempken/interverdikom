#ifndef ASFFILEPROPERTIESOBJECT_H_
#define ASFFILEPROPERTIESOBJECT_H_

#include "ASFObject.h"

/// ASF header object containing general information about the file
/*
 * This object contains the min and max packet size as indicated by the file header.
 */
class ASFFilePropertiesObject : public ASFObject
{
public:
	/// Constructor to initialize guid and size fields
	/*
	 * Should only be called from ASFObject::constructFromFile() 
	 */
	ASFFilePropertiesObject(const GUID guid, const QWORD size);
	
	/// Destructor
	virtual ~ASFFilePropertiesObject();
	
	/// Minimum data packet size
	static unsigned int minPacketSize;
	
	/// Maximum data packet size
	static unsigned int maxPacketSize;
	
protected:
	/// Method to initialize object data from file stream
	virtual void getDataFromFile(std::ifstream &file);
};

#endif /*ASFFILEPROPERTIESOBJECT_H_*/
