#ifndef ASFHEADEROBJECT_H_
#define ASFHEADEROBJECT_H_

#include "ASFObject.h"

#include <list>

/// Main header object of the ASF file
/**
 * This class wraps the data contained in the main header object of an ASF file.
 * There should be only one of these objects per file, which contains all header objects.
 */
class ASFHeaderObject : public ASFObject
{
public:
	/// Constructor to initialize guid and size fields
	/*
	 * Should only be called from ASFObject::constructFromFile() 
	 */
	ASFHeaderObject(const GUID guid, const QWORD size);
	
	
	/// Destructor
	virtual ~ASFHeaderObject();
	
	/// Getter for amout of header objects
	unsigned int getHeaderObjectCount()
		{ return this->headerObjectCount; }
		
	/// Getter for header object list
	std::list<ASFObject*> getHeaderObjects()
		{ return this->headerObjects; }
	
	/// Get stream number of the video stream
	unsigned int getVideoStreamNo();
	
	/// Get stream number of the audio stream 
	unsigned int getAudioStreamNo();
	
private:
	/// Method to initialize object data from file stream
	virtual void getDataFromFile(std::ifstream &file);
	
	/// Get stream number for specific content type
	/*
	 * Iterates over stream property objects and gets the number of the stream
	 * with the given stream type GUID
	 * \param guid Stream type GUID
	 */
	unsigned int getStreamNoByGUID(const GUID guid);

	/// Number of header objects within this object
	unsigned int headerObjectCount;
	
	/// List of header objects
	std::list<ASFObject*> headerObjects;
};

#endif /*ASFHEADEROBJECT_H_*/
