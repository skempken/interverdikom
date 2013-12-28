#include "PFWorkloadWidget.h"

#include "modbase/DataProvider.hpp"

#include "module/WorkloadDistributionWidget.h"


FACTORY_DEFINITIONS_FOR(PFWorkloadWidget)


PFWorkloadWidget::PFWorkloadWidget()
{
	setupUi(this);
}

PFWorkloadWidget::~PFWorkloadWidget()
{
}

void PFWorkloadWidget::createActions() {
	
}

void PFWorkloadWidget::loadModel() {
}

void PFWorkloadWidget::initModel() {
	result = (dynamic_cast<DataProvider<ISMPPFResult>*>(parentModule))->getData();
}

void PFWorkloadWidget::on_computeButton_clicked() {
	addSubWidget(new WorkloadDistributionWidget(new IWorkloadVector(result->getWorkload(upToSpin->value()))), tr("Workload"));
}
