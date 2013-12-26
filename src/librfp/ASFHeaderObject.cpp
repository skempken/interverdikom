#include "ASFHeaderObject.h"

#include "ASFStreamPropertiesObject.h"

#include <iostream>
#include <cstring>

using namespace std;

ASFHeaderObject::ASFHeaderObject(const GUID guid, const QWORD size) :
	ASFObject(guid,size)
{
	// ASFObject constructor handles field initialization
}

ASFHeaderObject::~ASFHeaderObject() {}

unsigned int ASFHeaderObject::getVideoStreamNo()
{
	// Call getStreamNoByGUID with video stream type GUID
	return getStreamNoByGUID(ASFStreamPropertiesObject::ASF_Video_Media);
}

unsigned int ASFHeaderObject::getAudioStreamNo()
{
	// Call getStreamNoByGUID with audio stream type GUID
	return getStreamNoByGUID(ASFStreamPropertiesObject::ASF_Audio_Media);
}

unsigned int ASFHeaderObject::getStreamNoByGUID(const GUID guid)
{
	// Iterate through header objects
	list<ASFObject*>::iterator it;
	for (it = headerObjects.begin(); it != headerObjects.end(); it++)
	{
		// Is this a stream properties object?
		if (memcmp((*it)->getGUID(),&ASFObject::ASF_Stream_Properties_Object,16) == 0)
		{
			ASFStreamPropertiesObject* stream_obj = (ASFStreamPropertiesObject*)(*it);

			// If this is the stream type we're looking for, get the stream number and return it
			if (memcmp(stream_obj->getStreamType(),guid,16) == 0)
			{
				return stream_obj->getStreamNumber();
			}
		}
	}

	return -1;
}

void ASFHeaderObject::getDataFromFile(std::ifstream& file)
{
	// Local variables
	ASFObject *newob;

	#ifdef DEBUG
		std::cout << file.tellg() << "::ASF_Header_Object - " << size << std::endl;
	#endif

	// Get data
	file.read((char*)&this->headerObjectCount,4); // Object count field
	file.ignore(2); // Reserved fields (0x0102)

	// Get embedded header objects
	for (unsigned int i = 0; i < headerObjectCount; i++)
	{
		newob = ASFObject::constructFromFile(file);
		headerObjects.push_back(newob);
	}
}
