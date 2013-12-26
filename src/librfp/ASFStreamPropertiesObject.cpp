#include "ASFStreamPropertiesObject.h"

#include <iostream>
#include <cstring>

using namespace std;

// GUID constants
char ASFStreamPropertiesObject::ASF_Audio_Media[16] =
		{0x40,0x9E,0x69,0xF8,0x4D,0x5B,0xCF,0x11,0xA8,0xFD,0x00,0x80,0x5F,0x5C,0x44,0x2B};
char ASFStreamPropertiesObject::ASF_Video_Media[16] =
		{0xC0,0xEF,0x19,0xBC,0x4D,0x5B,0xCF,0x11,0xA8,0xFD,0x00,0x80,0x5F,0x5C,0x44,0x2B};

ASFStreamPropertiesObject::ASFStreamPropertiesObject(const GUID guid, const QWORD size) :
	ASFObject(guid,size)
{
	// ASFObject constructor handles field initialization
}

ASFStreamPropertiesObject::~ASFStreamPropertiesObject()
{
}

void ASFStreamPropertiesObject::getDataFromFile(std::ifstream &file)
{
	#ifdef DEBUG
		cout << file.tellg() << "::ASF_Stream_Properties_Object - " << size << endl;
	#endif

	// Read stream type GUID
	file.read(streamType,16);
	// Pass over irrelevant data
	file.ignore(32);
	// Read stream flags (WORD)
	file.read(flags,2);
	// Ignore rest of stream property data
	file.ignore(size - 56 - 18);
}

unsigned int ASFStreamPropertiesObject::getStreamNumber()
{
	// 7 bits of flags[0]
	char buf;
	memcpy(&buf,flags,1);
	buf = buf & 127;

	// Implicit cast to int and return
	unsigned int res = buf;
	return res;
}

bool ASFStreamPropertiesObject::isVideoStream()
{
	// Check stream type GUID
	return (memcmp(streamType,ASFStreamPropertiesObject::ASF_Video_Media,16) == 0);
}

bool ASFStreamPropertiesObject::isAudioStream()
{
	// Check stream type GUID
	return (memcmp(streamType,ASFStreamPropertiesObject::ASF_Audio_Media,16) == 0);
}
