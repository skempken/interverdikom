#ifndef ONESTATEMODELERWIDGET_H_
#define ONESTATEMODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_RenewalModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "computation/RenewalModeler.h"

using namespace ivk;

class RenewalModelerWidget : public ModuleWidget, private Ui::RenewalModelerWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(RenewalModelerWidget)

public:
	RenewalModelerWidget();

	virtual ~RenewalModelerWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();

private:
	RenewalModeler *modeler;

	ComputationThread<RenewalModeler> *thread;

private slots:

	void spawnResultWidget();

	void on_numdstepsEdit_valueChanged(int value);

};

#endif /*ONESTATEMODELERWIDGET_H_*/
