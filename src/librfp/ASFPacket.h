#ifndef ASFPACKET_H_
#define ASFPACKET_H_

#include <fstream>
#include <list>

/// ASF data packet
/*
 * This class contains methods to construct a data packet with the corresponding metadata and payload
 * objects from a file stream.
 */
class ASFPacket
{
public:
	/// Constructor
	/**
	 * Construct the packet and its payload objects from a file stream.
	 * \param file The file stream
	 */
	ASFPacket(std::ifstream& file);

	/// Destructor
	virtual ~ASFPacket();
	
	/// Getter for payload list
	std::list<class ASFPayload*>* getPayloads() { return &this->payloads; }
	
private:
	/// Helper function
	/**
	 * Reads a lower endian integer field of variable width from a file stream and
	 * returns it as unsigned int.
	 * \param file The file stream
	 * \param byteCount Size of the data field
	 */
	unsigned int readVariableInt(std::ifstream& file,const int byteCount);
	
	/// Helper function
	/**
	 * Returns the number of bytes an ASF data field is big, as indicated by two bits
	 * from a flag byte extracted from a given offset.
	 * \param flag The flag byte
	 * \param offset The offset
	 */
	char getFlagTypeSize(char flag, const int offset);
	
	/// List of payloads contained in this data packet
	std::list<class ASFPayload*> payloads;
};

#endif /*ASFPACKET_H_*/
