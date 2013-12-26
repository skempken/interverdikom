#include "HelpDialog.h"

#include <QFile>

HelpDialog::HelpDialog(QWidget *parent, const QString &helpFile) : QDialog(parent)
{
	setupUi(this);
	QFile file(QString("help/") + helpFile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		contentText->setText(QString("Missing help file ") + helpFile + QChar('.'));
	else
		contentText->setText(QString::fromAscii(file.readAll()));
		
	file.close();
}

HelpDialog::~HelpDialog() {}
