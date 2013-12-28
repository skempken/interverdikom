#include "RepeatedStateContractionsWidget.h"
#include "ArrivalProcessDisplay.h"

FACTORY_DEFINITIONS_FOR(RepeatedStateContractionsWidget)

RepeatedStateContractionsWidget::RepeatedStateContractionsWidget()
{
	setupUi(this);
	thread = new ComputationThread<RepeatedStateContractions>(&modeler, this, computeButton, progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

RepeatedStateContractionsWidget::~RepeatedStateContractionsWidget()
{
}

void RepeatedStateContractionsWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(RepeatedStateContractions::PARAM_NUMCONTRACTIONS, loadInt(RepeatedStateContractions::PARAM_NUMCONTRACTIONS));
	numContractions->setValue(loadInt(RepeatedStateContractions::PARAM_NUMCONTRACTIONS));

	modeler->setParameters(params);
}

void RepeatedStateContractionsWidget::initModel()
{
	ComputationParameters params;
	params.setInt(RepeatedStateContractions::PARAM_NUMCONTRACTIONS, 1);

	const SSMProcess *process = dynamic_cast<DataProvider<SSMProcess>*>(parentModule)->getData();
	modeler = new RepeatedStateContractions(process, params);

	modeler->setParameters(params);
}

void RepeatedStateContractionsWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt(RepeatedStateContractions::PARAM_NUMCONTRACTIONS , params.getInt( RepeatedStateContractions::PARAM_NUMCONTRACTIONS ) );
}

void RepeatedStateContractionsWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	numContractions->setValue(params.getInt(RepeatedStateContractions::PARAM_NUMCONTRACTIONS));
}

void RepeatedStateContractionsWidget::createActions()
{

}

void RepeatedStateContractionsWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void RepeatedStateContractionsWidget::on_numContractions_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(RepeatedStateContractions::PARAM_NUMCONTRACTIONS, newText.toInt());
	modeler->setParameters(params);

	saveInt(RepeatedStateContractions::PARAM_NUMCONTRACTIONS, newText.toInt());
}
