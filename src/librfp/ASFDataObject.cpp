#include "ASFDataObject.h"

#include "ASFPacket.h"
#include "ASFPayload.h"

#include <iostream>
#include <list>

using namespace std;

ASFDataObject::ASFDataObject(const GUID guid, const QWORD size) :
	ASFObject(guid,size)
{
	// ASFObject constructor handles field initialization
}

ASFDataObject::~ASFDataObject()
{
	// Delete packets
	list<ASFPacket*>::iterator it;
	for (it = dataPackets.begin(); it != dataPackets.end(); it++)
	{
		delete (*it);
	}
}

void ASFDataObject::getDataFromFile(std::ifstream &file)
{
	// Backup initial file position
	std::ifstream::pos_type start_pos = file.tellg();

	// DEBUG REMOVEME
	// std::cout << file.tellg() << "::ASF_Data_Object - " << size << std::endl;

	// Get interesting data
	file.ignore(16); // uninteresting
	file.read((char*)&dataPacketCount,8); // Total data packets
	file.ignore(2); // uninteresting

	#ifdef DEBUG
		cout << "Total data packets: " << dataPacketCount << endl;
	#endif

	// Calculate file position at end of object
	std::ifstream::pos_type end_pos = start_pos + (std::ifstream::pos_type)size - (std::ifstream::pos_type)24;

	// Construct data packets
	//while (file.tellg() < end_pos)
	for (unsigned long long int i = 0; i < dataPacketCount; i++)
	{
		dataPackets.push_back(new ASFPacket(file)); // constructor also advances file position
	}
}

std::list<ASFPayload*>* ASFDataObject::getPayloads()
{
	list<ASFPayload*>* res_list = new list<ASFPayload*>(); // Result list

	// Iterate through packets and collect their payloads
	list<ASFPacket*>::iterator it;
	for (it = dataPackets.begin(); it != dataPackets.end(); it++)
	{
		res_list->merge(*((*it)->getPayloads()));
	}

	return res_list;
}
