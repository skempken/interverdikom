#include "PFResultWidget.h"

#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_marker.h>
#include <qwt-qt4/qwt_symbol.h>

#include <cmath>

#include <sstream>

#include "module/PFWorkloadWidget.h"

FACTORY_DEFINITIONS_FOR( PFResultWidget)

using std::stringstream;

PFResultWidget::PFResultWidget() :
	result(0) {
	setupUi(this);
	initDisplay();
}

PFResultWidget::PFResultWidget(ISMPPFResult * result) :
	result(result) {
	setupUi(this);
	initDisplay();
}

PFResultWidget::~PFResultWidget() {
}

void PFResultWidget::initPlot() {
	plot->clear();

	QwtPlotMarker *nullMarker1 = new QwtPlotMarker();
	nullMarker1->setLineStyle(QwtPlotMarker::HLine);
	nullMarker1->setYValue(0.0);
	nullMarker1->attach(plot);

	QwtPlotMarker *nullMarker2 = new QwtPlotMarker();
	nullMarker2->setLineStyle(QwtPlotMarker::VLine);
	nullMarker2->setXValue(0.0);
	nullMarker2->attach(plot);

	plot->replot();

	if (!result) {
		return;
	}

	for (int i = Lb(result->eigenValues); i <= Ub(result->eigenValues); i++) {
		QwtPlotMarker *evMarker = new QwtPlotMarker();
		QwtSymbol evSymbol(QwtSymbol::XCross, QBrush(Qt::SolidPattern), QPen(
				QColor("black")), QSize(7, 7));
		evMarker->setSymbol(evSymbol);
		evMarker->setXValue(_double(Re(mid(result->eigenValues[i]))));
		evMarker->setYValue(_double(Im(mid(result->eigenValues[i]))));
		evMarker->attach(plot);
	}

	int circlePoints = 200;
	double *xValues = new double[circlePoints];
	double *yValues = new double[circlePoints];

	for (int i = 0; i < circlePoints; i++) {
		xValues[i] = cos((double(i) / circlePoints) * 2 * M_PI);;
		yValues[i] = sin((double(i) / circlePoints) * 2 * M_PI);
	}

	QwtPlotCurve * circleCurve = new QwtPlotCurve("Circle");
	circleCurve->setData(xValues, yValues, circlePoints);
	circleCurve->setPen(QPen(QColor("Grey")));
	circleCurve->attach(plot);
	plot->replot();


	rvector absEvals = abs(mid(result->eigenValues));
	real maxEval = absEvals[Lb(absEvals)];
	for (int i = Lb(absEvals); i <= Ub(absEvals); i++) {
		if (absEvals[i] > maxEval) {
			maxEval = absEvals[i];
		}
	}

	double scaleFactor = _double(maxEval) * 1.0;
	plot->setAxisScale(0, -scaleFactor, scaleFactor);
	plot->setAxisScale(2, -scaleFactor, scaleFactor);
	plot->replot();

	delete[] xValues;
	delete[] yValues;
}

void PFResultWidget::initTable() {
	table->setRowCount(VecLen(result->eigenValues));
	table->setColumnCount(2 + Ub(result->eigenVectors, 1) - Lb(
			result->eigenVectors, 1));

	QStringList colHeaders;
	colHeaders << "Eigenvalue";
	for (int i = Lb(result->eigenVectors, 1); i <= Ub(result->eigenVectors, 1); i++) {
		colHeaders << QString("Eigenvector(%1)").arg(i);
	}

	table->setHorizontalHeaderLabels(colHeaders);

	for (int i = Lb(result->eigenValues); i <= Ub(result->eigenValues); i++) {
		stringstream evalStr;
		evalStr << Sup(result->eigenValues[i]) << endl << Inf(
				result->eigenValues[i]);
		QTableWidgetItem *evalItem = new QTableWidgetItem(
				QString::fromStdString(evalStr.str()));
		//evalItem->setSizeHint(QSize(35, 150));
		table->setItem(i - Lb(result->eigenValues), 0, evalItem);

		for (int j = Lb(result->eigenVectors, 1); j <= Ub(result->eigenVectors,
				1); j++) {
			stringstream evecStr;
			evecStr << Sup(result->eigenVectors[j][i]) << endl << Inf(
					result->eigenVectors[j][i]);
			QTableWidgetItem *evecItem = new QTableWidgetItem(
					QString::fromStdString(evecStr.str()));
			//evecItem->setSizeHint(QSize(35, 150));
			table->setItem(i - Lb(result->eigenValues), j - Lb(
					result->eigenVectors, 1) + 1, evecItem);
		}
	}

	table->resizeColumnsToContents();
	table->resizeRowsToContents();
}

void PFResultWidget::createActions() {
	QAction *workloadAction = new QAction(tr(
			"Compute workload probabilities..."), this);
	connect(workloadAction, SIGNAL(triggered()), this, SLOT(calculateWorkloadRequested()));
	addAction(workloadAction);
}

void PFResultWidget::calculateWorkloadRequested() {
	addSubWidget(new PFWorkloadWidget, tr("Compute workload probabilities"));
}

void PFResultWidget::loadModel() {

}
