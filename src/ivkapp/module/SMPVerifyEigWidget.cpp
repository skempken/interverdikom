#include "SMPVerifyEigWidget.h"

#include <cimatrix.hpp>
#include <civector.hpp>

#include "computation/SMPVerifyEig.h"

#include "modbase/DataProvider.hpp"

#include "module/PFResultWidget.h"

#include <qwt-qt4/qwt_symbol.h>

FACTORY_DEFINITIONS_FOR(SMPVerifyEigWidget)

SMPVerifyEigWidget::SMPVerifyEigWidget()
{
	setupUi(this);

	thread = new ComputationThread<SMPVerifyEig>(&computation, this, computeButton, progressBar, label);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));

}

SMPVerifyEigWidget::~SMPVerifyEigWidget()
{
}

void SMPVerifyEigWidget::initModel() {
	queue = (dynamic_cast<DataProvider<SSMPQueue>*>(parentModule))->getData();
	computation = new SMPVerifyEig(queue, ComputationParameters());
}


void SMPVerifyEigWidget::createActions() {

}

void SMPVerifyEigWidget::loadModel() {

}

void SMPVerifyEigWidget::spawnResultWidget() {
	addSubWidget(new PFResultWidget(thread->getResult()), tr("Phase distributions"));
}
