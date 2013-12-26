#ifndef IMPORTVIDEOFILEDIALOG_H_
#define IMPORTVIDEOFILEDIALOG_H_

#include <QDialog>
#include "ui_ImportVideoFileDialog.h"

class ImportVideoFileDialog : public QDialog, protected Ui::ImportVideoFileDialog
{
	Q_OBJECT
	
public:
	ImportVideoFileDialog(QWidget *parent = 0);
	
	virtual ~ImportVideoFileDialog();
	
	void exec();
	
protected slots:
	void accept();
	
private slots:
	/// Autoslot for click event of "Browse..." button for input file path
	void on_browseButton_clicked();
};

#endif /*IMPORTVIDEOFILEDIALOG_H_*/
