#ifndef ABOUTDIALOG_H_
#define ABOUTDIALOG_H_

#include <QDialog>
#include "ui_base/ui_AboutDialog.h"

/// Dialog with credits for the program
class AboutDialog : public QDialog, private Ui::AboutDialog
{
	Q_OBJECT
	
public:
	/// Default constructor
	AboutDialog(QWidget *parent = 0);
	
	/// Destructor
	virtual ~AboutDialog();
};

#endif /*ABOUTDIALOG_H_*/
