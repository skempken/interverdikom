#ifndef SMPPOLYFACWIDGET_H_
#define SMPPOLYFACWIDGET_H_

#include "modbase/ModuleWidget.h"
#include "ui_base/ui_SMPPolyFacWidget.h"

#include "data/SSMPQueue.h"

#include "modbase/ComputationThread.hpp"

using namespace ivk;

namespace ivk {
class SMPPolyFac;
}

class SMPPolyFacWidget : public ModuleWidget, private Ui::SMPPolyFacWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(SMPPolyFacWidget)

public:
	SMPPolyFacWidget();
	virtual ~SMPPolyFacWidget();

protected:
	void createActions();

	void loadModel();

	void initModel();

	const SSMPQueue * queue;

	SMPPolyFac * computation;

	class ComputationThread<SMPPolyFac> * thread;

private slots:
	void spawnResultWidget();

	void rootsMethodChanged(int methodIndex);

	void derminantMethodChanged(int methodIndex);
};

#endif /*SMPPOLYFACWIDGET_H_*/
