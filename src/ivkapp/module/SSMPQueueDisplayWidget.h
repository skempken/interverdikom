#ifndef QUEUEDISPLAYWIDGET_H_
#define QUEUEDISPLAYWIDGET_H_

#include "ModuleWidget.h"
#include "ui_SSMPQueueDisplayWidget.h"
#include "DataProvider.hpp"
#include "data/SSMPQueue.h"

using ivk::SSMPQueue;

class SSMPQueueDisplayWidget : public ModuleWidget, protected Ui::SSMPQueueDisplayWidget, public DataProvider<SSMPQueue>
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(SSMPQueueDisplayWidget)

public:
	SSMPQueueDisplayWidget();

	SSMPQueueDisplayWidget(const SSMPQueue *queue);

	void setQueue(const SSMPQueue *queue);

	const SSMPQueue* getData();

	virtual ~SSMPQueueDisplayWidget();

	virtual const SSMPQueue* getSSMPQueue() const;


protected:
	void loadModel();

	void createActions();

	void createFileElements();

private:
	const SSMPQueue *queue;

private slots:
	void wienerHopfRequested();

	void wienerHopfLvRequested();

	void smpTransientRequested();

	void verifyeigRequested();

	void smpPolyFacRequested();
};

#endif /*QUEUEDISPLAYWIDGET_H_*/
