#ifndef ADDSERVICEPROCESSWIDGET_H_
#define ADDSERVICEPROCESSWIDGET_H_

#include "modbase/ModuleWidget.h"
#include "ui_base/ui_AddServiceProcessWidget.h"

class AddServiceProcessWidget : public ModuleWidget, private Ui::AddServiceProcessWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(AddServiceProcessWidget)
	
public:
	AddServiceProcessWidget();
	virtual ~AddServiceProcessWidget();
	
protected:
	void createActions();
	
	void loadModel();
	
	void initModel();
	
private slots:
	void on_addButton_clicked();
	
	void on_factorSpin_valueChanged(double newValue);
	
	void on_capacitySpin_valueChanged(double newValue);
};

#endif /*ADDSERVICEPROCESSWIDGET_H_*/
