#include "ModuleOverview.h"

#include <stack>
#include <QTreeWidgetItem>

#include "MainWindow.h"

using namespace std;

ModuleOverview::ModuleOverview(QWidget *parent, class QTreeWidgetItem *widgetItem, QString explanationText) :
		QWidget(parent), originalItem(widgetItem)
{
	setupUi(this);
	descriptionLabel->setText(explanationText);
	if (explanationText.isNull())
		descriptionFrame->hide();
		
	connect(treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(selectSubModule(QTreeWidgetItem*)));
	connect(this,SIGNAL(subModuleSelected(QTreeWidgetItem*,int)),getModuleTreeWidget(),SIGNAL(itemClicked(QTreeWidgetItem*,int)));
}

ModuleOverview::~ModuleOverview() {}

void ModuleOverview::initTreeWidget()
{
	treeWidget->addTopLevelItem(originalItem->clone());
	treeWidget->expandAll();
}

QTreeWidget *ModuleOverview::getModuleTreeWidget()
{
	return 	MainWindow::getLastInstance()->getModuleTreeWidget();
}

void ModuleOverview::selectSubModule(QTreeWidgetItem *moduleItem)
{
	stack<int> indexHierarchy;
	while (moduleItem->parent() != 0)
	{
		// TODO FIXME: Workaround.. why is the item structure cloned backwards?!
		indexHierarchy.push(moduleItem->parent()->childCount() - 1 - moduleItem->parent()->indexOfChild(moduleItem));
		moduleItem = moduleItem->parent();
	}
	
	QTreeWidgetItem *selectedOriginalItem = originalItem;
	while (!indexHierarchy.empty())
	{
		selectedOriginalItem = selectedOriginalItem->child(indexHierarchy.top());
		indexHierarchy.pop();
	}
	
	getModuleTreeWidget()->setCurrentItem(selectedOriginalItem);
	emit subModuleSelected(selectedOriginalItem,0);
}
