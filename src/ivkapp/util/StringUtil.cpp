#include "StringUtil.h"

QString StringUtil::extractFileNameFromPath(const QString & filePath)
{
	return filePath.right(filePath.size()- filePath.lastIndexOf(QString("/"))
			- 1);
}
