#include "SPEA2ModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "TraceDisplay.h"

FACTORY_DEFINITIONS_FOR(SPEA2ModelerWidget)

SPEA2ModelerWidget::SPEA2ModelerWidget(){
	setupUi(this);
	thread = new ComputationThread<SPEA2Modeler>(&modeler, this, computeButton ,  progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

SPEA2ModelerWidget::~SPEA2ModelerWidget(){}

void SPEA2ModelerWidget::loadModel(){
	ComputationParameters param;

	param.setInt( SPEA2Modeler::PARAM_NUMSTATES, loadInt(SPEA2Modeler::PARAM_NUMSTATES ) );
	numstatesEdit->setValue( loadInt(SPEA2Modeler::PARAM_NUMSTATES ) );

	param.setInt( SPEA2Modeler::PARAM_NUMDSTEPS , loadInt( SPEA2Modeler::PARAM_NUMDSTEPS ));
	numdstepsEdit->setValue( loadInt(SPEA2Modeler::PARAM_NUMDSTEPS ) );

	param.setInt( SPEA2Modeler::PARAM_POPSIZE, loadInt( SPEA2Modeler::PARAM_POPSIZE ));
	popSize->setValue(loadInt( SPEA2Modeler::PARAM_POPSIZE ));

	param.setInt( SPEA2Modeler::PARAM_ARCHIVESIZE , loadInt( SPEA2Modeler::PARAM_ARCHIVESIZE ));
	archiveSize->setValue( loadInt( SPEA2Modeler::PARAM_ARCHIVESIZE ));

	param.setInt( SPEA2Modeler::PARAM_NUMITERATIONS , loadInt( SPEA2Modeler::PARAM_NUMITERATIONS ));
	numIterations->setValue(loadInt( SPEA2Modeler::PARAM_NUMITERATIONS ));

	param.setInt( SPEA2Modeler::PARAM_AUTOCORRELATION , loadInt( SPEA2Modeler::PARAM_AUTOCORRELATION ));
	autocorrelation->setValue( loadInt( SPEA2Modeler::PARAM_AUTOCORRELATION ));

	param.setReal( SPEA2Modeler::PARAM_MCROSSOVER, loadReal( SPEA2Modeler::PARAM_MCROSSOVER ) );
	mutCrossover->setValue( _double( loadReal( SPEA2Modeler::PARAM_MCROSSOVER ) ));

	param.setReal( SPEA2Modeler::PARAM_MBLOCK, loadReal( SPEA2Modeler::PARAM_MBLOCK ));
	mutBlock->setValue( _double( loadReal( SPEA2Modeler::PARAM_MBLOCK ) ));

	param.setReal( SPEA2Modeler::PARAM_MINVERSE, loadReal( SPEA2Modeler::PARAM_MINVERSE ));
	mutInverse->setValue( _double( loadReal( SPEA2Modeler::PARAM_MINVERSE ) ));

	param.setReal( SPEA2Modeler::PARAM_MSHUFFLE, loadReal( SPEA2Modeler::PARAM_MSHUFFLE ));
	mutShuffle->setValue( _double( loadReal( SPEA2Modeler::PARAM_MSHUFFLE ) ));

	param.setReal( SPEA2Modeler::PARAM_MSWAP, loadReal( SPEA2Modeler::PARAM_MSWAP ));
	mutSwap->setValue( _double( loadReal( SPEA2Modeler::PARAM_MSWAP ) ));

	modeler->setParameters( param );
}

void SPEA2ModelerWidget::initModel(){
	int length = ((TraceDisplay*) parentModule)->getTrace()->getLength();
	autocorrelation->setMaximum( length );
	sliderAutocorrelation->setMaximum( length );
	numdstepsEdit->setMaximum( length );
	sliderDSteps->setMaximum( length );

	ComputationParameters params;
	params.setInt(SPEA2Modeler::PARAM_NUMDSTEPS, 1);
	params.setInt(SPEA2Modeler::PARAM_NUMSTATES, 1);
	params.setInt(SPEA2Modeler::PARAM_POPSIZE, 10);
	params.setInt(SPEA2Modeler::PARAM_ARCHIVESIZE, 10);
	params.setInt(SPEA2Modeler::PARAM_NUMITERATIONS, 10);
	params.setInt(SPEA2Modeler::PARAM_AUTOCORRELATION, 1);
	params.setReal(SPEA2Modeler::PARAM_MCROSSOVER, 0.01);
	params.setReal(SPEA2Modeler::PARAM_MBLOCK, 0.01);
	params.setReal(SPEA2Modeler::PARAM_MINVERSE, 0.01);
	params.setReal(SPEA2Modeler::PARAM_MSHUFFLE, 0.01);
	params.setReal(SPEA2Modeler::PARAM_MSWAP, 0.01);

	const Trace *trace = ((TraceDisplay*) parentModule)->getTrace();
	modeler = new SPEA2Modeler(trace, params);

	params.setInt(SPEA2Modeler::PARAM_NUMDSTEPS, modeler->suggestNumDiscretizationSteps());
	params.setInt(SPEA2Modeler::PARAM_NUMSTATES, modeler->suggestNumStates());
	params.setInt(SPEA2Modeler::PARAM_AUTOCORRELATION, modeler->suggestNumStates());

	modeler->setParameters(params);
}

void SPEA2ModelerWidget::postCreation(){
	// save to XML structure
	ComputationParameters params = this->modeler->getParameters();

	saveInt(SPEA2Modeler::PARAM_NUMDSTEPS, 			params.getInt(SPEA2Modeler::PARAM_NUMDSTEPS));
	saveInt(SPEA2Modeler::PARAM_NUMSTATES, 			params.getInt(SPEA2Modeler::PARAM_NUMSTATES));
	saveInt(SPEA2Modeler::PARAM_POPSIZE, 			params.getInt(SPEA2Modeler::PARAM_POPSIZE));
	saveInt(SPEA2Modeler::PARAM_ARCHIVESIZE, 		params.getInt(SPEA2Modeler::PARAM_ARCHIVESIZE));
	saveInt(SPEA2Modeler::PARAM_NUMITERATIONS, 		params.getInt(SPEA2Modeler::PARAM_NUMITERATIONS));
	saveInt(SPEA2Modeler::PARAM_AUTOCORRELATION, 	params.getInt(SPEA2Modeler::PARAM_AUTOCORRELATION));
	saveReal(SPEA2Modeler::PARAM_MCROSSOVER, 		params.getReal(SPEA2Modeler::PARAM_MCROSSOVER));
	saveReal(SPEA2Modeler::PARAM_MBLOCK, 			params.getReal(SPEA2Modeler::PARAM_MBLOCK));
	saveReal(SPEA2Modeler::PARAM_MINVERSE, 			params.getReal(SPEA2Modeler::PARAM_MINVERSE));
	saveReal(SPEA2Modeler::PARAM_MSHUFFLE, 			params.getReal(SPEA2Modeler::PARAM_MSHUFFLE));
	saveReal(SPEA2Modeler::PARAM_MSWAP, 			params.getReal(SPEA2Modeler::PARAM_MSWAP));
}

void SPEA2ModelerWidget::updateGUI(){
	ComputationParameters params = modeler->getParameters();
	numstatesEdit->setValue( params.getInt(SPEA2Modeler::PARAM_NUMSTATES ) );
	numdstepsEdit->setValue( params.getInt(SPEA2Modeler::PARAM_NUMDSTEPS ) );
	popSize->setValue(params.getInt( SPEA2Modeler::PARAM_POPSIZE ));
	archiveSize->setValue( params.getInt( SPEA2Modeler::PARAM_ARCHIVESIZE ));
	numIterations->setValue(params.getInt( SPEA2Modeler::PARAM_NUMITERATIONS ));
	autocorrelation->setValue( params.getInt( SPEA2Modeler::PARAM_AUTOCORRELATION ));
	mutCrossover->setValue( _double( params.getReal( SPEA2Modeler::PARAM_MCROSSOVER ) ) );
	mutBlock->setValue( _double( params.getReal( SPEA2Modeler::PARAM_MBLOCK ) ));
	mutInverse->setValue( _double( params.getReal( SPEA2Modeler::PARAM_MINVERSE ) ));
	mutShuffle->setValue( _double( params.getReal( SPEA2Modeler::PARAM_MSHUFFLE ) ));
	mutSwap->setValue( _double( params.getReal( SPEA2Modeler::PARAM_MSWAP ) ));
}

void SPEA2ModelerWidget::createActions(){}

void SPEA2ModelerWidget::spawnResultWidget(){
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void SPEA2ModelerWidget::on_numdstepsEdit_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(SPEA2Modeler::PARAM_NUMDSTEPS, newText.toInt());
	modeler->setParameters(params);

	saveInt(SPEA2Modeler::PARAM_NUMDSTEPS, newText.toInt());
}

void SPEA2ModelerWidget::on_numstatesEdit_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(SPEA2Modeler::PARAM_NUMSTATES, newText.toInt());
	modeler->setParameters(params);

	saveInt(SPEA2Modeler::PARAM_NUMSTATES, newText.toInt());
}

void SPEA2ModelerWidget::on_popSize_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(SPEA2Modeler::PARAM_POPSIZE, newText.toInt());
	modeler->setParameters(params);

	saveInt(SPEA2Modeler::PARAM_POPSIZE, newText.toInt());
}

void SPEA2ModelerWidget::on_archiveSize_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(SPEA2Modeler::PARAM_ARCHIVESIZE, newText.toInt());
	modeler->setParameters(params);

	saveInt(SPEA2Modeler::PARAM_ARCHIVESIZE, newText.toInt());
}

void SPEA2ModelerWidget::on_numIterations_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(SPEA2Modeler::PARAM_NUMITERATIONS, newText.toInt());
	modeler->setParameters(params);

	saveInt(SPEA2Modeler::PARAM_NUMITERATIONS, newText.toInt());
}

void SPEA2ModelerWidget::on_autocorrelation_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setInt(SPEA2Modeler::PARAM_AUTOCORRELATION, newText.toInt());
	modeler->setParameters(params);

	saveInt(SPEA2Modeler::PARAM_AUTOCORRELATION, newText.toInt());
}

void SPEA2ModelerWidget::on_mutCrossover_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setReal(SPEA2Modeler::PARAM_MCROSSOVER, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SPEA2Modeler::PARAM_MCROSSOVER, newText.toDouble());
}

void SPEA2ModelerWidget::on_mutInverse_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setReal(SPEA2Modeler::PARAM_MINVERSE, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SPEA2Modeler::PARAM_MINVERSE, newText.toDouble());
}
void SPEA2ModelerWidget::on_mutBlock_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setReal(SPEA2Modeler::PARAM_MBLOCK, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SPEA2Modeler::PARAM_MBLOCK, newText.toDouble());
}
void SPEA2ModelerWidget::on_mutShuffle_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setReal(SPEA2Modeler::PARAM_MSHUFFLE, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SPEA2Modeler::PARAM_MSHUFFLE, newText.toDouble());
}
void SPEA2ModelerWidget::on_mutSwap_valueChanged(const QString & newText){
	ComputationParameters params = modeler->getParameters();
	params.setReal(SPEA2Modeler::PARAM_MSWAP, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SPEA2Modeler::PARAM_MSWAP, newText.toDouble());
}
