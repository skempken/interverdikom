
#if 0

#include "ServiceDistributionWidget.h"

#include "ProjectFile.h"
#include "ServiceDistributionEditPage.h"
#include "MainWindow.h"

ServiceDistributionWidget::ServiceDistributionWidget(QWidget* parent)
: DistributionWidget(parent)
{
	editPage = new ServiceDistributionEditPage(this);
	tabWidget->addTab(editPage, tr("Edit"));
}

ServiceDistributionWidget::~ServiceDistributionWidget()
{
}

void ServiceDistributionWidget::setFile(ProjectFile* openedFile)
{
	/*
	// refresh contents
	this->clearDistributions();
	
	SMPQueue* queue = openedFile->getSMPQueue();
	IntProbDist intDist = queue->getServiceDistribution();
	addIntervalDistribution(QString("Service"), intDist.getDistribution());
	
	editPage->updateValuesFromFile(openedFile);
	*/
}

#endif
