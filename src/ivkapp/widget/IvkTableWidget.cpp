#include "IvkTableWidget.h"

#include <iostream>

#include <QFile>
#include <QTextStream>
#include <qwt-qt4/qwt_plot_curve.h>
#include <QMessageBox>

#include "ExportTableDialog.h"
#include "IvkPlot.h"

using namespace std;

IvkTableWidget::IvkTableWidget(QWidget *parent) :
	QTableWidget(parent), attachedPlot(0), linkedCurves(), autoUpdatePlot(false)
{	
	exportDialog = new ExportTableDialog(this);
	exportDialog->setModal(true);
	
	QAction *exportAction = new QAction(tr("Export table..."),this);
	connect(exportAction,SIGNAL(triggered()),exportDialog,SLOT(show()));
	
	addAction(exportAction);
	setContextMenuPolicy(Qt::ActionsContextMenu);
	
	connect(exportDialog,SIGNAL(exportInitialized()),this,SLOT(exportData()));
}

IvkTableWidget::~IvkTableWidget() {}

void IvkTableWidget::setAutoUpdatePlot(bool doUpdate)
{
	this->autoUpdatePlot = doUpdate;
	if (doUpdate)
		connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(updatePlot()));
	else
		disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(updatePlot()));
}

void IvkTableWidget::addAttachedPlotCurve(TablePlotLink xValues, TablePlotLink yValues)
{
	xValues.setTableWidget(this);
	yValues.setTableWidget(this);
	linkedCurves.push_back(pair<TablePlotLink,TablePlotLink>(xValues,yValues));	
}

void IvkTableWidget::updatePlot()
{
	if (!attachedPlot)
		return;
		
	QwtPlotItemList curveList;
	
	for (LinkedCurveList::iterator it = linkedCurves.begin(); it != linkedCurves.end(); it++)
	{
		QwtPlotCurve *newCurve = new QwtPlotCurve();
		
		vector<double> xValues = (*it).first.getValues();
		vector<double> yValues = (*it).second.getValues();
		
		newCurve->setData(xValues.data(), yValues.data(), xValues.size());
		
		curveList << newCurve;
	}
	
	attachedPlot->importPlotItems(&curveList);
}

void IvkTableWidget::exportCsv(QFile &file, QString valueSeparator, QString lineSeparator, QString linebreakReplacement)
{
	// Local variables
	QTextStream fstream(&file);
	QString headerItemText;
			
	// Export horizontal headings if requested
	if (exportDialog->horizontalHeadingsCheck->isChecked())
	{
		if (exportDialog->verticalHeadingsCheck->isChecked())
			fstream << valueSeparator;
		  
		for (int i = 0; i < columnCount(); i++)
		{
			if (horizontalHeaderItem(i))
				headerItemText = horizontalHeaderItem(i)->text();
			else headerItemText = QString();
			
			if (!headerItemText.isNull())
				fstream << horizontalHeaderItem(i)->text() << valueSeparator;
			else
				fstream << valueSeparator;
		}
		fstream << lineSeparator;
	}
	
	// Iterate over table rows
	int rowNumber = 0;
	QVector<QString> *additionalLineContent = 0;		
	QVector<QString> *newAdditionalLineContent = 0;
	QString cellContent;
	while (rowNumber < rowCount())
	{
		// Export vertical heading if requested
		if (exportDialog->verticalHeadingsCheck->isChecked())
		{
			if (verticalHeaderItem(rowNumber))
				fstream << verticalHeaderItem(rowNumber)->text();
			fstream << valueSeparator;
		}
		
		// Are there additional cells to be printed?
		if (additionalLineContent)
		{
			// Initialize pointer for next additional cell vector
			newAdditionalLineContent = 0;
			
			// Iterate over cells in the additional content vector
			for (int columnNumber = 0; columnNumber < columnCount(); columnNumber++)
			{
				cellContent = (*additionalLineContent)[columnNumber];
				
				// Is there another linebreak?
				if (cellContent.contains('\n'))
				{
					// Create vector for next additional content if not existing
					if (!newAdditionalLineContent)
						newAdditionalLineContent = new QVector<QString>(columnCount());
						
					// Add text after linebreak to next overflow vector and cut it from value string
					(*newAdditionalLineContent)[columnNumber] = cellContent.mid(cellContent.indexOf('\n') + 1);
					cellContent = cellContent.left(cellContent.indexOf('\n'));
				}
				
				fstream << cellContent << valueSeparator;
			}
			
			// newAdditionalLineContent becomes additionalLineContent for the next iteration
			// (if there's no more overflowing content, the pointer gets set to zero)
			delete additionalLineContent;
			additionalLineContent = newAdditionalLineContent;
		}
		else
		{
			// Iterate over cells in this table row
			for (int columnNumber = 0; columnNumber < columnCount(); columnNumber++)
			{
				// Replace linebreaks if requested
				if (linebreakReplacement.isNull())
					cellContent =  item(rowNumber,columnNumber)->text();
				else
					cellContent =  item(rowNumber,columnNumber)->text().replace(QString("\n"),linebreakReplacement);
				
				// Is there a linebreak in the cell?
				if (cellContent.contains('\n'))
				{
					// Create overflow vector if not already existing
					if (!additionalLineContent)
						additionalLineContent = new QVector<QString>(columnCount());
						
					// Add text after linebreak to overflow vector and cut it from value string
					(*additionalLineContent)[columnNumber] = cellContent.mid(cellContent.indexOf('\n') + 1);
					cellContent = cellContent.left(cellContent.indexOf('\n'));
				}
				
				fstream << cellContent << valueSeparator;
			}
		}
		
		fstream << lineSeparator;
		
		// If there's no additional lines to be printed, go to next table row
		if (!additionalLineContent)
			rowNumber++;
	}
}

void IvkTableWidget::exportMatlab(QFile &file, QString linebreakReplacement)
{
	exportCsv(file,QString("\t"),QString("\n"), linebreakReplacement);
}

void IvkTableWidget::exportData()
{
	QFile file(exportDialog->pathEdit->text());
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
	    cerr << tr("Cannot write file %1: %2.").arg(exportDialog->pathEdit->text()).arg(file.errorString()).toStdString() << endl;
	    return;
	}
	
	QString linebreakReplacement;
	if (exportDialog->replaceLineBreakRadio->isChecked())
		linebreakReplacement = exportDialog->replaceLineBreakEdit->text();
		
	if (exportDialog->csvRadio->isChecked())
	{		
		QString columnSeparatorString = exportDialog->columnSeparatorEdit->text();
		QString rowSeparatorString =  exportDialog->rowSeparatorEdit->text();
		rowSeparatorString = rowSeparatorString.replace("\\n","\n");
		rowSeparatorString = rowSeparatorString.replace("\\t","\t");
		exportCsv(file, columnSeparatorString, rowSeparatorString, linebreakReplacement);
		exportDialog->accept();
	}
	else if (exportDialog->matlabRadio->isChecked())
	{
		exportMatlab(file, linebreakReplacement);
		exportDialog->accept();
	}
	
	file.close();
	
	cout << "Exported table data to " << exportDialog->pathEdit->text().toStdString() << "." << endl;
}
