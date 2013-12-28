#include "ASFPacket.h"

#include "ASFFilePropertiesObject.h"
#include "ASFPayload.h"
#include "EndianConverter.h"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

ASFPacket::ASFPacket(std::ifstream& file)
{
	// Safety measure, is the file in good condition?
	if (!file.good())
	{
		cout << "CRITICAL: !file.good(), exiting." << endl;
		exit(EXIT_FAILURE);
	}

	// Local variables
	char buf, lentype_flags, prop_flags;

	#ifdef DEBUG
		std::cout << file.tellg() << "::ASFPacket - ";
	#endif

	ifstream::pos_type start_pos = file.tellg();

	//--- Error Correction Data (optional) ---
	//
	file.read(&buf,1); // Get one byte to inspect it

	if ((buf & 0x80) == 0x80) // Is there error correction data?
	{
		unsigned int errcorr_size = (buf & 0x0F); // Get size of error correction data chunk

		#ifdef DEBUG
			cout << "ErrCorr present: " << errcorr_size << " ";
		#endif

		file.ignore(errcorr_size); // Skip over data
		file.read(&lentype_flags,1); // Get next byte as Length Type flags
	}
	else // No error correction here
	{
		#ifdef DEBUG
			cout << "No ErrorCorr Data! ";
		#endif

		lentype_flags = buf; // Already got next byte, so use that as Length Type flags
	}

	// --- Payload Parsing Information ---
	//
	file.read(&prop_flags,1); // Property Flags field

	// Get "Has Multiple Payloads" information corresponding to LSB of property flags
	bool has_multiple_payloads = ((lentype_flags & 0x01) == 0x01);
	#ifdef DEBUG
		cout << "Multiple payloads " << has_multiple_payloads;
	#endif

	// Get packet size
	unsigned int packet_size_int = readVariableInt(file,getFlagTypeSize(lentype_flags,5));
	#ifdef DEBUG
		cout << " - Packet size " << packet_size_int << "(" << packet_size_int << ")" << endl;
	#endif

	// Skip "Sequence" field
	file.ignore(getFlagTypeSize(lentype_flags,1));

	// Get Padding Length
	unsigned int padding_length = readVariableInt(file,getFlagTypeSize(lentype_flags,3));
	#ifdef DEBUG
		cout << "Padding Length " << padding_length << endl;
	#endif

	// Ignore Send Time + Duration
	file.ignore(6);

	//--- Payload(s) ---
	//
	if (!has_multiple_payloads) // Single payload?
	{
		char stream_no;
		file.read(&stream_no,1); // Get stream number
		stream_no &= 0x7F; // Ignore highest bit

		// Get Media Object Number
		unsigned int mobj_no = readVariableInt(file,getFlagTypeSize(prop_flags,4));
		#ifdef DEBUG
			cout << " mobj_no:" << mobj_no << " ";
		#endif

		// Skip "Offset Into Media object" field
		file.ignore(getFlagTypeSize(prop_flags,2));

		// Get Replicated Data Length
		unsigned int replicated_data_length = readVariableInt(file,getFlagTypeSize(prop_flags,0)); // Replicated Data Length
		#ifdef DEBUG
			cout << "Replicated Data Length " << replicated_data_length << endl;
		#endif

		// Skip over Replicated Data
		file.ignore(replicated_data_length);

		// Correct packet size if too low or not given in header
		if (packet_size_int < ASFFilePropertiesObject::minPacketSize)
		{
			packet_size_int = ASFFilePropertiesObject::minPacketSize;
		}

		// Calculate payload size (packet size - header size - padding length)
		unsigned int payload_size = packet_size_int - (file.tellg() - start_pos) - padding_length;

		// Construct and register payload object
		payloads.push_back(new ASFPayload(stream_no,payload_size,mobj_no));

		// Advance file pointer
		file.ignore(payload_size);
		file.ignore(padding_length);
	}
	else // Multiple payloads present
	{
		#ifdef DEBUG
			cout << file.tellg();
		#endif

		// Local variables
		char stream_no;
		char payload_flags;
		unsigned short int payload_length;
		unsigned int replicated_data_length;
		unsigned int mobj_no;

		// Get payload count
		file.read(&payload_flags,1); // Read flags byte
		int payload_count = (payload_flags & 0x3F); // Extract 6 lowest bits
		#ifdef DEBUG
			cout << "::payload_count = " << payload_count << endl;
		#endif

		// We could check for the type of the size field here, but it's fixed at 2 bytes anyways
		// int payload_length_size = getFlagTypeSize(payload_flags,6);

		// Iterate through payloads
		for (int i = 0; i < payload_count; i++)
		{
			file.read(&stream_no,1); // Get stream number
			stream_no &= 0x7F; // Ignore highest bit

			// Get Media Object Number
			mobj_no = readVariableInt(file,getFlagTypeSize(prop_flags,4));
			#ifdef DEBUG
				cout << " mobj_no:" << mobj_no << " ";
			#endif

			// Ignore Offset Into Media object
			file.ignore(getFlagTypeSize(prop_flags,2));

			// Get Replicated Data Length
			replicated_data_length = readVariableInt(file,getFlagTypeSize(prop_flags,0)); // Replicated Data Length
			#ifdef DEBUG
				cout << "Replicated Data Length " << replicated_data_length << endl;
			#endif

			// Ignore Replicated Data
			file.ignore(replicated_data_length);

			// Get Payload Length NOTE complete standard conformity would require variable field size here
			file.read((char*)&payload_length,2);

			#ifdef DEBUG
				cout << file.tellg() << "::";
			#endif

			// Construct payload object and add to list
			payloads.push_back(new ASFPayload(stream_no,payload_length,mobj_no));

			// Skip over payload data
			file.ignore(payload_length);
		}
		// Skip over padding bytes
		file.ignore(padding_length);
	}
}

char ASFPacket::getFlagTypeSize(char flag, const int offset)
{
	flag >>= offset; // Shift until offset at LSB
	flag &= 0x03; // AND to extract lowest 2 bits

	// Special case: 11 equals DWORD size type
	if (flag == 0x03)
		return 4;
	else
		return flag;
}

unsigned int ASFPacket::readVariableInt(std::ifstream& file,const int byteCount)
{
	// Read into buffer
	char read_buf[byteCount];
	file.read(read_buf,byteCount);

	// Copy into integer buffer and return that
	unsigned int result_int = 0;
	memcpy(((char*)&result_int),read_buf,byteCount);

	return result_int;
}

ASFPacket::~ASFPacket()
{
	// Delete payloads
	list<ASFPayload*>::iterator it;
	for (it = payloads.begin(); it != payloads.end(); it++)
	{
		delete (*it);
	}
}
