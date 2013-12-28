#ifndef RIFFNODE_H_
#define RIFFNODE_H_

#include <string>

/// Base class for RIFF nodes
class RIFFNode
{
public:
	/// Destructor
	virtual ~RIFFNode() {}
	
	/// isList query to be implemented by subclasses
	virtual bool isList() = 0;
	
	/// Simple getter for size
	unsigned int getSize() {return size;}
	
	/// Simple getter for name
	std::string getName() {return name;}
		
protected:
	/// Size in bytes of this node
	unsigned int size;
	
	/// Name of this node
	std::string name;
};

#endif /*RIFFNODE_H_*/
