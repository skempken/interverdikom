#ifndef ASFPAYLOAD_H_
#define ASFPAYLOAD_H_

/// Data of a single ASF payload
/*
 * This class is used as a simple data container since there are no real object-specific methods to implement.
 */
class ASFPayload
{
public:
	/// Constructor initializing streamNumber, size and mediaObjectNumber
	ASFPayload(unsigned int streamNumber, unsigned int size, unsigned int mediaObjectNumber);
	
	/// Destructor
	virtual ~ASFPayload();
	
	/// Simple inline getter for streamNumber
	unsigned int getStreamNumber() { return this->streamNumber; }
	
	/// Simple inline  getter for size
	unsigned int getSize() { return this->size; }
	
	/// Simple inline getter for mediaObjectNumber
	unsigned int getMediaObjectNumber() { return this->mediaObjectNumber; }
	
private:
	/// The size of the data contained in this payload
	unsigned int size;
	
	/// The number of the stream this payload belongs to
	unsigned int streamNumber;
	
	/// The number of the media object this payload belongs to
	unsigned int mediaObjectNumber;
};

#endif /*ASFPAYLOAD_H_*/
