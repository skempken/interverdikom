#include "IvkPlot.h"

#include <iostream>

#include <QWheelEvent>
#include <QAction>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <qwt-qt4/qwt_plot_item.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_scale_div.h>

#include "ExportGraphDialog.h"

using namespace std;

IvkPlot::IvkPlot(QWidget *parent) :
	QwtPlot(parent), exportDialog(ExportGraphDialog::getInstance(parent)) {
	plotZoomer = 0;
	plotZoomer = new MyQwtPlotZoomer(QwtPlot::xBottom, QwtPlot::yLeft,
			QwtPicker::DragSelection, QwtPicker::AlwaysOff, canvas());
	plotZoomer->setZoomBase();
	plotZoomer->firstZoomAttempted = false;

	QAction *exportAction = new QAction(tr("Export graph..."), this);
	connect(exportAction, SIGNAL(triggered()), this, SLOT(showExportDialog()));

	QAction *resetZoomAction = new QAction(tr("Reset zoom"), this);
	connect(resetZoomAction, SIGNAL(triggered()), this, SLOT(resetZoom()));

	QAction *separator = new QAction(this);
	separator->setSeparator(true);

	addAction(resetZoomAction);
	addAction(separator);
	addAction(exportAction);

	setContextMenuPolicy(Qt::ActionsContextMenu);
}

IvkPlot::~IvkPlot() {
}

void IvkPlot::importPlotItems(QwtPlotItemList* newPlotItems) {
	QwtPlotItemList currentPlotItems = itemList();
	foreach(QwtPlotItem *currentItem, currentPlotItems) {
			currentItem->detach();
			delete currentItem;
		}

	foreach(QwtPlotItem *newItem, *newPlotItems) {
			newItem->attach(this);
		}

	replot();
	emit importFinished();
}

void IvkPlot::replot() {
	static int lastItemCount = 0;

	if (plotZoomer && !plotZoomer->firstZoomAttempted && lastItemCount != itemList().count()) {
		lastItemCount = itemList().count();
		resetZoom();
		lastItemCount = itemList().count();
	}

	QwtPlot::replot();
}

void IvkPlot::exportGraph() {
	QFile file(exportDialog->pathEdit->text());
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		cerr
				<< tr("Cannot write to file %1: %2.").arg(
						exportDialog->pathEdit->text()).arg(file.errorString()).toStdString()
				<< endl;
		file.close();
		return;
	}
	file.close();

	// Create QwtPlot of appropriate size
	QwtPlot *exportPlot = new QwtPlot();
	QSize exportSize = QSize(exportDialog->widthEdit->text().toInt(),
			exportDialog->heightEdit->text().toInt());
	exportPlot->setFixedSize(exportSize);

	// Set the widget to be frameless with a white background
	QPalette exportPalette;
	exportPalette.setColor(exportPlot->backgroundRole(), QColor("white"));
	exportPlot->setPalette(exportPalette);
	exportPlot->setCanvasBackground(QColor("white"));
	exportPlot->canvas()->setFrameShape(QFrame::NoFrame);

	// Set up the scales
	if (exportDialog->exportEntireGraphRadio->isChecked()) {
		exportPlot->setAxisAutoScale(xBottom);
		exportPlot->setAxisAutoScale(yLeft);
	} else {
		exportPlot->setAxisScaleDiv(xBottom, *(axisScaleDiv(xBottom)));
		exportPlot->setAxisScaleDiv(yLeft, *(axisScaleDiv(yLeft)));
	}

	// Attach items to export plot
	QwtPlotItemList plotItems = itemList();
	foreach(QwtPlotItem *exportItem, plotItems) {
			exportItem->attach(exportPlot);
		}

	// Replot and grab the image data
	exportPlot->replot();
	QPixmap pixMap = QPixmap::grabWidget(exportPlot);

	// Reattach plot items to this IvkPlot
	plotItems = exportPlot->itemList();
	foreach(QwtPlotItem *exportItem, plotItems) {
			exportItem->attach(this);
		}

	// Cleanup
	delete exportPlot;

	// Did we succeed in getting the pixmap?
	if (pixMap.isNull()) {
		cerr << "Couldn't grab widget into pixmap." << endl;
		return;
	}

	// Convert pixmap to image, success?
	QImage capturedImage = pixMap.toImage();
	if (capturedImage.isNull()) {
		cerr << "Couldn't convert pixmap into image." << endl;
		return;
	}

	// Get specified compression
	int compressionLevel = -1;
	if (exportDialog->compressionManualRadio->isChecked())
		compressionLevel = exportDialog->compressionSlider->value();

	// Save image to file, success?
	if (!capturedImage.save(exportDialog->pathEdit->text(), 0, compressionLevel)) {
		cerr << "Couldn't save image to file.";

		QString pathString = exportDialog->pathEdit->text();
		QString fileName = pathString.right(pathString.size()
				- pathString.lastIndexOf(QString("/")) - 1);
		if (!fileName.contains(QChar('.')))
			cerr
					<< " Please make sure that you are using a supported file extension.";

		cerr << endl;
		return;
	}

	// Success!
	cout << "Exported graph to "
			<< exportDialog->pathEdit->text().toStdString() << "." << endl;
	exportDialog->accept();
}

void IvkPlot::showExportDialog() {
	disconnect(exportDialog->exportButton, SIGNAL(clicked()), 0, 0);
	connect(exportDialog->exportButton, SIGNAL(clicked()), this, SLOT(exportGraph()));

	exportDialog->setGraphDimensions(this->width(), this->height());
	exportDialog->show();
}

void IvkPlot::resetZoom() {
	setAxisAutoScale(QwtPlot::xBottom);
	setAxisAutoScale(QwtPlot::yLeft);

	if (plotZoomer) {
		plotZoomer->setZoomBase();
	}

	replot();
}

void IvkPlot::setAxisScale(int i, double j, double k)
{
	QwtPlot::setAxisScale(i, j, k);
	plotZoomer->setZoomBase();
}

void IvkPlot::MyQwtPlotZoomer::widgetMouseReleaseEvent(QMouseEvent *me) {
	firstZoomAttempted = true;
	if (!mouseMatch(MouseSelect2, me))
		QwtPlotZoomer::widgetMouseReleaseEvent(me);
}

void IvkPlot::MyQwtPlotZoomer::widgetWheelEvent(QWheelEvent *we) {
	if (we->delta() < 0) {
		zoom(-1);
	} else if (we->delta() > 0) {
		zoom(+1);
	}

	QwtPlotZoomer::widgetWheelEvent(we);
}

IvkPlot::MyQwtPlotZoomer::MyQwtPlotZoomer(int xAxis, int yAxis,
		int selectionFlags, DisplayMode trackerMode, QwtPlotCanvas *canvas,
		bool doReplot) :
	QwtPlotZoomer(xAxis, yAxis, selectionFlags, trackerMode, canvas, doReplot) {
	// Nothing else to do.
}
