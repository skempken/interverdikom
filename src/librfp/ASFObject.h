#ifndef ASFOBJECT_H_
#define ASFOBJECT_H_

#include <fstream>

/// 64-bit integer type
typedef long long QWORD;

/// Globally Unique Identifier string type
typedef char GUID[16];

/// Base class for all ASF objects, in itself "dummy" ASF object
/*
 * All specific ASF objects inherit from this class. However, this class itself may be used while parsing
 * to skip over uninteresting or unknown objects by initializing them as a generic ASFObject.
 */
class ASFObject
{
public:
	/// Destructor
	virtual ~ASFObject();

	/// Constructs an object from a file
	/*
	 * Calls the constructor of the appropriate subclass of ASFObject and
	 * initializes the resulting object with data from the file.
	 * \param file The file stream
	 */
	static ASFObject* constructFromFile(std::istream& file);

	/// Getter for guid
	GUID* getGUID()
	{
		return &this->guid;
	}

	/// Getter for size	
	QWORD getSize()
	{
		return this->size;
	}

	/// Constant for the ASF_Header_Object GUID
	static char ASF_Header_Object[16];

	/// Constant for the ASF_Data_Object GUID
	static char ASF_Data_Object[16];

	/// Constant for the ASF_Stream_Properties_Object GUID
	static char ASF_Stream_Properties_Object[16];

	/// Constant for the ASF_Extended_Stream_Properties_Object GUID
	static char ASF_Extended_Stream_Properties_Object[16];

	/// Constant for the ASF_File_Properties_Object GUID
	static char ASF_File_Properties_Object[16];

protected:
	/// Protected constructor to initialize object from file
	/*
	 * This will only be called by ASFObject::constructFromFile()
	 */
	ASFObject(const GUID guid, const QWORD size);

	/// Virtual function to read object data from file
	/**
	 * This function is called when the object is constructed from a file and used to initialize the
	 * object-specific data fields from the file stream.
	 * \param file The file stream
	 */
	virtual void getDataFromFile(std::istream &file);

	/// GUID of this object type
	GUID guid;

	/// Size (in bytes) of this object
	QWORD size;
};

#endif /*ASFOBJECT_H_*/
