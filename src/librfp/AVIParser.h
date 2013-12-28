#ifndef AVIPARSER_H_
#define AVIPARSER_H_

#include "ContainerFormatParser.h"
#include "RIFFList.h"

#include <iostream>

/// Parser class for .avi files
/**
 * This class is responsible for parsing files builts after the RIFF specification for AVI.
 */
class AVIParser : public ContainerFormatParser
{
public:
	/// Constructor
	AVIParser();

	/// Destructor
	~AVIParser();

	virtual void parseFile(std::istream& file);
	virtual void writeOutputFiles(std::ostream& vids_file,
			std::ostream& auds_file);

	void setMicroSecondsPerFrame(int mspf)
	{
		microSecondsPerFrame = mspf;
	}

private:
	/// Root RIFF list containing all other RIFF data
	RIFFList *riffRoot;

	int microSecondsPerFrame;
};

#endif /*AVIPARSER_H_*/
