#ifndef MMCMODELERWIDGET_H_
#define MMCMODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_MMCModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "computation/MMCModeler.h"

using namespace ivk;

class MMCModelerWidget : public ModuleWidget, private Ui::MMCModelerWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(MMCModelerWidget)

public:
	MMCModelerWidget();

	virtual ~MMCModelerWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();
private:
	MMCModeler *modeler;

	ComputationThread<MMCModeler> *thread;

private slots:
	void on_numdstepsEdit_valueChanged(const QString & newText);

	void on_wEdit_valueChanged(const QString & newText);

	void on_MaEdit_valueChanged(const QString & newText);

	void on_MsEdit_valueChanged(const QString & newText);

	void spawnResultWidget();

};

#endif /*MMCMODELERWIDGET_H_*/
