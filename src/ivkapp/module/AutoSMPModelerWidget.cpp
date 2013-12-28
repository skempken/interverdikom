#include "AutoSMPModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "TraceDisplay.h"

FACTORY_DEFINITIONS_FOR(AutoSMPModelerWidget)

AutoSMPModelerWidget::AutoSMPModelerWidget()
{
	setupUi(this);
	thread = new ComputationThread<AutoSMPModeler>(&modeler, this, computeButton);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

AutoSMPModelerWidget::~AutoSMPModelerWidget()
{
}

void AutoSMPModelerWidget::loadModel()
{
	ComputationParameters params;
	
	params.setInt(AutoSMPModeler::PARAM_NUMDSTEPS, loadInt(AutoSMPModeler::PARAM_NUMDSTEPS));
	numdstepsEdit->setValue(loadInt(AutoSMPModeler::PARAM_NUMDSTEPS));
	
	params.setInt(AutoSMPModeler::PARAM_NUMSTATES, loadInt(AutoSMPModeler::PARAM_NUMSTATES));
	numstatesEdit->setValue(loadInt(AutoSMPModeler::PARAM_NUMSTATES));
		
	params.setInt(AutoSMPModeler::PARAM_CONFNIVEAU, loadInt(AutoSMPModeler::PARAM_CONFNIVEAU));
	confniveauEdit->setValue(loadInt(AutoSMPModeler::PARAM_CONFNIVEAU));
	
	modeler->setParameters(params);
}

void AutoSMPModelerWidget::initModel()
{
	ComputationParameters params;
	params.setInt(AutoSMPModeler::PARAM_NUMDSTEPS, 1);
	params.setInt(AutoSMPModeler::PARAM_NUMSTATES, 1);
	params.setInt(AutoSMPModeler::PARAM_CONFNIVEAU, 1);
	
	const Trace *trace = ((TraceDisplay*) parentModule)->getTrace();
	modeler = new AutoSMPModeler(trace, params);
}

void AutoSMPModelerWidget::createActions()
{
	
}

void AutoSMPModelerWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void AutoSMPModelerWidget::on_numdstepsEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(AutoSMPModeler::PARAM_NUMDSTEPS, newText.toInt());
	modeler->setParameters(params);
	
	saveInt(AutoSMPModeler::PARAM_NUMDSTEPS, newText.toInt());
}

void AutoSMPModelerWidget::on_numstatesEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(AutoSMPModeler::PARAM_NUMSTATES, newText.toInt());
	modeler->setParameters(params);
	
	saveInt(AutoSMPModeler::PARAM_NUMSTATES, newText.toInt());
}

void AutoSMPModelerWidget::on_confniveauEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(AutoSMPModeler::PARAM_CONFNIVEAU, newText.toInt());
	modeler->setParameters(params);
	
	saveInt(AutoSMPModeler::PARAM_CONFNIVEAU, newText.toInt());
}
