#include "SMPPolyFacWidget.h"

#include <cimatrix.hpp>
#include <civector.hpp>

#include "computation/SMPPolyFac.h"

#include "modbase/DataProvider.hpp"

#include "module/PFResultWidget.h"

#include <qwt-qt4/qwt_symbol.h>

FACTORY_DEFINITIONS_FOR(SMPPolyFacWidget)

SMPPolyFacWidget::SMPPolyFacWidget()
{
	setupUi(this);

	thread = new ComputationThread<SMPPolyFac>(&computation, this, computeButton, progressBar, label);
	connect(thread, SIGNAL(computationFinished()), this, SLOT(spawnResultWidget()));
	connect(rootsCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(rootsMethodChanged(int)));
	connect(determinantCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(determinantMethodChanged(int)));
}

SMPPolyFacWidget::~SMPPolyFacWidget()
{
}

void SMPPolyFacWidget::initModel() {
	queue = (dynamic_cast<DataProvider<SSMPQueue>*>(parentModule))->getData();
	ComputationParameters params;
	params.setInt(SMPPolyFac::PARAM_ROOTS, 0);
	params.setInt(SMPPolyFac::PARAM_DETERMINANT, 0);
	computation = new SMPPolyFac(queue, params);
}


void SMPPolyFacWidget::createActions() {

}

void SMPPolyFacWidget::loadModel() {

}

void SMPPolyFacWidget::spawnResultWidget() {
	addSubWidget(new PFResultWidget(thread->getResult()), tr("Phase distributions"));
}

void SMPPolyFacWidget::rootsMethodChanged(int methodIndex) {
	if (methodIndex < 0) {
		return;
	}

	ComputationParameters params = computation->getParameters();
	params.setInt(SMPPolyFac::PARAM_ROOTS, methodIndex);
	computation->setParameters(params);
}

void SMPPolyFacWidget::derminantMethodChanged(int methodIndex) {
	if (methodIndex < 0) {
		return;
	}

	ComputationParameters params = computation->getParameters();
	params.setInt(SMPPolyFac::PARAM_DETERMINANT, methodIndex);
	computation->setParameters(params);
}
