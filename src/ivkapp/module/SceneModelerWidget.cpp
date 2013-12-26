#include "SceneModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "TraceDisplay.h"
#include "utility/RealUtils.h"

FACTORY_DEFINITIONS_FOR(SceneModelerWidget)

SceneModelerWidget::SceneModelerWidget()
{
	setupUi(this);
	thread = new ComputationThread<SceneModeler>(&modeler, this, computeButton , progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

SceneModelerWidget::~SceneModelerWidget()
{
}

void SceneModelerWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(SceneModeler::PARAM_NUMDSTEPS, loadInt(SceneModeler::PARAM_NUMDSTEPS));
	numdstepsEdit->setValue(loadInt(SceneModeler::PARAM_NUMDSTEPS));

	params.setReal(SceneModeler::PARAM_EPSILON, loadReal(SceneModeler::PARAM_EPSILON));
	epsilon->setValue(_double(loadReal(SceneModeler::PARAM_EPSILON)));

	params.setInt(AbstractDiscreteSSMPModeler::PARAM_NUMSTATES, 0);

	modeler->setParameters(params);
}

void SceneModelerWidget::initModel()
{
	int length = ((TraceDisplay*) parentModule)->getTrace()->getLength();
	numdstepsEdit->setMaximum( length );
	sliderDSteps->setMaximum( length );

	ComputationParameters params;
	params.setInt(SceneModeler::PARAM_NUMDSTEPS, 1);
	params.setInt(SceneModeler::PARAM_NUMSTATES, 1);
	params.setReal(SceneModeler::PARAM_EPSILON, 1.0);

	const Trace *trace = ((TraceDisplay*) parentModule)->getTrace();
	modeler = new SceneModeler(trace, params);

	params.setInt(SceneModeler::PARAM_NUMDSTEPS, modeler->suggestNumDiscretizationSteps());
	params.setInt(SceneModeler::PARAM_NUMSTATES, modeler->suggestNumStates());

	modeler->setParameters(params);
}

void SceneModelerWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt( SceneModeler::PARAM_NUMDSTEPS, params.getInt( SceneModeler::PARAM_NUMDSTEPS ) );
	saveInt( SceneModeler::PARAM_NUMSTATES, params.getInt( SceneModeler::PARAM_NUMSTATES ) );
	saveReal( SceneModeler::PARAM_EPSILON, params.getReal( SceneModeler::PARAM_EPSILON ) );
}

void SceneModelerWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	numdstepsEdit->setValue(params.getInt(SceneModeler::PARAM_NUMDSTEPS));
	epsilon->setValue(_double(params.getReal(SceneModeler::PARAM_EPSILON)));
}

void SceneModelerWidget::createActions()
{

}

void SceneModelerWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void SceneModelerWidget::on_numdstepsEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(SceneModeler::PARAM_NUMDSTEPS, newText.toInt());
	modeler->setParameters(params);

	saveInt(SceneModeler::PARAM_NUMDSTEPS, newText.toInt());
}

void SceneModelerWidget::on_epsilon_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setReal(SceneModeler::PARAM_EPSILON, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SceneModeler::PARAM_EPSILON, newText.toDouble());
}
