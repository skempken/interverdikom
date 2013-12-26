#ifndef COMPUTATIONTHREADBASE_H_
#define COMPUTATIONTHREADBASE_H_

#include <QThread>
#include "utility/BaseProgressListener.h"

class QProgressBar;
class QPushButton;
class QLabel;
class ModuleWidget;

/// Base class for the ComputationThread template
/**
 * This is the base class for the parameterized ComputationThread class.
 * This class is necessary since the QT MOC does not support parameterized classes
 * directly inheriting from QObject. Thus, this class contains the
 * unparameterized signal / slot functionality of ComputationThread.
 */
class ComputationThreadBase : public QThread, public ivk::AbstractProgressListener
{
	Q_OBJECT
	
public:
	/// Default constructor
	/**
	 * The constructor optionally takes a button, a progress bar and a label widget.
	 * The button is the one used to start the computation, the progress bar will
	 * be used in order to show the computation progress, and the label will be set
	 * up to display a description of the task which the computation is currently executing.
	 * The controls' relevant slots will automatically be connected to the thread's
	 * signals to achieve functionality as expected.
	 * 
	 * \param computeButton Button to start computation
	 * \param progressBar Progress bar to display progress
	 * \param taskLabel Label to display currently performed computation step 
	 */
	ComputationThreadBase(ModuleWidget *parentWidget, QPushButton *computeButton = 0,
			QProgressBar *progressBar = 0, QLabel *taskLabel = 0);
			
	/// Destructor
	virtual ~ComputationThreadBase() {};

	/// run() function to be implemented in ComputationThread subclass
	virtual void run() = 0;

	/// Implementation of ProgressListener::setTaskText()
	/**
	 * Emits the progressTextUpdate signal with the corresponding text
	 * as argument. Also updates the attached label if there is one.
	 * 
	 * \param text Textual description of currently performed action
	 */
	void updateProgressText(const std::string &text);
	
	/// Implementation of ProgressListener::setTaskMax()
	/**
	 * Emits the progressMaxUpdate signal with the corresponding new
	 * maximum value. Also updates the attached progress bar if there
	 * is one.
	 * 
	 * \param value The maximum progress value
	 */
	void updateProgressMax(const int &max);
	
	/// Implementation of ProgressListener::setTaskValue()
	/**
	 * Emits the progressUpdate signal with the corresponding new
	 * maximum value. Also updates the attached progress bar if there
	 * is one.
	 * 
	 * \param value The progress value
	 */
	void updateProgressValue(const int &value);
	
	void updateProgressETA(const int &eta);
	
protected:
	void enableParentWidget();
	
private:
	ModuleWidget *parentWidget;
	
	/// Attached button
	QPushButton *computeButton;
	
	/// Attached progress bar
	QProgressBar *progressBar;
	
	/// Attached label
	QLabel *taskLabel;
	
	/// Current label text
	QString m_taskLabelText;
	
	/// Current number of seconds left
	int m_secondsLeft;
	
	/// Emits signal to updates the task display label with a new text
	void updateProgressDisplay();
	
private slots:
	/// Enables the attached button
	void enableComputeButton();
	
	/// Disables the attached button
	void disableComputeButton();
	
	void disableParentWidget();
	
	void setProgressDone();
	
signals:
	/// Emitted as the attached computation triggers a maximum progress value update
	/**
	 * This signal will automatically be connected to the attached progress bar
	 * if there is one.
	 * 
	 * \param progressMaximum The new maximum value for progress measuring
	 */
	void progressMaxUpdate(int progressMaximum);
	
	/// Emitted as the attached computation triggers a progress update
	/**
	 * This signal will automatically be connected to the attached progress bar
	 * if there is one.
	 * 
	 * \param progressValue The new value indicating computation progress
	 */
	void progressUpdate(int progressValue);
	
	/// Emitted as the attached computation triggers a task description text update
	/**
	 * This signal will automatically be connected to the attached label if there is one.
	 * 
	 * \param taskText The new description
	 */
	void progressTextUpdate(QString taskText);
	
	/// Emitted as the attached computation triggers an exception
	/**
	 * \param message The exception message
	 */
	void exception(QString message);
	
	void message(QString message);
	
	void error(QString message);
	
	void computationFinished();
};

#endif /*COMPUTATIONTHREADBASE_H_*/
