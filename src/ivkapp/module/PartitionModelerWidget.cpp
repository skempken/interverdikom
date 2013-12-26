#include "PartitionModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "TraceDisplay.h"
#include "utility/RealUtils.h"

FACTORY_DEFINITIONS_FOR(PartitionModelerWidget)

PartitionModelerWidget::PartitionModelerWidget()
{
	setupUi(this);
	thread = new ComputationThread<PartitionModeler>(&modeler, this, computeButton, progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

PartitionModelerWidget::~PartitionModelerWidget()
{
}

void PartitionModelerWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(PartitionModeler::PARAM_NUMDSTEPS, loadInt(PartitionModeler::PARAM_NUMDSTEPS));
	numdstepsEdit->setValue(loadInt(PartitionModeler::PARAM_NUMDSTEPS));

	params.setInt(PartitionModeler::PARAM_NUMSTATES, loadInt(PartitionModeler::PARAM_NUMSTATES));
	numstatesEdit->setValue(loadInt(PartitionModeler::PARAM_NUMSTATES));

	modeler->setParameters(params);
}

void PartitionModelerWidget::initModel()
{
	int length = ((TraceDisplay*) parentModule)->getTrace()->getLength();
	numdstepsEdit->setMaximum( length );
	sliderDSteps->setMaximum( length );

	ComputationParameters params;
	params.setInt(PartitionModeler::PARAM_NUMDSTEPS, 1);
	params.setInt(PartitionModeler::PARAM_NUMSTATES, 1);

	const Trace *trace = ((TraceDisplay*) parentModule)->getTrace();
	modeler = new PartitionModeler(trace, params);

	params.setInt(PartitionModeler::PARAM_NUMDSTEPS, modeler->suggestNumDiscretizationSteps());
	params.setInt(PartitionModeler::PARAM_NUMSTATES, modeler->suggestNumStates());

	modeler->setParameters(params);
}

void PartitionModelerWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt(PartitionModeler::PARAM_NUMDSTEPS , params.getInt( PartitionModeler::PARAM_NUMDSTEPS ) );
	saveInt(PartitionModeler::PARAM_NUMSTATES , params.getInt( PartitionModeler::PARAM_NUMSTATES ) );
}

void PartitionModelerWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	numdstepsEdit->setValue(params.getInt(PartitionModeler::PARAM_NUMDSTEPS));
	numstatesEdit->setValue(params.getInt(PartitionModeler::PARAM_NUMSTATES));
}

void PartitionModelerWidget::createActions()
{

}

void PartitionModelerWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void PartitionModelerWidget::on_numdstepsEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(PartitionModeler::PARAM_NUMDSTEPS, newText.toInt());
	modeler->setParameters(params);

	saveInt(PartitionModeler::PARAM_NUMDSTEPS, newText.toInt());
}

void PartitionModelerWidget::on_numstatesEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(PartitionModeler::PARAM_NUMSTATES, newText.toInt());
	modeler->setParameters(params);

	saveInt(PartitionModeler::PARAM_NUMSTATES, newText.toInt());
}
