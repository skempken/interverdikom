#include "StatePartitioningWidget.h"
#include "ArrivalProcessDisplay.h"

FACTORY_DEFINITIONS_FOR(StatePartitioningWidget)

StatePartitioningWidget::StatePartitioningWidget()
{
	setupUi(this);
	thread = new ComputationThread<StatePartitioning>(&modeler, this, computeButton, progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

StatePartitioningWidget::~StatePartitioningWidget()
{
}

void StatePartitioningWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(StatePartitioning::PARAM_NUMCONTRACTIONS, loadInt(StatePartitioning::PARAM_NUMCONTRACTIONS));
	numContractions->setValue(loadInt(StatePartitioning::PARAM_NUMCONTRACTIONS));

	modeler->setParameters(params);
}

void StatePartitioningWidget::initModel()
{
	ComputationParameters params;
	params.setInt(StatePartitioning::PARAM_NUMCONTRACTIONS, 1);

	const SSMProcess *process = dynamic_cast<DataProvider<SSMProcess>*>(parentModule)->getData();
	modeler = new StatePartitioning(process, params);

	this->numContractions->setMaximum( process->getNumStates() );

	modeler->setParameters(params);
}

void StatePartitioningWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt(StatePartitioning::PARAM_NUMCONTRACTIONS , params.getInt( StatePartitioning::PARAM_NUMCONTRACTIONS ) );
}

void StatePartitioningWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	numContractions->setValue(params.getInt(StatePartitioning::PARAM_NUMCONTRACTIONS));
}

void StatePartitioningWidget::createActions()
{

}

void StatePartitioningWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void StatePartitioningWidget::on_numContractions_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(StatePartitioning::PARAM_NUMCONTRACTIONS, newText.toInt() );
	modeler->setParameters(params);

	saveInt(StatePartitioning::PARAM_NUMCONTRACTIONS, newText.toInt());
}
