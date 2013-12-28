#ifndef GENETICMODELERWIDGET_H_
#define GENETICMODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_GeneticModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "computation/GeneticModeler.h"

using namespace ivk;

class GeneticModelerWidget : public ModuleWidget, private Ui::GeneticModelerWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(GeneticModelerWidget)

public:
	GeneticModelerWidget();

	virtual ~GeneticModelerWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();
private:
	GeneticModeler *modeler;

	ComputationThread<GeneticModeler> *thread;

private slots:
	void on_numdstepsEdit_valueChanged(const QString & newText);

	void on_numstatesEdit_valueChanged(const QString & newText);

	void on_numautocEdit_valueChanged(const QString & newText);

	void on_numiterationsEdit_valueChanged(const QString & newText);

	void on_numpoolEdit_valueChanged(const QString & newText);

	void on_mutBlock_valueChanged( const QString & newText);

	void on_mutInverse_valueChanged( const QString & newText);

	void on_mutShuffle_valueChanged( const QString & newText);

	void on_mutSwap_valueChanged( const QString & newText);

	void on_mutCrossover_valueChanged( const QString & newText);

	void spawnResultWidget();

};

#endif /*GENETICMODELERWIDGET_H_*/
