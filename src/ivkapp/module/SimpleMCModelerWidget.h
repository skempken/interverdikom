#ifndef SIMPLEMMODELERWIDGET_H_
#define SIMPLEMMODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_SimpleMCModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "computation/SimpleMCModeler.h"

using namespace ivk;

class SimpleMCModelerWidget : public ModuleWidget, private Ui::SimpleMCModelerWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(SimpleMCModelerWidget)

public:
	SimpleMCModelerWidget();

	virtual ~SimpleMCModelerWidget();

protected:
	void createActions();

	void loadModel();

	void postCreation();

	void initModel();

	void updateGUI();

private:
	SimpleMCModeler *modeler;

	ComputationThread<SimpleMCModeler> *thread;

private slots:
	void on_numdstepsEdit_valueChanged(const QString & newText);

	void on_numstatesEdit_valueChanged(const QString & newText);

	void spawnResultWidget();

};

#endif /*SIMPLEMMODELERWIDGET_H_*/
