#include "SampleComputation.h"

#if 0

#include <sstream>
#include <iostream>

#include "rvector.hpp"

using namespace std;
using namespace cxsc;

SampleComputation::~SampleComputation() {}

QDomElement SampleComputation::exportXml(QDomDocument document)
{
	/*
	 
	// Create test rvector (1, 2, 3, 4)
	rvector rvtest; // Test rvector
	Resize(rvtest, 4);
	for (int i = 1; i <= 4; i++)
		rvtest[i] = i;
		
	// Create test ivector ((1,2), (2,3), (3,4), (4,5))
	ivector ivtest; // Test rvector
	Resize(ivtest, 4);
	for (int i = 1; i <= 4; i++)
		ivtest[i] = interval(i, i+1);
	
	// Create test rmatrix
	rmatrix rmtest;
	Resize(rmtest,3,5);
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 5; j++)
			rmtest[i][j] = i * j;
			
	// Create test imatrix
	imatrix imtest;
	Resize(imtest,3,5);
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 5; j++)
			imtest[i][j] = interval(i,i + j);
			
	elements["TestRVector"] = xml.rvectorToXml(rvtest);
	elements["TestRMatrix"] = xml.rmatrixToXml(rmtest);
	elements["TestIVector"] = xml.ivectorToXml(ivtest);
	elements["TestIMatrix"] = xml.imatrixToXml(imtest);
	

	
	// Utility typedef, collection of DOM elements
	XMLTools::ElementMap elements;
	
	// Generate XML and assign to element collection
	elements["Result"] = xml.realToXml(resultValue);
		
	// Return XML generated from joining the collection
	return xml.joinDomElements(elements);
		*/	
	
	return QDomElement();
}

void SampleComputation::importXml(QDomElement domElement)
{
	/*
	// Unserialize element collection
	XMLTools::ElementMap elements = XMLTools::splitDomElements(domElement);
	
	// Read in serialized values
	resultValue = xml.xmlToReal(elements["Result"]);
	
	
	rvector rvtest = xml.xmlToRvector(elements["TestRVector"]);
	rmatrix rmtest = xml.xmlToRmatrix(elements["TestRMatrix"]);
	ivector ivtest = xml.xmlToIvector(elements["TestIVector"]);
	imatrix imtest = xml.xmlToImatrix(elements["TestIMatrix"]);
	
	// TODO DEBUG REMOVEME test of rvector serialization
	cout << "SampleComputation: Unsserialized rvector (size " << VecLen(rvtest) << "): " << endl << rvtest;
	cout << "SampleComputation: Unsserialized rmatrix (size " << ColLen(rmtest) << " x " << RowLen(rmtest) << "): " << endl << rmtest;
	cout << "SampleComputation: Unsserialized ivector (size " << VecLen(ivtest) << "): " << endl << ivtest;
	cout << "SampleComputation: Unsserialized imatrix (size " << ColLen(imtest) << " x " << RowLen(imtest) << "): " << endl << imtest;
	*/
}

bool* SampleComputation::compute()
{
	/*
	// We've got 100000000 operations to count and are computing stuff
	setProgressMax(100000000);
	setProgressText("Computing stuff.");
	
	// Let's do some bogus calculations
	int i = 1;
	for (int j = 1; j <= 100000000; j++)
	{
		// Random operations to waste some CPU power
		i *= j;
		i += j;
		i *= j;
		
		// Update task text after 20000 operations
		if ((j % 1000000) == 0)
		{
			std::stringstream msgStream;
			setProgressValue(j);
    		msgStream << "Computing stuff step " << j / 1000000 << ".";
			setProgressText(msgStream.str());
		}
	}
	
	setProgressText("Finished.");
		
	// Increase result by one each time
	resultValue += 1;
	*/
	
	return new bool(true);
}

#endif
