#ifndef STATETRANSITIONWIDGET_H_
#define STATETRANSITIONWIDGET_H_

#include <QWidget>
#include "ui_base/ui_StateTransitionWidget.h"

#include <imatrix.hpp>
#include <ivector.hpp>

#include "ProjectFile.h"

using namespace cxsc;

class StateTransitionWidget : public QWidget, private Ui::StateTransitionWidget
{
	Q_OBJECT
	
public:
	/// Default constructor
	/**
	 * \param parent Parent widget
	 */
	StateTransitionWidget(QWidget *parent = 0);
	
	/// Destructor
	virtual ~StateTransitionWidget();
	
private:
	/// Updates the display with given transition matrix.
	void updateTransitionMatrix(const imatrix &transition);
	
	/// Updates the display with given steady state distribution.
	void updateSteadyDistribution(const ivector &dist);
	
public slots:
	void setFile(ProjectFile* openedFile);
	
};

#endif /*STATETRANSITIONWIDGET_H_*/
