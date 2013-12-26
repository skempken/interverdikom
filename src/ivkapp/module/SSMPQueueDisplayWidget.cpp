#include "module/SSMPQueueDisplayWidget.h"

#include "module/WienerHopfWidget.h"
#include "module/WienerHopfLVWidget.h"
#include "module/SMPTransientWidget.h"
#include "module/SMPVerifyEigWidget.h"
#include "module/SMPPolyFacWidget.h"

FACTORY_DEFINITIONS_FOR(SSMPQueueDisplayWidget)

SSMPQueueDisplayWidget::SSMPQueueDisplayWidget() :
	queue(0) {
	setupUi(this);
}

SSMPQueueDisplayWidget::SSMPQueueDisplayWidget(const SSMPQueue *queue) :
	queue(queue) {
	setupUi(this);
	setQueue(queue);
}

SSMPQueueDisplayWidget::~SSMPQueueDisplayWidget() {
}

void SSMPQueueDisplayWidget::setQueue(const SSMPQueue *queue) {
	this->queue = queue;
	arrivalWidget->displayProcess(queue->getArrivalProcess());
	serviceWidget->displayProcess(queue->getServiceProcess());
	resultWidget->displayProcess(queue);
}

const SSMPQueue* SSMPQueueDisplayWidget::getData() {
	return this->queue;
}

const SSMPQueue* SSMPQueueDisplayWidget::getSSMPQueue() const {
	return this->queue;
}

void SSMPQueueDisplayWidget::createFileElements() {
	saveSSMPQueue("Queue", *queue);
}

void SSMPQueueDisplayWidget::loadModel() {
	setQueue(new SSMPQueue(loadSSMPQueue("Queue")));
}

void SSMPQueueDisplayWidget::createActions() {
	QAction *wienerHopfAction = new QAction(tr("Workload analysis by Wiener-Hopf factorization..."), this);
	connect(wienerHopfAction, SIGNAL(triggered()), this,
	SLOT(wienerHopfRequested()));
	addAction(wienerHopfAction);

	QAction *wienerHopfLvAction = new QAction(tr("Workload analysis by Wiener-Hopf LV factorization..."), this);
	connect(wienerHopfLvAction, SIGNAL(triggered()), this,
	SLOT(wienerHopfLvRequested()));
	addAction(wienerHopfLvAction);

	QAction *polyFacAction = new QAction(tr("Workload analysis by polynomial roots..."), this);
	connect(polyFacAction, SIGNAL(triggered()), this,
	SLOT(smpPolyFacRequested()));
	addAction(polyFacAction);

	QAction *verifyeigAction = new QAction(tr("Workload analysis by verified eigenvalues..."), this);
	connect(verifyeigAction, SIGNAL(triggered()), this,
	SLOT(verifyeigRequested()));
	addAction(verifyeigAction);

	QAction *smpTransientAction = new QAction(tr("Workload analysis by transient states..."), this);
	connect(smpTransientAction, SIGNAL(triggered()), this,
	SLOT(smpTransientRequested()));
	addAction(smpTransientAction);
}

void SSMPQueueDisplayWidget::verifyeigRequested() {
	addSubWidget(new SMPVerifyEigWidget,
			tr("Verified Eigenvalue Factorization"));
}

void SSMPQueueDisplayWidget::smpPolyFacRequested() {
	addSubWidget(new SMPPolyFacWidget, tr("Polynomial Factorization"));
}

void SSMPQueueDisplayWidget::wienerHopfRequested() {
	addSubWidget(new WienerHopfWidget, tr("Wiener-Hopf Factorization"));
}

void SSMPQueueDisplayWidget::wienerHopfLvRequested() {
	addSubWidget(new WienerHopfLVWidget, tr("Wiener-Hopf LV Factorization"));
}

void SSMPQueueDisplayWidget::smpTransientRequested() {
	addSubWidget(new SMPTransientWidget, tr("Transient Analysis"));
}
