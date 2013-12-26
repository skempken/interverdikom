#include "BaseOutputLink.h"

#include <iostream>

using std::make_pair;
using std::cout;
using std::endl;


namespace ivk
{

BaseOutputLink::BaseOutputLink(const int bufferSize, const ivector &capacity)
{
	m_bufferSize = bufferSize;
	m_capacity = capacity;
	m_tickCount = 0;
}

BaseOutputLink::~BaseOutputLink()
{
}

void BaseOutputLink::addOutFlow(Traffic* input, Traffic* output)
{
	m_inTraffics.push_back(input);
	m_outTraffics.insert(make_pair(input, output));
	ivector buffer(0, m_bufferSize);
	buffer[0] = interval(1.0);
	for(int i=1; i<=Ub(buffer); ++i)
		buffer[i] = interval(0.0);
	m_buffers.insert(make_pair(output, buffer));
}

ivector BaseOutputLink::computeStep(ivector &buffer, interval &loss, const ivector &arrival, const ivector &service)
{
	const int N = Ub(buffer);
	const int capacity = Ub(service);
	
	// Berechnung Puffer
	ivector buffer1(Lb(buffer), Ub(buffer));
	for(int i = Lb(buffer1); i<=Ub(buffer1); ++i)
	{
		buffer1[i] = 0.0;
	}
	
	// Neue Ankünfte in Puffer
	for(int i = Lb(buffer1); i<=Ub(buffer1); ++i)
	{
		idotprecision sum;
		sum = interval(0.0);
		for(int j = Lb(arrival); j<= std::min<int>(Ub(arrival),i); ++j) // Mehr rein als raus
		{
			accumulate(sum, buffer[i-j], arrival[j]);
		}
		buffer1[i] = rnd(sum);
	}
	
	// Überlauf / Verlustwahrscheinlichkeit
	loss = 0.0;
	idotprecision _loss;
	_loss = interval(0.0);
	for(int i = 0; i<Ub(arrival); ++i)
	{
		for(int j = i+1; j<=Ub(arrival); ++j)
		{ 
			accumulate(_loss, buffer[N-i],arrival[j]);
		}
	}
	loss = rnd(_loss);
	// Wenn Überlauf, dann Puffer ganz voll
	buffer1[N] += rnd(_loss);
	
	//// cout << "Puffer nach Ankunft:" << endl << buffer1 << endl;
	
	// Abgänge aus Puffer
	ivector depart(Lb(service), Ub(service));
	for(int i=Lb(depart); i<=Ub(depart); ++i)
		depart[i] = 0.0;
		
	ivector buffer2(Lb(buffer1), Ub(buffer1));
	for(int i=Lb(buffer2); i<=Ub(buffer2); ++i)
		buffer2[i] = 0.0;
		
	// Abgangsverteilung
	for(int k = Lb(depart); k<=Ub(depart); ++k)
	{
		idotprecision _depart;
		_depart = interval(0.0);
		
		for(int i=k; i<=Ub(service); ++i)
		{
			accumulate(_depart, buffer1[k], service[i]);
		}
		
		for(int j=k+1; j<=Ub(buffer1); ++j)
		{
			accumulate(_depart, service[k], buffer1[j]);
		}
		
		depart[k] = rnd(_depart);
	}
	
	// Buffer
	for(int k = 1; k<=Ub(buffer2); ++k)
	{
		idotprecision _buffer2;
		_buffer2 = interval(0.0);
		for(int i=0; i<=std::min<int>(Ub(service), Ub(buffer1)-k); ++i)
		{
			accumulate(_buffer2, service[i], buffer1[k+i]);
		}
		buffer2[k] = rnd(_buffer2);
	}
	idotprecision _buffer2;
	_buffer2 = interval(0.0);
	for(int i=Lb(service); i<=Ub(service); ++i)
	{
		for(int j=0; j<=i; ++j)
		{
			accumulate(_buffer2, service[i], buffer1[j]);
		}
	}
	buffer2[0] = rnd(_buffer2);
	
	//// cout << "Abgangswahrscheinlichkeiten: " << endl << depart << endl;
	//// cout << "Puffer nach Abgang: " << endl << buffer2 << endl;
	buffer = buffer2;
	return depart;
}

ivector BaseOutputLink::computeRemaining(ivector depart, ivector remainingCapacity)
{
	ivector remCap(remainingCapacity);
	for(int i=Lb(remCap); i<=Ub(remCap); ++i)
		remCap[i] = 0.0;
			
	idotprecision _remCap;
	_remCap = interval(0.0);
	
	for(int i=Lb(depart); i<=Ub(depart); ++i)
	{
		for(int j=0; j<=i; ++j)
		{
			accumulate(_remCap, depart[i], remainingCapacity[j]);
		} 
	}
	remCap[0] = rnd(_remCap);
		
	for(int j=1; j<=Ub(remCap); ++j)
	{
		_remCap = 0.0;
		for(int i=Lb(depart); i<=std::min<int>(Ub(depart), Ub(remainingCapacity)-j); ++i)
		{
			accumulate(_remCap, depart[i], remainingCapacity[j+i]);
		}
		remCap[j] = rnd(_remCap);
	}
	return remCap;
}


}
