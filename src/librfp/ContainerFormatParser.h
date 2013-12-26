#ifndef CONTAINERFORMATPARSER_H_
#define CONTAINERFORMATPARSER_H_

#include <string>

/// Interface for specific container format parsers
class ContainerFormatParser
{
public:
	/// Destructor
	virtual ~ContainerFormatParser() {}

	/// Parse file contents and construct corresponding data structures
	/**
	 * \param file File stream to parse
	 */
	virtual void parseFile(std::istream& file) = 0;
	
	/// Dump data from file structures to stream data files
	/**
	 * \param vids_file File stream for video data
	 * \param auds_file File stream for audio data
	 */
	virtual void writeOutputFiles
		(std::ostream& vids_file, std::ostream& auds_file) = 0;
		
	/// Helper function, construct appropriate parser for file type
	/**
	 * \param file File to check
	 * \return Appropriate parser or 0 if none found
	 */
	static ContainerFormatParser* getParserForFile(std::istream& file);
	
	void setDumpTimeIndex(bool doDump)
	{
		dumpTimeIndex = doDump;
	}
	
protected:
	bool dumpTimeIndex;
};

#endif /*CONTAINERFORMATPARSER_H_*/
