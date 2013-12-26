#include "AddServiceProcessWidget.h"

#include <QDoubleValidator>

#include "module/SSMPQueueDisplayWidget.h"

#include "module/ArrivalProcessDisplay.h"
#include "data/SSMProcess.h"
#include "data/GIProcess.h"
#include "data/SSMPQueue.h"

using ivk::SSMProcess;
using ivk::GIProcess;
using ivk::SSMPQueue;

FACTORY_DEFINITIONS_FOR(AddServiceProcessWidget)

AddServiceProcessWidget::AddServiceProcessWidget()
{
	setupUi(this);
}

AddServiceProcessWidget::~AddServiceProcessWidget()
{
}

void AddServiceProcessWidget::createActions()
{
}

void AddServiceProcessWidget::initModel()
{
	SSMProcess *process = ((ArrivalProcessDisplay*)parentModule)->getProcess();

	expectationValueEdit->setText(QString("%1").arg(_double(process->getExpectationValue())));
	standardDeviationEdit->setText(QString("%1").arg(_double(process->getStandardDeviation())));
	
	on_factorSpin_valueChanged(0.0);
}

void AddServiceProcessWidget::loadModel()
{
}

void AddServiceProcessWidget::on_addButton_clicked()
{
	
	capacitySpin->setEnabled(false);
	factorSpin->setEnabled(false);
	addButton->setEnabled(false);

	double averageCapacity = capacitySpin->value();
	int topState = (int)ceil(averageCapacity);
	int lowerState = (int)floor(averageCapacity);
	rvector distributionVector(0, topState);
	
	// TODO Validate whether generated vector is as intended
	for (int i = Lb(distributionVector); i <= Ub(distributionVector); i++)
	{
		if (i == lowerState)
		{
			distributionVector[i] = 1 - (averageCapacity - lowerState);
		}
		else if (i == topState)
		{
			distributionVector[i] = 1 - (topState - averageCapacity);
		}
		else
		{
			distributionVector[i] = 0;
		}
	}
	
	
	SSMProcess *arrivalProcess = ((ArrivalProcessDisplay*)parentModule)->getProcess();
	GIProcess *serviceProcess = new GIProcess(distributionVector);
	
	const SSMPQueue *smpQueue = SSMPQueue::constructTimeSlottedQueue(arrivalProcess, serviceProcess); 

	SSMPQueueDisplayWidget *display = new SSMPQueueDisplayWidget(smpQueue); 
	addSubWidget(display, tr("Model"));
}

void AddServiceProcessWidget::on_factorSpin_valueChanged(double newValue)
{
	double average = expectationValueEdit->text().toDouble();
	double deviation = standardDeviationEdit->text().toDouble();

	capacitySpin->setValue(average + newValue * deviation);
}

void AddServiceProcessWidget::on_capacitySpin_valueChanged(double newValue)
{
	double average = expectationValueEdit->text().toDouble();
	double deviation = standardDeviationEdit->text().toDouble();

	factorSpin->setValue((newValue - average) / deviation);
}
