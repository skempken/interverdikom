#ifndef LOGTEXTBUFFER_H_
#define LOGTEXTBUFFER_H_

#include <streambuf>
#include <cstdio>
#include <QMutex>

class LogTextField;

typedef enum {CoutBuf, CerrBuf} LogBufferType;

/// Custom streambuf for redirecting standard streams to GUI console
class LogTextBuffer : public std::streambuf
{
public:
	/// Default constructor
	/**
	 * \param outputField LogTextField to write the buffer into
	 * \param type CoutBuf or CerrBuff, determines text color in output field
	 */
	LogTextBuffer(LogTextField *outputField, LogBufferType type = CoutBuf);
	
	/// Destructor
	virtual ~LogTextBuffer();
	
private:
	/// Pointer to associated LogTextField 
	LogTextField *outputField;
	
	/// Type of this LogTextBuffer
	LogBufferType type;
	
	QMutex mutex;
	
protected:
	/// Custom overflow function, writes to attached LogTextField
	int overflow(int c = EOF);
};

#endif /*LOGTEXTBUFFER_H_*/
