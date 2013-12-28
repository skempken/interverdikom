#ifndef WMVPARSER_H_
#define WMVPARSER_H_

#include "ContainerFormatParser.h"

#include <list>

/// Parser class for .wmv files
/**
 * This container format parser handles the parsing of .wmv files, which should comply to the ASF specification.
 */
class WMVParser : public ContainerFormatParser
{
public:
	/// Constructor
	WMVParser();

	/// Destructor
	virtual ~WMVParser();

	virtual void parseFile(std::istream& file);
	virtual void writeOutputFiles(std::ostream& vids_file,
			std::ostream& auds_file);

private:
	/// The ASF header objetc of the parsed file
	class ASFHeaderObject* headerObject;

	/// ASF data object of the parsed file
	class ASFDataObject* dataObject;

	/// Helper function, writes the payload sizes of a specific stream to a given file
	/**
	 * \param stream_no Number of the stream of which the data should be extracted
	 * \param payloads Pointer to list containing all the payloads within the file
	 * \param file The file stream to write the data to
	 */
	void dumpStreamPayloadsToFile(const unsigned int stream_no,
			std::list<class ASFPayload*>* payloads, std::ostream& file);
};

#endif /*WMVPARSER_H_*/
