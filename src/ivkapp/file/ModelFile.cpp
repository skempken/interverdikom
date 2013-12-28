#include "ModelFile.h"

#include <QFile>
#include <QDomDocument>
#include <QTextStream>

#include <iostream>

#include "XMLUtil.h"

#include "data/SSMPQueue.h"

using namespace std;

ModelFile::ModelFile()
{
}

ModelFile::~ModelFile()
{
}

SMPQueue * ModelFile::readSMPQueueFromFile(const QString &fileName)
{
	// TODO rethink file format
	return 0;
}

bool ModelFile::addServiceProcessToFile(const QString & fileName,
		double capacityAverage)
{
	// Parse document
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
		return false;

	QDomDocument doc;

	if (!doc.setContent(&file))
	{
		file.close();
		return false;
	}

	QDomElement serviceProcessElement = XMLUtil::getOrCreateChild(doc,
			doc.documentElement(), QString("ServiceProcess"));
	QDomElement giProcessElement = XMLUtil::getOrCreateChild(doc,
			serviceProcessElement, "GIProcess");
	QDomElement giDistributionElement = XMLUtil::getOrCreateChild(doc,
			giProcessElement, "GIDistribution");

	while (!giDistributionElement.firstChild().isNull())
		giDistributionElement.removeChild(giDistributionElement.firstChild());

	unsigned int numSteps = int(capacityAverage) + 2;

	giDistributionElement.setAttribute("steps", numSteps);

	for (unsigned int i = 0; i < numSteps; i++)
	{
		QDomElement newDistValueElement = doc.createElement("GIDistValue");
		newDistValueElement.setAttribute("step", i);

		double distValue;
		if (i == uint(capacityAverage))
			distValue = -(capacityAverage - i) + 1;
		else if (i == (uint(capacityAverage) + 1))
			distValue = (capacityAverage - i) + 1;
		else
			distValue = 0.0;

		newDistValueElement.appendChild(doc.createTextNode(QString("%1").arg(distValue)));

		giDistributionElement.appendChild(newDistValueElement);
	}

	QFile outputFile(fileName);
	if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
		return false;

	QTextStream outputStream(&outputFile);
	outputStream << doc.toString(2);
	outputFile.close();

	return true;
}

