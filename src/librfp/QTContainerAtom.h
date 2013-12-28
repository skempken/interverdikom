#ifndef QTCONTAINERATOM_H_
#define QTCONTAINERATOM_H_

#include "QTAtom.h"
#include "QTPlaceholderAtom.h"

#include <list>

/// Quicktime container atom
/**
 * A quicktime container atom is a data structure that contains only other quicktime atoms.
 * The container atom constructs its content as QTPlaceholderAtoms in its constructor.
 */
class QTContainerAtom : public QTAtom
{
public:
	/// Initialize object from file
	QTContainerAtom(unsigned int size, std::string& name, int filePos, std::istream& file);
	
	/// Destructor
	virtual ~QTContainerAtom();
	
	/// Simple getter for container element list
	std::list<QTPlaceholderAtom*>* getElements() { return &containerElements; }
	
	/// Gets a specific atom from the container element list
	/**
	 * \param name The name of the atom to retrieve from the list
	 */
	QTPlaceholderAtom* getAtom(std::string& name);
	
	/// Get a list of all atoms with specific name
	/**
	 * \param name The name of the atom(s) to add to the resulting list
	 * \return List of all atoms with the given name
	 */
	std::list<QTPlaceholderAtom*> getAllAtoms(std::string& name);
	
private:
	/// List of contained elements
	std::list<QTPlaceholderAtom*> containerElements;
};

#endif /*QTCONTAINERATOM_H_*/
