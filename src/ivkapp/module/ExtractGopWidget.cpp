#include "ExtractGopWidget.h"

#include "modbase/DataProvider.hpp"
#include "module/TraceDisplay.h"

#include "data/Trace.h"

#include <vector>

#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_marker.h>
#include <qwt-qt4/qwt_symbol.h>

#include <utility/Logging.hpp>

FACTORY_DEFINITIONS_FOR(ExtractGopWidget)

using std::vector;
using ivk::Logging;

ExtractGopWidget::ExtractGopWidget()
: trace(0), correlationCurve(0), boundMarker(0)
{
	setupUi(this);

	boundMarker = new QwtPlotMarker();
	boundMarker->setLineStyle(QwtPlotMarker::HLine);
	boundMarker->setLinePen(QPen(QColor(0x88, 0x88, 0xee), 3.0));
	boundMarker->attach(plot);

	QwtPlotMarker *nullMarker = new QwtPlotMarker();
	nullMarker->setLineStyle(QwtPlotMarker::HLine);
	nullMarker->setYValue(0.0);
	nullMarker->attach(plot);
}

ExtractGopWidget::~ExtractGopWidget() {
}

void ExtractGopWidget::boundSliderChanged(int newValue) {
	updateBound((double)newValue / 100.0);
}

void ExtractGopWidget::loadFileData() {

}

void ExtractGopWidget::createActions() {

}

void ExtractGopWidget::updateLengthRange(int min, int max) {
	lengthSlider->setMinimum(min);
	lengthSlider->setMaximum(max);
	lengthSpin->setMinimum(min);
	lengthSpin->setMaximum(max);
}

void ExtractGopWidget::updateLength(int newLength) {
	autoCorrelation = trace->getAutocorrelation(newLength);

	int size = Ub(autoCorrelation) - Lb(autoCorrelation) + 1;
	double *xValues = new double[size];
	double *yValues = new double[size];

	int i = 0;
	for (int j = Lb(autoCorrelation); j <= Ub(autoCorrelation); j++) {
		xValues[i] = j;
		yValues[i] = _double(autoCorrelation[j]);
		i++;
	}

	if (correlationCurve) {
		correlationCurve->detach();
		delete correlationCurve;
	}

	correlationCurve = new QwtPlotCurve("Autocorrelation");
	correlationCurve->setData(xValues, yValues, size);
	correlationCurve->attach(plot);
	plot->replot();

	delete[] xValues;
	delete[] yValues;

	if (lengthSlider->value() != newLength) {
		lengthSlider->setValue(newLength);
	}

	if (lengthSpin->value() != newLength) {
		lengthSpin->setValue(newLength);
	}

	updateCalculatedInterval();
}

void ExtractGopWidget::updateCalculatedInterval() {
	double bound = boundSpin->value();

	vector<real> maxes;
	vector<int> maxIndices;
	for (int i = Lb(autoCorrelation) + 1; i < Ub(autoCorrelation); i++) {
		if ((autoCorrelation[i-1] < autoCorrelation[i]) &&
				(autoCorrelation[i] > autoCorrelation[i+1])) {
			maxes.push_back(autoCorrelation[i]);
			maxIndices.push_back(i);
		}
	}

	for (list<QwtPlotMarker*>::iterator it = maxMarkers.begin(); it != maxMarkers.end(); it++) {
		(*it)->detach();
		delete (*it);
	}

	maxMarkers.clear();

	int firstInterestingMax = -1, lastInterestingMax, interestingMaxCount = 0;
	double highestMax = 0.0, maxSum = 0;

	for (uint i = 0; i < maxes.size(); i++) {
		real maxValue = maxes[i];
		int maxIndex = maxIndices[i];

		if (maxValue > highestMax) {
			highestMax = _double(maxValue);
		}

		maxSum += _double(maxValue);

		QwtPlotMarker *newMarker = new QwtPlotMarker();

		newMarker->attach(plot);
		newMarker->setXValue(maxIndex);
		newMarker->setYValue(_double(maxValue));
		maxMarkers.push_back(newMarker);

		if (maxValue > bound) {
			newMarker->setLineStyle(QwtPlotMarker::VLine);
			newMarker->setLinePen(QPen(QColor(0x99, 0xcc, 0x99), 3.0,
					Qt::DotLine));

			if (firstInterestingMax == -1) {
				firstInterestingMax = maxIndex;
			}

			interestingMaxCount++;
			lastInterestingMax = maxIndex;
		} else {
			newMarker->setSymbol(QwtSymbol(QwtSymbol::Ellipse, QBrush(QColor(0xff, 0x66, 0x66)), QPen(QColor("black"), 1.0), QSize(6, 6)));
		}
	}

	double averageMax = (maxSum / (double)(maxes.size()));

	averageLabel->setText(QString("%1").arg(averageMax));
	highestLabel->setText(QString("%1").arg(highestMax));

	if (interestingMaxCount > 1) {
		int interval = (lastInterestingMax - firstInterestingMax) / (interestingMaxCount - 1);
		intervalEdit->setValue(interval);
		performButton->setEnabled(true);
	} else {
		intervalEdit->setValue(0);
		performButton->setEnabled(false);
	}

	plot->replot();
}

void ExtractGopWidget::createAggregatedTrace() {
	int interval = intervalEdit->text().toInt();

	if (interval <= 1) {
		cerr << "Invalid interval for GoP aggregation." << endl;
		return;
	}

	rvector oldTraceVector = trace->getTrace();
	const int oldLength = VecLen(oldTraceVector);
	const int newLength = (int) ceil(oldLength / interval);
	rvector newTraceVector(Lb(oldTraceVector), Lb(oldTraceVector) + newLength -1);

	int offsetIntoGop = 0;
	int gopSizeSum = 0;
	int gopIndex = Lb(newTraceVector);

	for (int i = Lb(oldTraceVector); i <= Ub(oldTraceVector)+1; i++) {
		if (offsetIntoGop == interval) {
			newTraceVector[gopIndex] = gopSizeSum;
			gopIndex++;
			offsetIntoGop = gopSizeSum = 0;
		}

		gopSizeSum += (int)_double(oldTraceVector[i]);
		offsetIntoGop++;
	}

	TraceDisplay *newTraceDisplay = TraceDisplay::importFromRVector(newTraceVector);
	addSubWidget(newTraceDisplay, tr("Aggregated Trace"));
}

void ExtractGopWidget::updateBound(double newBound) {
	boundMarker->setYValue(newBound);

	int newSliderValue = (int)floor(newBound * 100);
	if (std::abs(newSliderValue - boundSlider->value()) > 1) {
		boundSlider->setValue(newSliderValue);
	}

	if (boundSpin->value() != newBound) {
		boundSpin->setValue(newBound);
	}

	updateCalculatedInterval();
}

void ExtractGopWidget::postCreation() {
	updateLength(min(trace->getLength(), 100));
	updateBound(0.5);
}

void ExtractGopWidget::useAverageMax() {
	updateBound(averageLabel->text().toDouble());
}

void ExtractGopWidget::initModel() {
	trace = (dynamic_cast<DataProvider<Trace>*>(parentModule))->getData();

	connect(lengthSlider, SIGNAL(valueChanged(int)), this, SLOT(updateLength(int)));
	connect(lengthSpin, SIGNAL(valueChanged(int)), this, SLOT(updateLength(int)));
	connect(boundSpin, SIGNAL(valueChanged(double)), this, SLOT(updateBound(double)));
	connect(boundSlider, SIGNAL(sliderMoved(int)), this, SLOT(boundSliderChanged(int)));
	connect(useAvgButton, SIGNAL(clicked()), this, SLOT(useAverageMax()));
	connect(performButton, SIGNAL(clicked()), this, SLOT(createAggregatedTrace()));

	updateLengthRange(0, trace->getLength());
	updateBound(0.5);
}
