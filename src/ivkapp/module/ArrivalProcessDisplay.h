#ifndef ARRIVALPROCESSDISPLAY_H_
#define ARRIVALPROCESSDISPLAY_H_

#include "ModuleWidget.h"
#include "DataProvider.hpp"
#include "ui_ArrivalProcessDisplay.h"

namespace ivk
{
class SSMProcess;
}

using ivk::SSMProcess;

class ArrivalProcessDisplay : public ModuleWidget, private Ui::ArrivalProcessDisplay, public DataProvider<SSMProcess>
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(ArrivalProcessDisplay)

public:
	ArrivalProcessDisplay();

	ArrivalProcessDisplay(SSMProcess *process);

	virtual ~ArrivalProcessDisplay();

	SSMProcess *getProcess()
	{
		return process;
	}

	const SSMProcess* getData()
	{
		return process;
	}

protected:
	void createActions();

	void loadModel();

	void createFileElements();

	void createDefaulSubwidgets();

private:
	void initializeDisplay();
	SSMProcess *process;

private slots:
	void createServiceProcessRequested();

	void createRepeatedStateContractionsRequested();

	void createStateMergeRequested();

	void createStatePartitioningRequested();
};

#endif /*ARRIVALPROCESSDISPLAY_H_*/
