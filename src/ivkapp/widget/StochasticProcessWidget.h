#ifndef ARRIVALDISTRIBUTIONWIDGET_H_
#define ARRIVALDISTRIBUTIONWIDGET_H_


#include "ui_base/ui_StochasticProcessWidget.h"

#include <vector>
#include <utility>

#include <QWidget>

#include <rvector.hpp>
#include <imatrix.hpp>
#include <ivector.hpp>


namespace ivk
{
class SSMProcess;
class GIProcess;
}

class QwtPlotMarker;


using ivk::SSMProcess;
using ivk::GIProcess;

using cxsc::imatrix;
using cxsc::ivector;

using std::vector;
using std::pair;


/// Specialized widget for displaying arrival distributions
class StochasticProcessWidget : public QWidget, protected Ui::StochasticProcessWidget
{
	Q_OBJECT

public:
	/// Default constructor
	/**
	 * \param parent The parent widget
	 */
	StochasticProcessWidget(QWidget* parent = 0);

	/// Destructor
	virtual ~StochasticProcessWidget();

	/// Displays the given process
	/**
	 * \param process The process to display
	 */
	void displayProcess(const SSMProcess *process);


protected:
	typedef pair<QwtPlotMarker*, QwtPlotMarker*> PlotMarkerPair;
	
	/// Adds an interval distribution to the list of displayed distributions.
	bool addIntervalDistributionToGraph(QString title, ivector values);

	void updateColors();
	
	void updateSelectAllColumn(int index);
	
	void updateSelectAllRow(int index);
	
	void setScalingEnabled(bool isEnabled);
	
	void updateTransitionColors();
	
	void setupDistributionTable(const imatrix & distributionMatrix);
	
	void setupTransitionTable(const imatrix & transitionMatrix);
	
	void setupQuantileTable();
	
	/// List of displayed curves.
	vector<QwtPlotCurve*> infCurves;

	vector<QwtPlotCurve*> supCurves;

	vector<QwtPlotMarker*> avgMarkers;

	vector<PlotMarkerPair> stdDevMarkers;
	
	vector<ivector> intervalDists;
	
	imatrix transitionMatrix;
	
	const SSMProcess *process;
	
	rvector statProbs;
	
	QwtPlotCurve *correlationCurve;

private slots:
	void handleCellEvent(int row, int column);
	
	void addQuantile();
	
	void updateAutocorrelationCurve();
	
	void handleQuantileChange(int row, int column);
};

#endif /*ARRIVALDISTRIBUTIONWIDGET_H_*/
