#include "MMCModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "TraceDisplay.h"

FACTORY_DEFINITIONS_FOR(MMCModelerWidget)

MMCModelerWidget::MMCModelerWidget()
{
	setupUi(this);
	thread = new ComputationThread<MMCModeler>(&modeler, this, computeButton ,  progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

MMCModelerWidget::~MMCModelerWidget()
{
}

void MMCModelerWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(MMCModeler::PARAM_NUMDSTEPS, loadInt(MMCModeler::PARAM_NUMDSTEPS));
	numdstepsEdit->setValue(loadInt(MMCModeler::PARAM_NUMDSTEPS));

	params.setInt(MMCModeler::PARAM_W, loadInt(MMCModeler::PARAM_W));
	wEdit->setValue(loadInt(MMCModeler::PARAM_W));

	params.setInt(MMCModeler::PARAM_MS, loadInt(MMCModeler::PARAM_MS));
	MsEdit->setValue(loadInt(MMCModeler::PARAM_MS));

	params.setInt(MMCModeler::PARAM_MA, loadInt(MMCModeler::PARAM_MA));
	MaEdit->setValue(loadInt(MMCModeler::PARAM_MA));

	modeler->setParameters(params);
}

void MMCModelerWidget::initModel()
{
	int length = ((TraceDisplay*) parentModule)->getTrace()->getLength();
	wEdit->setMaximum( length );
	sliderW->setMaximum( length );
	numdstepsEdit->setMaximum( length );
	sliderDSteps->setMaximum( length );



	ComputationParameters params;
	params.setInt(MMCModeler::PARAM_NUMDSTEPS, 1);
	params.setInt(MMCModeler::PARAM_NUMSTATES, 1);
	params.setInt(MMCModeler::PARAM_W, 1);
	params.setInt(MMCModeler::PARAM_MA, 1);
	params.setInt(MMCModeler::PARAM_MS, 1);

	const Trace *trace = ((TraceDisplay*) parentModule)->getTrace();
	modeler = new MMCModeler(trace, params);

	params.setInt(MMCModeler::PARAM_NUMDSTEPS, modeler->suggestNumDiscretizationSteps());
	params.setInt(MMCModeler::PARAM_MA, (int)sqrt(modeler->suggestNumStates()));
	params.setInt(MMCModeler::PARAM_MS, (int)sqrt(modeler->suggestNumStates()));

	modeler->setParameters(params);
}

void MMCModelerWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt( MMCModeler::PARAM_NUMDSTEPS, params.getInt( MMCModeler::PARAM_NUMDSTEPS ) );
	saveInt( MMCModeler::PARAM_NUMSTATES, params.getInt( MMCModeler::PARAM_NUMSTATES ) );
	saveInt( MMCModeler::PARAM_W, params.getInt( MMCModeler::PARAM_W ) );
	saveInt( MMCModeler::PARAM_MA, params.getInt( MMCModeler::PARAM_MA ) );
	saveInt( MMCModeler::PARAM_MS, params.getInt( MMCModeler::PARAM_MS ) );
}

void MMCModelerWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	numdstepsEdit->setValue(params.getInt(MMCModeler::PARAM_NUMDSTEPS));
	wEdit->setValue(params.getInt(MMCModeler::PARAM_W));
	MsEdit->setValue(params.getInt(MMCModeler::PARAM_MS));
	MaEdit->setValue(params.getInt(MMCModeler::PARAM_MA));
}

void MMCModelerWidget::createActions()
{

}

void MMCModelerWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void MMCModelerWidget::on_numdstepsEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(MMCModeler::PARAM_NUMDSTEPS, newText.toInt());
	modeler->setParameters(params);

	saveInt(MMCModeler::PARAM_NUMDSTEPS, newText.toInt());
}

void MMCModelerWidget::on_wEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(MMCModeler::PARAM_W, newText.toInt());
	modeler->setParameters(params);

	saveInt(MMCModeler::PARAM_W, newText.toInt());
}

void MMCModelerWidget::on_MaEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(MMCModeler::PARAM_MA, newText.toInt());
	modeler->setParameters(params);

	saveInt(MMCModeler::PARAM_MA, newText.toInt());
}

void MMCModelerWidget::on_MsEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(MMCModeler::PARAM_MS, newText.toInt());
	modeler->setParameters(params);

	saveInt(MMCModeler::PARAM_MS, newText.toInt());
}
