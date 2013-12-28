#include "WHResultWidget.h"
#include "WHWorkloadWidget.h"

#include "utility/MatrixPolynomial.hpp"

FACTORY_DEFINITIONS_FOR(WHResultWidget)

WHResultWidget::WHResultWidget() : factors(0)
{
	setupUi(this);
}

WHResultWidget::WHResultWidget(const ISMPWHFactors *factors) : factors(factors)
{
	setupUi(this);
	setTable( factors->getIdleDistributions() , idleDist );
	setTable( factors->getPhaseDistributions() , phaseDist );
}

WHResultWidget::~WHResultWidget()
{
}

const ISMPWHFactors* WHResultWidget::getISMPWHFactors() const
{
	return this->factors;
}

void WHResultWidget::createActions()
{
	QAction *workloadAction = new QAction(tr("Compute workload probabilities..."), this);
	connect(workloadAction, SIGNAL(triggered()), this,
			SLOT(workloadRequested()));
	addAction(workloadAction);
}

void WHResultWidget::workloadRequested()
{
	addSubWidget(new WHWorkloadWidget, tr("Compute workload probabilities"));
}

void WHResultWidget::setTable( IMatrixPolynomial distribution , QTableWidget* table){
	int lb = distribution.lowerBound();
	int ub = distribution.upperBound();
	int lbHeight = Lb( distribution.at( lb ) , 1 );
	int height = distribution.matrixHeight();
	int lbWidth = Lb( distribution.at( lb ) , 2 );
	int width = distribution.matrixWidth();


	QStringList columnHeaders;
	int columnCount = 0;
	for( int i = lbHeight ; i <= height ; i++ ){
		for( int j = lbWidth ; j <= width ; j++ ){
			columnCount++;
			columnHeaders << QString("%1 -> %2").arg(i).arg(j);
		}
	}
	table->setColumnCount( columnCount );
	table->setHorizontalHeaderLabels( columnHeaders );

	table->setRowCount( ub - lb +1 );
	int colCount = 0;
	for( int i = lbHeight ; i <= height ; i++ ){
		for( int j = lbWidth ; j <= width ; j++ ){
			//columnHeaders << QString("%1 -> %2").arg(i).arg(j);
			ivector iv = distribution.getVectorAt( i , j );

			for( int c = Lb( iv ) ; c <= Ub( iv ) ; c++ ){
				double inf = _double( Inf( iv[c] ) );
				double sup = _double( Sup( iv[c] ) );
				QString itemText = QString("%1\n%2").arg(sup).arg(inf);
				QTableWidgetItem *newItem =	new QTableWidgetItem(itemText);
				table->setItem( c, colCount , newItem);
			}
			colCount++;
		}
	}

	table->resizeRowsToContents();
}
