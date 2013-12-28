#include "RIFFList.h"
#include "RIFFChunk.h"

#include <iostream>
#include <cstring>

using namespace std;

RIFFList::RIFFList(istream& file, AVIParser *parser)
{
	// 4 byte buffer with null byte ending
	char buf[5];
	buf[4] = 0x00;

	// int pos = file.tellg(); // DEBUG position in file

	// Fetch list size in bytes
	file.read(buf, 4);
	size = *((unsigned int*)buf);

	// Fetch list name
	file.read(buf, 4); // Listenname lesen
	name.assign(buf);

	// DEBUG output
	// cout << pos << "::New List: " << name << " (size: " << size << ")" << endl;

	// Now, let's construct the list elements
	unsigned int constructedSize = 4; // first 4 bytes contain list name, got those already
	while ((constructedSize < size) && file.good()) // repeat until list complete
	{
		// DEBUG output
		// cout << "constructedSize " << constructedSize << " size " << size << endl;
		RIFFNode *new_element; // The new element
		file.read(buf, 4); // ...  and it's name / type

		if (strcmp(buf, "LIST") == 0) // is it a list?
		{
			new_element = new RIFFList(file, parser);
			constructedSize += 12; // add size of list header (12 bytes)
		}
		else // is it a chunk?
		{
			new_element = new RIFFChunk(buf, file, parser);
			constructedSize += 8; // add size of chunk header (8 bytes)
		}
		listElements.push_back(new_element); // add the new element
		constructedSize += new_element->getSize(); // add size of actual data
	}
}

RIFFList::~RIFFList()
{
	// Delete list elements
	for (list<RIFFNode*>::iterator it = listElements.begin(); it
			!= listElements.end(); it++)
	{
		delete *it;
	}
}
