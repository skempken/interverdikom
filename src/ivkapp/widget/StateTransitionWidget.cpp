#include "StateTransitionWidget.h"

#include <imatrix.hpp>
#include <ivector.hpp>

using cxsc::imatrix;
using cxsc::ivector;

StateTransitionWidget::StateTransitionWidget(QWidget *parent)
:	QWidget(parent)
{
	setupUi(this);
}

StateTransitionWidget::~StateTransitionWidget()
{
}

void StateTransitionWidget::setFile(ProjectFile* openedFile)
{
	/*
	SMPQueue* queue = openedFile->getSMPQueue();
	SMP process = queue->getArrivalProcess();

	updateTransitionMatrix(process.getTransitionMatrix());
	updateSteadyDistribution(process.getSteadyDistribution().getDistribution());
	*/
}

void StateTransitionWidget::updateTransitionMatrix(const imatrix &matrix)
{
	QTableWidget* table = this->tableTransition;
	table->clear();

	const int rows = Ub(matrix,1) - Lb(matrix,1) +1;
	const int cols = (Ub(matrix,2) - Lb(matrix,2) +1)*2;
	table->setRowCount(rows);
	table->setColumnCount(cols);

	// Column headers
	for(int col = Lb(matrix, 2); col <= Ub(matrix, 2); ++col)
	{
		QTableWidgetItem* _colHeaderInf = new QTableWidgetItem(QString("State #%1 (Inf)").arg(col));
		QTableWidgetItem* _colHeaderSup = new QTableWidgetItem(QString("State #%1 (Sup)").arg(col));
		table->setHorizontalHeaderItem((col-Lb(matrix,2))*2, _colHeaderInf);
		table->setHorizontalHeaderItem(1+(col-Lb(matrix,2))*2, _colHeaderSup);
	}

	// Values
	Qt::ItemFlag flags = Qt::ItemIsEnabled;
	for(int row = Lb(matrix, 1); row <= Ub(matrix, 1); ++row)
	{
		// Row headers
		QTableWidgetItem* _rowHeader = new QTableWidgetItem(QString("State #%1").arg(row));
		table->setVerticalHeaderItem(row - Lb(matrix,1), _rowHeader);

		// Values
		for(int col = Lb(matrix, 2); col <= Ub(matrix, 2); ++col)
		{
			QTableWidgetItem* _itemInf = new QTableWidgetItem(QString("%1").arg(cxsc::_double(Inf(matrix[row][col]))));
			QTableWidgetItem* _itemSup = new QTableWidgetItem(QString("%1").arg(cxsc::_double(Sup(matrix[row][col]))));
			_itemInf->setFlags(flags);
			_itemSup->setFlags(flags);
			table->setItem(row-Lb(matrix,1), (col-Lb(matrix,2))*2, _itemInf);
			table->setItem(row-Lb(matrix,1), 1+(col-Lb(matrix,2))*2, _itemSup);
		}
	}

	table->resizeRowsToContents();
}

void StateTransitionWidget::updateSteadyDistribution(const ivector &dist)
{
	QTableWidget* table = this->tableSteady;

	const int cols = (Ub(dist) - Lb(dist) +1)*2;

	table->setColumnCount(cols);
	table->setRowCount(1);
	table->clear();

	// Column headers
	Qt::ItemFlag flags = Qt::ItemIsEnabled; // No operation permitted.
	for(int col = Lb(dist); col <= Ub(dist); ++col)
	{
		QTableWidgetItem* _colHeaderInf = new QTableWidgetItem(QString("State #%1 (Inf)").arg(col));
		QTableWidgetItem* _colHeaderSup = new QTableWidgetItem(QString("State #%1 (Sup)").arg(col));
		table->setHorizontalHeaderItem((col-Lb(dist))*2, _colHeaderInf);
		table->setHorizontalHeaderItem(1+(col-Lb(dist))*2, _colHeaderSup);

		QTableWidgetItem* _itemInf = new QTableWidgetItem(QString("%1").arg(cxsc::_double(Inf(dist[col]))));
		QTableWidgetItem* _itemSup = new QTableWidgetItem(QString("%1").arg(cxsc::_double(Sup(dist[col]))));
		_itemInf->setFlags(flags);
		_itemSup->setFlags(flags);
		table->setItem(0, (col-Lb(dist))*2, _itemInf);
		table->setItem(0, 1+(col-Lb(dist))*2, _itemSup);
	}

	table->resizeRowsToContents();
}
