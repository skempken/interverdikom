#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <QString>

class StringUtil
{
public:
	static QString extractFileNameFromPath(const QString & filePath);
};

#endif /*STRINGUTIL_H_*/
