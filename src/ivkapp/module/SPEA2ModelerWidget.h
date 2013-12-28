#ifndef SPEA2MODELERWIDGET_H_
#define SPEA2MODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_SPEA2ModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "computation/SPEA2Modeler.h"

using namespace ivk;

class SPEA2ModelerWidget : public ModuleWidget, private Ui::SPEA2ModelerWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(SPEA2ModelerWidget)

public:
	SPEA2ModelerWidget();

	virtual ~SPEA2ModelerWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();
private:
	SPEA2Modeler *modeler;

	ComputationThread<SPEA2Modeler> *thread;

private slots:
	void on_numdstepsEdit_valueChanged(const QString & newText);

	void on_numstatesEdit_valueChanged(const QString & newText);

	void on_popSize_valueChanged(const QString & newText);

	void on_archiveSize_valueChanged(const QString & newText);

	void on_numIterations_valueChanged(const QString & newText);

	void on_autocorrelation_valueChanged(const QString & newText);

	void on_mutCrossover_valueChanged(const QString & newText);

	void on_mutInverse_valueChanged(const QString & newText);

	void on_mutBlock_valueChanged(const QString & newText);

	void on_mutShuffle_valueChanged(const QString & newText);

	void on_mutSwap_valueChanged(const QString & newText);

	void spawnResultWidget();

};

#endif /*SPEA2MODELERWIDGET_H_*/
