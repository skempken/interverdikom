#ifndef WHRESULTWIDGET_H_
#define WHRESULTWIDGET_H_

#include "ModuleWidget.h"
#include "ui_WHResultWidget.h"
#include "data/ISMPWHFactors.h"

using namespace ivk;

class WHResultWidget: public ModuleWidget, protected Ui::WHResultWidget
{
	Q_OBJECT
	FACTORY_DECLARATIONS_FOR(WHResultWidget)

public:
	WHResultWidget();

	WHResultWidget(const ISMPWHFactors *queue);

	virtual ~WHResultWidget();

	virtual const ISMPWHFactors* getISMPWHFactors() const;

protected:
	void loadModel()
	{}

	void createActions();

	void setTable( IMatrixPolynomial distribution , QTableWidget* table);
private:
	const ISMPWHFactors *factors;

private slots:
	void workloadRequested();
};

#endif /*WHRESULTWIDGET_H_*/
