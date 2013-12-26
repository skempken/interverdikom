#ifndef MODULEMANAGER_H_
#define MODULEMANAGER_H_

#include <QObject>

#include <vector>
#include <deque>
#include <map>

#include <QPoint>

using namespace std;

class QTreeWidget;
class QTreeWidgetItem;
class QLabel;
class QStackedWidget;
class QComboBox;
class QToolButton;
class ModulePage;
class QWidget;
class IvkModuleOverview;
class ModuleWidget;
class DisplayModuleBase;
class ProjectFile;

/// Manages the module list of the main window
class ModuleManager : public QObject
{
	Q_OBJECT

public:
	/// Default constructor
	/**
	 * \param treeWidget MainWindow tree widget
	 * \param stackedWidget MainWindow QStackedWidget
	 */
	ModuleManager(QTreeWidget *treeWidget, QStackedWidget *stackedWidget,
			QLabel *titleLabel, ProjectFile * file,
			QComboBox *rootCombo);

	/// Setter for the tree widget
	/**
	 * \param treeWidget QTreeWidget widget to assiciate with this ModuleManager
	 */
	void setTreeWidget(QTreeWidget *treeWidget)
	{
		this->treeWidget = treeWidget;
	}

	/// Setter for the stacked layout widget
	/**
	 * \param stackedWidget Stacked layout widget to assiciate with this ModuleManager
	 */
	void setStackedWidget(QStackedWidget *stackedWidget)
	{
		this->stackedWidget = stackedWidget;
	}

	void duplicateModule(ModuleWidget *module);

	static ModuleWidget * cloneModule(ModuleWidget *module);

	/// Appends a new item with associated widget to the tree at the current depth
	/**
	 * \param moduleWidget Module widget to associate with tree item
	 * \param name Caption of the new tree item
	 */
	bool addModule(ModuleWidget *theWidget, const QString &name,
			ModuleWidget *parentWidget = 0, bool createFileStructure = true, bool autoRename = true);

	bool clearModuleList();

	void moduleNameChanged(QTreeWidgetItem *module);

	/// Destructor
	virtual ~ModuleManager();

	void setNewRoot(QTreeWidgetItem *newRoot);

private:
	/// Singleton instance
	static ModuleManager *instance;

	bool treeItemHasChildWithName(QTreeWidgetItem *item, const QString & name);

	void renameTreeItemChildren(QTreeWidgetItem *item,
			const QString &oldName, const QString &newName);

	/// Associated tree widget
	QTreeWidget *treeWidget;

	/// Associated stacked layout widget
	QStackedWidget *stackedWidget;

	/// Associated title label
	QLabel *titleLabel;

	ProjectFile *file;

	QComboBox *rootCombo;

	/// Map that associates tree items with their corresponding widgets
	std::map<QTreeWidgetItem*,ModuleWidget*> moduleMappings;

	unsigned int hashString(const std::string& str);

	deque<QTreeWidgetItem*> currentHierarchy;

	QTreeWidgetItem *currentRoot;

	QTreeWidgetItem *currentRootParent;

	QTreeWidgetItem *currentRootParentTop;

	list<QTreeWidgetItem*> hiddenTopLevelItems;

public:
	ModuleWidget * getMatchingModule(QTreeWidgetItem *treeItem) {
		return moduleMappings[treeItem];
	}

public slots:
	/// Callback for associated tree widget
	/**
	 * \param module The clicked module's tree widget item
	 */
	void moduleSelected(QTreeWidgetItem *module = 0);

	void showContextMenu(const QPoint & pos);

private slots:
	void rootComboActivated(int index);
};

#endif /*MODULEMANAGER_H_*/
