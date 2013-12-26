#include "RenewalModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "TraceDisplay.h"

FACTORY_DEFINITIONS_FOR(RenewalModelerWidget)

RenewalModelerWidget::RenewalModelerWidget()
{
	// call to Qt function to initialise GUI
	setupUi(this);

	// Setup Computation object and connect to GUI button.
	thread = new ComputationThread<RenewalModeler>(&modeler, this, computeButton, progressBar, progressLabel);

	// Connect ComputationFinished signal to spawnResultWidget method.
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

RenewalModelerWidget::~RenewalModelerWidget()
{
	// Nothing to do here.
}

void RenewalModelerWidget::loadModel()
{
	// Get existing parameter object.
	ComputationParameters params;

	// Set parameters according to XML file data
	params.setInt(RenewalModeler::PARAM_NUMDSTEPS, loadInt(RenewalModeler::PARAM_NUMDSTEPS));
	params.setInt(RenewalModeler::PARAM_NUMSTATES, loadInt(RenewalModeler::PARAM_NUMSTATES));

	// Set parameters for modeler.
	modeler->setParameters(params);
}

void RenewalModelerWidget::initModel()
{
	int length = ((TraceDisplay*) parentModule)->getTrace()->getLength();
	numdstepsEdit->setMaximum( length );
	sliderDSteps->setMaximum( length );
	// Create new parameter object
	ComputationParameters params;

	// Set default values
	params.setInt(AbstractDiscreteSSMPModeler::PARAM_NUMDSTEPS, 1);
	params.setInt(AbstractDiscreteSSMPModeler::PARAM_NUMSTATES, 1);

	// Get pointer to data object to work on
	const Trace *trace = ((TraceDisplay*) parentModule)->getTrace();

	// Create computation object with data object and parameters
	modeler = new RenewalModeler(trace, params);

	params.setInt(RenewalModeler::PARAM_NUMDSTEPS, modeler->suggestNumDiscretizationSteps());

	modeler->setParameters(params);
}

void RenewalModelerWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt( RenewalModeler::PARAM_NUMDSTEPS, params.getInt( RenewalModeler::PARAM_NUMDSTEPS ) );
	saveInt( RenewalModeler::PARAM_NUMSTATES, params.getInt( RenewalModeler::PARAM_NUMSTATES ) );
}

void RenewalModelerWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	int _tmp = params.getInt(RenewalModeler::PARAM_NUMDSTEPS);
	numdstepsEdit->setValue(_tmp);
}

void RenewalModelerWidget::createActions()
{
	// Set up actions to be available at this module
	// Nothing to do here, since it's a computation module.
}

void RenewalModelerWidget::spawnResultWidget()
{
	// Add sub widget with resulting arrival process.
	addSubWidget(new ArrivalProcessDisplay(thread->getResult()), tr("Arrival Process"));
}

void RenewalModelerWidget::on_numdstepsEdit_valueChanged(int value)
{
	// Value has been changed. Update XML data and modeler parameters.

	// update modeler parameters
	ComputationParameters params = modeler->getParameters();
	params.setInt(RenewalModeler::PARAM_NUMDSTEPS, value);
	modeler->setParameters(params);

	// Use saveXXX methods to set to XML data.
	saveInt(RenewalModeler::PARAM_NUMDSTEPS, value);
}
