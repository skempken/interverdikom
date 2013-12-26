#include "HelpButton.h"

#include "HelpDialog.h"
#include <QMessageBox>

HelpButton::HelpButton(QWidget *parent) : QPushButton(parent), dialog(0)
{
	connect(this, SIGNAL(clicked()), this, SLOT(showHelpDialog()));
}

HelpButton::~HelpButton() {}

void HelpButton::showHelpDialog()
{
	if (!dialog)
		dialog = new HelpDialog(this, whatsThis());
		
	dialog->show();
}
