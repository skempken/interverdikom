#ifndef QTATOM_H_
#define QTATOM_H_

#include <string>

/// Base class for all quicktime atoms
/**
 * The different types of QT atoms - container, leaf and placeholder - all inherit from this.
 */ 
class QTAtom
{
public:
	/// Destructor
	virtual ~QTAtom();
	
	/// Simple getter for size
	unsigned int const getSize() { return size; }
	
	/// Simple getter for name
	std::string& getName() { return name; }
	
protected:
	/// Constructor to initialize size, name and filePos fields
	/**
	 * This constructor is only to be called by child classes.
	 */
	QTAtom(unsigned int size, std::string& name, int filePos);
	
	/// Size of this atom in bytes
	unsigned int size;
	
	/// Name of this atom
	std::string name;
	
	/// Position of data in file
	unsigned int filePos;
};

#endif /*QTATOM_H_*/
