#ifndef DATAPROVIDER_HPP_
#define DATAPROVIDER_HPP_

#include "DataProviderBase.h"

template<class D>
class DataProvider : public DataProviderBase
{
public:
	virtual const D* getData() = 0;
};

#endif /*DATAPROVIDER_HPP_*/
