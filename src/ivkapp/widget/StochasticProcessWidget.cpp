#include "StochasticProcessWidget.h"

#include <algorithm>
#include <iostream>

#include <qwt-qt4/qwt_legend.h>
#include <qwt-qt4/qwt_legend_item.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_marker.h>

#include <QHeaderView>
#include <QDoubleValidator>

#include "data/SSMProcess.h"
#include "data/GIProcess.h"

#include "util/PlotUtil.h"
#include "util/CompUtil.h"

StochasticProcessWidget::StochasticProcessWidget(QWidget* parent) :
	QWidget(parent), correlationCurve(0) {
	setupUi(this);

	// Add check boxes
	for (int i = 0; i <= 5; i++) {
		if (i == 4) { // Except for Range row
			continue;
		}

		QTableWidgetItem *item = distGraphTable->item(i, 0);

		if (item) {
			item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

			if (i != 3) {
				item->setCheckState(Qt::Checked);
			} else {
				item->setCheckState(Qt::Unchecked);
			}
		}
	}

	distGraphTable->horizontalHeader()->hide();
	quantileTable->verticalHeader()->hide();

	quantileEdit->setValidator(new QDoubleValidator(0.0, 1.0, 15, quantileEdit));


	distGraphTable->resizeRowsToContents();
	quantileTable->resizeRowsToContents();
}

StochasticProcessWidget::~StochasticProcessWidget() {
}

void StochasticProcessWidget::handleQuantileChange(int row, int column) {
	if (column == (quantileTable->columnCount() - 1)) {
		quantileTable->removeRow(row);
	}
}

void StochasticProcessWidget::displayProcess(const SSMProcess *process) {
	if (!process) {
		cout << "StochasticProcessWidget: process is 0, canceling initialization..." << endl;
		return;
	}

	this->process = process;

	statProbs = process->getStationaryProbabilities();

	imatrix distributionMatrix = process->getDistributions();
	for (int i = Lb(distributionMatrix, 1); i <= Ub(distributionMatrix, 1); ++i) {
		addIntervalDistributionToGraph(QString("State #%1").arg(i), distributionMatrix[i]);
	}

	setupDistributionTable(distributionMatrix);

	transitionMatrix = process->getTransitionMatrix();
	setupTransitionTable(transitionMatrix);

	upToSpin->setValue(10);
	updateAutocorrelationCurve();

	connect(distGraphTable, SIGNAL(cellChanged(int, int)), this, SLOT(handleCellEvent(int, int)));
	connect(quantileTable, SIGNAL(cellClicked(int
							, int)), this, SLOT(handleQuantileChange(int, int)));

							updateTransitionColors();
							updateColors();
	connect(upToSpin, SIGNAL(valueChanged(int)), this, SLOT(updateAutocorrelationCurve()));
	connect(addQuantileButton, SIGNAL(clicked()), this, SLOT(addQuantile()));

	if (process->getNumStates() == 1) {
		tabWidget->removeTab(4);
		tabWidget->removeTab(3);
		tabWidget->removeTab(2);

		distGraphTable->setRowHidden(3, true);
	}

	setupQuantileTable();
}

void StochasticProcessWidget::setupQuantileTable() {
	int distCount = process->getNumStates();
	quantileTable->setColumnCount(distCount + 2);

	QStringList quantileHeaderLabels;
	quantileHeaderLabels << "Limit";

	for (int i = 1; i <= distCount; i++) {
		quantileHeaderLabels << QString("S%1").arg(i);
	}

	quantileHeaderLabels << " ";

	quantileTable->setHorizontalHeaderLabels(quantileHeaderLabels);
}

void StochasticProcessWidget::setupTransitionTable(
		const imatrix & transitionMatrix) {
	IvkTableWidget *table = transitionTable;
	table->clear();

	const int rows = Ub(transitionMatrix, 1) - Lb(
			transitionMatrix, 1) + 1;
	const int cols = Ub(transitionMatrix, 2) - Lb(
			transitionMatrix, 2) + 1;
	table->setRowCount(rows);
	table->setColumnCount(cols);

	// Column headers
	for (int col = Lb(transitionMatrix, 2); col <= Ub(
			transitionMatrix, 2); ++col) {
		QTableWidgetItem* columnHeader =
				new QTableWidgetItem(QString("S%1").arg(col));
		table->setHorizontalHeaderItem(col - Lb(
				transitionMatrix, 2), columnHeader);
	}

	// Values
	Qt::ItemFlag flags = Qt::ItemIsEnabled;
	for (int row = Lb(transitionMatrix, 1); row <= Ub(
			transitionMatrix, 1); ++row) {
		// Row headers
		QTableWidgetItem* rowHeader =
				new QTableWidgetItem(QString("S%1 ->").arg(row));
		table->setVerticalHeaderItem(row - Lb(
				transitionMatrix, 1), rowHeader);

		// Values
		for (int col = Lb(transitionMatrix, 2); col
				<= Ub(transitionMatrix, 2); ++col) {
			double
					lowerBound =
							cxsc::_double(Inf(transitionMatrix[row][col]));
			double
					upperBound =
							cxsc::_double(Sup(transitionMatrix[row][col]));
			QTableWidgetItem* cellItem = 0;

			cellItem = new QTableWidgetItem(QString("%1\n%2").arg(lowerBound).arg(upperBound));
			cellItem->setFlags(flags);
			cellItem->setFont(QFont(
					"Helvetica [Cronyx]", 8));
			table->setItem(row
					- Lb(transitionMatrix, 1), col
					- Lb(transitionMatrix, 2), cellItem);
		}
	}

	table->verticalHeader()->setUpdatesEnabled(false);
	for (int i = 0; i < rows; i++) {
		table->verticalHeader()->resizeSection(i, 30);
	}

	table->verticalHeader()->setUpdatesEnabled(true);

	for (int i = 0; i < transitionTable->rowCount(); i++) {
		transitionTable->setRowHeight(i, 40);
	}

	table->resizeRowsToContents();
}

void StochasticProcessWidget::updateTransitionColors() {
	int distCount = distGraphTable->columnCount() - 1;
	QColor cellColor;

	int rowLb = Lb(transitionMatrix, 1);
	int colLb = Lb(transitionMatrix, 2);

	for (int i = 0; i < distCount; i++) {
		for (int j = 0; j
				< transitionTable->columnCount(); j++) {
			QTableWidgetItem *item =
					transitionTable->item(i, j);
			if (!item) {
				continue;
			}

			double
					value =
							_double(mid(transitionMatrix[rowLb + i][colLb + j]));
			int hueValue = (int)round(255.0
					/ ((double)distCount / (double)i));
			cellColor.setHsv(hueValue, (int)floor(90.0
					* sqrt(value)), 255);
			item->setBackgroundColor(cellColor);
		}
	}
}

void StochasticProcessWidget::setupDistributionTable(
		const imatrix & distributionMatrix) {
	const int distLb = Lb(distributionMatrix, 1);
	const int distUb = Ub(distributionMatrix, 1);
	const int valueLb = Lb(distributionMatrix, 2);
	const int valueUb = Ub(distributionMatrix, 2);
	const int distCount = distUb - distLb + 1;
	const int valueCount = valueUb - valueLb + 1;

	distTable->setRowCount(valueCount);
	distTable->setColumnCount(distCount);

	QStringList columnHeaders;
	for (int i = distLb; i <= distUb; i++) {
		columnHeaders << QString("S%1").arg(i);
	}

	distTable->setHorizontalHeaderLabels(columnHeaders);

	QStringList rowHeaders;
	for (int i = valueLb; i <= valueUb; i++) {
		rowHeaders << QString("%1").arg(i);
	}

	distTable->setVerticalHeaderLabels(rowHeaders);

	for (int r = distLb; r <= distUb; r++) {
		for (int c = valueLb; c <= valueUb; c++) {
			double
					inf =
							_double(Inf(distributionMatrix[r][c]));
			double
					sup =
							_double(Sup(distributionMatrix[r][c]));

			QString itemText = QString("%1\n%2").arg(sup).arg(inf);

			QTableWidgetItem *newItem =
					new QTableWidgetItem(itemText);
			distTable->setItem(c - valueLb, r - distLb,
					newItem);
		}
	}
}

void StochasticProcessWidget::updateSelectAllColumn(
		int index) {
	bool allChecked = true;
	bool allUnchecked = true;

	for (int i = 0; i <= 2; i++) {
		QTableWidgetItem *item = distGraphTable->item(
				i, index);
		if (item) {
			bool isChecked = item->checkState()
					== Qt::Checked;
			bool isPartiallyChecked =
					item->checkState()
							== Qt::PartiallyChecked;
			allChecked = allChecked && isChecked
					&& !isPartiallyChecked;
			allUnchecked = allUnchecked && !isChecked
					&& !isPartiallyChecked;
		}
	}

	QTableWidgetItem *selectAllItem =
			distGraphTable->item(5, index);
	if (selectAllItem) {
		if (allChecked) {
			selectAllItem->setCheckState(Qt::Checked);
		} else if (allUnchecked) {
			selectAllItem->setCheckState(Qt::Unchecked);
		} else {
			selectAllItem->setCheckState(Qt::PartiallyChecked);
		}
	}
}

void StochasticProcessWidget::updateSelectAllRow(
		int index) {
	if (index == 3) {
		return;
	}

	bool allChecked = true;
	bool allUnchecked = true;
	int columnCount = distGraphTable->columnCount();

	for (int i = 0; i <= columnCount - 2; i++) {
		QTableWidgetItem *item = distGraphTable->item(
				index, i);
		if (item) {
			bool isChecked = item->checkState()
					== Qt::Checked;
			bool isPartiallyChecked =
					item->checkState()
							== Qt::PartiallyChecked;
			allChecked = allChecked && isChecked
					&& !isPartiallyChecked;
			allUnchecked = allUnchecked && !isChecked
					&& !isPartiallyChecked;
		}
	}

	QTableWidgetItem
			*selectAllItem = distGraphTable->item(
					index, columnCount - 1);
	if (selectAllItem) {
		if (allChecked) {
			selectAllItem->setCheckState(Qt::Checked);
		} else if (allUnchecked) {
			selectAllItem->setCheckState(Qt::Unchecked);
		} else {
			selectAllItem->setCheckState(Qt::PartiallyChecked);
		}
	}
}

bool StochasticProcessWidget::addIntervalDistributionToGraph(
		QString title, ivector values) {
	rvector inf = Inf(values);
	rvector sup = Sup(values);

	intervalDists.push_back(values);

	////////////////////////////////////////////
	// Update distribution graph
	////////////////////////////////////////////
	QwtPlotCurve *infCurve =
			PlotUtil::constructCurveFromRVector(inf);
	QwtPlotCurve *supCurve =
			PlotUtil::constructCurveFromRVector(sup);

	infCurve->attach(distGraph);
	supCurve->attach(distGraph);

	infCurves.push_back(infCurve);
	supCurves.push_back(supCurve);

	int columnIndex = distGraphTable->columnCount() - 1;
	distGraphTable->setColumnCount(columnIndex + 2);

	for (int i = 0; i <= 5; i++) {
		distGraphTable->setItem(
				i,
				columnIndex + 1,
				distGraphTable->takeItem(i, columnIndex));
	}

	QTableWidgetItem *valueItem = new QTableWidgetItem(QString("%1").arg(columnIndex+1));
	valueItem->setFlags(Qt::ItemIsUserCheckable
			| Qt::ItemIsEnabled);
	valueItem->setCheckState(Qt::Checked);
	valueItem->setTextAlignment(Qt::AlignCenter);
	distGraphTable->setItem(0, columnIndex, valueItem);

	double
			average =
					_double(CompUtil::getExpectationValue(values));

	QwtPlotMarker *avgMarker = new QwtPlotMarker();
	avgMarker->setLineStyle(QwtPlotMarker::VLine);
	avgMarker->setXValue(average);
	avgMarker->attach(distGraph);
	avgMarkers.push_back(avgMarker);

	QTableWidgetItem *avgItem = new QTableWidgetItem(QString("%1").arg(average));
	avgItem->setFlags(Qt::ItemIsUserCheckable
			| Qt::ItemIsEnabled);
	avgItem->setCheckState(Qt::Checked);
	avgItem->setTextAlignment(Qt::AlignCenter);
	distGraphTable->setItem(1, columnIndex, avgItem);

	distGraphTable->resizeRowsToContents();

	double
			stdDev =
					_double(CompUtil::getDistributionStandardDeviation(values));

	QwtPlotMarker *lowerStdDevMarker =
			new QwtPlotMarker();
	lowerStdDevMarker->setLineStyle(QwtPlotMarker::VLine);
	lowerStdDevMarker->setXValue(average - stdDev);
	lowerStdDevMarker->attach(distGraph);

	QwtPlotMarker *upperStdDevMarker =
			new QwtPlotMarker();
	upperStdDevMarker->setLineStyle(QwtPlotMarker::VLine);
	upperStdDevMarker->setXValue(average + stdDev);
	upperStdDevMarker->attach(distGraph);

	stdDevMarkers.push_back(PlotMarkerPair(
			lowerStdDevMarker, upperStdDevMarker));

	QTableWidgetItem *stdDevItem =
			new QTableWidgetItem(QString("%1").arg(stdDev));
	stdDevItem->setFlags(Qt::ItemIsUserCheckable
			| Qt::ItemIsEnabled);
	stdDevItem->setCheckState(Qt::Checked);
	stdDevItem->setTextAlignment(Qt::AlignCenter);
	distGraphTable->setItem(2, columnIndex, stdDevItem);

	QTableWidgetItem
			*statProbItem =
					new QTableWidgetItem(QString("%1").arg(_double(statProbs[columnIndex + Lb(statProbs)])));
	statProbItem->setTextAlignment(Qt::AlignCenter);
	distGraphTable->setItem(3, columnIndex,
			statProbItem);

	QTableWidgetItem *rangeItem = new QTableWidgetItem(QString("%1 - %2").arg(Lb(values)).arg(Ub(values)));
	rangeItem->setTextAlignment(Qt::AlignCenter);
	distGraphTable->setItem(4, columnIndex, rangeItem);

	QTableWidgetItem *selectAllItem =
			new QTableWidgetItem(tr("Show All"));
	selectAllItem->setFlags(Qt::ItemIsUserCheckable
			| Qt::ItemIsEnabled);
	selectAllItem->setCheckState(Qt::Checked);
	selectAllItem->setTextAlignment(Qt::AlignCenter);
	distGraphTable->setItem(5, columnIndex,
			selectAllItem);

	////////////////////////////////////////////
	// Update distribution table
	////////////////////////////////////////////
	int lb = Lb(values);
	int ub = Ub(values);
	int vectorSize = ub - lb + 1;
	int newDistRowCount = (int)_double(max(
			distTable->rowCount(), vectorSize + lb));
	distTable->setRowCount(newDistRowCount);
	for (int i = 0; i < newDistRowCount; i++) {
		distTable->setVerticalHeaderItem(i,
				new QTableWidgetItem(QString("%1").arg(i)));
	}

	columnIndex = distTable->columnCount();
	distTable->setColumnCount(columnIndex + 1);

	for (int i = lb; i <= ub; i++) {
		QTableWidgetItem
				*newItem =
						new QTableWidgetItem(QString("%1\n%2").arg(_double(sup[i - lb])).arg(_double(inf[i - lb])));
		distTable->setItem(i, columnIndex, newItem);
	}

	return true;
}

void StochasticProcessWidget::updateAutocorrelationCurve() {
	if (!process) {
		return;
	}

	int newLength = upToSpin->value();
	rvector autoCorrelation =
			process->getAutocorrelation(newLength);

	int size = Ub(autoCorrelation)
			- Lb(autoCorrelation) + 1;
	double *xValues = new double[size];
	double *yValues = new double[size];

	int i = 0;
	for (int j = Lb(autoCorrelation); j
			<= Ub(autoCorrelation); j++) {
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
	correlationCurve->attach(autocorrelationPlot);
	autocorrelationPlot->replot();

	delete[] xValues;
	delete[] yValues;
}

void StochasticProcessWidget::addQuantile() {
	QTableWidgetItem *item;

	int lastRowIndex = quantileTable->rowCount();
	quantileTable->setRowCount(lastRowIndex + 1);

	double probabilityLimit = quantileEdit->text().toDouble();
	int stateCount = process->getNumStates();


	item = new QTableWidgetItem(quantileEdit->text());
	item->setTextAlignment(Qt::AlignCenter);
	quantileTable->setItem(lastRowIndex, 0, item);
	item = new QTableWidgetItem("[DEL]");
	item->setTextAlignment(Qt::AlignCenter);
	quantileTable->setItem(lastRowIndex, stateCount+1, item);

	for (int stateIndex = 1; stateIndex <= stateCount; stateIndex++) {
		ivector distValues = intervalDists[stateIndex-1];
		real probabilityInf = 0.0;
		real probabilitySup = 0.0;
		int distIndexSup;
		int distIndexInf;
		for (distIndexSup = Lb(distValues); distIndexSup <= Ub(distValues); distIndexSup++) {
			interval distValue = distValues[distIndexSup];
			probabilityInf += Inf(distValue);
			probabilitySup += Sup(distValue);
			if (probabilitySup >= probabilityLimit) {
				if(probabilityInf <probabilityLimit)
					distIndexInf = distIndexSup - 1;
				else
					distIndexInf = distIndexSup;
				break;
			}
		}

		QTableWidgetItem *resultItem = new QTableWidgetItem(QString("[%1..%2]").arg(distIndexInf).arg(distIndexSup));
		resultItem->setTextAlignment(Qt::AlignCenter);
		quantileTable->setItem(lastRowIndex, stateIndex, resultItem);
	}

	int distCount = process->getNumStates();
	QColor quantileCellColor;

	for (int i = 0; i < distCount; i++) {
		int hueValue = (int)round(255.0
				/ ((double)distCount / (double)i));
		quantileCellColor.setHsv(hueValue, 40, 245);
		quantileTable->item(lastRowIndex, i+1)->setBackgroundColor(quantileCellColor);
	}
}

void StochasticProcessWidget::handleCellEvent(int row,
		int column) {
	if ((row < 0) || (row > 5)) {
		return;
	}

	Qt::CheckState checkState = distGraphTable->item(row, column)->checkState();
	bool isChecked = checkState == Qt::Checked;

	if (checkState == Qt::PartiallyChecked) {
		return;
	}

	int lastColumnIndex = distGraphTable->columnCount()
			- 1;
	if (column == lastColumnIndex) {
		if (row != 3) {
			for (int i = 0; i < lastColumnIndex; i++) {
				QTableWidgetItem *item =
						distGraphTable->item(row, i);
				if (item) {
					item->setCheckState(checkState);
				}

				updateSelectAllColumn(i);
			}
		} else {
			setScalingEnabled(isChecked);
		}

		if (row == 5) {
			for (int i = 0; i <= 2; i++) {
				QTableWidgetItem *item =
						distGraphTable->item(i,
								lastColumnIndex);
				if (item) {
					item->setCheckState(checkState);
				}
			}
		}

		updateSelectAllColumn(lastColumnIndex);

		return;
	}

	QTableWidgetItem *item = 0;

	switch (row) {
	case 0:
		if (isChecked) {
			infCurves[column]->attach(distGraph);
			supCurves[column]->attach(distGraph);
		} else {
			infCurves[column]->detach();
			supCurves[column]->detach();
		}

		break;
	case 1:
		if (isChecked) {
			avgMarkers[column]->attach(distGraph);
		} else {
			avgMarkers[column]->detach();
		}

		break;
	case 2:
		if (isChecked) {
			stdDevMarkers[column].first->attach(distGraph);
			stdDevMarkers[column].second->attach(distGraph);
		} else {
			stdDevMarkers[column].first->detach();
			stdDevMarkers[column].second->detach();
		}

		break;
	case 5:
		for (int i = 0; i <= 2; i++) {
			item = distGraphTable->item(i, column);
			if (item) {
				item->setCheckState(checkState);
				updateSelectAllRow(i);
			}
		}

		break;
	default:
		break;
	}

	updateSelectAllColumn(column);
	updateSelectAllRow(row);

	updateSelectAllColumn(lastColumnIndex);
	updateSelectAllRow(5);

	distGraph->replot();
}

void StochasticProcessWidget::setScalingEnabled(
		bool isEnabled) {
	if (infCurves.size() <= 0) {
		return;
	}

	imatrix distributionMatrix =
			process->getDistributions();
	int ubDistMatrix = Ub(distributionMatrix, 1);
	int lbDistMatrix = Lb(distributionMatrix, 1);
	unsigned int distCount = ubDistMatrix -lbDistMatrix
			+ 1;

	for (unsigned int i = 0; i < distCount; i++) {
		if (i >= infCurves.size()) {
			return;
		}

		if (infCurves[i]) {
			infCurves[i]->detach();
			delete infCurves[i];
		}

		if (supCurves[i]) {
			supCurves[i]->detach();
			delete supCurves[i];
		}
	}

	infCurves.clear();
	supCurves.clear();

	rvector statProbabilities =
			process->getStationaryProbabilities();

	for (int i = lbDistMatrix; i <= ubDistMatrix; i++) {
		ivector values = distributionMatrix[i];

		if (isEnabled) {
			values *= statProbabilities[i];
		}

		rvector inf = Inf(values);
		rvector sup = Sup(values);

		////////////////////////////////////////////
		// Update distribution graph
		////////////////////////////////////////////
		QwtPlotCurve
				*infCurve =
						PlotUtil::constructCurveFromRVector(inf);
		QwtPlotCurve
				*supCurve =
						PlotUtil::constructCurveFromRVector(sup);

		infCurve->attach(distGraph);
		supCurve->attach(distGraph);

		infCurves.push_back(infCurve);
		supCurves.push_back(supCurve);
	}

	updateColors();
}

void StochasticProcessWidget::updateColors() {
	int distCount = process->getNumStates();
	QColor weakestDistColor;
	QColor weakDistColor;
	QColor avgDistColor;
	QColor strongDistColor;

	for (int i = 0; i < distCount; i++) {
		int hueValue = (int)round(255.0
				/ ((double)distCount / (double)i));
		weakDistColor.setHsv(hueValue, 40, 245);
		weakestDistColor.setHsv(hueValue, 15, 245);
		avgDistColor.setHsv(hueValue, 100, 255);
		strongDistColor.setHsv(hueValue, 150, 255);

		QPen curvePen(QBrush(strongDistColor), 3.0,
				Qt::SolidLine);
		infCurves[i]->setPen(curvePen);
		supCurves[i]->setPen(curvePen);

		QPen avgPen(QBrush(avgDistColor), 3.0,
				Qt::DashLine);
		avgMarkers[i]->setLinePen(avgPen);

		QPen stdDevPen(QBrush(avgDistColor), 3.0,
				Qt::DotLine);
		stdDevMarkers[i].first->setLinePen(stdDevPen);
		stdDevMarkers[i].second->setLinePen(stdDevPen);

		for (int j = 0; j <= 4; j++) {
			distGraphTable->item(j, i)->setBackgroundColor(weakDistColor);
		}

		for (int j = 0; j < distTable->rowCount(); j++) {
			QTableWidgetItem *item = distTable->item(j,
					i);
			if (item) {
				if (item->text() == "0\n0") {
					item->setBackgroundColor(weakestDistColor);
				} else {
					item->setBackgroundColor(weakDistColor);
				}
			}
		}
	}

	distGraph->replot();
}
