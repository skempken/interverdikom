#include "RIFFChunk.h"

#include <iostream>

#include "AVIParser.h"

using namespace std;

RIFFChunk::RIFFChunk(char *name, std::istream& file, AVIParser *parser) : chunkData(0)
{
	// int pos = file.tellg(); // DEBUG position in file
	char buf[4]; // Read buffer
	this->name.assign(name); // The name's conveniently already in the parameters

	// Fetch chunk size
	file.read(buf, 4);
	size = *((unsigned int*)buf);

	// Correct chunk size (round up to mod 2 = 0)
	if ((size % 2) != 0)
		size += 1;

	// Assign chunk data if relevant
	if (this->name == "avih")
	{
		chunkData = new char[size];
		file.read(chunkData, size);
		int microSecondsPerFrame =  *((int*)(chunkData));
		parser->setMicroSecondsPerFrame(microSecondsPerFrame);
	}
	else
	{
		file.seekg(file.tellg() + (streampos)size);
	}

	// DEBUG output	
	// cout << pos << "::New chunk: " << name << " (size: " << size << ")" << endl;
}

RIFFChunk::~RIFFChunk()
{
	delete chunkData;
}

bool RIFFChunk::isVideoStream()
{
	return ((name.substr(2) == "dc") || (name.substr(2) == "db"));
}

bool RIFFChunk::isAudioStream()
{
	return (name.substr(2) == "wb");
}
