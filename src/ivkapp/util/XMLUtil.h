#ifndef XMLUTIL_H_
#define XMLUTIL_H_

#include <QDomElement>
#include <real.hpp>
#include <interval.hpp>
#include <rmatrix.hpp>
#include <imatrix.hpp>
#include <rvector.hpp>
#include <ivector.hpp>
#include <intvector.hpp>

#include "data/SSMProcess.h"
#include "data/SSMPQueue.h"

#include <map>
#include <string>

using cxsc::real;
using cxsc::interval;
using cxsc::rmatrix;
using cxsc::imatrix;
using cxsc::rvector;
using cxsc::ivector;
using cxsc::intvector;

using ivk::SSMProcess;
using ivk::SSMPQueue;

class XMLUtil
{
public:
	static QDomElement getOrCreateChild(QDomDocument document, QDomElement parent,
			QString childName);

	static real xmlToReal(const QDomElement & domElement);
	
	static int xmlToInt(const QDomElement & domElement);

	static rvector xmlToRvector(const QDomElement & domElement);

	static rmatrix xmlToRmatrix(const QDomElement & domElement);

	static interval xmlToInterval(const QDomElement & domElement);

	static ivector xmlToIvector(const QDomElement & domElement);

	static imatrix xmlToImatrix(const QDomElement & domElement);
	
	static intvector xmlToIntvector(const QDomElement & domElement);
	
	static SSMProcess xmlToSSMProcess(const QDomElement & domElement);
	
	static SSMPQueue xmlToSSMPQueue(const QDomElement & domElement);

	static QDomElement realToXml(const real & value, QDomDocument document);
	
	static QDomElement intToXml(const int & value, QDomDocument document);

	static QDomElement rvectorToXml(const rvector & value, QDomDocument document);

	static QDomElement rmatrixToXml(const rmatrix & value, QDomDocument document);

	static QDomElement intervalToXml(const interval & value, QDomDocument document);

	static QDomElement ivectorToXml(const ivector & value, QDomDocument document);

	static QDomElement imatrixToXml(imatrix & value, QDomDocument document);
	
	static QDomElement intvectorToXml(const intvector & value, QDomDocument document);
	
	static QDomElement ssmProcessToXml(const SSMProcess & value, QDomDocument document);
	
	static QDomElement ssmpQueueToXml(const SSMPQueue & value, QDomDocument document);
};

#endif /*XMLUTIL_H_*/
