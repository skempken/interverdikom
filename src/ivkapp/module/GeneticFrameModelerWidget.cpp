#include "GeneticFrameModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "DataProvider.hpp"
#include "data/Trace.h"
#include "MainWindow.h"

FACTORY_DEFINITIONS_FOR(GeneticFrameModelerWidget)

GeneticFrameModelerWidget::GeneticFrameModelerWidget(CyclePeriodWizard* wizard)
{
	setupUi(this);
	thread = new ComputationThread<GeneticFrameModeler>(&modeler, this, computeButton , progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
	connect(thread, SIGNAL(message(QString)), MainWindow::getOutputConsole(), SLOT(printMessage(QString)));
	connect(thread, SIGNAL(exception(QString)), MainWindow::getOutputConsole(), SLOT(printError(QString)));

	if(wizard)
		connect(wizard->intervalEdit, SIGNAL(valueChanged(int)), this->framelevel, SLOT(setValue(int)));
}

GeneticFrameModelerWidget::~GeneticFrameModelerWidget()
{
}

const Trace* GeneticFrameModelerWidget::getData()
{
	return (dynamic_cast<DataProvider<Trace>*>(parentModule))->getData();
}

void GeneticFrameModelerWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(GeneticFrameModeler::PARAM_NUMDSTEPS, loadInt(GeneticFrameModeler::PARAM_NUMDSTEPS));
	numdstepsEdit->setValue(loadInt(GeneticFrameModeler::PARAM_NUMDSTEPS));

	params.setInt(GeneticFrameModeler::PARAM_NUMSTATES, loadInt(GeneticFrameModeler::PARAM_NUMSTATES));
	numstatesEdit->setValue(loadInt(GeneticFrameModeler::PARAM_NUMSTATES));

	params.setInt(GeneticFrameModeler::PARAM_AUTOC, loadInt(GeneticFrameModeler::PARAM_AUTOC));
	numautocEdit->setValue(loadInt(GeneticFrameModeler::PARAM_AUTOC));

	params.setInt(GeneticFrameModeler::PARAM_NUMITERATIONS, loadInt(GeneticFrameModeler::PARAM_NUMITERATIONS));
	numiterationsEdit->setValue(loadInt(GeneticFrameModeler::PARAM_NUMITERATIONS));

	params.setInt(GeneticFrameModeler::PARAM_NUMPOOLSIZE, loadInt(GeneticFrameModeler::PARAM_NUMPOOLSIZE));
	numpoolEdit->setValue(loadInt(GeneticFrameModeler::PARAM_NUMPOOLSIZE));

	params.setReal(GeneticFrameModeler::PARAM_MUTBLOCK, loadReal(GeneticFrameModeler::PARAM_MUTBLOCK));
	mutBlock->setValue(_double ( loadReal(GeneticFrameModeler::PARAM_MUTBLOCK) ));

	params.setReal(GeneticFrameModeler::PARAM_MUTINVERSE, loadReal(GeneticFrameModeler::PARAM_MUTINVERSE));
	mutInverse->setValue(_double ( loadReal(GeneticFrameModeler::PARAM_MUTINVERSE) ));

	params.setReal(GeneticFrameModeler::PARAM_MUTSHUFFLE, loadReal(GeneticFrameModeler::PARAM_MUTSHUFFLE));
	mutShuffle->setValue(_double ( loadReal(GeneticFrameModeler::PARAM_MUTSHUFFLE) ));

	params.setReal(GeneticFrameModeler::PARAM_MUTSWAP, loadReal(GeneticFrameModeler::PARAM_MUTSWAP));
	mutSwap->setValue(_double ( loadReal(GeneticFrameModeler::PARAM_MUTSWAP) ));

	params.setReal(GeneticFrameModeler::PARAM_MUTCROSSOVER, loadReal(GeneticFrameModeler::PARAM_MUTCROSSOVER));
	mutCrossover->setValue(_double ( loadReal(GeneticFrameModeler::PARAM_MUTCROSSOVER) ));

	params.setInt( GeneticFrameModeler::PARAM_FRAMELEVEL, loadInt(GeneticFrameModeler::PARAM_FRAMELEVEL));
	framelevel->setValue( loadInt( GeneticFrameModeler::PARAM_FRAMELEVEL ) );

	modeler->setParameters(params);
}

void GeneticFrameModelerWidget::initModel()
{
	const Trace *trace = (dynamic_cast<DataProvider<Trace>*>(parentModule))->getData();
	int length = trace->getLength();
	numdstepsEdit->setMaximum( length );
	sliderDSteps->setMaximum( length );
	numautocEdit->setMaximum( length );
	sliderAutoc->setMaximum( length );

	ComputationParameters params;
	params.setInt(GeneticFrameModeler::PARAM_NUMDSTEPS, 1);
	params.setInt(GeneticFrameModeler::PARAM_NUMSTATES, 1);
	params.setInt(GeneticFrameModeler::PARAM_AUTOC, 1);
	params.setInt(GeneticFrameModeler::PARAM_NUMITERATIONS, 10);
	params.setInt(GeneticFrameModeler::PARAM_NUMPOOLSIZE, 10);
	params.setReal(GeneticFrameModeler::PARAM_MUTBLOCK, 0.1);
	params.setReal(GeneticFrameModeler::PARAM_MUTINVERSE, 0.2);
	params.setReal(GeneticFrameModeler::PARAM_MUTSHUFFLE, 0.3);
	params.setReal(GeneticFrameModeler::PARAM_MUTSWAP, 0.4);
	params.setReal(GeneticFrameModeler::PARAM_MUTCROSSOVER, 0.5);
	params.setInt(GeneticFrameModeler::PARAM_FRAMELEVEL, 1 );


	modeler = new GeneticFrameModeler(trace, params);

	params.setInt(GeneticFrameModeler::PARAM_NUMDSTEPS, modeler->suggestNumDiscretizationSteps());
	params.setInt(GeneticFrameModeler::PARAM_NUMSTATES, modeler->suggestNumStates());
	params.setInt(GeneticFrameModeler::PARAM_AUTOC, modeler->suggestNumStates());

	modeler->setParameters(params);
}

void GeneticFrameModelerWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt( GeneticFrameModeler::PARAM_NUMDSTEPS , params.getInt( GeneticFrameModeler::PARAM_NUMDSTEPS ) );
	saveInt( GeneticFrameModeler::PARAM_NUMSTATES , params.getInt( GeneticFrameModeler::PARAM_NUMSTATES ) );
	saveInt( GeneticFrameModeler::PARAM_AUTOC , params.getInt( GeneticFrameModeler::PARAM_AUTOC ) );
	saveInt( GeneticFrameModeler::PARAM_NUMITERATIONS , params.getInt( GeneticFrameModeler::PARAM_NUMITERATIONS ) );
	saveInt( GeneticFrameModeler::PARAM_NUMPOOLSIZE , params.getInt( GeneticFrameModeler::PARAM_NUMPOOLSIZE ) );
	saveReal( GeneticFrameModeler::PARAM_MUTBLOCK , params.getReal( GeneticFrameModeler::PARAM_MUTBLOCK ) );
	saveReal( GeneticFrameModeler::PARAM_MUTINVERSE , params.getReal( GeneticFrameModeler::PARAM_MUTINVERSE ) );
	saveReal( GeneticFrameModeler::PARAM_MUTSHUFFLE , params.getReal( GeneticFrameModeler::PARAM_MUTSHUFFLE ) );
	saveReal( GeneticFrameModeler::PARAM_MUTSWAP , params.getReal( GeneticFrameModeler::PARAM_MUTSWAP ) );
	saveReal( GeneticFrameModeler::PARAM_MUTCROSSOVER , params.getReal( GeneticFrameModeler::PARAM_MUTCROSSOVER ) );
	saveInt( GeneticFrameModeler::PARAM_FRAMELEVEL, params.getInt( GeneticFrameModeler::PARAM_FRAMELEVEL ) );
}

void GeneticFrameModelerWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	numstatesEdit->setValue(params.getInt(GeneticFrameModeler::PARAM_NUMSTATES));
	numdstepsEdit->setValue(params.getInt(GeneticFrameModeler::PARAM_NUMDSTEPS));
	numautocEdit->setValue(params.getInt(GeneticFrameModeler::PARAM_AUTOC));
	numiterationsEdit->setValue(params.getInt(GeneticFrameModeler::PARAM_NUMITERATIONS));
	numpoolEdit->setValue(params.getInt(GeneticFrameModeler::PARAM_NUMPOOLSIZE));
	mutBlock->setValue( _double( params.getReal( GeneticFrameModeler::PARAM_MUTBLOCK) ) );
	mutInverse->setValue( _double( params.getReal( GeneticFrameModeler::PARAM_MUTINVERSE) ) );
	mutShuffle->setValue( _double( params.getReal( GeneticModeler::PARAM_MUTSHUFFLE) ) );
	mutSwap->setValue( _double( params.getReal( GeneticFrameModeler::PARAM_MUTSWAP) ) );
	mutCrossover->setValue( _double( params.getReal( GeneticFrameModeler::PARAM_MUTCROSSOVER) ) );
	framelevel->setValue( params.getInt(GeneticFrameModeler::PARAM_FRAMELEVEL));
}

void GeneticFrameModelerWidget::createActions()
{

}

void GeneticFrameModelerWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void GeneticFrameModelerWidget::on_numdstepsEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticFrameModeler::PARAM_NUMDSTEPS, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticFrameModeler::PARAM_NUMDSTEPS, newText.toInt());
}

void GeneticFrameModelerWidget::on_numstatesEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticFrameModeler::PARAM_NUMSTATES, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticFrameModeler::PARAM_NUMSTATES, newText.toInt());
}

void GeneticFrameModelerWidget::on_numautocEdit_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticFrameModeler::PARAM_AUTOC, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticFrameModeler::PARAM_AUTOC, newText.toInt());
}

void GeneticFrameModelerWidget::on_numiterationsEdit_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticFrameModeler::PARAM_NUMITERATIONS, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticFrameModeler::PARAM_NUMITERATIONS, newText.toInt());
}

void GeneticFrameModelerWidget::on_numpoolEdit_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(GeneticFrameModeler::PARAM_NUMPOOLSIZE, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticFrameModeler::PARAM_NUMPOOLSIZE, newText.toInt());
}

void GeneticFrameModelerWidget::on_mutBlock_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticFrameModeler::PARAM_MUTBLOCK, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticFrameModeler::PARAM_MUTBLOCK, newText.toDouble());
}

void GeneticFrameModelerWidget::on_mutInverse_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticFrameModeler::PARAM_MUTINVERSE, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticFrameModeler::PARAM_MUTINVERSE, newText.toDouble());
}

void GeneticFrameModelerWidget::on_mutShuffle_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticFrameModeler::PARAM_MUTSHUFFLE, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticFrameModeler::PARAM_MUTSHUFFLE, newText.toDouble());
}

void GeneticFrameModelerWidget::on_mutSwap_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticFrameModeler::PARAM_MUTSWAP, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticFrameModeler::PARAM_MUTSWAP, newText.toDouble());
}

void GeneticFrameModelerWidget::on_mutCrossover_valueChanged( const QString & newText ){
	ComputationParameters params = modeler->getParameters();
	params.setReal(GeneticFrameModeler::PARAM_MUTCROSSOVER, newText.toDouble());
	modeler->setParameters(params);

	saveReal(GeneticFrameModeler::PARAM_MUTCROSSOVER, newText.toDouble());
}

void GeneticFrameModelerWidget::on_framelevel_valueChanged( const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt( GeneticFrameModeler::PARAM_FRAMELEVEL, newText.toInt());
	modeler->setParameters(params);

	saveInt(GeneticFrameModeler::PARAM_FRAMELEVEL, newText.toInt());
}
