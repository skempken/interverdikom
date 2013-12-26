#include "AVIParser.h"
#include "RIFFNode.h"
#include "RIFFList.h"
#include "RIFFChunk.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

AVIParser::AVIParser() :
	riffRoot(0)
{
}

AVIParser::~AVIParser()
{
	// Delete pointer object
	if (riffRoot)
		delete riffRoot;
}

void AVIParser::parseFile(std::istream& file)
{
	// Read buffer
	char buf[4];
	file.read(buf, 4);

	if (memcmp(buf, "RIFF", 4) == 0) // Looks like an AVI file
	{
		// Construct the RIFF data structure
		//  The RIFFList constructor takes the file handle as argument and
		//  recursively constructs the contained data structure.... minus
		//  the data (since we only want the structure and chunk sizes).
		riffRoot = new RIFFList(file, this);
	}
	else // Isn't an AVI file
	{
		cout << "File is not an AVI file, exiting."<< endl;
		exit(0);
	}
}

void AVIParser::writeOutputFiles(std::ostream& vids_file,
		std::ostream& auds_file)
{
	// Local declarations
	list<RIFFNode*>* riffList = riffRoot->getElements();
	list<RIFFNode*>::iterator it;
	list<RIFFNode*>* moviList = 0;
	RIFFChunk *currChunk;

	// Find the "movi" RIFF list structure
	for (it = riffList->begin(); it != riffList->end(); it++)
	{
		if ((*it)->getName() == "movi")
		{
			moviList = ((RIFFList*)(*it))->getElements();
			break;
		}
	}
	if (moviList == 0) // Looks like something went wrong
	{
		cout << "Couldn't find \"movi\" list, fatal."<< endl;
		exit(0);
	}

	// Now it's time to check whether this particular file uses
	// "rec " lists for its frames or simply contains all the chunks
	// in the "movi" list. Checking the first node should be sufficient
	int videoFrameNo = 1;
	double frameLength = ((double)microSecondsPerFrame) / ((double)1000000);
	if (moviList->front()->isList())
	{
		// The "movi" list contains sublists, so "rec "s it is
		// Now, iterate through movi list
		for (it = moviList->begin(); (it != moviList->end()) && (*it)->isList(); it++)
		{
			list<RIFFNode*> *currRecList = ((RIFFList*)(*it))->getElements();

			// Iterate through record list
			list<RIFFNode*>::iterator recIt;
			for (recIt = currRecList->begin(); recIt != currRecList->end(); recIt++)
			{
				// Check chunk type and output size to file accordingly
				currChunk = (RIFFChunk*)(*recIt);
				if (currChunk->isAudioStream())
					auds_file << currChunk->getSize() << endl;
				else if (currChunk->isVideoStream())
				{
					vids_file << currChunk->getSize();
					if (dumpTimeIndex)
					{
						vids_file << "\t" << ((double)videoFrameNo) * frameLength;
						videoFrameNo++;
					}
					vids_file << endl;
				}
			}
		}
	}
	else // simple interleaved chunks
	{
		// Iterate through movi list
		for (it = moviList->begin(); it != moviList->end(); it++)
		{
			// Check chunk type and output size to file accordingly
			currChunk = (RIFFChunk*)(*it);
			if (currChunk->isAudioStream())
				auds_file << currChunk->getSize() << endl;
			else if (currChunk->isVideoStream())
			{
				vids_file << currChunk->getSize();
				if (dumpTimeIndex)
				{
					vids_file << "\t" << ((double)videoFrameNo) * frameLength;
					videoFrameNo++;
				}
				vids_file << endl;
			}
		}
	}
}
