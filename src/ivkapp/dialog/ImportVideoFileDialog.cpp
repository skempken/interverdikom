#include "ImportVideoFileDialog.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <QFileDialog>

#include "MainWindow.h"
#include "ModuleManager.h"
#include "TraceDisplay.h"
#include "StringUtil.h"

#include "ContainerFormatParser.h"

using namespace std;

ImportVideoFileDialog::ImportVideoFileDialog(QWidget *parent) :
	QDialog(parent), Ui::ImportVideoFileDialog()
{
	setupUi(this);
}

ImportVideoFileDialog::~ImportVideoFileDialog()
{
}

void ImportVideoFileDialog::on_browseButton_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(this,
			tr("Select video file"), QString(),
			tr("Movies (*.3gp *.avi *.mov *.wmv *.mpg)"));

	if (!filePath.isNull())
	{
		pathEdit->setText(filePath);
	}
}

void ImportVideoFileDialog::exec()
{
	on_browseButton_clicked();
	if (pathEdit->text() != "")
	{
		QDialog::exec();
	}
}

void ImportVideoFileDialog::accept()
{
	QString filePath = pathEdit->text();
	QString fileName = StringUtil::extractFileNameFromPath(pathEdit->text());

	close();

	cout << tr("Importing video file '%1'...").arg(filePath).toStdString() << endl;

	cout << tr("Invoking Raw File Parser...").toStdString() << endl;

	ifstream inputFileStream(pathEdit->text().toAscii());
	if (!inputFileStream.good())
	{
		cerr << tr("Bad file '%1'.").arg(filePath).toStdString() << "."<< endl;
		return;
	}

	ContainerFormatParser
			*parser = ContainerFormatParser::getParserForFile(inputFileStream);
	if (parser == 0)
	{
		cerr << tr("Unsupported file format.").toStdString() << endl;
		return;
	}

	ostringstream videoStreamData, audioStreamData;
	parser->parseFile(inputFileStream);
	parser->writeOutputFiles(videoStreamData, audioStreamData);

	TraceDisplay *videoStreamDisplay = 0, *audioStreamDisplay = 0;

	cout << tr("Importing traces...").toStdString() << endl;
	ModuleManager * moduleManager = MainWindow::getLastInstance()->getModuleManager();
	if (importVideoCheck->isChecked())
	{
		cout << tr("Importing video trace data...").toStdString() << endl;
		if ((videoStreamDisplay
				= TraceDisplay::importFromStdString(videoStreamData.str())))
		{
			moduleManager->addModule(videoStreamDisplay, tr("VTrace: %1").arg(fileName));
		}
	}

	if (importAudioCheck->isChecked())
	{
		cout << tr("Importing audio trace data...").toStdString() << endl;
		if ((audioStreamDisplay
				= TraceDisplay::importFromStdString(audioStreamData.str())))
		{
			moduleManager->addModule(audioStreamDisplay, tr("ATrace: %1").arg(fileName));
		}
	}

	cout << tr("Imported '%1'.").arg(filePath).toStdString() << endl;
}
