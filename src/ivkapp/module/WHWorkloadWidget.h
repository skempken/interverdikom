#ifndef WHWORKLOADWIDGET_H_
#define WHWORKLOADWIDGET_H_

#include "ui_base/ui_WHWorkloadWidget.h"
#include "ModuleWidget.h"
#include "computation/ISMPWHWorkload.h"
#include "data/ISMPWHFactors.h"
#include "ComputationThread.hpp"

using namespace ivk;

class WHWorkloadWidget : public ModuleWidget, public Ui::WHWorkloadWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(WHWorkloadWidget)
	
private:
	ISMPWHWorkload* workloadComputation;
	ComputationThread<ISMPWHWorkload>* thread;
	
public:
	WHWorkloadWidget();
	virtual ~WHWorkloadWidget();
	
	void createActions() {};
	void initModel();
	void loadModel();
	void updateGUI();
	
public slots:
	void on_upTo_valueChanged(int value);
	void spawnResultWidget();
};

#endif /*WHWORKLOADWIDGET_H_*/
