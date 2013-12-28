#ifndef AUTOSMPMODELERWIDGET_H_
#define AUTOSMPMODELERWIDGET_H_

#include "ModuleWidget.h"
#include "ui_AutoSMPModelerWidget.h"

#include "ComputationThread.hpp"

#include "data/Trace.h"
#include "computation/AutoSMPModeler.h"

using namespace ivk;

class AutoSMPModelerWidget : public ModuleWidget, private Ui::AutoSMPModelerWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(AutoSMPModelerWidget)
	
public:
	AutoSMPModelerWidget();
	
	virtual ~AutoSMPModelerWidget();
	
protected:
	void createActions();
	
	void loadModel();
	
	void initModel();
	
private:	
	AutoSMPModeler *modeler;
	
	ComputationThread<AutoSMPModeler> *thread;
	
private slots:
	void on_numdstepsEdit_valueChanged(const QString & newText);
	
	void on_numstatesEdit_valueChanged(const QString & newText);

	void on_confniveauEdit_valueChanged(const QString & newText);
	
	void spawnResultWidget();
	
};

#endif /*AUTOSMPMODELERWIDGET_H_*/
