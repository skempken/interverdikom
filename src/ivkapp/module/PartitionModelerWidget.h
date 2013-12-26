#ifndef PARTITIONMODELERWIDGET_H_
#define PARTITIONMODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_PartitionModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "computation/PartitionModeler.h"

using namespace ivk;

class PartitionModelerWidget : public ModuleWidget, private Ui::PartitionModelerWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(PartitionModelerWidget)

public:
	PartitionModelerWidget();

	virtual ~PartitionModelerWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();

private:
	PartitionModeler *modeler;

	ComputationThread<PartitionModeler> *thread;

private slots:
	void on_numdstepsEdit_valueChanged(const QString & newText);

	void on_numstatesEdit_valueChanged(const QString & newText);

	void spawnResultWidget();

};

#endif /*PARTITIONMODELERWIDGET_H_*/
