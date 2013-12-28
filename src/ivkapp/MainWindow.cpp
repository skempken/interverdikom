#include "MainWindow.h"

#include <iostream>

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>

#include "StringUtil.h"

#include "ModuleManager.h"
#include "RawFileParserDialog.h"
#include "AboutDialog.h"
#include "TraceDisplay.h"
#include "ImportVideoFileDialog.h"
#include "ImportModelDialog.h"

#include "ProjectFile.h"

#include "GetPot.h"

#include "utility/Logging.hpp"
#include "SignalLogger.h"

using namespace std;
using namespace ivk;

MainWindow *MainWindow::lastInstance = 0;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setupUi(this);

	lastInstance = this;
	moduleSelect->setColumnCount(1);

	moduleManager = new ModuleManager(moduleSelect, moduleContent, moduleTitleLabel, &file, rootCombo);

	moduleSelect->setEnabled(false);
	navigationPath->setTreeWidget(moduleSelect);
	connect(moduleSelect, SIGNAL(itemClicked(QTreeWidgetItem*,int)), navigationPath, SLOT(moduleSelected(QTreeWidgetItem*)));
	connect(moduleSelect->itemDelegate(), SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), this, SLOT(updateModuleName())); 

	// Workaround, prevents stderr message from QT (QT bug?)
	qRegisterMetaType<QTextCursor>("QTextCursor");
	
	// Setup signal logger
	SignalLogger *logger = new SignalLogger();
	Logging::setLogger(logger);
	Logging::setLogLevel(Logging::Debug);
	connect(logger, SIGNAL(logMessage(QString)), outputConsole, SLOT(printMessage(QString)));
	connect(logger, SIGNAL(logError(QString)), outputConsole, SLOT(printError(QString)));
	
	actionSave->setEnabled(false);
	actionSave_As->setEnabled(false);
	menuImport->setEnabled(false);
}

void MainWindow::showAllDeletedPage() {
	moduleContent->setCurrentWidget(allDeletedPage);
	moduleTitleLabel->setText(tr("InterVerdiKom - All modules deleted"));
}

void MainWindow::updateModuleName()
{
	file.wasModified();
	updateFileStatus();
	navigationPath->moduleSelected(moduleSelect->currentItem());
	moduleManager->moduleNameChanged(moduleSelect->currentItem());
}

MainWindow::~MainWindow()
{
	delete moduleManager;
}

void MainWindow::parseCommandLine(int argc, char **argv)
{
	GetPot commandLine(argc, argv);
	
	// TODO command line parsing
}

void MainWindow::on_actionSave_triggered()
{
	cout << tr("Saving...").toStdString() << endl;
	if (file.hasPath())
	{
		moduleManager->setNewRoot(0);
		getFile().write();
		cout << tr("Saved.").toStdString() << endl;
	}
	else
	{
		on_actionSave_As_triggered();
	}

	updateFileStatus();
}

void MainWindow::on_actionImport_Video_File_triggered()
{
	ImportVideoFileDialog(this).exec();
	
	updateFileStatus();
}

void MainWindow::on_actionImport_Model_triggered()
{
	ImportModelDialog(this).exec();
	
	updateFileStatus();
}

void MainWindow::on_actionOpen_triggered()
{
	if (file.isModified())
	{
		QMessageBox msgBox;
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No
				| QMessageBox::Cancel);
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText(tr("There are unsaved changes.\nDo you want to save before opening a new file?"));
		msgBox.setWindowTitle(tr("Warning"));

		switch (msgBox.exec())
		{
		case QMessageBox::Yes:
			on_actionSave_triggered();
			break;
		case QMessageBox::Cancel:
			return;
		case QMessageBox::No:
		default:
			break;
		}
	}

	QString filePath = QFileDialog::getOpenFileName(this, tr("Open Project"),
			QString(), tr("IVK project files (*.ivk);;All files (*.*)"));

	if (filePath.isNull())
	{
		return;
	}

	if (!file.open(filePath))
	{
		cerr << tr("Could not open file '%1'.").arg(filePath).toStdString() << endl;
	}
	else
	{
		moduleSelect->setEnabled(true);
		actionSave->setEnabled(true);
		actionSave_As->setEnabled(true);
		menuImport->setEnabled(true);
		actionImport_Video_File->setEnabled(true);
		actionImport_Trace->setEnabled(true);
		actionImport_Model->setEnabled(true);
		rootCombo->setEnabled(true);
		
		moduleTitleLabel->setText("InterVerdiKom - Opened project");
		moduleContent->setCurrentWidget(openedProjectFilePage);

		cout << tr("Opened '%1'.").arg(filePath).toStdString() << endl;
	}
	
	updateFileStatus();
}

void MainWindow::on_actionImport_Trace_triggered()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Import Trace"),
			QString(), tr("Trace files (*.*)"));

	if (filePath.isNull())
	{
		return;
	}

	cout << tr("Importing trace '%1'...").arg(filePath).toStdString() << endl;
	TraceDisplay *traceDisplay = TraceDisplay::importFromFile(filePath);

	if (traceDisplay)
	{
		cout << tr("Imported trace '%1'.").arg(filePath).toStdString() << endl;
		moduleManager->addModule(traceDisplay, tr("Trace: %1").arg(StringUtil::extractFileNameFromPath(filePath)));
	}
	else
	{
		cerr << tr("Canceled import of trace '%1'.").arg(filePath).toStdString() << endl;
	}
	
	updateFileStatus();
}

void MainWindow::on_actionSave_As_triggered()
{
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save Project"),
			QString(), tr("IVK project files (*.ivk);;All files (*.*)"));

	if (filePath.isNull())
	{
		return;
	}

	cout << tr("Saving as '%1'...").arg(filePath).toStdString() << endl;
	moduleManager->setNewRoot(0);

	if (getFile().write(filePath))
	{
		cout << tr("Saved as '%1'.").arg(filePath).toStdString() << endl;
	}
	else
	{
		cerr << tr("Could not save.").arg(filePath).toStdString() << endl;
	}

	updateFileStatus();
}

void MainWindow::on_actionNew_triggered()
{
	getFile().createNewFile();
	updateFileStatus();

	moduleTitleLabel->setText("InterVerdiKom - New project");
	moduleContent->setCurrentWidget(newProjectFilePage);

	actionSave->setEnabled(true);
	actionSave_As->setEnabled(true);
	
	rootCombo->setEnabled(true);

	menuImport->setEnabled(true);
	actionImport_Video_File->setEnabled(true);
	actionImport_Trace->setEnabled(true);
	actionImport_Model->setEnabled(true);

	cout << tr("Created new project file.").toStdString() << endl;
}

void MainWindow::updateFileStatus()
{
	if (file.isOpened())
	{
		setWindowTitle(QString("InterVerdiKom - %1[*]").arg(file.getFileName()));
		moduleSelect->setEnabled(true);
	}
	else
	{
		setWindowTitle("InterVerdiKom [*]");
		moduleSelect->setEnabled(false);
	}
	
	setWindowModified(file.isModified());
}

void MainWindow::setTitleForFile(ProjectFile* openedFile)
{
	// TODO REIMPLEMENT
	//QString fname(openedFile->getFileName().c_str());
	//setWindowTitle(QString("InterVerdiKom - %1[*]").arg(fname.right(fname.size() - fname.lastIndexOf(QString("/")) - 1)));
	//setWindowModified(false);
	//moduleSelect->setEnabled(true);
}

void MainWindow::on_actionQuit_triggered()
{
	cout << "Terminating program."<< endl;
	QCoreApplication::quit();
}

void MainWindow::on_actionClear_Console_triggered()
{
	outputConsole->clear();
}

void MainWindow::on_actionCreate_Trace_From_Video_File_triggered()
{
	RawFileParserDialog *parserDialog = new RawFileParserDialog(this);
	parserDialog->exec();
}

void MainWindow::on_actionSave_Console_As_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this,
			tr("Specify output file"));
	if (fileName.isEmpty())
	{
		return;
	}

	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		cerr << tr("Cannot write file %1: %2.").arg(fileName).arg(file.errorString()).toStdString() << endl;
		return;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << outputConsole->toPlainText();
	QApplication::restoreOverrideCursor();

	cout << tr("Console content saved to %1.").arg(fileName).toStdString() << endl;

	return;
}


void MainWindow::on_actionAbout_triggered()
{

}
