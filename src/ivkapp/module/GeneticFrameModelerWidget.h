#ifndef GENETICFRAMEMODELERWIDGET_H_
#define GENETICFRAMEMODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_GeneticFrameModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "DataProvider.hpp"
#include "computation/GeneticFrameModeler.h"
#include "CyclePeriodWizard.h"

using namespace ivk;

class GeneticFrameModelerWidget : public ModuleWidget, private Ui::GeneticFrameModelerWidget, public DataProvider<Trace>
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(GeneticFrameModelerWidget)

public:
	GeneticFrameModelerWidget(CyclePeriodWizard* wizard = 0);

	virtual ~GeneticFrameModelerWidget();

	const Trace* getData();

protected:
	void createActions();

	void loadModel();

	void initModel();

	void postCreation();

	void updateGUI();
private:
	GeneticFrameModeler *modeler;

	ComputationThread<GeneticFrameModeler> *thread;

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

	void on_framelevel_valueChanged( const QString & newText);

	void spawnResultWidget();

};

#endif /*GENETICFRAMEMODELERWIDGET_H_*/
