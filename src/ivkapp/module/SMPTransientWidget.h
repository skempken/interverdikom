#ifndef SMPTRANSIENTWIDGET_H_
#define SMPTRANSIENTWIDGET_H_

#include "ModuleWidget.h"
#include "ui_SMPTransientWidget.h"

#include "ComputationThread.hpp"

#include "data/SSMPQueue.h"
#include "computation/SMPTransient.h"

using namespace ivk;

class SMPTransientWidget : public ModuleWidget, private Ui::SMPTransientWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(SMPTransientWidget)

public:
	SMPTransientWidget();

	virtual ~SMPTransientWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();
private:
	SMPTransient *modeler;

	ComputationThread<SMPTransient> *thread;

private slots:
	void on_iterations_valueChanged(const QString & newText);

	void on_threshold_valueChanged(const QString & newText);

	void spawnResultWidget();

};
#endif /*SMPTRANSIENTWIDGET_H_*/
