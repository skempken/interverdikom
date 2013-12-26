#ifndef WIENERHOPFWIDGET_H_
#define WIENERHOPFWIDGET_H_

#include "ui_base/ui_WienerHopfWidget.h"
#include "ModuleWidget.h"
#include "computation/SMPWienerHopf.h"
#include "data/SSMPQueue.h"
#include "ComputationThread.hpp"

using namespace ivk;

class WienerHopfWidget : public ModuleWidget, public Ui::WienerHopfWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(WienerHopfWidget)

protected:
	SMPWienerHopf* whComputation;
	ComputationThread<SMPWienerHopf>* thread;

public:
	WienerHopfWidget();
	virtual ~WienerHopfWidget();

	void createActions() {};
	virtual void initModel();
	void loadModel();
	void updateGUI();

public slots:
	void on_numIterations_valueChanged(int value);
	void on_relaxationSpin_valueChanged(int value);
	void on_epsilon_valueChanged(int value);
	void spawnResultWidget();
};

#endif /*WIENERHOPFWIDGET_H_*/
