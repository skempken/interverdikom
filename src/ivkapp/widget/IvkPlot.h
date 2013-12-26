#ifndef IVKPLOT_H_
#define IVKPLOT_H_

#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_zoomer.h>

#include <QList>

#include <rvector.hpp>

class QwtPlotCurve;

using cxsc::rvector;

/// Custom plot control
/**
 * Customized plot widget with export function and zoomer
 */
class IvkPlot : public QwtPlot
{
	Q_OBJECT

	private: class MyQwtPlotZoomer : public QwtPlotZoomer
	{
		public:
			MyQwtPlotZoomer(int xAxis, int yAxis, int selectionFlags, DisplayMode trackerMode, QwtPlotCanvas *canvas, bool doReplot = true);

			bool firstZoomAttempted;

		protected:
			void widgetMouseReleaseEvent(QMouseEvent *me);

			void widgetWheelEvent(QWheelEvent *we);
	};


public:
	/// Default constructor
	/**
	 * \param parent Parent widget
	 */
	IvkPlot(QWidget *parent);

	void replot();


	void setAxisScale(int i, double j, double k);

	/// Destructor
	virtual ~IvkPlot();

public slots:
	/// Reset the zoom level
	void resetZoom();

	/// Replace current plot items
	/**
	 * \param newPlotItems New plot items
	 */
	void importPlotItems(QwtPlotItemList* newPlotItems);

private slots:
	/// Show the export options dialog
	void showExportDialog();

	/// Perform graph export
	void exportGraph();

private:
	/// Pointer to associated zoomer object
	class MyQwtPlotZoomer *plotZoomer;

	/// Pointer to associated export options dialog
	class ExportGraphDialog *exportDialog;

signals:
	void importFinished();
};

#endif /*IVKPLOT_H_*/
