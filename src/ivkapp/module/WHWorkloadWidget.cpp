#include "WHWorkloadWidget.h"

#include "WHResultWidget.h"
#include "WorkloadDistributionWidget.h"

#include <math.h>

FACTORY_DEFINITIONS_FOR(WHWorkloadWidget)

WHWorkloadWidget::WHWorkloadWidget()
: ModuleWidget()
{
	setupUi(this);
	
	// Setup Computation object and connect to GUI button.
	thread = new ComputationThread<ISMPWHWorkload>(&workloadComputation, this, computeButton);
	
	// Connect ComputationFinished signal to spawnResultWidget method.
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

WHWorkloadWidget::~WHWorkloadWidget() {}

void WHWorkloadWidget::initModel()
{
	// Create new parameter object
	ComputationParameters params;
	
	// Set default values
	params.setInt(ISMPWHWorkload::PARAM_UPTO, 1);
	
	// Use saveXXX methods to set to XML data.
	saveInt(ISMPWHWorkload::PARAM_UPTO, params.getInt(ISMPWHWorkload::PARAM_UPTO));
	
	// Get parent data
	const ISMPWHFactors *factors = ((WHResultWidget*) parentModule)->getISMPWHFactors();
	
	workloadComputation = new ISMPWHWorkload(factors, params);
}

void WHWorkloadWidget::loadModel()
{
	// Get existing parameter object.
	ComputationParameters params = workloadComputation->getParameters();
	
	// Set parameters according to XML file data
	params.setInt(ISMPWHWorkload::PARAM_UPTO, loadInt(ISMPWHWorkload::PARAM_UPTO));
	
	// Set parameters for modeler.
	workloadComputation->setParameters(params);
}

void WHWorkloadWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = workloadComputation->getParameters();
	
	// Convert epsilon from real to int
	upTo->setValue(params.getInt(ISMPWHWorkload::PARAM_UPTO));
}

void WHWorkloadWidget::on_upTo_valueChanged(int value)
{
	// Value has been changed. Update XML data and modeler parameters.
		
	// Use saveXXX methods to set to XML data.
	saveInt(ISMPWHWorkload::PARAM_UPTO, value);
	
	// update modeler parameters
	ComputationParameters params = workloadComputation->getParameters();
	params.setInt(ISMPWHWorkload::PARAM_UPTO, value);
	workloadComputation->setParameters(params);
}


void WHWorkloadWidget::spawnResultWidget()
{
	// Add sub widget with resulting arrival process.
	addSubWidget(new WorkloadDistributionWidget(thread->getResult()), tr("Workload distributions"));
}



