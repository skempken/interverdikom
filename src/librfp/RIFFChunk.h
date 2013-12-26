#ifndef RIFFCHUNK_H_
#define RIFFCHUNK_H_

#include "RIFFNode.h"

#include <fstream>
#include <string>

class AVIParser;

/// RIFF node containing raw data
/**
 * RIFF chunks contain not-further-specified data
 */
class RIFFChunk : public RIFFNode
{
public:
	/// Initialize object from file
	RIFFChunk(char *name, std::istream& file, AVIParser *parser);
	
	/// Destructor
	virtual ~RIFFChunk();
	
	/// isList query defaults to false
	virtual bool isList() {return false;}
	
	/// Checks whether this data chunk is from a video stream
	bool isVideoStream();
	
	/// Checks whether this data chunk is from an audio stream
	bool isAudioStream();
		
private:
	/// Pointer to data contained within chunk
	char *chunkData;
};

#endif /*RIFFCHUNK_H_*/
