#ifndef QTPLACEHOLDERATOM_H_
#define QTPLACEHOLDERATOM_H_

#include "QTAtom.h"

#include <fstream>
#include <string>

/// A placeholder quicktime atom
/**
 * This atom is used as a placeholder when containers are created, to avoid parsing of unnecessary objects.
 * The atom can be made into a true container and Leaf atom with content through the use of the
 * makeContainerAtom() and makeLeafAtom() functions.
 */
class QTPlaceholderAtom : public QTAtom
{
public:
	/// Initialize object from file
	QTPlaceholderAtom(unsigned int size, std::string& name, int filePos);
	
	/// Destructor
	virtual ~QTPlaceholderAtom();
	
	/// Convert placeholder atom to container atom
	/**
	 * \param file The file stream containing atom data
	 * \return The constructed container atom
	 */
	class QTContainerAtom* makeContainerAtom(std::istream& file);
	
	/// Convert placeholder atom to leaf atom
	/**
	 * \param file Th file stream containing the atom data
	 * \return The constructed leaf atom
	 */
	class QTLeafAtom* makeLeafAtom(std::istream& file);
};

#endif /*QTPLACEHOLDERATOM_H_*/
