#include "ContainerFormatParser.h"

#include <iostream>
#include <fstream>
#include <cstring>

#include "ASFObject.h"
#include "AVIParser.h"
#include "MOVParser.h"
#include "WMVParser.h"

using namespace std;

ContainerFormatParser* ContainerFormatParser::getParserForFile(std::istream& file)
{
	//cout << "Type: ";

	// Get the first 16 bytes of the file to determine the type
	char buf[16];
	file.read(buf,16);
	file.seekg(0);

	if (memcmp(buf,"RIFF",4) == 0) // RIFF list present?
	{
		// Use AVIParser object
		//cout << "RIFF (.avi). ";
		return new AVIParser();
	}

	if (memcmp(buf+4,"ftyp3gp",7) == 0)
	{
		//cout << "3GP (QT compatible). ";
		return new MOVParser();
	}

	if ((memcmp(buf+4,"wide",4) == 0) |
		(memcmp(buf+4,"skip",4) == 0) |
		(memcmp(buf+4,"free",4) == 0) |
		(memcmp(buf+4,"pnot",4) == 0) |
		(memcmp(buf+4,"mdat",4) == 0) |
		(memcmp(buf+4,"ftyp",4) == 0) |
		(memcmp(buf+4,"moov",4) == 0)) // One of the typical quicktime atoms present?
	{
		// Use MOVParser object
		//cout << "QT movie format or compatible. ";
		return new MOVParser();
	}

	if (memcmp(buf,ASFObject::ASF_Header_Object,16) == 0) // ASF_Header_Object GUID present?
	{
		// Use WMVParser object
		//cout << "ASF (.wmv). ";
		return new WMVParser();
	}

	//cout << "unknown. ";
	return 0;
}
