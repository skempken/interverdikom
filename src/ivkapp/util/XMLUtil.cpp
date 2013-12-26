#include "XMLUtil.h"

#include <sstream>
#include <QDomDocument>

using std::ostringstream;
using std::istringstream;

QDomElement XMLUtil::getOrCreateChild(QDomDocument document,
		QDomElement parent, QString childName) {
	QDomElement childElement = parent.namedItem(childName).toElement();
	if (childElement.isNull()) {
		childElement = document.createElement(childName);
		parent.appendChild(childElement);
	}

	return childElement;
}

real XMLUtil::xmlToReal(const QDomElement & domElement) {
	real result;
	istringstream isst(domElement.text().toStdString());
	isst >> result;
	return result;
}

int XMLUtil::xmlToInt(const QDomElement & domElement) {
	int result;
	istringstream isst(domElement.text().toStdString());
	isst >> result;
	return result;
}

rvector XMLUtil::xmlToRvector(const QDomElement & domElement) {
	rvector result;
	int lowerBound = domElement.attribute("lowerBound").toInt();
	int upperBound = domElement.attribute("upperBound").toInt();
	SetLb(result, lowerBound);
	SetUb(result, upperBound);
	Resize(result, upperBound - lowerBound + 1);
	for (QDomElement currEl = domElement.firstChild().toElement(); !currEl.isNull(); currEl
			= currEl.nextSiblingElement()) {
		if (currEl.tagName() != QString("RvectorValue"))
			continue;

		int vectorIndex = currEl.attribute("index").toInt();
		real vectorValue = xmlToReal(currEl);
		result[vectorIndex] = vectorValue;
	}

	return result;
}

intvector XMLUtil::xmlToIntvector(const QDomElement & domElement) {
	intvector result;
	int lowerBound = domElement.attribute("lowerBound").toInt();
	int upperBound = domElement.attribute("upperBound").toInt();
	SetLb(result, lowerBound);
	SetUb(result, upperBound);
	Resize(result, upperBound - lowerBound + 1);
	for (QDomElement currEl = domElement.firstChild().toElement(); !currEl.isNull(); currEl
			= currEl.nextSiblingElement()) {
		if (currEl.tagName() != QString("IntVectorValue"))
			continue;

		int vectorIndex = currEl.attribute("index").toInt();
		int vectorValue = xmlToInt(currEl);
		result[vectorIndex] = vectorValue;
	}

	return result;
}

rmatrix XMLUtil::xmlToRmatrix(const QDomElement & domElement) {
	int lowerBound1 = domElement.attribute("lowerBound1").toInt();
	int upperBound1 = domElement.attribute("upperBound1").toInt();
	int lowerBound2 = domElement.attribute("lowerBound2").toInt();
	int upperBound2 = domElement.attribute("upperBound2").toInt();

	rmatrix result(lowerBound1, upperBound1, lowerBound2, upperBound2);

	for (QDomElement currEl = domElement.firstChild().toElement(); !currEl.isNull(); currEl
			= currEl.nextSiblingElement()) {
		if (currEl.tagName() != QString("RMatrixValue"))
			continue;

		int rowIndex = currEl.attribute("row").toInt();
		int columnIndex = currEl.attribute("column").toInt();

		result[rowIndex][columnIndex] = xmlToReal(currEl);
	}

	return result;
}

interval XMLUtil::xmlToInterval(const QDomElement & domElement) {
	interval result;

	QDomElement infElement = domElement.namedItem("IntervalInf").toElement();
	SetInf(result, xmlToReal(infElement));

	QDomElement supElement = domElement.namedItem("IntervalSup").toElement();
	SetSup(result, xmlToReal(supElement));

	return result;
}

ivector XMLUtil::xmlToIvector(const QDomElement & domElement) {
	ivector result;

	int lowerBound = domElement.attribute("lowerBound").toInt();
	int upperBound = domElement.attribute("upperBound").toInt();

	SetLb(result, lowerBound);
	SetUb(result, upperBound);
	Resize(result, upperBound - lowerBound + 1);

	for (QDomElement currEl = domElement.firstChild().toElement(); !currEl.isNull(); currEl
			= currEl.nextSiblingElement()) {
		if (currEl.tagName() != QString("IVectorValue"))
			continue;

		int vectorIndex = currEl.attribute("index").toInt();
		interval vectorValue = xmlToInterval(currEl);
		result[vectorIndex] = vectorValue;
	}

	return result;
}

imatrix XMLUtil::xmlToImatrix(const QDomElement & domElement) {
	if (domElement.isNull()) {
		return imatrix();
	}

	int lowerBound1 = domElement.attribute("lowerBound1").toInt();
	int upperBound1 = domElement.attribute("upperBound1").toInt();
	int lowerBound2 = domElement.attribute("lowerBound2").toInt();
	int upperBound2 = domElement.attribute("upperBound2").toInt();

	imatrix result(lowerBound1, upperBound1, lowerBound2, upperBound2);

	for (QDomElement currEl = domElement.firstChild().toElement(); !currEl.isNull(); currEl
			= currEl.nextSiblingElement()) {
		if (currEl.tagName() != QString("IMatrixValue"))
			continue;

		int rowIndex = currEl.attribute("row").toInt();
		int columnIndex = currEl.attribute("column").toInt();

		result[rowIndex][columnIndex] = xmlToInterval(currEl);
	}
	
	return result;
}

SSMProcess XMLUtil::xmlToSSMProcess(const QDomElement & domElement) {
	QDomElement transitionElement = domElement.namedItem("TransitionMatrix").toElement();
	QDomElement distributionElement = domElement.namedItem("Distributions").toElement();

	return SSMProcess(xmlToImatrix(transitionElement),
			xmlToImatrix(distributionElement));
}

SSMPQueue XMLUtil::xmlToSSMPQueue(const QDomElement & domElement) {
	QDomElement arrivalElement = domElement.namedItem("ArrivalProcess").toElement();
	QDomElement serviceElement = domElement.namedItem("ServiceProcess").toElement();
	QString queueType = domElement.attribute("queueType");

	SSMProcess * arrivalProcess = new SSMProcess(xmlToSSMProcess(arrivalElement));
	SSMProcess * serviceProcess = new SSMProcess(xmlToSSMProcess(serviceElement));
	if (queueType == "Interarrival") {
		return *SSMPQueue::constructInterarrivalQueue(arrivalProcess, serviceProcess);
	} else {
		return *SSMPQueue::constructTimeSlottedQueue(arrivalProcess, serviceProcess);
	}
}

QDomElement XMLUtil::ssmpQueueToXml(const SSMPQueue & value,
		QDomDocument document) {
	QDomElement result = document.createElement("SSMPQueue");
	
	if (value.getQueueType() == SSMPQueue::Interarrival) {
		result.setAttribute("queueType", "Interarrival");
	} else {
		result.setAttribute("queueType", "TimeSlotted");
	}

	SSMProcess arrivalProcess = *(value.getArrivalProcess());
	QDomElement arrivalElement = ssmProcessToXml(arrivalProcess, document);
	arrivalElement.setTagName("ArrivalProcess");
	result.appendChild(arrivalElement);

	SSMProcess serviceProcess = *(value.getServiceProcess());
	QDomElement serviceElement = ssmProcessToXml(serviceProcess, document);
	serviceElement.setTagName("ServiceProcess");
	result.appendChild(serviceElement);

	return result;
}

QDomElement XMLUtil::ssmProcessToXml(const SSMProcess & value,
		QDomDocument document) {
	QDomElement result = document.createElement("SSMProcess");

	imatrix transitionMatrix = value.getTransitionMatrix();
	QDomElement transitionElement = imatrixToXml(transitionMatrix, document);
	transitionElement.setTagName("TransitionMatrix");
	result.appendChild(transitionElement);

	imatrix distributions = value.getDistributions();
	QDomElement distributionElement = imatrixToXml(distributions, document);
	distributionElement.setTagName("Distributions");
	result.appendChild(distributionElement);

	return result;
}

QDomElement XMLUtil::realToXml(const real & value, QDomDocument document) {
	QDomElement result = document.createElement("Real");
	std::string stringValue;
	stringValue << value;
	result.appendChild(document.createTextNode(QString::fromStdString(stringValue).trimmed()));
	return result;
}

QDomElement XMLUtil::intToXml(const int &value, QDomDocument document) {
	QDomElement result = document.createElement("Int");
	ostringstream stringValue;
	stringValue << value;
	result.appendChild(document.createTextNode(QString::fromStdString(stringValue.str()).trimmed()));
	return result;
}

QDomElement XMLUtil::rvectorToXml(const rvector & value, QDomDocument document) {
	QDomElement result = document.createElement("RVector");
	result.setAttribute("upperBound", Ub(value));
	result.setAttribute("lowerBound", Lb(value));
	for (int i = Lb(value); i <= Ub(value); i++) {
		QDomElement valueElement = realToXml(value[i], document);
		valueElement.setTagName("RvectorValue");
		valueElement.setAttribute("index", i);
		result.appendChild(valueElement);
	}
	return result;
}

QDomElement XMLUtil::rmatrixToXml(const rmatrix & value, QDomDocument document) {
	QDomElement result = document.createElement("RMatrix");

	int lowerBound1 = Lb(value, 1);
	int upperBound1 = Ub(value, 1);
	int lowerBound2 = Lb(value, 2);
	int upperBound2 = Ub(value, 2);

	result.setAttribute("lowerBound1", lowerBound1);
	result.setAttribute("upperBound1", upperBound1);
	result.setAttribute("lowerBound2", lowerBound2);
	result.setAttribute("upperBound2", upperBound2);

	for (int row = lowerBound1; row <= upperBound1; ++row) {
		for (int column = lowerBound2; column <= upperBound2; ++column) {
			QDomElement valueElement = XMLUtil::realToXml(value[row][column],
					document);

			valueElement.setTagName("RMatrixValue");
			valueElement.setAttribute("row", row);
			valueElement.setAttribute("column", column);

			result.appendChild(valueElement);
		}
	}

	return result;
}

QDomElement XMLUtil::intervalToXml(const interval & value, QDomDocument document) {
	QDomElement result = document.createElement("Interval");

	QDomElement infElement = realToXml(Inf(value), document);
	infElement.setTagName("IntervalInf");
	result.appendChild(infElement);

	QDomElement supElement = realToXml(Sup(value), document);
	supElement.setTagName("IntervalSup");
	result.appendChild(supElement);

	return result;
}

QDomElement XMLUtil::ivectorToXml(const ivector & value, QDomDocument document) {
	QDomElement result = document.createElement("IVector");

	result.setAttribute("upperBound", Ub(value));
	result.setAttribute("lowerBound", Lb(value));

	for (int i = Lb(value); i <= Ub(value); i++) {
		QDomElement valueElement = intervalToXml(value[i], document);
		valueElement.setTagName("IVectorValue");
		valueElement.setAttribute("index", i);
		result.appendChild(valueElement);
	}

	return result;
}

QDomElement XMLUtil::imatrixToXml(imatrix & value, QDomDocument document) {
	QDomElement result = document.createElement("IMatrix");

	int lowerBound1 = Lb(value, 1);
	int upperBound1 = Ub(value, 1);
	int lowerBound2 = Lb(value, 2);
	int upperBound2 = Ub(value, 2);

	result.setAttribute("lowerBound1", lowerBound1);
	result.setAttribute("upperBound1", upperBound1);
	result.setAttribute("lowerBound2", lowerBound2);
	result.setAttribute("upperBound2", upperBound2);

	for (int row = lowerBound1; row <= upperBound1; ++row) {
		for (int column = lowerBound2; column <= upperBound2; ++column) {
			QDomElement valueElement = XMLUtil::intervalToXml(
					value[row][column], document);

			valueElement.setTagName("IMatrixValue");
			valueElement.setAttribute("row", row);
			valueElement.setAttribute("column", column);

			result.appendChild(valueElement);
		}
	}

	return result;
}

QDomElement XMLUtil::intvectorToXml(const intvector & value,
		QDomDocument document) {
	QDomElement result = document.createElement("IntVector");
	result.setAttribute("upperBound", Ub(value));
	result.setAttribute("lowerBound", Lb(value));

	for (int i = Lb(value); i <= Ub(value); i++) {
		QDomElement valueElement = intToXml(value[i], document);
		valueElement.setTagName("IntVectorValue");
		valueElement.setAttribute("index", i);
		result.appendChild(valueElement);
	}

	return result;
}
