#ifndef EXTRACTGOPWIDGET_H_
#define EXTRACTGOPWIDGET_H_

#include "modbase/ModuleWidget.h"
#include "ui_base/ui_ExtractGopWidget.h"

#include <rvector.hpp>

#include <list>

using cxsc::rvector;

namespace ivk {
	class Trace;
}

class QwtPlotCurve;
class QwtPlotMarker;

using ivk::Trace;

class ExtractGopWidget : public ModuleWidget, public Ui::ExtractGopWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(ExtractGopWidget)

public:
	ExtractGopWidget();

	virtual ~ExtractGopWidget();

protected:
	void createActions();

	void loadFileData();

	void initModel();

	void postCreation();

	void loadModel() {};

private:
	const Trace *trace;

	rvector autoCorrelation;

	QwtPlotCurve *correlationCurve;

	QwtPlotMarker *boundMarker;

	list<QwtPlotMarker*> maxMarkers;


private slots:
	void updateLengthRange(int min, int max);

	void updateLength(int newLength);

	void updateBound(double newBound);

	void boundSliderChanged(int newValue);

	void updateCalculatedInterval();

	void useAverageMax();

	void createAggregatedTrace();
};

#endif /*EXTRACTGOPWIDGET_H_*/
