#ifndef IMPORTMODELDIALOG_H_
#define IMPORTMODELDIALOG_H_

#include <QDialog>
#include "ui_ImportModelDialog.h"

#include "data/SSMProcess.h"
#include "data/GIProcess.h"
#include "data/SSMPQueue.h"

#include <rvector.hpp>

#include <fstream>
#include <iostream>

using namespace cxsc;
using namespace ivk;
using std::ifstream;

class ImportModelDialog : public QDialog, protected Ui::ImportModelDialog
{
	
	Q_OBJECT
	
public:
	ImportModelDialog(QWidget* parent = 0);
	
	virtual ~ImportModelDialog();
	
public slots:
	void exec();
	void on_browseButton_clicked();
	
protected slots:
	void accept();
	
private:
	SSMProcess* createSSMProcess(ifstream& stream);
	GIProcess* createGIProcess(ifstream& stream);
	rvector readDistribution(ifstream& stream, int length);
};

#endif /*IMPORTMODELDIALOG_H_*/
