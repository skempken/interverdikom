#ifndef SAPARTITIONMODELERWIDGET_H_
#define SAPARTITIONMODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_SAPartitionModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "computation/SAPartitionModeler.h"

using namespace ivk;

class SAPartitionModelerWidget : public ModuleWidget, private Ui::SAPartitionModelerWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(SAPartitionModelerWidget)

public:
	SAPartitionModelerWidget();

	virtual ~SAPartitionModelerWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();

private:
	SAPartitionModeler *modeler;

	ComputationThread<SAPartitionModeler> *thread;

private slots:
	void on_numdstepsEdit_valueChanged(const QString & newText);

	void on_numstatesEdit_valueChanged(const QString & newText);

	void on_autoc_valueChanged(const QString & newText);

	void on_initTemp_valueChanged(const QString & newText);

	void on_abortTemp_valueChanged(const QString & newText);

	void on_alpha_valueChanged(const QString & newText);

	void spawnResultWidget();

};

#endif /*PARTITIONMODELERWIDGET_H_*/
