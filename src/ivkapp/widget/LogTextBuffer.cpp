#include "LogTextBuffer.h"

#include <iostream>

#include <QMutexLocker>

#include "LogTextField.h"

using namespace std;

LogTextBuffer::LogTextBuffer(LogTextField *outputField, LogBufferType type)
{
	this->outputField = outputField;
	this->type = type;
}

LogTextBuffer::~LogTextBuffer()
{
}

int LogTextBuffer::overflow(int c)
{
	QMutexLocker locker(&mutex);
	
	char cc = traits_type::to_char_type(c);
	
	if (type == CoutBuf)
		outputField->outputCout(cc);
	else if (type == CerrBuf)
		outputField->outputCerr(cc);
		
	return 1;
}
