#ifndef RIFFLIST_H_
#define RIFFLIST_H_

#include "RIFFNode.h"

#include <string>
#include <list>
#include <fstream>

class AVIParser;

/// RIFF list node
/**
 * A RIFF list node contains a number of other RIFF nodes which are either lists again or chunks.
 */
class RIFFList : public RIFFNode
{
public:
	/// Construct from file
	RIFFList(std::istream& file, AVIParser *parser);
	
	/// Destructor
	virtual ~RIFFList();
	
	/// isList query always returns true
	virtual bool isList() {return true;}
	
	/// Simple getter for list elements
	std::list<RIFFNode*>* getElements()
		{ return &listElements; }
	
private:
	/// List of elements in container
	std::list<RIFFNode*> listElements;
};

#endif /*RIFFLIST_H_*/
