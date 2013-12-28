#ifndef IVKMODULEOVERVIEW_H_
#define IVKMODULEOVERVIEW_H_

// TODO REMOVEME? UNUSED (as of 2007-09-11)

#include <QWidget>
#include "ui_base/ui_ModuleOverview.h"

#include <QString>
#include <QVBoxLayout>

/// Widget giving information about submodules of module parent node
/**
 * This widget is automatically generated and initialized by ModuleManager
 * if a parent node without an explicit widget is inserted. It contains
 * an optional description text entered by the GUI designer and displays
 * a list of submodules under the node it is associated with. It also
 * allows to directly navigate to these submodules.
 */
class ModuleOverview : public QWidget, private Ui::ModuleOverview
{
	Q_OBJECT
	
public:
	/// Constructor
	/**
	 * \param parent The parent widget
	 * \param widgetItem The widget item this overview is associated with
	 * \param explanationText The custom description text
	 */
	ModuleOverview(QWidget *parent, class QTreeWidgetItem *widgetItem, QString explanationText = QString());
	
	/// Destructor
	virtual ~ModuleOverview();
	
	/// Initialized the tree structure of submodules
	/**
	 * This function should only be called after the complete tree structure
	 * of the main module selection widget is complete. It will then clone
	 * the node which it is associated with, which in turn clones all subnodes
	 * and display this node in the submodule tree widget.
	 */
	void initTreeWidget();
	
	class QTreeWidget *getModuleTreeWidget();
	
public slots:
	void selectSubModule(class QTreeWidgetItem *moduleItem);
	
signals:
	void subModuleSelected(class QTreeWidgetItem *moduleItem, int column);
	
private:
	/// Associated item in the main module tree widget
	class QTreeWidgetItem *originalItem;
};

#endif /*IVKMODULEOVERVIEW_H_*/
