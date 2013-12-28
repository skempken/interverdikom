#ifndef CLASSFACTORY_H_
#define CLASSFACTORY_H_

// Concept used: http://www.codeproject.com/cpp/SimpleDynCreate.asp

#include <QString>
#include <map>
#include <vector>

template<typename BaseType, typename KeyType = QString,
		typename PredicateFunction = std::less<QString> > class ClassFactory
{
public:
	ClassFactory()
	{
	}

	virtual ~ClassFactory()
	{
	}

	typedef BaseType* (*CreatorFunctionType)(void);

	typedef std::map<KeyType, CreatorFunctionType, PredicateFunction>
			FactoryMapType;

	typedef std::vector<KeyType> RegisteredKeysVectorType;

	static KeyType registerClass(KeyType key,
			CreatorFunctionType creatorFunction)
	{
		getFactoryMap()->insert(std::pair<KeyType, CreatorFunctionType>(key, creatorFunction));
		getRegisteredKeys()->push_back(key);
		return key;
	}

	static BaseType* createInstance(KeyType idKey)
	{
		typename FactoryMapType::iterator it = getFactoryMap()->find(idKey);
		if (it != getFactoryMap()->end())
		{
			if (it->second)
			{
				return it->second();
			}
		}

		return 0;
	}

	static unsigned int getHue(KeyType idkey)
	{
		RegisteredKeysVectorType *keys = getRegisteredKeys();
		int size = keys->size();
		int index = 0;
		for (index = 0; index < size - 1; index++)
		{
			if (keys->at(index) == idkey)
			{
				break;
			}
		}

		return (index * 255) / size;
	}

protected:
	static FactoryMapType * getFactoryMap()
	{
		static FactoryMapType factoryMap;
		return &factoryMap;
	}

	static RegisteredKeysVectorType * getRegisteredKeys()
	{
		static RegisteredKeysVectorType keysVector;
		return &keysVector;
	}
};

#endif /*CLASSFACTORY_H_*/
