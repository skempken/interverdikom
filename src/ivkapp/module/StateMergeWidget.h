#ifndef STATEMERGEWIDGET_H_
#define STATEMERGEWIDGET_H_

#include "ModuleWidget.h"
#include "ui_StateMergeWidget.h"

#include "ComputationThread.hpp"
#include "module/TraceDisplay.h"

#include "data/Trace.h"
#include "computation/StateMerge.h"

#include <QWidget>

using namespace ivk;

class StateMergeWidget : public ModuleWidget, private Ui::StateMergeWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(StateMergeWidget)
	
public:
	StateMergeWidget();
	
	virtual ~StateMergeWidget();
	
protected:
	void createActions();
	
	void loadModel();
	
	void initModel();
	
	void updateGUI();
	
	void generateContractTable( int states , rvector statProb , rvector means , intvector contractionVector);
private:	
	StateMerge *modeler;
	
	void setTableUnchecked();
	
	void setTableCellsChecked(intvector cells);
	
	ComputationThread<StateMerge> *thread;
	
private slots:
	void handleCellEvent(int row, int col);
	
	void on_numContractions_valueChanged(const QString & newText);
	
	void on_statProb_clicked();
	
	void on_means_clicked();
	
	void tableToVector();
		
	void spawnResultWidget();
	
};
#endif /*STATEMERGEWIDGET_H_*/
