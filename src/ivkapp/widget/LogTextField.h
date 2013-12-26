#ifndef LOGTEXTFIELD_H_
#define LOGTEXTFIELD_H_

#include <QTextEdit>

#include <sstream>

class LogTextBuffer;

/// Custom text field which logs standard stream data
class LogTextField : public QTextEdit
{
	Q_OBJECT
	
public:
	/// Default constructor
	LogTextField(QWidget *parent = 0);
	
	/// Destructor
	virtual ~LogTextField();
	
public slots:
	void printMessage(const QString & text);
	
	void printError(const QString & text);
	
private:
	/// Helper function: Writes a character from standard output stream
	void outputCout(char c);
	
	/// Helper function: Writes a character from standard error stream
	void outputCerr(char c);
	
	/// Custom standard output stream buffer
	LogTextBuffer *coutBuffer;
	
	/// Custom standard error stream buffer
	LogTextBuffer *cerrBuffer;
	
	friend class LogTextBuffer;
	
	QString coutBufferStr;
	
	QString cerrBufferStr;
	
signals:
	void signalMessage(const QString & text);
	
	void signalError(const QString & text);
};

#endif /*LOGTEXTFIELD_H_*/
