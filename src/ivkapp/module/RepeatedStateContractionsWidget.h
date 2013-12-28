#ifndef REPEATEDSTATECONTRACTIONSWIDGET_H_
#define REPEATEDSTATECONTRACTIONSWIDGET_H_

#include "ModuleWidget.h"
#include "ui_RepeatedStateContractionsWidget.h"

#include "ComputationThread.hpp"
#include "module/TraceDisplay.h"

#include "data/Trace.h"
#include "computation/RepeatedStateContractions.h"

using namespace ivk;

class RepeatedStateContractionsWidget : public ModuleWidget, private Ui::RepeatedStateContractionsWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(RepeatedStateContractionsWidget)

public:
	RepeatedStateContractionsWidget();

	virtual ~RepeatedStateContractionsWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();

private:
	RepeatedStateContractions *modeler;

	ComputationThread<RepeatedStateContractions> *thread;

private slots:
	void on_numContractions_valueChanged(const QString & newText);

	void spawnResultWidget();

};
#endif /*REPEATEDSTATECONTRACTIONSWIDGET_H_*/
