#include "LogTextField.h"

#include <iostream>

#include "LogTextBuffer.h"

using namespace std;

LogTextField::LogTextField(QWidget *parent) :
	QTextEdit(parent) {
	// NOTE: Comment out here to direct output to console.
	coutBuffer = new LogTextBuffer(this,CoutBuf);
	cerrBuffer = new LogTextBuffer(this,CerrBuf);
	// cout.rdbuf(coutBuffer);
	// cerr.rdbuf(cerrBuffer);

	connect(this, SIGNAL(signalMessage(const QString &)), this, SLOT(printMessage(const QString &)));
	connect(this, SIGNAL(signalError(const QString &)), this, SLOT(printError(const QString &)));
}

LogTextField::~LogTextField() {
}

void LogTextField::printMessage(const QString & text) {
	moveCursor(QTextCursor::End);
	setTextColor(QColor(QString("black")));
	textCursor().insertText(text);
	textCursor().insertText("\n");
}

void LogTextField::printError(const QString & text) {
	moveCursor(QTextCursor::End);
	setTextColor(QColor(QString("red")));
	textCursor().insertText(text);
	textCursor().insertText("\n");
}

void LogTextField::outputCout(char c) {
	coutBufferStr += c;
	if (c == '\n') {
		signalMessage(coutBufferStr);
		coutBufferStr = "";
	}
}

void LogTextField::outputCerr(char c) {
	cerrBufferStr += c;
	if (c == '\n') {
		signalError(cerrBufferStr);
		cerrBufferStr = "";
	}
}
