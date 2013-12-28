#include "ComputationThreadBase.h"

#include "ModuleWidget.h"
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>
#include <utility/StringUtils.h>

ComputationThreadBase::ComputationThreadBase(ModuleWidget *parentWidget,
		QPushButton *computeButton, QProgressBar *progressBar,
		QLabel *taskLabel) :
	parentWidget(parentWidget), computeButton(computeButton),
			progressBar(progressBar), taskLabel(taskLabel)
{
	m_secondsLeft = 0;
	m_taskLabelText = QString("");
	
	if (computeButton)
	{
		connect(computeButton, SIGNAL(clicked()), this, SLOT(start()));
		connect(this, SIGNAL(started()), this, SLOT(disableComputeButton()));
		connect(this, SIGNAL(started()), this, SLOT(disableParentWidget()));
		connect(this, SIGNAL(finished()), this, SLOT(enableComputeButton()));
	}

	if (progressBar)
	{
		connect(this,SIGNAL(progressMaxUpdate(int)),progressBar,SLOT(setMaximum(int)));
		connect(this,SIGNAL(progressUpdate(int
								)),progressBar,SLOT(setValue(int)));
							}
		connect(this, SIGNAL(computationFinished()), this, SLOT(setProgressDone()));

	if (taskLabel)
	{
		connect(this, SIGNAL(progressTextUpdate(QString)), taskLabel,
				SLOT(setText(QString)));
	}
}

void ComputationThreadBase::setProgressDone()
{
	if(progressBar)
	{
		emit progressMaxUpdate(1);
		emit progressUpdate(1);
	}
	if(taskLabel)
	{
		emit progressTextUpdate("Done.");
	}
}

void ComputationThreadBase::enableComputeButton()
{
	if (computeButton)
		computeButton->setEnabled(true);
}

void ComputationThreadBase::disableComputeButton()
{
	if (computeButton)
		computeButton->setEnabled(false);
}


void ComputationThreadBase::enableParentWidget()
{
	if (parentWidget)
	{
		parentWidget->setEnabled(true);
	}
}

void ComputationThreadBase::disableParentWidget()
{
	if (parentWidget)
	{
		parentWidget->setEnabled(false);
	}
}

void ComputationThreadBase::updateProgressDisplay()
{
	QString taskLabelText = m_taskLabelText;
	if(m_secondsLeft)
	{
		taskLabelText.append(" (");
		taskLabelText.append(QString::fromStdString(ivk::StringUtils::formatTime(m_secondsLeft)));
		taskLabelText.append(")");
	}
	emit progressTextUpdate(taskLabelText);
}

void ComputationThreadBase::updateProgressText(const std::string &text)
{
	m_taskLabelText = QString::fromStdString(text);
	updateProgressDisplay();
}

void ComputationThreadBase::updateProgressETA(const int &seconds)
{
	m_secondsLeft = seconds;
	updateProgressDisplay();
}

void ComputationThreadBase::updateProgressMax(const int &max)
{
	emit progressMaxUpdate(max);
}

void ComputationThreadBase::updateProgressValue(const int &value)
{
	emit progressUpdate(value);
}
