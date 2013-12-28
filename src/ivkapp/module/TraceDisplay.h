#ifndef TRACEDISPLAY_H_
#define TRACEDISPLAY_H_

#include "ModuleWidget.h"
#include "ui_TraceDisplay.h"

#include <string>

#include <QString>
#include <QTextStream>

#include "DataProvider.hpp"

namespace ivk
{
class Trace;
}

class QwtPlotMarker;

using namespace std;

using ivk::Trace;

class TraceDisplay : public ModuleWidget, protected Ui::TraceDisplay, public DataProvider<Trace>
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(TraceDisplay)

public:
	virtual ~TraceDisplay();

	const Trace * getTrace();
	
	virtual const Trace * getData();
	
	void createActions();
	
	void createDefaultSubWidgets();

	void setTrace(const Trace * newTrace);

	static TraceDisplay * importFromFile(const QString & filePath);
	
	static TraceDisplay * importFromStdString(const string & source);
	
	static TraceDisplay * importFromRVector(const rvector & source);
	
protected:
	void loadModel();
	
	void createFileElements();

private slots:
	void renewalModelerRequested();
	
	void simpleMcModelerRequested();
	
	void gopExtractionRequested();
	
	void geneticModelerRequested();

	void mmcModelerRequested();

	void partitionModelerRequested();

	void sceneModelerRequested();
	
	void sAPartitionModelerRequested();
	
	void sPEA2ModelerRequested();
	
	void geneticFrameModelerRequested();
	
	void updateAutocorrelationCurve();
	
	void updateHistogramCurve();
	
private:
	TraceDisplay();
	
	static TraceDisplay * importFromTextStream(QTextStream & textStream, int size);
	
	const Trace * trace;
	
	QwtPlotCurve *correlationCurve;

	QwtPlotCurve *histogramCurve;
	
	QwtPlotMarker *histStdDevPlusAvgMarker;
	
	QwtPlotMarker *histStdDevMarker;
	
	QwtPlotMarker *histAvgMarker;
};

#endif /*TRACEDISPLAY_H_*/
