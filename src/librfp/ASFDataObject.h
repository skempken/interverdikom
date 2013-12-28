#ifndef ASFDATAOBJECT_H_
#define ASFDATAOBJECT_H_

#include "ASFObject.h"

#include <list>

/// Main data object of the ASF file
/**
 * This class wraps the data contained in the main data object of an ASF file.
 * There should be only one of these objects per file, which contains all data packet objects, which
 * in turn contain the payloads.
 */
class ASFDataObject : public ASFObject
{
public:
	/// Constructor to initialize guid and size fields
	/*
	 * Should only be called from ASFObject::constructFromFile() 
	 */
	ASFDataObject(const GUID guid, const QWORD size);
	
	/// Destructor
	virtual ~ASFDataObject();
	
	/// Get list of contained payload objects
	/**
	 * Constructs a list of all the payload objects contained in the packet objects of this data object.
	 * \return The list of payload objects
	 */ 
	std::list<class ASFPayload*>* getPayloads();
	
protected:
	virtual void getDataFromFile(std::ifstream &file);
	
private:
	/// Number of packet objects in this data object
	unsigned long long int dataPacketCount;
	
	/// List of the contained packet objects
	std::list<class ASFPacket*> dataPackets;
};

#endif /*ASFDATAOBJECT_H_*/
