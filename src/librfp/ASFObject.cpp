#include "ASFObject.h"

#include "ASFHeaderObject.h"
#include "ASFDataObject.h"

#include "ASFFilePropertiesObject.h"
#include "ASFStreamPropertiesObject.h"
#include "ASFExtendedStreamPropertiesObject.h"

#include <iostream>
#include <cstring>

using namespace std;

// GUID constants
char ASFObject::ASF_Header_Object[16] =
	{0x30,0x26,0xB2,0x75,0x8E,0x66,0xCF,0x11,0xA6,0xD9,0x00,0xAA,0x00,0x62,0xCE,0x6C};
char ASFObject::ASF_Data_Object[16] =
	{0x36,0x26,0xB2,0x75,0x8E,0x66,0xCF,0x11,0xA6,0xD9,0x00,0xAA,0x00,0x62,0xCE,0x6C};
char ASFObject::ASF_Stream_Properties_Object[16] =
	{0x91,0x07,0xDC,0xB7,0xB7,0xA9,0xCF,0x11,0x8E,0xE6,0x00,0xC0,0x0C,0x20,0x53,0x65};
char ASFObject::ASF_Extended_Stream_Properties_Object[16] =
	{0xCB,0xA5,0xE6,0x14,0x72,0xC6,0x32,0x43,0x83,0x99,0xA9,0x69,0x52,0x06,0x5B,0x5A};
char ASFObject::ASF_File_Properties_Object[16] =
	{0xA1,0xDC,0xAB,0x8C,0x47,0xA9,0xCF,0x11,0x8E,0xE4,0x00,0xC0,0x0C,0x20,0x53,0x65};

ASFObject::ASFObject(const GUID guid, const QWORD size)
{
	// Generic constructor (protected)
	memcpy(this->guid,guid,16);
	this->size = size;
}

ASFObject::~ASFObject() {}

void ASFObject::getDataFromFile(std::istream& file)
{
	#ifdef DEBUG
		std::cout << file.tellg() << "::ASF_Dummy_Object - " << size << std::endl;
	#endif

	// Skip data since it's uninteresting anyway
	file.seekg((std::ifstream::pos_type)file.tellg() + ((std::ifstream::pos_type)getSize() - (std::ifstream::pos_type)24));
}

ASFObject* ASFObject::constructFromFile(std::istream& file)
{
	// Local variables
	ASFObject *newob;
	char guid[16];
	unsigned long long size;

	// Fetch object GUID and size
	file.read(guid,16);
	file.read((char*)&size,8);

	// Call appropriate constructor for the GUID
	if (memcmp(guid,&ASFObject::ASF_Header_Object,16) == 0)
		newob = new ASFHeaderObject(guid,size);
	else if (memcmp(guid,&ASFObject::ASF_Data_Object,16) == 0)
		newob = new ASFDataObject(guid,size);
	else if (memcmp(guid,&ASFObject::ASF_Stream_Properties_Object,16) == 0)
		newob = new ASFStreamPropertiesObject(guid,size);
	else if (memcmp(guid,&ASFObject::ASF_Extended_Stream_Properties_Object,16) == 0)
		newob = new ASFExtendedStreamPropertiesObject(guid,size);
	else if (memcmp(guid,&ASFObject::ASF_File_Properties_Object,16) == 0)
		newob = new ASFFilePropertiesObject(guid,size);
	else
		newob = new ASFObject(guid,size); // Placeholder object

	// Initialize and return object (also advances file pointer to end of object)
	newob->getDataFromFile(file);
	return newob;
}
