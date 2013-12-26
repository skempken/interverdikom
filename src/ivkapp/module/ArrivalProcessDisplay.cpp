#include "ArrivalProcessDisplay.h"

#include <QAction>
#include <QInputDialog>

#include "data/SSMProcess.h"

#include "module/AddServiceProcessWidget.h"
#include "module/RepeatedStateContractionsWidget.h"
#include "module/StateMergeWidget.h"
#include "module/StatePartitioningWidget.h"

FACTORY_DEFINITIONS_FOR(ArrivalProcessDisplay)

ArrivalProcessDisplay::ArrivalProcessDisplay()
{
	setupUi(this);
}

ArrivalProcessDisplay::ArrivalProcessDisplay(SSMProcess *process) :
	process(process)
{
	setupUi(this);
	initializeDisplay();
}

ArrivalProcessDisplay::~ArrivalProcessDisplay()
{
}

void ArrivalProcessDisplay::createFileElements()
{
	saveSSMProcess("Process", *process);
}

void ArrivalProcessDisplay::createActions()
{
	QAction *serviceProcessAction = new QAction(tr("Create service process..."), this);
	connect(serviceProcessAction, SIGNAL(triggered()), this,
			SLOT(createServiceProcessRequested()));
	addAction(serviceProcessAction);

	QAction *repeatedStateContractionsProcessAction = new QAction(tr("Repeated State Contractions..."), this);
	connect(repeatedStateContractionsProcessAction, SIGNAL(triggered()), this,
			SLOT(createRepeatedStateContractionsRequested()));
	addAction(repeatedStateContractionsProcessAction);

	QAction *stateMergeProcessAction = new QAction(tr("State Merge..."), this);
	connect(stateMergeProcessAction, SIGNAL(triggered()), this,
			SLOT(createStateMergeRequested()));
	addAction(stateMergeProcessAction);

	QAction *statePartitioningAction = new QAction( tr( "State Partitioning..." )  , this );
	connect( statePartitioningAction , SIGNAL( triggered() ) , this ,
			SLOT( createStatePartitioningRequested() ) );
	addAction( statePartitioningAction );
}

void ArrivalProcessDisplay::loadModel()
{
	process = new SSMProcess(loadSSMProcess("Process"));

	initializeDisplay();
}

void ArrivalProcessDisplay::initializeDisplay()
{
	widget->displayProcess(process);
}

void ArrivalProcessDisplay::createServiceProcessRequested()
{
	addSubWidget(new AddServiceProcessWidget, tr("Service Process Definition"));
}

void ArrivalProcessDisplay::createRepeatedStateContractionsRequested(){
	addSubWidget(new RepeatedStateContractionsWidget, tr("Repeated State Contractions..."));
}

void ArrivalProcessDisplay::createStateMergeRequested(){
	addSubWidget(new StateMergeWidget, tr("State Merge..."));
}

void ArrivalProcessDisplay::createStatePartitioningRequested(){
	addSubWidget(new StatePartitioningWidget, tr( "State Partitioning..." ) );
}
