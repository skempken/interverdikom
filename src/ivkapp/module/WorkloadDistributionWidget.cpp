#include "WorkloadDistributionWidget.h"

#include <qwt-qt4/qwt_legend.h>
#include <qwt-qt4/qwt_legend_item.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_marker.h>

FACTORY_DEFINITIONS_FOR(WorkloadDistributionWidget)

WorkloadDistributionWidget::WorkloadDistributionWidget()
: workloads(0) , distributionCurve(0)
{
	setupUi(this);
}


WorkloadDistributionWidget::WorkloadDistributionWidget(const WorkloadVector<ivector>* workloads)
: workloads(workloads) , distributionCurve(0)
{
	setupUi(this);
	updateDistributionGraph();
	setupDistributionTable();
}

WorkloadDistributionWidget::~WorkloadDistributionWidget()
{
}

void WorkloadDistributionWidget::updateDistributionGraph(){
	const rvector workloadDistribution = mid( this->workloads->getWorkloadVector() );

	int size = Ub( workloadDistribution ) - Lb( workloadDistribution ) + 1;
	double *xValues = new double[size];
	double *yValues = new double[size];

	int i = 0;
	for (int j = Lb( workloadDistribution ); j <= Ub( workloadDistribution ); j++) {
		xValues[i] = j;
		yValues[i] = _double( workloadDistribution[j] );
		i++;
	}

	distributionCurve = new QwtPlotCurve( "Workload Distribution" );
	distributionCurve->setData(xValues, yValues, size);
	distributionCurve->attach(distGraph);
	distGraph->replot();

	delete[] xValues;
	delete[] yValues;
}

void WorkloadDistributionWidget::setupDistributionTable(){
	const ivector wlvector = this->workloads->getWorkloadVector();
	const int distLb = Lb( wlvector );
	const int distUb = Ub( wlvector );
	const int distCount = distUb - distLb + 1;

	distTable->setRowCount(distCount);

	QStringList rowHeaders;
	for (int i = distLb; i <= distUb; i++) {
		rowHeaders << QString("%1").arg(i);
	}

	distTable->setVerticalHeaderLabels(rowHeaders);

	for (int i = distLb; i <= distUb; i++) {
			stringstream strStr;
			strStr << Scientific << SetPrecision(15,16) << Sup(wlvector[i]) << endl
					<< Scientific << SetPrecision(15,16) << Inf(wlvector[i]);

			QString itemText = QString::fromStdString(strStr.str());
			QTableWidgetItem *newItem =	new QTableWidgetItem(itemText);
			distTable->setItem(i , 0 , newItem);
	}

	distTable->resizeRowsToContents();
}
