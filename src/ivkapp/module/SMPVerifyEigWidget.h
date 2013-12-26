#ifndef SMPVERIFYEIGWIDGET_H_
#define SMPVERIFYEIGWIDGET_H_

#include "modbase/ModuleWidget.h"
#include "ui_base/ui_SMPVerifyEigWidget.h"

#include "data/SSMPQueue.h"

#include "modbase/ComputationThread.hpp"

using namespace ivk;

namespace ivk {
class SMPVerifyEig;
}

class SMPVerifyEigWidget : public ModuleWidget, private Ui::SMPVerifyEigWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(SMPVerifyEigWidget)
	
public:
	SMPVerifyEigWidget();
	virtual ~SMPVerifyEigWidget();
	
protected:
	void createActions();
	
	void loadModel();
	
	void initModel();
	
	const SSMPQueue * queue;
	
	SMPVerifyEig * computation;
	
	class ComputationThread<SMPVerifyEig> * thread;
	
private slots:
	void spawnResultWidget();
};

#endif /*SMPVERIFYEIGWIDGET_H_*/
