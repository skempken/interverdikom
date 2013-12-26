#ifndef STATEPARTITIONINGWIDGET_H_
#define STATEPARTITIONINGWIDGET_H_

#include "ModuleWidget.h"
#include "ui_StatePartitioningWidget.h"

#include "ComputationThread.hpp"
#include "module/TraceDisplay.h"

#include "data/Trace.h"
#include "computation/StatePartitioning.h"

#include <QWidget>

using namespace ivk;

class StatePartitioningWidget : public ModuleWidget, private Ui::StatePartitioningWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(StatePartitioningWidget)

public:
	StatePartitioningWidget();

	virtual ~StatePartitioningWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();

private:
	StatePartitioning *modeler;

	ComputationThread<StatePartitioning> *thread;

private slots:
	void on_numContractions_valueChanged(const QString & newText);

	void spawnResultWidget();

};
#endif /*STATEPARTITIONINGWIDGET_H_*/
