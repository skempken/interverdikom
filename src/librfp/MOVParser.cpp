#include "MOVParser.h"

#include "QTAtom.h"
#include "QTPlaceholderAtom.h"
#include "QTContainerAtom.h"
#include "QTLeafAtom.h"
#include "EndianConverter.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <list>
#include <fstream>

using namespace std;

MOVParser::MOVParser() :
	movieAtom(0), videoStszAtom(0), videoStssAtom(0), audioStszAtom(0)
{
}

MOVParser::~MOVParser()
{
	delete movieAtom;
	delete videoStszAtom;
	delete videoStssAtom;
	delete audioStszAtom;
}

void MOVParser::parseFile(std::istream& file)
{
	// Local variables
	char buf[5];
	buf[4] = 0x00;
	string search_str;

	// Find the metadata container
	findMOOVContainer(file);

	// Fetch size, name and current file position
	file.read(buf, 4);
	int size_int = EndianConverter::convertInt(*((int*)buf));
	file.read(buf, 4);
	string name_str(buf);
	unsigned int fpos = file.tellg();

	// Construct moov atom container
	movieAtom = new QTContainerAtom(size_int,name_str,fpos,file);

	// Find and iterate through "trak" atoms
	search_str = "trak";
	list<QTPlaceholderAtom*> trakAtoms = movieAtom->getAllAtoms(search_str);
	for (list<QTPlaceholderAtom*>::iterator it = trakAtoms.begin(); it
			!= trakAtoms.end(); it++)
	{
		// Construct "trak" container and parse contents
		QTContainerAtom *trakContainer = (*it)->makeContainerAtom(file);
		handleTrakContainer(trakContainer, file);
		delete trakContainer;
	}
}

void MOVParser::handleTrakContainer(QTContainerAtom *container, istream& file)
{
	// Construct structure of interesting subcontainers
	QTContainerAtom *mdiaAtom = findContainerAtomOrDie("mdia", container, file);
	QTContainerAtom *minfAtom = findContainerAtomOrDie("minf", mdiaAtom, file);
	QTContainerAtom *stblAtom = findContainerAtomOrDie("stbl", minfAtom, file);

	// Get interesting leaf atoms
	QTLeafAtom *hdlrAtom = findLeafAtomOrDie("hdlr", mdiaAtom, file);
	QTLeafAtom *mdhdAtom = findLeafAtomOrDie("mdhd", mdiaAtom, file);
	QTLeafAtom *stszAtom = findLeafAtomOrDie("stsz", stblAtom, file);
	QTLeafAtom *sttsAtom = findLeafAtomOrDie("stts", stblAtom, file);

	QTLeafAtom *stssAtom = 0;
	QTPlaceholderAtom *stssPlaceholder = stblAtom->getAtom(*(new string("stss")));
	if (stssPlaceholder)
	{
		stssAtom = stssPlaceholder->makeLeafAtom(file);
	}

	// Data buffer
	char buf[5];
	buf[4] = 0x00;

	unsigned int
			timeScale= EndianConverter::convertInt(*((unsigned int*)((char*)mdhdAtom->getData()
					+ 12)));

	// Check component subtype field of handler atom and assign pointer to size table atom accordingly
	memcpy(&buf, (void*)((size_t)hdlrAtom->getData() + 8), 4);
	if (strcmp(buf, "vide") == 0)
	{
		videoStszAtom = stszAtom;
		videoStssAtom = stssAtom;
		videoSttsAtom = sttsAtom;
		videoTimeScale = timeScale;
	}
	else if (strcmp(buf, "soun") == 0)
	{
		audioStszAtom = stszAtom;
		audioSttsAtom = stssAtom;
		audioTimeScale = timeScale;
	}

	// Cleanup
	delete mdiaAtom;
	delete minfAtom;
	delete stblAtom;
	delete hdlrAtom;
}

QTContainerAtom* MOVParser::findContainerAtomOrDie(const char* atomName,
		QTContainerAtom* container, std::istream& file)
{
	// Wrapper for QTContainerAtom::getAtom()
	QTPlaceholderAtom *search_res = 0;
	string search_str(atomName);
	search_res = container->getAtom(search_str);
	if (search_res == 0)
	{
		cerr << "Couldn't find container atom \""<< atomName << "\", fatal."
				<< endl;
		exit(0);
		return 0;
	}

	return search_res->makeContainerAtom(file);
}

QTLeafAtom* MOVParser::findLeafAtomOrDie(const char* atomName,
		QTContainerAtom* container, std::istream& file)
{
	// Wrapper for QTContainerAtom::getAtom()
	QTPlaceholderAtom *search_res = 0;
	string search_str(atomName);
	search_res = container->getAtom(search_str);
	if (search_res == 0)
	{
		cerr << "Couldn't find container atom \""<< atomName << "\", fatal."
				<< endl;
		exit(0);
	}
	return search_res->makeLeafAtom(file);
}

void MOVParser::findMOOVContainer(istream& file)
{
	// Not a very nice implementation :/

	char curChar;
	char buf[4];
	buf[3] = 0x00;

	while (file.good() && !file.eof())
	{
		file.read(&curChar, 1);
		if (curChar == 'm')
		{
			file.read(buf, 3);
			if (strcmp(buf, "oov") == 0)
			{
				file.seekg((unsigned int)file.tellg() - 8);
				// cout << "MOOV FOUND! " << (unsigned int)file.tellg() << endl;
				return;
			}
			file.seekg((unsigned int)file.tellg() - 3);
		}
	}
	cerr << "Couldn't find \"moov\" atom, fatal."<< endl;
	exit(0);
}

void MOVParser::dumpSizeTable(QTLeafAtom* sizeTable, std::ostream& file,
		QTLeafAtom *ttsAtom, QTLeafAtom *syncTable)
{
	void *data = sizeTable->getData();
	unsigned int this_size;
	unsigned int data_size = sizeTable->getDataSize();
	unsigned int sample_no = 1;

	unsigned int
			overall_sample_size = EndianConverter::convertInt(*((int*)(size_t)data
					+ 1));
	if (overall_sample_size != 0) // Is there a standardized sample size?
	{
		// Dump that size to the file for the given number of samples
		unsigned int
				total_samples = EndianConverter::convertInt(*((int*)(size_t)data
						+ 2));
		for (unsigned int i = 0; i < total_samples; i++)
		{
			file << overall_sample_size << endl;
		}
	}
	else // The sample size is variable
	{
		unsigned int keyframe_count = 0, next_keyframe = -1;
		bool is_keyframe;
		is_keyframe = false;
		unsigned int *keyframe_data = 0, *keyframe_data_start = 0;

		if (syncTable)
		{
			keyframe_data_start = keyframe_data
					= (unsigned int*)syncTable->getData();
			keyframe_count
					= EndianConverter::convertInt(*((int*)(size_t)keyframe_data
							+ 1));
			next_keyframe
					= EndianConverter::convertInt(*((int*)(size_t)keyframe_data
							+ 2));
			keyframe_data += 2;
		}

		unsigned int thisTimeFramesLeft = 0,
				thisTimeUnits = 0, timeSegments = 0, timeSegment = 0, *nextTimeEntry = 0;
		double timeIndex = 0.0;
		if (dumpTimeIndex)
		{
			timeSegments
					= EndianConverter::convertInt(*((int*)((char*)ttsAtom->getData()
							+ 4)));
			nextTimeEntry = (unsigned int*)ttsAtom->getData() + 2;
		}

		// Go through table and dump sizes to file
		unsigned int offset = 3;
		while ((offset * 4) < data_size)
		{
			is_keyframe = false;

			if (syncTable)
			{
				if (sample_no == next_keyframe)
				{
					is_keyframe = true;
					if ((keyframe_data - keyframe_data_start)
							< ((int)keyframe_count - 3))
					{
#ifdef DEBUG
						cout << "Keyframe "<< sample_no << " ("
								<< (keyframe_data - keyframe_data_start)<< ")"
								<< endl;
#endif
						next_keyframe
								= EndianConverter::convertInt(*((int*)(size_t)++keyframe_data));
					}
					else
					{
						next_keyframe = -1;
					}
				}
			}

			this_size = EndianConverter::convertInt(*((int*)(size_t)data
					+ offset));
			file << this_size;

			if (dumpTimeIndex)
			{
				if ((thisTimeFramesLeft == 0) && (timeSegment < timeSegments))
				{
					thisTimeFramesLeft =  EndianConverter::convertInt(nextTimeEntry[0]);
					thisTimeUnits =  EndianConverter::convertInt(nextTimeEntry[1]);
					nextTimeEntry += 2;
				}

				thisTimeFramesLeft--;
				file << "\t" << timeIndex;
				timeIndex += (1.0 / (double)videoTimeScale) * (double)thisTimeUnits;
			}

			if (is_keyframe)
				file << "\tK";
			file << endl;

			++offset;
			++sample_no;
		}
	}
}

void MOVParser::writeOutputFiles(std::ostream& vids_file,
		std::ostream& auds_file)
{
	// Dump size tables of both streams
	if (videoStszAtom)
	{
		dumpSizeTable(videoStszAtom, vids_file, videoSttsAtom, videoStssAtom);
	}

	if (audioStszAtom)
	{

		dumpSizeTable(audioStszAtom, auds_file, audioSttsAtom);
	}
}
