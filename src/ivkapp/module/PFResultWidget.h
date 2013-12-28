#ifndef PFRESULTWIDGET_H_
#define PFRESULTWIDGET_H_

#include "modbase/ModuleWidget.h"
#include "modbase/DataProvider.hpp"
#include "ui_base/ui_PFResultWidget.h"

#include "data/ISMPPFResult.h"

using namespace ivk;

class PFResultWidget : public ModuleWidget, private Ui::PFResultWidget,
	public DataProvider<ISMPPFResult> {
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(PFResultWidget)

public:
	PFResultWidget();

	PFResultWidget(ISMPPFResult * result);

	virtual ~PFResultWidget();

	virtual void createActions();

	virtual void loadModel();

	virtual ISMPPFResult * getData() {
		return result;
	}

protected:
	ISMPPFResult * result;

private slots:
	void calculateWorkloadRequested();
	
	void initPlot();
	
	void initTable();
	
	void initDisplay() {
		initPlot();
		initTable();
	}
};

#endif /*PFRESULTWIDGET_H_*/
