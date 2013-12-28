#ifndef WORKLOADDISTRIBUTIONWIDGET_H_
#define WORKLOADDISTRIBUTIONWIDGET_H_

#include "ModuleWidget.h"
#include "ui_WorkloadDistributionWidget.h"

#include "data/WorkloadVector.hpp"

#include <QWidget>
#include <utility>

using namespace ivk;

class WorkloadDistributionWidget : public ModuleWidget, protected Ui::WorkloadDistributionWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(WorkloadDistributionWidget)

public:
	WorkloadDistributionWidget();
	WorkloadDistributionWidget(const IWorkloadVector* workloads);
	virtual ~WorkloadDistributionWidget();

	void createActions() {};
	void loadModel() {};

	void updateDistributionGraph();
	void setupDistributionTable();

private:
	const WorkloadVector<ivector>* workloads;

	QwtPlotCurve *distributionCurve;
};

#endif /*WORKLOADDISTRIBUTIONWIDGET_H_*/
