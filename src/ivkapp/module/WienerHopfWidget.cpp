#include "WienerHopfWidget.h"

#include "SSMPQueueDisplayWidget.h"
#include "WHResultWidget.h"
#include "MainWindow.h"

#include <math.h>

FACTORY_DEFINITIONS_FOR(WienerHopfWidget)

WienerHopfWidget::WienerHopfWidget()
: ModuleWidget()
{
	setupUi(this);

	// Setup Computation object and connect to GUI button.
	thread = new ComputationThread<SMPWienerHopf>(&whComputation, this, computeButton);

	// Connect ComputationFinished signal to spawnResultWidget method.
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
	connect(thread, SIGNAL(message(QString)), MainWindow::getOutputConsole(), SLOT(printMessage(QString)));
	connect(thread, SIGNAL(exception(QString)), MainWindow::getOutputConsole(), SLOT(printError(QString)));
}

WienerHopfWidget::~WienerHopfWidget() {}

void WienerHopfWidget::initModel()
{
	// Create new parameter object
	ComputationParameters params;

	// Set default values
	params.setReal(SMPWienerHopf::PARAM_EPSILON, 1e-15);
	params.setInt(SMPWienerHopf::PARAM_NUMITERATIONS, 200);
	params.setInt(SMPWienerHopf::PARAM_RELAXATIONSTEPS, 0);

	// Use saveXXX methods to set to XML data.
	saveReal(SMPWienerHopf::PARAM_EPSILON, params.getReal(SMPWienerHopf::PARAM_EPSILON));
	saveInt(SMPWienerHopf::PARAM_NUMITERATIONS, params.getInt(SMPWienerHopf::PARAM_NUMITERATIONS));

	// Get parent data
	const SSMPQueue *queue = ((SSMPQueueDisplayWidget*) parentModule)->getSSMPQueue();

	whComputation = new SMPWienerHopf(queue, params);
}

void WienerHopfWidget::loadModel()
{
	// Get existing parameter object.
	ComputationParameters params = whComputation->getParameters();

	// Set parameters according to XML file data
	params.setReal(SMPWienerHopf::PARAM_EPSILON, loadReal(SMPWienerHopf::PARAM_EPSILON));
	params.setInt(SMPWienerHopf::PARAM_NUMITERATIONS, loadInt(SMPWienerHopf::PARAM_NUMITERATIONS));
	params.setInt(SMPWienerHopf::PARAM_RELAXATIONSTEPS, loadInt(SMPWienerHopf::PARAM_RELAXATIONSTEPS));

	// Set parameters for modeler.
	whComputation->setParameters(params);
}

void WienerHopfWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = whComputation->getParameters();

	// Convert epsilon from real to int
	int eps = (int) std::log10(_double(params.getReal(SMPWienerHopf::PARAM_EPSILON)));
	epsilon->setValue(eps);
	numIterations->setValue(params.getInt(SMPWienerHopf::PARAM_NUMITERATIONS));
}

void WienerHopfWidget::on_numIterations_valueChanged(int value)
{
	// Value has been changed. Update XML data and modeler parameters.

	// Use saveXXX methods to set to XML data.
	saveInt(SMPWienerHopf::PARAM_NUMITERATIONS, value);

	// update modeler parameters
	ComputationParameters params = whComputation->getParameters();
	params.setInt(SMPWienerHopf::PARAM_NUMITERATIONS, value);
	whComputation->setParameters(params);
}

void WienerHopfWidget::on_epsilon_valueChanged(int value)
{
	// Value has been changed. Update XML data and modeler parameters.

	// Compute real from int
	double eps = std::pow(10.0, value);
	// Use saveXXX methods to set to XML data.
	saveReal(SMPWienerHopf::PARAM_EPSILON, eps);

	// update modeler parameters
	ComputationParameters params = whComputation->getParameters();
	params.setReal(SMPWienerHopf::PARAM_EPSILON, eps);
	whComputation->setParameters(params);
}

void WienerHopfWidget::on_relaxationSpin_valueChanged(int value)
{
	// Value has been changed. Update XML data and modeler parameters.

	saveReal(SMPWienerHopf::PARAM_RELAXATIONSTEPS, value);

	// update modeler parameters
	ComputationParameters params = whComputation->getParameters();
	params.setReal(SMPWienerHopf::PARAM_RELAXATIONSTEPS, value);
	whComputation->setParameters(params);
}

void WienerHopfWidget::spawnResultWidget()
{
	// Add sub widget with resulting arrival process.
	addSubWidget(new WHResultWidget(thread->getResult()), tr("Phase distributions"));
}


