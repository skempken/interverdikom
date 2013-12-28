#include "TraceDisplay.h"

#include <sstream>
#include <vector>

#include <QFile>
#include <QTextStream>
#include <QProgressDialog>
#include <QMessageBox>
#include <QHeaderView>

#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_marker.h>

#include "data/Trace.h"

#include "rvector.hpp"

#include "RenewalModelerWidget.h"
#include "SimpleMCModelerWidget.h"
#include "GeneticModelerWidget.h"
#include "AutoSMPModelerWidget.h"
#include "MMCModelerWidget.h"
#include "PartitionModelerWidget.h"
#include "SceneModelerWidget.h"
#include "SAPartitionModelerWidget.h"
#include "SPEA2ModelerWidget.h"
#include "GeneticFrameModelerWidget.h"
#include "ExtractGopWidget.h"
#include "CyclePeriodWizard.h"

#include "ModuleManager.h"

#include "utility/Logging.hpp"

using namespace std;
using namespace cxsc;
using ivk::Logging;

FACTORY_DEFINITIONS_FOR(TraceDisplay)

TraceDisplay::TraceDisplay() : trace(0), correlationCurve(0), histogramCurve(0)
{
	setupUi(this);

	histAvgMarker = new QwtPlotMarker();
	histAvgMarker->setLineStyle(QwtPlotMarker::VLine);
	histAvgMarker->setLinePen(QPen(QColor(0x88, 0x88, 0xee), 3.0));
	histAvgMarker->attach(histogramPlot);

	histStdDevMarker = new QwtPlotMarker();
	histStdDevMarker->setLineStyle(QwtPlotMarker::VLine);
	histStdDevMarker->setLinePen(QPen(QColor(0x99, 0xcc, 0x99), 3.0,
					Qt::DotLine));
	histStdDevMarker->attach(histogramPlot);

	histStdDevPlusAvgMarker = new QwtPlotMarker();
	histStdDevPlusAvgMarker->setLineStyle(QwtPlotMarker::VLine);
	histStdDevPlusAvgMarker->setLinePen(QPen(QColor(0x99, 0xcc, 0x99), 3.0,
			Qt::DotLine));
	histStdDevPlusAvgMarker->attach(histogramPlot);


	QwtPlotMarker *nullMarker = new QwtPlotMarker();
	nullMarker->setLineStyle(QwtPlotMarker::HLine);
	nullMarker->setYValue(0.0);
	nullMarker->attach(autocorrelationPlot);
}

TraceDisplay::~TraceDisplay() {
	delete trace;
}

const Trace *  TraceDisplay::getTrace()
{
	return this->trace;
}

const Trace *  TraceDisplay::getData()
{
	return this->trace;
}

void TraceDisplay::createDefaultSubWidgets() {
}

void TraceDisplay::createFileElements() {
	saveRvector("TraceVector", trace->getTrace());
}

void TraceDisplay::updateAutocorrelationCurve() {
	int newLength = upToSpin->value();
	rvector autoCorrelation = trace->getAutocorrelation(newLength);

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
	correlationCurve->attach(autocorrelationPlot);
	autocorrelationPlot->replot();

	delete[] xValues;
	delete[] yValues;
}

void TraceDisplay::loadModel() {
	rvector fileVector = loadRvector("TraceVector");

	if (loadSuccess()) {
		setTrace(new Trace(fileVector));
	} else {
		Logging::log(Logging::Error, "Error loading trace data!");
	}

	upToSpin->setValue(min(100, trace->getLength()));
}

void TraceDisplay::updateHistogramCurve() {
	int groupCount = groupSpin->value();
	rvector traceData = trace->getTrace();

	double *xValues = new double[groupCount + 1];
	double *yValues = new double[groupCount + 1];

	real max = trace->getMaximum();
	double groupSize = _double(max / groupCount);
	for (int i = 0; i <= groupCount; i++) {
		xValues[i] = ((double)i) * groupSize;
		yValues[i] = 0.0;
	}

	int groupIndex;
	for (int i = Lb(traceData); i <= Ub(traceData); i++) {
		groupIndex = (int)floor(_double((traceData[i] / max) * groupCount));
		yValues[groupIndex] += 1.0;
	}

	yValues[groupCount] = yValues[groupCount - 1];

	if (histogramCurve) {
		histogramCurve->detach();
		delete histogramCurve;
	}

	histogramCurve = new QwtPlotCurve("Histogram");
	histogramCurve->setData(xValues, yValues, groupCount + 1);
	histogramCurve->setStyle(QwtPlotCurve::Steps);
	histogramCurve->setBrush(QBrush(QColor(0xee, 0xbb, 0xbb)));
	histogramCurve->setPen(QPen(QColor("black"), 3.0));
	histogramCurve->attach(histogramPlot);

	histogramPlot->replot();

	delete[] xValues;
	delete[] yValues;
}

void TraceDisplay::createActions() {
	QAction *extractGopAction = new QAction(tr("Aggregate GoPs"), this);
	connect(extractGopAction, SIGNAL(triggered()), this,
			SLOT(gopExtractionRequested()));
	addAction(extractGopAction);

	QAction *separator = new QAction(this);
	separator->setSeparator(true);
	addAction(separator);

	QAction *renewalModelerAction = new QAction(tr("Renewal Modeler"), this);
	connect(renewalModelerAction, SIGNAL(triggered()), this,
			SLOT(renewalModelerRequested()));
	addAction(renewalModelerAction);

	QAction *simpleMcModelerAction = new QAction(tr("Simple MC Modeler"), this);
	connect(simpleMcModelerAction, SIGNAL(triggered()), this,
			SLOT(simpleMcModelerRequested()));
	addAction(simpleMcModelerAction);

	QAction *geneticModelerAction = new QAction(tr("Genetic Modeler"), this);
	connect(geneticModelerAction, SIGNAL(triggered()), this,
			SLOT(geneticModelerRequested()));
	addAction(geneticModelerAction);

	QAction *mmcModelerAction = new QAction(tr("Memory Markov Chain Modeler"), this);
	connect(mmcModelerAction, SIGNAL(triggered()), this,
			SLOT(mmcModelerRequested()));
	addAction(mmcModelerAction);

	QAction *partitionModelerAction = new QAction(tr("Partition Modeler"), this);
	connect(partitionModelerAction, SIGNAL(triggered()), this,
			SLOT(partitionModelerRequested()));
	addAction(partitionModelerAction);

	QAction *sceneModelerAction = new QAction(tr("Scene Modeler"), this);
	connect(sceneModelerAction, SIGNAL(triggered()), this,
			SLOT(sceneModelerRequested()));
	addAction(sceneModelerAction);

	QAction *sAPartitionModelerAction = new QAction(tr("SA Partition Modeler"), this);
	connect(sAPartitionModelerAction, SIGNAL(triggered()), this,
			SLOT(sAPartitionModelerRequested()));
	addAction(sAPartitionModelerAction);

	QAction *sPEA2ModelerAction = new QAction(tr("SPEA2 Modeler"), this);
	connect(sPEA2ModelerAction, SIGNAL(triggered()), this,
			SLOT(sPEA2ModelerRequested()));
	addAction(sPEA2ModelerAction);

	QAction *geneticFrameModelerAction = new QAction(tr("Genetic Frame Modeler"), this);
	connect(geneticFrameModelerAction, SIGNAL(triggered()), this,
			SLOT(geneticFrameModelerRequested()));
	addAction(geneticFrameModelerAction);
}

void TraceDisplay::renewalModelerRequested() {
	RenewalModelerWidget *newWidget = new RenewalModelerWidget();
	addSubWidget(newWidget, tr("Renewal Modeler"));
}

void TraceDisplay::gopExtractionRequested() {
	ExtractGopWidget *newWidget = new ExtractGopWidget();
	addSubWidget(newWidget, tr("GoP Aggregation"));
}

void TraceDisplay::simpleMcModelerRequested() {
	SimpleMCModelerWidget *newWidget = new SimpleMCModelerWidget();
	addSubWidget(newWidget, tr("Simple MC Modeler"));
}

void TraceDisplay::geneticModelerRequested() {
	GeneticModelerWidget *newWidget = new GeneticModelerWidget();
	addSubWidget(newWidget, tr("Genetic Modeler"));
}

void TraceDisplay::mmcModelerRequested() {
	MMCModelerWidget *newWidget = new MMCModelerWidget();
	addSubWidget(newWidget, tr("Memory Markov Chain Modeler"));
}

void TraceDisplay::partitionModelerRequested() {
	 PartitionModelerWidget *newWidget = new PartitionModelerWidget();
	 addSubWidget(newWidget, tr("Partition Modeler"));
}

void TraceDisplay::sceneModelerRequested() {
	 SceneModelerWidget *newWidget = new SceneModelerWidget();
	 addSubWidget(newWidget, tr("Scene Modeler"));
}

void TraceDisplay::sAPartitionModelerRequested() {
	 SAPartitionModelerWidget *newWidget = new SAPartitionModelerWidget();
	 addSubWidget(newWidget, tr("SA Parition Modeler"));
}

void TraceDisplay::sPEA2ModelerRequested() {
	 SPEA2ModelerWidget *newWidget = new SPEA2ModelerWidget();
	 addSubWidget(newWidget, tr("SPEA2 Modeler"));
}

void TraceDisplay::geneticFrameModelerRequested() {
	CyclePeriodWizard* wizard = new CyclePeriodWizard();
	GeneticFrameModelerWidget *newWidget = new GeneticFrameModelerWidget(wizard);
	addSubWidget(newWidget, tr("Genetic Frame Modeler"));
	moduleManager->addModule(wizard, tr("Set Cycle Period"), newWidget);

}

TraceDisplay * TraceDisplay::importFromFile(const QString & filePath) {
	// Open file
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly)) {
		Logging::log(Logging::Error, tr("Could not open trace file '%1'.").arg(filePath).toStdString());
		return 0;
	}

	// Init local variables
	QTextStream fileStream(&file);
	return TraceDisplay::importFromTextStream(fileStream, file.size());
}

TraceDisplay * TraceDisplay::importFromTextStream(QTextStream & textStream,
		int size) {
	// Initialize local variables
	QString currentLine;
	unsigned int bytesRead = 0;

	// List to temporarily hold values until total number of values is clear
	list<real> values;

	// Initialize progress dialog
	QProgressDialog progressDialog(tr("Reading source data..."), tr("Cancel"),
			0, size, 0);
	progressDialog.setAutoClose(false);
	progressDialog.setWindowTitle(tr("Importing Trace"));
	progressDialog.setWindowModality(Qt::WindowModal);

	// Iterate over lines in file
	int progressCount = 0;
	while (!(currentLine = textStream.readLine()).isNull()) {
		// Check whether process was canceled
		if (progressDialog.wasCanceled())
			return 0;

		// Update progress dialog
		bytesRead += currentLine.size() + 2;
		if (!(progressCount++ % 100)) // refresh every 100th time only
			progressDialog.setValue(bytesRead);
		qApp->processEvents();

		// Extract value
		currentLine = currentLine.trimmed();
		unsigned int value;
		bool conversionSuccess;
		int spaceIndex = currentLine.indexOf(QChar(' '));
		if (spaceIndex == -1) {
			spaceIndex = currentLine.indexOf("\t");
		}
		if (spaceIndex != -1) {
			value = currentLine.left(spaceIndex + 1).toInt(&conversionSuccess);
		} else {
			value = currentLine.toInt(&conversionSuccess);
		}

		// If line format illegal, continue with next line
		if (!conversionSuccess) {
			continue;
		}

		// Push value to the back of the temporary list
		values.push_back((int)value);
	}

	// Set progress to max
	progressDialog.setValue(size);

	// Initialize result vector with correct size
	rvector traceVector;
	SetLb(traceVector, 1);
	Resize(traceVector, values.size());

	// Copy values from temporary list to result vector
	list<real>::iterator it;
	int valueIndex = 1;
	for (it = values.begin(); it != values.end(); it++) {
		traceVector[valueIndex] = (*it);
		valueIndex++;
	}

	// Initialize second progress display
	progressDialog.setLabelText(tr("Creating data structures..."));
	progressDialog.setRange(0, 0);
	progressDialog.setValue(0);
	progressDialog.setAutoClose(true);
	progressDialog.repaint();

	// Create and return display widget
	TraceDisplay * newTraceDisplay = new TraceDisplay();
	newTraceDisplay->setTrace(new ivk::Trace(traceVector));
	progressDialog.setValue(1);

	return newTraceDisplay;
}

TraceDisplay * TraceDisplay::importFromRVector(const rvector & source) {
	TraceDisplay * newTraceDisplay = new TraceDisplay();
	newTraceDisplay->setTrace(new ivk::Trace(source));

	return newTraceDisplay;
}

TraceDisplay * TraceDisplay::importFromStdString(const string & source) {
	QString dataString = QString::fromStdString(source);
	QTextStream dataStream(&dataString);
	return TraceDisplay::importFromTextStream(dataStream, dataString.size());
}

void TraceDisplay::setTrace(const ivk::Trace * newTrace) {
	// Assign trace member variable
	trace = newTrace;

	int length = trace->getLength();

	if (length <= 0) {
		sampleCountEdit->setText(QString("%1").arg(length));
		setEnabled(false);
	}

	sampleCountEdit->setText(QString("%1").arg(length));
	averageSizeEdit->setText(QString("%1").arg(_double(trace->getMean())));
	varianceEdit->setText(QString("%1").arg(_double(trace->getVariance())));
	standardDeviationEdit->setText(QString("%1").arg(_double(trace->getStandardDeviation())));

	double *xValues = new double[length], *yValues = new double[length];

	rvector traceData = trace->getTrace();
	valueTable->setColumnCount(length);
	int j = 0;
	for (int i = 0; i <= Ub(traceData) - Lb(traceData); i++) {
		valueTable->setItem(0, i, new QTableWidgetItem(QVariant(i + Lb(traceData)).toString()));
		valueTable->setItem(1, i, new QTableWidgetItem(QString("%1").arg(_double(traceData[i + Lb(traceData)]))));

		xValues[j] = i;
		yValues[j] = _double(traceData[i]);
		j++;
	}

	valueTable->resizeRowsToContents();

	QwtPlotCurve *sampleCurve = new QwtPlotCurve("Samples");
	sampleCurve->setData(xValues, yValues, length);
	sampleCurve->attach(valuePlot);
	valuePlot->replot();
	delete[] xValues;
	delete[] yValues;

	QwtPlotMarker *avgMarker = new QwtPlotMarker();
	avgMarker->setLineStyle(QwtPlotMarker::HLine);
	avgMarker->setLinePen(QPen(QColor(0x88, 0x88, 0xee), 3.0));
	avgMarker->setYValue(_double(trace->getMean()));
	avgMarker->attach(valuePlot);

	QwtPlotMarker *stdDevMarker = new QwtPlotMarker();
	stdDevMarker->setLineStyle(QwtPlotMarker::HLine);
	stdDevMarker->setLinePen(QPen(QColor(0x99, 0xcc, 0x99), 3.0,
			Qt::DotLine));
	stdDevMarker->setYValue(_double(trace->getMean())
			- _double(trace->getStandardDeviation()));
	stdDevMarker->attach(valuePlot);

	QwtPlotMarker *stdDevPlusAvgMarker = new QwtPlotMarker();
	stdDevPlusAvgMarker->setLineStyle(QwtPlotMarker::HLine);
	stdDevPlusAvgMarker->setLinePen(QPen(QColor(0x99, 0xcc, 0x99), 3.0,
			Qt::DotLine));
	stdDevPlusAvgMarker->setYValue(_double(trace->getStandardDeviation())
			+ _double(trace->getMean()));
	stdDevPlusAvgMarker->attach(valuePlot);

	groupSlider->setMaximum(length);
	groupSpin->setMaximum(length);
	upToSlider->setMaximum(length);
	upToSpin->setMaximum(length);

	histStdDevPlusAvgMarker->setXValue(_double(trace->getMean())
			+ _double(trace->getStandardDeviation()));
	histStdDevMarker->setXValue(_double(trace->getMean())
			- _double(trace->getStandardDeviation()));
	histAvgMarker->setXValue(_double(trace->getMean()));

	connect(upToSpin, SIGNAL(valueChanged(int)), this, SLOT(updateAutocorrelationCurve()));
	upToSpin->setValue(min(100, trace->getLength()));

	connect(groupSpin, SIGNAL(valueChanged(int)), this, SLOT(updateHistogramCurve()));
	groupSpin->setValue(min(trace->getLength(), 10));

	valueTable->horizontalHeader()->hide();
}
