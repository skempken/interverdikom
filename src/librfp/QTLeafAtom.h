#ifndef QTLEAFATOM_H_
#define QTLEAFATOM_H_

#include "QTAtom.h"

/// Quicktime leaf atom
/**
 * A QTLeafAtom contains but a simple data chunk. Its content is not further specified.
 */
class QTLeafAtom : public QTAtom
{
public:
	/// Initialize object from file
	QTLeafAtom(unsigned int size, std::string& name, int filePos, std::istream& file);
	
	/// Destructor
	virtual ~QTLeafAtom();
	
	/// Simple getter for data chunk pointer
	void* getData() { return data; }
	
	/// Simple getter for data size
	unsigned int getDataSize() { return dataSize; }
	
private:
	/// Data chunk pointer
	void *data;
	
	/// Size of data chunk
	unsigned int dataSize;
};

#endif /*QTLEAFATOM_H_*/
