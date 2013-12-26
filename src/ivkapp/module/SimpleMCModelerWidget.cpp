#include "SimpleMCModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "TraceDisplay.h"
#include "utility/RealUtils.h"

FACTORY_DEFINITIONS_FOR(SimpleMCModelerWidget)

SimpleMCModelerWidget::SimpleMCModelerWidget()
{
	setupUi(this);
	thread = new ComputationThread<SimpleMCModeler>(&modeler, this, computeButton, progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

SimpleMCModelerWidget::~SimpleMCModelerWidget()
{
}

void SimpleMCModelerWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(SimpleMCModeler::PARAM_NUMDSTEPS, loadInt(SimpleMCModeler::PARAM_NUMDSTEPS));
	numdstepsEdit->setValue(loadInt(SimpleMCModeler::PARAM_NUMDSTEPS));

	params.setInt(SimpleMCModeler::PARAM_NUMSTATES, loadInt(SimpleMCModeler::PARAM_NUMSTATES));
	numstatesEdit->setValue(loadInt(SimpleMCModeler::PARAM_NUMSTATES));

	modeler->setParameters(params);
}

void SimpleMCModelerWidget::initModel()
{
	int length = ((TraceDisplay*) parentModule)->getTrace()->getLength();
	numdstepsEdit->setMaximum( length );
	sliderDSteps->setMaximum( length );

	ComputationParameters params;
	params.setInt(SimpleMCModeler::PARAM_NUMDSTEPS, 1);
	params.setInt(SimpleMCModeler::PARAM_NUMSTATES, 1);

	const Trace *trace = ((TraceDisplay*) parentModule)->getTrace();
	modeler = new SimpleMCModeler(trace, params);

	params.setInt(SimpleMCModeler::PARAM_NUMDSTEPS, modeler->suggestNumDiscretizationSteps());
	params.setInt(SimpleMCModeler::PARAM_NUMSTATES, modeler->suggestNumStates());

	modeler->setParameters(params);
}

void SimpleMCModelerWidget::postCreation()
{
	ComputationParameters params = modeler->getParameters();
	saveInt( SimpleMCModeler::PARAM_NUMDSTEPS, params.getInt( SimpleMCModeler::PARAM_NUMDSTEPS ) );
	saveInt( SimpleMCModeler::PARAM_NUMSTATES, params.getInt( SimpleMCModeler::PARAM_NUMSTATES ) );
}

void SimpleMCModelerWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	numdstepsEdit->setValue(params.getInt(SimpleMCModeler::PARAM_NUMDSTEPS));
	numstatesEdit->setValue(params.getInt(SimpleMCModeler::PARAM_NUMSTATES));
}

void SimpleMCModelerWidget::createActions()
{

}

void SimpleMCModelerWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void SimpleMCModelerWidget::on_numdstepsEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(SimpleMCModeler::PARAM_NUMDSTEPS, newText.toInt());
	modeler->setParameters(params);

	saveInt(SimpleMCModeler::PARAM_NUMDSTEPS, newText.toInt());
}

void SimpleMCModelerWidget::on_numstatesEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(SimpleMCModeler::PARAM_NUMSTATES, newText.toInt());
	modeler->setParameters(params);

	saveInt(SimpleMCModeler::PARAM_NUMSTATES, newText.toInt());
}
