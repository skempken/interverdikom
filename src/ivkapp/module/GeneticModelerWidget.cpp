#include "GeneticModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "DataProvider.hpp"
#include "data/Trace.h"
#include "MainWindow.h"

FACTORY_DEFINITIONS_FOR(GeneticModelerWidget)

GeneticModelerWidget::GeneticModelerWidget()
{
	setupUi(this);
	thread = new ComputationThread<GeneticModeler>(&modeler, this, computeButton , progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
	connect(thread, SIGNAL(message(QString)), MainWindow::getOutputConsole(), SLOT(printMessage(QString)));
	connect(thread, SIGNAL(exception(QString)), MainWindow::getOutputConsole(), SLOT(printError(QString)));

	/*
	CyclePeriodWizard* neuesWidget = new CyclePeriodWizard();
	addSubWidget(neuesWidget, tr("Cylce Period Wizard"));
	connect(neuesWidget, SIGNAL(on_intervalEdit_valueChanged(QString)), this, SLOT(on_framelevel_valueChanged(QString)));
	*/
}

GeneticModelerWidget::~GeneticModelerWidget()
{
}

void GeneticModelerWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(GeneticModeler::PARAM_NUMDSTEPS, loadInt(GeneticModeler::PARAM_NUMDSTEPS));
	numdstepsEdit->setValue(loadInt(GeneticModeler::PARAM_NUMDSTEPS));

	params.setInt(GeneticModeler::PARAM_NUMSTATES, loadInt(GeneticModeler::PARAM_NUMSTATES));
	numstatesEdit->setValue(loadInt(GeneticModeler::PARAM_NUMSTATES));

	params.setInt(GeneticModeler::PARAM_AUTOC, loadInt(GeneticModeler::PARAM_AUTOC));
	numautocEdit->setValue(loadInt(GeneticModeler::PARAM_AUTOC));

	params.setInt(GeneticModeler::PARAM_NUMITERATIONS, loadInt(GeneticModeler::PARAM_NUMITERATIONS));
	numiterationsEdit->setValue(loadInt(GeneticModeler::PARAM_NUMITERATIONS));

	params.setInt(GeneticModeler::PARAM_NUMPOOLSIZE, loadInt(GeneticModeler::PARAM_NUMPOOLSIZE));
	numpoolEdit->setValue(loadInt(GeneticModeler::PARAM_NUMPOOLSIZE));

	params.setReal(GeneticModeler::PARAM_MUTBLOCK, loadReal(GeneticModeler::PARAM_MUTBLOCK));
	mutBlock->setValue(_double ( loadReal(GeneticModeler::PARAM_MUTBLOCK) ));

	params.setReal(GeneticModeler::PARAM_MUTINVERSE, loadReal(GeneticModeler::PARAM_MUTINVERSE));
	mutInverse->setValue(_double ( loadReal(GeneticModeler::PARAM_MUTINVERSE) ));

	params.setReal(GeneticModeler::PARAM_MUTSHUFFLE, loadReal(GeneticModeler::PARAM_MUTSHUFFLE));
	mutShuffle->setValue(_double ( loadReal(GeneticModeler::PARAM_MUTSHUFFLE) ));

	params.setReal(GeneticModeler::PARAM_MUTSWAP, loadReal(GeneticModeler::PARAM_MUTSWAP));
	mutSwap->setValue(_double ( loadReal(GeneticModeler::PARAM_MUTSWAP) ));

	params.setReal(GeneticModeler::PARAM_MUTCROSSOVER, loadReal(GeneticModeler::PARAM_MUTCROSSOVER));
	mutCrossover->setValue(_double ( loadReal(GeneticModeler::PARAM_MUTCROSSOVER) ));

	modeler->setParameters(params);
}

void GeneticModelerWidget::initModel()
{
	ComputationParameters params;
	params.setInt(GeneticModeler::PARAM_NUMDSTEPS, 1);
	params.setInt(GeneticModeler::PARAM_NUMSTATES, 1);
	params.setInt(GeneticModeler::PARAM_AUTOC, 1);
	params.setInt(GeneticModeler::PARAM_NUMITERATIONS, 10);
	params.setInt(GeneticModeler::PARAM_NUMPOOLSIZE, 10);
	params.setReal(GeneticModeler::PARAM_MUTBLOCK, 0.1);
	params.setReal(GeneticModeler::PARAM_MUTINVERSE, 0.2);
	params.setReal(GeneticModeler::PARAM_MUTSHUFFLE, 0.3);
	params.setReal(GeneticModeler::PARAM_MUTSWAP, 0.4);
	params.setReal(GeneticModeler::PARAM_MUTCROSSOVER, 0.5);

	const Trace *trace = dynamic_cast<DataProvider<Trace>*>(parentModule)->getData();

	modeler = new GeneticModeler(trace, params);
	int length = trace->getLength();
	numdstepsEdit->setMaximum( length );
	sliderDSteps->setMaximum( length );
	numautocEdit->setMaximum( length );
	sliderAutoc->setMaximum( length );



	params.setInt(GeneticModeler::PARAM_NUMDSTEPS, modeler->suggestNumDiscretizationSteps());
	params.setInt(GeneticModeler::PARAM_NUMSTATES, modeler->suggestNumStates());
	params.setInt(GeneticModeler::PARAM_AUTOC, modeler->suggestNumStates());

	modeler->setParameters(params);
}

void GeneticModelerWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt( GeneticModeler::PARAM_NUMDSTEPS , params.getInt( GeneticModeler::PARAM_NUMDSTEPS ) );
	saveInt( GeneticModeler::PARAM_NUMSTATES , params.getInt( GeneticModeler::PARAM_NUMSTATES ) );
	saveInt( GeneticModeler::PARAM_AUTOC , params.getInt( GeneticModeler::PARAM_AUTOC ) );
	saveInt( GeneticModeler::PARAM_NUMITERATIONS , params.getInt( GeneticModeler::PARAM_NUMITERATIONS ) );
	saveInt( GeneticModeler::PARAM_NUMPOOLSIZE , params.getInt( GeneticModeler::PARAM_NUMPOOLSIZE ) );
	saveReal( GeneticModeler::PARAM_MUTBLOCK , params.getReal( GeneticModeler::PARAM_MUTBLOCK ) );
	saveReal( GeneticModeler::PARAM_MUTINVERSE , params.getReal( GeneticModeler::PARAM_MUTINVERSE ) );
	saveReal( GeneticModeler::PARAM_MUTSHUFFLE , params.getReal( GeneticModeler::PARAM_MUTSHUFFLE ) );
	saveReal( GeneticModeler::PARAM_MUTSWAP , params.getReal( GeneticModeler::PARAM_MUTSWAP ) );
	saveReal( GeneticModeler::PARAM_MUTCROSSOVER , params.getReal( GeneticModeler::PARAM_MUTCROSSOVER ) );
}

void GeneticModelerWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	numstatesEdit->setValue(params.getInt(GeneticModeler::PARAM_NUMSTATES));
	numdstepsEdit->setValue(params.getInt(GeneticModeler::PARAM_NUMDSTEPS));
	numautocEdit->setValue(params.getInt(GeneticModeler::PARAM_AUTOC));
	numiterationsEdit->setValue(params.getInt(GeneticModeler::PARAM_NUMITERATIONS));
	numpoolEdit->setValue(params.getInt(GeneticModeler::PARAM_NUMPOOLSIZE));
	mutBlock->setValue( _double( params.getReal( GeneticModeler::PARAM_MUTBLOCK) ) );
	mutInverse->setValue( _double( params.getReal( GeneticModeler::PARAM_MUTINVERSE) ) );
	mutShuffle->setValue( _double( params.getReal( GeneticModeler::PARAM_MUTSHUFFLE) ) );
	mutSwap->setValue( _double( params.getReal( GeneticModeler::PARAM_MUTSWAP) ) );
	mutCrossover->setValue( _double( params.getReal( GeneticModeler::PARAM_MUTCROSSOVER) ) );
}

void GeneticModelerWidget::createActions()
{

}

void GeneticModelerWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void GeneticModelerWidget::on_numdstepsEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticModeler::PARAM_NUMDSTEPS, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticModeler::PARAM_NUMDSTEPS, newText.toInt());
}

void GeneticModelerWidget::on_numstatesEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticModeler::PARAM_NUMSTATES, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticModeler::PARAM_NUMSTATES, newText.toInt());
}

void GeneticModelerWidget::on_numautocEdit_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticModeler::PARAM_AUTOC, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticModeler::PARAM_AUTOC, newText.toInt());
}

void GeneticModelerWidget::on_numiterationsEdit_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticModeler::PARAM_NUMITERATIONS, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticModeler::PARAM_NUMITERATIONS, newText.toInt());
}

void GeneticModelerWidget::on_numpoolEdit_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticModeler::PARAM_NUMPOOLSIZE, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticModeler::PARAM_NUMPOOLSIZE, newText.toInt());
}

void GeneticModelerWidget::on_mutBlock_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticModeler::PARAM_MUTBLOCK, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticModeler::PARAM_MUTBLOCK, newText.toDouble());
}

void GeneticModelerWidget::on_mutInverse_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticModeler::PARAM_MUTINVERSE, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticModeler::PARAM_MUTINVERSE, newText.toDouble());
}

void GeneticModelerWidget::on_mutShuffle_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticModeler::PARAM_MUTSHUFFLE, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticModeler::PARAM_MUTSHUFFLE, newText.toDouble());
}

void GeneticModelerWidget::on_mutSwap_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticModeler::PARAM_MUTSWAP, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticModeler::PARAM_MUTSWAP, newText.toDouble());
}

void GeneticModelerWidget::on_mutCrossover_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticModeler::PARAM_MUTCROSSOVER, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticModeler::PARAM_MUTCROSSOVER, newText.toDouble());
}
