#ifndef PFWORKLOADWIDGET_H_
#define PFWORKLOADWIDGET_H_

#include "modbase/ModuleWidget.h"
#include "ui_base/ui_PFWorkloadWidget.h"

#include "data/ISMPPFResult.h"


using namespace ivk;


class PFWorkloadWidget : public ModuleWidget, private Ui::PFWorkloadWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(PFWorkloadWidget)
	
public:
	PFWorkloadWidget();
	
	virtual ~PFWorkloadWidget();

	virtual void createActions();
	
	virtual void loadModel();
	
	virtual void initModel();
	
	const ISMPPFResult * result;
	
private slots:
	void on_computeButton_clicked();
};

#endif /*PFWORKLOADWIDGET_H_*/
