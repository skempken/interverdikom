#ifndef SERVICEDISTRIBUTIONWIDGET_H_
#define SERVICEDISTRIBUTIONWIDGET_H_

#if 0

#include "DistributionWidget.h"

class ServiceDistributionEditPage;
class ProjectFile;

/// DistributionWidget for displaying service distributions
class ServiceDistributionWidget : public DistributionWidget
{
	Q_OBJECT
	
public:
	/// Default constructor
	/**
	 * \param parent Parent widget
	 */
	ServiceDistributionWidget(QWidget* parent = 0);
	
	/// Destructor
	virtual ~ServiceDistributionWidget();

public slots:
	/// Sets the currently opened file
	/**
	 * \param openedFile Opened File
	 */
	void setFile(ProjectFile* openedFile);
	
private:
	ServiceDistributionEditPage *editPage;
};

#endif /*SERVICEDISTRIBUTIONWIDGET_H_*/

#endif
