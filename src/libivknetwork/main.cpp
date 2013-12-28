#include "Traffic.h"
#include "TrafficNode.h"

#include <interval.hpp>
#include <iostream>
#include <fstream>

using cxsc::ivector;
using std::endl;
using std::cout;
using std::ostream;
using std::ofstream;
using namespace ivk;
using namespace cxsc;

void printCSV(const ivector &vector, ostream &out)
{
	out << cxsc::SetPrecision(12,11);
	for(int i = Lb(vector); i<=Ub(vector)-1; ++i)
	{
		out << (Inf(vector[i])+Sup(vector[i]))/2 << "\t";
	}
	out << (Inf(vector[Ub(vector)])+Sup(vector[Ub(vector)]))/2 << "\n";	
}

int main(int argc, char **argv) {
	// cout << cxsc::SetPrecision(15,14);

	/* Example 1: Tandem queue
	// Arrival
	const int g = 50;
	ivector arrival(0,g);
	for(int i = Lb(arrival); i<=Ub(arrival); ++i) arrival[i] = 0.0;
	arrival[10] = interval(0.8,0.8);
	arrival[50] = interval(0.2,0.2);
	
	// Service 1
	ivector service1(0,30);
	for(int i = Lb(service1); i<=Ub(service1); ++i) service1[i] = 0.0;
	service1[15] = interval(0.4, 0.4);
	service1[30] = interval(0.6, 0.6);
	
	// Service 2
	ivector service2(0,25);
	for(int i = Lb(service2); i<=Ub(service2); ++i) service2[i] = 0.0;
	service2[15] = interval(0.4, 0.4);
	service2[25] = interval(0.6, 0.6);
	
	// Tandem queue
	Traffic* ptrArrival = new Traffic(arrival);
	TrafficNode Q1;
	TrafficNode Q2;
	TrafficNode senke;
	Q1.addOutputLink(&Q2, 2000, service1, TrafficNode::Ordered);
	Q2.addOutputLink(&senke, 2000, service2, TrafficNode::Ordered);
	
	Traffic* outFlow1 = Q1.addTrafficFlow(ptrArrival, &Q2);
	Traffic* outFlow2 = Q2.addTrafficFlow(outFlow1, &senke);
	
	// Output
	ofstream O1;
	O1.open("O1.csv");
	ofstream O2;
	O2.open("O2.csv");
	ofstream L1;
	L1.open("L1.csv");
	ofstream L2;
	L2.open("L2.csv");

	
	for(int i=0; i<1000; ++i)
	{
		cout << i << endl;
		Q1.tick();
		Q2.tick();
		printCSV(outFlow1->getDistribution(), O1);
		printCSV(outFlow2->getDistribution(), O2);
		interval loss;
		loss = outFlow1->getLoss(); 
		L1 << mid(loss) << endl;
		loss = outFlow2->getLoss();
		L2 << mid(loss) << endl;
	}
	
	*/
	// Example 2: Multiple streams
	
	// Arrival distribution
	const int g = 5;
	ivector arrival(0,g);
	for(int i = Lb(arrival); i<=Ub(arrival); ++i) arrival[i] = 0.0;
	arrival[1] = interval(0.5);
	arrival[5] = interval(0.5);
	// correct arrival
	interval _accu;
	_accu = interval(0.0);
	for(int i=Lb(arrival); i<=Ub(arrival); ++i)
		_accu += arrival[i];
	//arrival[1] -= interval(1.0) - rnd(_accu); 
	// cout << "Arrival: " << _accu << endl << arrival << endl;
	Traffic* ptrArrival1 = new Traffic(arrival);
	Traffic* ptrArrival2 = new Traffic(arrival);
	Traffic* ptrArrival3 = new Traffic(arrival);
	
	// Service distribution
	const int h = 10;
	ivector capacity(0,h);
	for(int i = Lb(capacity); i<=Ub(capacity); ++i) capacity[i] = 0.0;
	capacity[10] = 1.0;
	
	
	TrafficNode node;
	TrafficNode senke;
	
	node.addOutputLink(&senke, 2000, capacity, TrafficNode::Ordered);
	Traffic* outFlow1 = node.addTrafficFlow(ptrArrival1, &senke);
	Traffic* outFlow2 = node.addTrafficFlow(ptrArrival2, &senke);
	Traffic* outFlow3 = node.addTrafficFlow(ptrArrival3, &senke);
	
	// Output
	ofstream O1;
	O1.open("O1.csv");
	ofstream O2;
	O2.open("O2.csv");
	ofstream O3;
	O3.open("O3.csv");
	ofstream L1;
	L1.open("L1.csv");
	ofstream L2;
	L2.open("L2.csv");
	ofstream L3;
	L3.open("L3.csv");
	
	for(int i=0; i<1000; ++i)
	{
		cout << i << endl;
		node.tick();
		printCSV(outFlow1->getDistribution(), O1);
		printCSV(outFlow2->getDistribution(), O2);
		printCSV(outFlow3->getDistribution(), O3);
		interval loss;
		loss = outFlow1->getLoss(); 
		L1 << mid(loss) << endl;
		loss = outFlow2->getLoss();
		L2 << mid(loss) << endl;
		loss = outFlow3->getLoss();
		L3 << mid(loss) << endl;
	}
	O1.close();
	O2.close();
	O3.close();
	L1.close();
	L2.close();
	L3.close();
	
	
}
