#ifndef MOVPARSER_H_
#define MOVPARSER_H_

#include "ContainerFormatParser.h"

class QTLeafAtom;
class QTContainerAtom;

/// Parser class for .mov and compatible files
class MOVParser : public ContainerFormatParser
{
public:
	/// Constructor
	MOVParser();

	/// Destructor
	virtual ~MOVParser();

	virtual void parseFile(std::istream& file);
	
	virtual void writeOutputFiles(std::ostream& vids_file,
			std::ostream& auds_file);

private:
	/// Helper function, advances file stream to location of "moov" atom
	/**
	 * \param file The file stream
	 */
	void findMOOVContainer(std::istream& file);

	/// Helper function, parses "trak" atom
	/**
	 * \param container The "trak" atom
	 * \param file The file stream currently parsed
	 */
	void handleTrakContainer(QTContainerAtom *container,
			std::istream& file);

	/// Helper function, extracts specific container atom or quits with fatal error
	/**
	 * \param atomName Name of the atom to extract
	 * \param container Container object that contains this atom
	 * \param file Currently parsed file stream 
	 */
	class QTContainerAtom* findContainerAtomOrDie(const char* atomName,
			QTContainerAtom* container, std::istream& file);

	/// Helper function, extracts leaf atom or quits with fatal error
	/**
	 * \param atomName Name of the atom to extract
	 * \param container Container object that contains this atom
	 * \param file Currently parsed file stream 
	 */
	class QTLeafAtom* findLeafAtomOrDie(const char* atomName,
			QTContainerAtom* container, std::istream& file);

	/// Helper function, writes size table to file
	/**
	 * \param sizeTable Atom containing the size table
	 * \param file The file stream to write to
	 */
	void dumpSizeTable(QTLeafAtom* sizeTable, std::ostream& file, QTLeafAtom *ttsAtom,
			QTLeafAtom *syncTable = 0);

	/// Pointer to the "moov" atom
	QTContainerAtom *movieAtom;

	/// Pointer to the video size table atom
	QTLeafAtom *videoStszAtom;

	/// Pointer to the 
	QTLeafAtom *videoStssAtom;
		
	QTLeafAtom *videoSttsAtom;
	
	/// Pointer to the audio size table atom 
	QTLeafAtom *audioStszAtom;
	
	QTLeafAtom *audioSttsAtom;
	
	unsigned int videoTimeScale;
	
	unsigned int audioTimeScale;
};

#endif /*MOVPARSER_H_*/
