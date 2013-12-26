#ifndef MODELFILE_H_
#define MODELFILE_H_

#include <QString>

namespace ivk
{
class SMPQueue;
}

using namespace ivk;

class ModelFile
{
public:
	ModelFile();

	virtual ~ModelFile();

	static bool addServiceProcessToFile(const QString & fileName,
			double capacityAverage);

	static SMPQueue * readSMPQueueFromFile(const QString &fileName);
};

#endif /*MODELFILE_H_*/
