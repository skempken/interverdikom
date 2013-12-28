#ifndef EXPORTABLETABLEWIDGET_H_
#define EXPORTABLETABLEWIDGET_H_

#include <QFile>
#include <QTableWidget>

#include <list>
#include <utility>

#include <QList>
#include <QStringList>
#include <qwt-qt4/qwt_plot_dict.h>

#include "TablePlotLink.h"

/// List of TablePlotLink pairs
typedef std::list< std::pair<TablePlotLink, TablePlotLink> > LinkedCurveList;

/// Customized QTableWidget
/**
 * IvkTableWidget adds functionality on top of QTableWidget. The two major new functions are support for exporting the
 * table to an ASCII file and support for linking the table to an IvkPlot, so that plot curves are automatically
 * generated from chosen values in the table.
 */
class IvkTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	/// Default constructor
	/**
	 * \param parent Parent widget
	 */
	IvkTableWidget(QWidget *parent = 0);

	/// Destructor
	virtual ~IvkTableWidget();

	/// Attach an IvkPlot object to this table
	/**
	 * \param plot The plot object to attach
	 */
	void attachPlot(class IvkPlot *plot)
		{ this->attachedPlot = plot; }

	/// Specifies a new pair of values that should be exported as a curve
	/**
	 * \param xValues Specification for x values of the curve
	 * \param yValues Specification for y values of the curve
	 */
	void addAttachedPlotCurve(TablePlotLink xValues, TablePlotLink yValues);

	/// Sets whether the plot is automatically updates when table contents change
	/**
	 * \param doUpdate Auto update on or off
	 */
	void setAutoUpdatePlot(bool doUpdate = true);

public slots:
	/// Update attached plot with table data
	void updatePlot();

	/// Export table data
	void exportData();

private:
	/// Helper function: Export table data as comma seperated values
	/**
	 * \param file Target file
	 * \param valueSeperator String which seperates cell values on one row
	 * \param lineSeperator String which seperates rows
	 */
	void exportCsv(QFile &file, QString valueSeperator = QString(";"), QString lineSeperator = QString("\n"), QString linebreakReplacement = QString());

	/// Helper function: Export table data in MATLAB format
	/**
	 * \param File Target file
	 */
	void exportMatlab(QFile &file, QString linebreakReplacement = QString());

	/// The plot attached to this IvkTableWidget
	class IvkPlot *attachedPlot;

	/// List of curves that should be exported to attached plot
	LinkedCurveList linkedCurves;

	/// Indicated whether the attached plot should automatically be updates
	bool autoUpdatePlot;

	/// Pointer to associated export options dialog
	class ExportTableDialog *exportDialog;

	/// Helper function: Generate plot item list to export to attached plot
	QwtPlotItemList *makePlotItems();
};

#endif /*EXPORTABLETABLEWIDGET_H_*/
