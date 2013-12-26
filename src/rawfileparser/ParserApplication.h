#ifndef PARSERAPPLICATION_H_
#define PARSERAPPLICATION_H_

#include <string>

/// Main application class
/**
 * This class controls the main program flow.
 */
class ParserApplication
{
public:
	/// Constructor
	ParserApplication();
	
	/// Destructor
	virtual ~ParserApplication();
	
	/// Handles a call from the command line
	/**
	 * \param arc Argument Count
	 * \param argv Array of arguments
	 * */
	int handleCall(int argc, char **argv);
	
	void printUsage(const char * programName);
};

#endif /*PARSERAPPLICATION_H_*/
