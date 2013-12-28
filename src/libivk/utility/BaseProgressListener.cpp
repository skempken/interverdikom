#include "BaseProgressListener.h"

#include <iostream>
#include <sstream>
#include <ctime>
#include "StringUtils.h"

using namespace std;

namespace ivk
{

BaseProgressListener::BaseProgressListener()
{
	this->m_max = 0;
	this->m_eta = 0;
	this->m_currentTask = "";
}

BaseProgressListener::~BaseProgressListener()
{
}

void BaseProgressListener::updateProgressText(const std::string &text)
{
	m_currentTask = text;
}

void BaseProgressListener::updateProgressValue(const int &value)
{
	cout << m_currentTask << ": Step " << value << " of " << m_max << " (about " << StringUtils::formatTime(m_eta) << " left)" << endl;
}

void BaseProgressListener::updateProgressETA(const int &value)
{
	m_eta = value;
}

void BaseProgressListener::updateProgressMax(const int &value)
{
	this->m_max = value;
}

}
