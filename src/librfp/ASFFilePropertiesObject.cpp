#include "ASFFilePropertiesObject.h"

#include <fstream>
#include <iostream>

using namespace std;

unsigned int ASFFilePropertiesObject::minPacketSize = 0;
unsigned int ASFFilePropertiesObject::maxPacketSize = 0;

ASFFilePropertiesObject::ASFFilePropertiesObject(const GUID guid, const QWORD size) :
	ASFObject(guid,size)
{
	// ASFObject constructor handles field initialization
}

ASFFilePropertiesObject::~ASFFilePropertiesObject() {}

void ASFFilePropertiesObject::getDataFromFile(std::ifstream &file)
{
	#ifdef DEBUG
		cout << file.tellg() << "::";
	#endif
	
	file.ignore(68); // Uninteresting data
	file.read((char*)&minPacketSize,4); // Min packet size
	file.read((char*)&maxPacketSize,4); // Max packet size
	file.ignore(4); // Some more uninteresting stuff
	
	#ifdef DEBUG
		cout << "ASFFilePropertiesObject :: minPacketSize:" << maxPacketSize;
		cout << " maxPacketSize:" << maxPacketSize << endl;
	#endif
}
