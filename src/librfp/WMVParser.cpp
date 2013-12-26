#include "WMVParser.h"

#include "ASFHeaderObject.h"
#include "ASFDataObject.h"
#include "ASFPayload.h"

#include <fstream>
#include <list>

using namespace std;

WMVParser::WMVParser()
{
	headerObject = 0;
	dataObject = 0;
}

WMVParser::~WMVParser()
{
	if (headerObject)
		delete headerObject;
	if (dataObject)
		delete dataObject;
}

void WMVParser::parseFile(std::istream& file)
{
	file.seekg(0,ios::beg);
	headerObject = (ASFHeaderObject*)ASFObject::constructFromFile(file); // construct header object from file
	dataObject = (ASFDataObject*)ASFObject::constructFromFile(file); // construct data object from file
}

void WMVParser::dumpStreamPayloadsToFile(const unsigned int stream_no, list<ASFPayload*>* payloads, std::ostream& file)
{
	list<ASFPayload*>::iterator it;
	unsigned int last_mobj = -1;
	unsigned int mobj_size = -1;
	unsigned int mobj_no;
	
	for (it = payloads->begin(); it != payloads->end(); it++)
	{
		if ((*it)->getStreamNumber() != stream_no)
			continue;
			
		mobj_no = (*it)->getMediaObjectNumber();
		
		if ((mobj_no != last_mobj) || (mobj_no == 0))
		{
			if (mobj_size != (unsigned int)-1)
			{
				file << mobj_size << endl;
			}
			last_mobj = mobj_no;
			mobj_size = (*it)->getSize();
		}
		else
		{
			mobj_size += (*it)->getSize();
		}
	}
	
	if (mobj_size)
		file << mobj_size << endl;
}

void WMVParser::writeOutputFiles
	(std::ostream& vids_file, std::ostream& auds_file)
{
	unsigned int video_stream_no = headerObject->getVideoStreamNo(); 
	unsigned int audio_stream_no = headerObject->getAudioStreamNo();
	
	list<ASFPayload*>* payloads = dataObject->getPayloads();
	
	dumpStreamPayloadsToFile(video_stream_no, payloads, vids_file);
	dumpStreamPayloadsToFile(audio_stream_no, payloads, auds_file);
	
	delete payloads;	
}
