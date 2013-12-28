#include "SMPTransientWidget.h"
#include "ArrivalProcessDisplay.h"
#include "TraceDisplay.h"
#include "WorkloadDistributionWidget.h"

FACTORY_DEFINITIONS_FOR(SMPTransientWidget)

SMPTransientWidget::SMPTransientWidget()
{
	setupUi(this);
	thread = new ComputationThread<SMPTransient>(&modeler, this, computeButton ,  progressBar, progressLabel);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
}

SMPTransientWidget::~SMPTransientWidget()
{
}

void SMPTransientWidget::loadModel()
{
	ComputationParameters params;

	params.setInt(SMPTransient::PARAM_ITERATIONS, loadInt(SMPTransient::PARAM_ITERATIONS));
	iterations->setValue(loadInt(SMPTransient::PARAM_ITERATIONS));

	params.setReal(SMPTransient::PARAM_THRESHOLD, loadReal(SMPTransient::PARAM_THRESHOLD));
	threshold->setValue( _double( loadReal(SMPTransient::PARAM_THRESHOLD) ) );

	modeler->setParameters(params);
}

void SMPTransientWidget::initModel()
{
	ComputationParameters params;
	params.setInt(SMPTransient::PARAM_ITERATIONS, 1);
	params.setReal(SMPTransient::PARAM_THRESHOLD, 0.001);

    const SSMProcess *process = dynamic_cast<DataProvider<SSMPQueue>*>(parentModule)->getData();
	modeler = new SMPTransient(process, params);

	modeler->setParameters(params);
}

void SMPTransientWidget::postCreation(){
	ComputationParameters params = this->modeler->getParameters();

	saveInt( SMPTransient::PARAM_ITERATIONS, params.getInt( SMPTransient::PARAM_ITERATIONS ) );
	saveReal( SMPTransient::PARAM_THRESHOLD, params.getReal( SMPTransient::PARAM_THRESHOLD ) );
}

void SMPTransientWidget::updateGUI()
{
	// Copy values from model to GUI fields
	ComputationParameters params = modeler->getParameters();
	iterations->setValue(params.getInt(SMPTransient::PARAM_ITERATIONS));
	threshold->setValue( _double( params.getReal(SMPTransient::PARAM_THRESHOLD) ));
}

void SMPTransientWidget::createActions()
{

}

void SMPTransientWidget::spawnResultWidget()
{
	IWorkloadVector* result = thread->getResult();
	addSubWidget(new WorkloadDistributionWidget(result), tr("Workload Distribution"));
}

void SMPTransientWidget::on_iterations_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setInt(SMPTransient::PARAM_ITERATIONS, newText.toInt());
	modeler->setParameters(params);

	saveInt(SMPTransient::PARAM_ITERATIONS, newText.toInt());
}

void SMPTransientWidget::on_threshold_valueChanged(const QString & newText)
{
	ComputationParameters params = modeler->getParameters();
	params.setReal(SMPTransient::PARAM_THRESHOLD, newText.toDouble());
	modeler->setParameters(params);

	saveReal(SMPTransient::PARAM_THRESHOLD, newText.toDouble());
}

