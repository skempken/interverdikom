#ifndef ENDIANCONVERTER_H_
#define ENDIANCONVERTER_H_

#include <cstring>

/// Utility class for converting endianness
class EndianConverter
{
public:
	/// Static inline conversion of a normal 32 bit int
	/**
	 * \param original Integer to convert
	 * \return Conversion result
	 */
	static int convertInt(int original)
	{
		char org_buf[4], res_buf[4];
		memcpy(org_buf,&original,4);
		for (int i = 0; i < 4; i++)
			res_buf[i] = org_buf[3-i];
		return *((int*)res_buf);
	}
};

#endif /*ENDIANCONVERTER_H_*/
