#ifndef ASFSTREAMPROPERTIESOBJECT_H_
#define ASFSTREAMPROPERTIESOBJECT_H_

#include "ASFObject.h"

/// A stream properties header object
/*
 * Wraps data extracted from a stream properties header object. These are contained within the root header
 * object. There should be one for each stream per file.
 */
class ASFStreamPropertiesObject : public ASFObject
{
public:
	/// Constructor to initialize guid and size fields
	/*
	 * Should only be called from ASFObject::constructFromFile() 
	 */
	ASFStreamPropertiesObject(const GUID guid, const QWORD size);
	
	/// Destructor
	virtual ~ASFStreamPropertiesObject();
	
	/// Extracts the stream number from the stream flags
	unsigned int getStreamNumber();
	
	/// Simple inline getter for stream type GUID
	GUID* getStreamType() { return &this->streamType; }
	
	/// Checks stream type against video stream type constant
	bool isVideoStream();
	
	/// Checks stream type against audio stream type constant
	bool isAudioStream();
	
	/// GUID constant for audio stream type
	static char ASF_Audio_Media[16];
	
	/// GUID constant for video stream type
	static char ASF_Video_Media[16];
	
protected:
	/// Method to initialize object data from file stream
	virtual void getDataFromFile(std::ifstream &file);
	
	/// The GUID indicating the stream type
	GUID streamType;
	
	/// Stream flags as found inside the ASF file
	char flags[2];
};

#endif /*ASFSTREAMPROPERTIESOBJECT_H_*/
