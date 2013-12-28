#ifndef HELPDIALOG_H_
#define HELPDIALOG_H_

#include <QDialog>
#include "ui_base/ui_HelpDialog.h"

class HelpDialog : public QDialog, private Ui::HelpDialog
{
public:
	HelpDialog(QWidget *parent, const QString &helpFile);
	virtual ~HelpDialog();
};

#endif /*HELPDIALOG_H_*/
