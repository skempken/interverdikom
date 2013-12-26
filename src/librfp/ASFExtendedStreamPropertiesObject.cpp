#include "ASFExtendedStreamPropertiesObject.h"

#include <iostream>

// NOTE
// Currently unused - may be used in implementation for forward compatibility with
// files where the stream information is stored in the header extension objects
// then: parse stream property objects at the end of the data chunk and use them
// instead of the top level ones -Holger Pretzsch

ASFExtendedStreamPropertiesObject::ASFExtendedStreamPropertiesObject(const GUID guid, const QWORD size) :
	ASFObject(guid,size)
{
	// ASFObject constructor handles field initialization
}

ASFExtendedStreamPropertiesObject::~ASFExtendedStreamPropertiesObject()
{
}

void ASFExtendedStreamPropertiesObject::getDataFromFile(std::ifstream &file)
{
	// DEBUG REMOVEME
	std::cout << file.tellg() << "::ASF_Extended_Stream_Properties_Object - " << size << std::endl;
	
	// Backup initial file position
	std::ifstream::pos_type start_pos = file.tellg();
	
	file.ignore(72);
	file.read((char*)&streamNumber,2);
	file.ignore(10);
	file.read((char*)&streamNameCount,2);
	file.read((char*)&payloadExtensionCount,2);
	
	// Skip stream name objects
	for (int i = 0; i < streamNameCount; i++)
	{
		unsigned short int name_len;
		file.ignore(2);
		file.read((char*)&name_len,2);
		file.ignore(name_len);
	}
	
	// Skip payload extension objects
	for (int i = 0; i < payloadExtensionCount; i++)
	{
		unsigned int ext_data_size;
		file.ignore(18);
		file.read((char*)&ext_data_size,4);
		file.ignore(ext_data_size);
	}
}
