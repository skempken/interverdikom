#include "ASFPayload.h"

#include <iostream>

using namespace std;

ASFPayload::ASFPayload(unsigned int streamNumber, unsigned int size, unsigned int mediaObjectNumber)
{
	// Simply assign stuff
	this->size = size;
	this->streamNumber = streamNumber;
	this->mediaObjectNumber = mediaObjectNumber;
	
	#ifdef DEBUG
		cout << "Payload::" << (int)streamNumber << "::" << (int)mediaObjectNumber << " >> " << size << endl;
	#endif
}

ASFPayload::~ASFPayload()
{
}
