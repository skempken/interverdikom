#include "QTContainerAtom.h"

#include "QTPlaceholderAtom.h"
#include "EndianConverter.h"

#include <iostream>

using std::string;
using std::list;
using std::cout;
using std::endl;

QTContainerAtom::QTContainerAtom(unsigned int size, std::string& name, int filePos, std::istream& file) :
	QTAtom(size,name,filePos)
{
	// DEBUG REMOVEME
	// cout << filePos << "::CONTAINER::" << name << " - " << size << endl;
		
	// Local variables
	QTPlaceholderAtom *new_atom;
	char size_buf[4],name_buf[5];
	name_buf[4] = 0x00;
	string name_str;
	unsigned int size_int;
	
	file.seekg(filePos); // Seek given file position

	// Construct elements of atom container
	unsigned int constructedSize = 8; // Got the name and size fields already
	while ((constructedSize < size) && file.good())
	{
		// Fetch atom name and size
		file.read(size_buf,(std::ifstream::pos_type)4);
		file.read(name_buf,4);
		name_str.assign(name_buf);
		size_int = EndianConverter::convertInt(*((unsigned int*)size_buf));
				
		// Construct new placeholder atom and add to element list		
		new_atom = new QTPlaceholderAtom(size_int,name_str,file.tellg());
		containerElements.push_back(new_atom);
		
		file.ignore(size_int - 8); // Advance file position
		constructedSize += size_int; // Increase counter
	}
	
	// If we reached EOF in the construction process, clear the EOF flag for future file operations
	if (file.eof())
	{
		file.clear();
	}
}

QTContainerAtom::~QTContainerAtom()
{
	// Iterate through and delete elements
	for (list<QTPlaceholderAtom*>::iterator it = containerElements.begin(); it != containerElements.end(); it++)
	{
		delete (*it);
	}
}

QTPlaceholderAtom* QTContainerAtom::getAtom(std::string& name)
{
	// Iterate through container elements
	for (list<QTPlaceholderAtom*>::iterator it = containerElements.begin(); it != containerElements.end(); it++)
	{
		// Is this the one? If so, return it
		if ((*it)->getName().compare(name) == 0)
		{
			return (*it);
		}
	}
	// End of iteration with no result, thus we return 0
	return 0; 
}

std::list<QTPlaceholderAtom*> QTContainerAtom::getAllAtoms(std::string& name)
{
	// Result list
	std::list<QTPlaceholderAtom*> res;
	// Iterate through elements
	for (list<QTPlaceholderAtom*>::iterator it = containerElements.begin(); it != containerElements.end(); it++)
	{
		// Does this one match? If so, add to results
		if ((*it)->getName().compare(name) == 0)
		{
			res.push_back(*it);
		}
	}
	// Return result list
	return res;
}
