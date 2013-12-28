#ifndef SCENEMODELERWIDGET_H_
#define SCENEMODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_SceneModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "computation/SceneModeler.h"

using namespace ivk;

class SceneModelerWidget : public ModuleWidget, private Ui::SceneModelerWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(SceneModelerWidget)

public:
	SceneModelerWidget();

	virtual ~SceneModelerWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();

private:
	SceneModeler *modeler;

	ComputationThread<SceneModeler> *thread;

private slots:
	void on_numdstepsEdit_valueChanged(const QString & newText);

	void on_epsilon_valueChanged(const QString & newText);

	void spawnResultWidget();

};

#endif /*SCENEMODELERWIDGET_H_*/
