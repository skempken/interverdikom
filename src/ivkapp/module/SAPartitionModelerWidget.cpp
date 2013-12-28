#include "SAPartitionModelerWidget.h"
#include "ArrivalProcessDisplay.h"
#include "TraceDisplay.h"
#include "utility/RealUtils.h"

FACTORY_DEFINITIONS_FOR(SAPartitionModelerWidget)

SAPartitionModelerWidget::SAPartitionModelerWidget()
{
	setupUi(this);
	thread = new ComputationThread<SAPartitionModeler>(&modeler, this, computeButton, progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

SAPartitionModelerWidget::~SAPartitionModelerWidget()
{
}

void SAPartitionModelerWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(SAPartitionModeler::PARAM_NUMDSTEPS, loadInt(SAPartitionModeler::PARAM_NUMDSTEPS));
	numdstepsEdit->setValue(loadInt(SAPartitionModeler::PARAM_NUMDSTEPS));

	params.setInt(SAPartitionModeler::PARAM_NUMSTATES, loadInt( SAPartitionModeler::PARAM_NUMSTATES ) );
	numstatesEdit->setValue( loadInt( SAPartitionModeler::PARAM_NUMSTATES ) );

	params.setInt(SAPartitionModeler::PARAM_AUTOCORRELATION, loadInt(SAPartitionModeler::PARAM_AUTOCORRELATION));
	autoc->setValue(loadInt(SAPartitionModeler::PARAM_AUTOCORRELATION));

	params.setReal(SAPartitionModeler::PARAM_INITTEMP, loadReal(SAPartitionModeler::PARAM_INITTEMP));
	initTemp->setValue(_double(loadReal(SAPartitionModeler::PARAM_INITTEMP)));

	params.setReal(SAPartitionModeler::PARAM_ABORTTEMP, loadReal(SAPartitionModeler::PARAM_ABORTTEMP));
	abortTemp->setValue(_double(loadReal(SAPartitionModeler::PARAM_ABORTTEMP)));

	params.setReal(SAPartitionModeler::PARAM_ALPHA, loadReal(SAPartitionModeler::PARAM_ALPHA));
	alpha->setValue(_double(loadReal(SAPartitionModeler::PARAM_ALPHA)));

	modeler->setParameters(params);
}

void SAPartitionModelerWidget::initModel()
{
	int length = ((TraceDisplay*) parentModule)->getTrace()->getLength();
	numdstepsEdit->setMaximum( length );
	sliderDSteps->setMaximum( length );
	autoc->setMaximum( length );
	sliderAutoc->setMaximum( length );

	ComputationParameters params;
	params.setInt(SAPartitionModeler::PARAM_NUMDSTEPS, 1);
	params.setInt(SAPartitionModeler::PARAM_NUMSTATES, 1);
	params.setInt(SAPartitionModeler::PARAM_AUTOCORRELATION, 1);
	params.setReal(SAPartitionModeler::PARAM_INITTEMP, 10);
	params.setReal(SAPartitionModeler::PARAM_ABORTTEMP, 0.0001);
	params.setReal(SAPartitionModeler::PARAM_ALPHA, 0.99);

	const Trace *trace = ((TraceDisplay*) parentModule)->getTrace();
	modeler = new SAPartitionModeler(trace, params);

	params.setInt(SAPartitionModeler::PARAM_NUMDSTEPS, modeler->suggestNumDiscretizationSteps());
	params.setInt(SAPartitionModeler::PARAM_NUMSTATES, modeler->suggestNumStates());
	params.setReal(SAPartitionModeler::PARAM_INITTEMP, 10);
	params.setReal(SAPartitionModeler::PARAM_ABORTTEMP, 0.0001);
	params.setReal(SAPartitionModeler::PARAM_ALPHA, 0.99);

	modeler->setParameters(params);
}

void SAPartitionModelerWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt( SAPartitionModeler::PARAM_NUMDSTEPS, params.getInt( SAPartitionModeler::PARAM_NUMDSTEPS ) );
	saveInt( SAPartitionModeler::PARAM_NUMSTATES, params.getInt( SAPartitionModeler::PARAM_NUMSTATES ) );
	saveInt( SAPartitionModeler::PARAM_AUTOCORRELATION, params.getInt( SAPartitionModeler::PARAM_AUTOCORRELATION ) );
	saveReal( SAPartitionModeler::PARAM_INITTEMP, params.getReal( SAPartitionModeler::PARAM_INITTEMP ) );
	saveReal( SAPartitionModeler::PARAM_ABORTTEMP, params.getReal( SAPartitionModeler::PARAM_ABORTTEMP ) );
	saveReal( SAPartitionModeler::PARAM_ALPHA, params.getReal( SAPartitionModeler::PARAM_ALPHA ) );
}

void SAPartitionModelerWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	numdstepsEdit->setValue(params.getInt(SAPartitionModeler::PARAM_NUMDSTEPS));
	numstatesEdit->setValue(params.getInt(SAPartitionModeler::PARAM_NUMSTATES));
	autoc->setValue(params.getInt(SAPartitionModeler::PARAM_AUTOCORRELATION));
	initTemp->setValue(_double ( params.getReal(SAPartitionModeler::PARAM_INITTEMP) ));
	abortTemp->setValue(_double ( params.getReal(SAPartitionModeler::PARAM_ABORTTEMP) ));
	alpha->setValue(_double ( params.getReal(SAPartitionModeler::PARAM_ALPHA) ));
}

void SAPartitionModelerWidget::createActions()
{

}

void SAPartitionModelerWidget::spawnResultWidget()
{
	SSMProcess* result = thread->getResult();
	addSubWidget(new ArrivalProcessDisplay(result), tr("Arrival Process"));
}

void SAPartitionModelerWidget::on_numdstepsEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(SAPartitionModeler::PARAM_NUMDSTEPS, newText.toInt());
	modeler->setParameters(params);

	saveInt(SAPartitionModeler::PARAM_NUMDSTEPS, newText.toInt());
}

void SAPartitionModelerWidget::on_numstatesEdit_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(SAPartitionModeler::PARAM_NUMSTATES, newText.toInt());
	modeler->setParameters(params);

	saveInt(SAPartitionModeler::PARAM_NUMSTATES, newText.toInt());
}

void SAPartitionModelerWidget::on_autoc_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(SAPartitionModeler::PARAM_AUTOCORRELATION, newText.toInt());
	modeler->setParameters(params);

	saveInt(SAPartitionModeler::PARAM_AUTOCORRELATION, newText.toInt());
}

void SAPartitionModelerWidget::on_initTemp_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setReal(SAPartitionModeler::PARAM_INITTEMP, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SAPartitionModeler::PARAM_INITTEMP, newText.toDouble());
}

void SAPartitionModelerWidget::on_abortTemp_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setReal(SAPartitionModeler::PARAM_ABORTTEMP, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SAPartitionModeler::PARAM_ABORTTEMP, newText.toDouble());
}

void SAPartitionModelerWidget::on_alpha_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setReal(SAPartitionModeler::PARAM_ALPHA, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SAPartitionModeler::PARAM_ALPHA, newText.toDouble());
}
