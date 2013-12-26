#include "ExportTableDialog.h"

#include <QFileDialog>

ExportTableDialog::ExportTableDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
	
	csvOptionsGroup->hide();
}

ExportTableDialog::~ExportTableDialog() {}

void ExportTableDialog::on_browseButton_clicked()
{
	QString fname = QFileDialog::getSaveFileName(this, tr("Specify output file"));
	if (fname.size())
		pathEdit->setText(fname);
}

void ExportTableDialog::on_exportButton_clicked()
{
	emit exportInitialized();
}
