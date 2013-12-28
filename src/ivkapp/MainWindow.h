#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "ui_base/ui_MainWindow.h"

#include "getter_setter_macros.h"

#include "ProjectFile.h"

class ModuleManager;
class QTreeWidget;

/// Main window of the GUI application
class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	/// Default constructor
	/**
	 * \param parent Parent widget
	 */
	MainWindow(QWidget *parent = 0);

	/// Destructor
	virtual ~MainWindow();

	void parseCommandLine(int argc, char **argv);

	void updateFileStatus();

	/// Return the instance that was last constructed
	static MainWindow *getLastInstance()
	{
		return lastInstance;
	}
	
	static LogTextField *getOutputConsole()
	{
		return lastInstance->outputConsole;
	}
	
	void showAllDeletedPage();
	
	GETTER_R(file, ProjectFile, getFile)

	GETTER(moduleSelect, QTreeWidget*, getModuleTreeWidget)

	GETTER(moduleManager, ModuleManager*, getModuleManager)

	GETTER(menuActions, QMenu*, getActionsMenu)

private:
	/// Helper function: Sets up the module list and associated widgets
	void setupModules();

	/// Last constructed instance
	static MainWindow *lastInstance;

	/// Currently opened file
	ProjectFile file;

	ModuleManager * moduleManager;

private slots:
	
	/// Autoslot for "Quit" menu entry
	void on_actionQuit_triggered();
	
	/// Autoslot for "Clear Console" menu entry
	void on_actionClear_Console_triggered();
	
	/// Autoslot for "Save Console As..." menu entry
	void on_actionSave_Console_As_triggered();
	
	/// Autoslot for "Create trace from file..." menu entry
	void on_actionCreate_Trace_From_Video_File_triggered();
	
	/// Autoslot for "About..." menu entry
	void on_actionAbout_triggered();
	
	/// Autoslot for "Save" menu entry
	void on_actionSave_triggered();
	
	/// Autoslot for "Save As..." menu entry
	void on_actionSave_As_triggered();
	
	/// Autoslot for "New" menu entry
	void on_actionNew_triggered();
	
	/// Autoslot for "Open..." menu entry
	void on_actionOpen_triggered();
	
	/// Autoslot for "Import Trace..." menu entry
	void on_actionImport_Trace_triggered();
	
	/// Autoslot for "Import Video File..." menu entry
	void on_actionImport_Video_File_triggered();
	
	/// Autoslot for "Import Model..." menu entry
	void on_actionImport_Model_triggered();
	
	/// Helper function: Adjusts the window title to reflect the currently opened file
	void setTitleForFile(ProjectFile* openedFile);
	
	void updateModuleName();

signals:
	/// Emitted when a new file has been opened
	void fileChanged(ProjectFile* openedFile);
};

#endif /*MAINWINDOW_H_*/
