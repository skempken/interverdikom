#include "ModuleManager.h"

#include <iostream>
#include <map>

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QStackedWidget>
#include <QLabel>

#include "ClassFactory.hpp"
#include "ModuleWidget.h"
#include "ModuleOverview.h"
#include "MainWindow.h"

using namespace std;

ModuleManager *ModuleManager::instance = 0;

ModuleManager::~ModuleManager() {
}

void ModuleManager::showContextMenu(const QPoint & pos) {
	QList<QTreeWidgetItem *> selectedItems = treeWidget->selectedItems();
	if (!selectedItems.isEmpty()) {
		moduleMappings[selectedItems[0]]->displayContextMenu(treeWidget->mapToGlobal(pos));
	}
}

void ModuleManager::duplicateModule(ModuleWidget *module) {
	QDomElement rootElement = module->rootElement.cloneNode(false).toElement();
	rootElement.setAttribute("enabled", "true");
	rootElement.appendChild(module->dataElement.cloneNode(true));

	ModuleWidget *parentWidget = module->getParentModule();
	if (parentWidget) {
		parentWidget->getRootElement().firstChildElement("SubModuleList").appendChild(rootElement);
	} else {
		file->getDocument().documentElement().firstChildElement("ModuleList").appendChild(rootElement);
	}

	file->loadModule(rootElement, parentWidget, true);
}

ModuleWidget * ModuleManager::cloneModule(ModuleWidget *module) {
	QDomElement moduleElement = module->rootElement.cloneNode(false).toElement();
	QString moduleType = moduleElement.attribute("type");
	ModuleWidget
			*newModule = ClassFactory<ModuleWidget>::createInstance(moduleType);
	newModule->setRootElement(moduleElement);
	newModule->setDataElement(moduleElement.firstChildElement("ModuleData"));
	newModule->initPostClone();
	return newModule;
}

ModuleManager::ModuleManager(QTreeWidget *treeWidget,
		QStackedWidget *stackedWidget, QLabel *titleLabel, ProjectFile * file,
		QComboBox *rootCombo) :
	treeWidget(treeWidget), stackedWidget(stackedWidget),
			titleLabel(titleLabel), file(file), rootCombo(rootCombo),
			currentRoot(0), currentRootParent(0) {
	connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(moduleSelected(QTreeWidgetItem*)));

	treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(treeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));

	connect(rootCombo, SIGNAL(activated(int
							)), this, SLOT(rootComboActivated(int)));

							file->setModuleManager(this);
						}

void ModuleManager::rootComboActivated(int index) {
	if (index) {
		setNewRoot(currentHierarchy[index-1]);
	} else {
		setNewRoot(0);
	}
}

bool ModuleManager::clearModuleList() {
	std::map<QTreeWidgetItem*,ModuleWidget*>::iterator
			it;
	for (it = moduleMappings.begin(); it
			!= moduleMappings.end(); it++) {
		delete (*it).second;
	}

	treeWidget->clear();
	moduleMappings.clear();

	return true;
}

bool ModuleManager::addModule(ModuleWidget *theWidget,
		const QString &name,
		ModuleWidget * parentWidget,
		bool createFileStructure, bool autoRename) {
	QTreeWidgetItem *newModuleItem = 0;
	QTreeWidgetItem *futureRootItem = 0;

	if (parentWidget) {
		futureRootItem
				= parentWidget->getTreeWidgetItem();
		parentWidget->getSubWidgets().push_back(theWidget);
		theWidget->setParentModule(parentWidget);
	} else {
		futureRootItem
				= treeWidget->invisibleRootItem();
	}

	QString newName(name);
	if (autoRename) {
		int newNameIndex = 0;

		int hashIndex = newName.lastIndexOf("#");
		if (hashIndex != -1) {
			bool conversionOk;
			newName.mid(hashIndex + 1).toInt(&conversionOk);
			if (conversionOk) {
				newName = newName.left(max(0, hashIndex
						- 1));
			}
		}

		if (treeItemHasChildWithName(futureRootItem,
				newName)) {
			renameTreeItemChildren(futureRootItem,
					newName, newName + " #1");
			newNameIndex = 1;
		} else if (treeItemHasChildWithName(
				futureRootItem, newName + " #1")) {
			newNameIndex = 2;
		}

		if (newNameIndex) {
			while (treeItemHasChildWithName(
					futureRootItem, newName + QString(" #%1").arg(newNameIndex))) {
				newNameIndex++;
			}

			newName += QString(" #%1").arg(newNameIndex);
		}
	}

	theWidget->updateModuleNameInFile(newName);
	newModuleItem = new QTreeWidgetItem(futureRootItem, QStringList(newName));
	newModuleItem->setFlags(Qt::ItemIsSelectable
			| Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled );
	QColor backgroundColor;
	backgroundColor.setHsv(
			ClassFactory<ModuleWidget>::getHue(theWidget->getType()) ,
			20, 250);
	newModuleItem->setBackground(0,
			QBrush(backgroundColor));

	treeWidget->expandItem(futureRootItem);
	stackedWidget->addWidget(theWidget);
	moduleMappings[newModuleItem] = theWidget;
	theWidget->setTreeWidgetItem(newModuleItem);
	theWidget->setModuleManager(this);

	if (createFileStructure) {
		file->insertDataNodesForModule(theWidget);
		theWidget->initPostCreation();
	}

	return true;
}

unsigned int ModuleManager::hashString(
		const std::string& str) {
	unsigned int hash = 0;
	unsigned int x = 0;

	for (std::size_t i = 0; i < str.length(); i++) {
		hash = (hash << 4) + str[i];
		if ((x = hash & 0xF0000000L) != 0) {
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}

	return hash;
}

bool ModuleManager::treeItemHasChildWithName(
		QTreeWidgetItem *item, const QString & name) {
	for (int i = 0; i < item->childCount(); i++) {
		QString currentText(item->child(i)->text(0));

		if (currentText == name) {
			return true;
		}
	}

	return false;
}

void ModuleManager::renameTreeItemChildren(
		QTreeWidgetItem *item, const QString &oldName,
		const QString &newName) {
	for (int i = 0; i < item->childCount(); i++) {
		QString currentText(item->child(i)->text(0));

		if (currentText == oldName) {
			item->child(i)->setText(0, newName);
			moduleMappings[item->child(i)]->updateModuleNameInFile(newName);
		}
	}
}

void ModuleManager::moduleNameChanged(
		QTreeWidgetItem *module) {
	moduleMappings[module]->updateModuleNameInFile(module->text(0));
	moduleSelected(module);
}

void ModuleManager::moduleSelected(
		QTreeWidgetItem *module) {
	if (!module) {
		module = treeWidget->currentItem();
	}

	if (!module) {
		MainWindow::getLastInstance()->showAllDeletedPage();
		return;
	}

	ModuleWidget *associatedWidget =
			moduleMappings[module];

	if (associatedWidget) {
		stackedWidget->setCurrentWidget(associatedWidget);
		titleLabel->setText(QString(module->text(0)));

		associatedWidget->updateActionsMenu(MainWindow::getLastInstance()->getActionsMenu());
	}

	QStringList rootComboStrings;

	QTreeWidgetItem *currentItem = module;
	int currentRootIndex = 0, reverseCurrentRootIndex =
			-1, index = 0;
	bool aboveCurrentRoot = false;
	currentHierarchy.clear();
	while (currentItem) {
		currentHierarchy.push_front(currentItem);
		if (currentItem == currentRoot) {
			reverseCurrentRootIndex = index;
		}

		index++;

		currentItem = currentItem->parent();

		if (!currentItem && !aboveCurrentRoot
				&& currentRootParent) {
			aboveCurrentRoot = true;
			currentItem = currentRootParent;
		}
	}

	rootComboStrings << tr("<Top Level>");

	deque<QTreeWidgetItem*>::iterator it;
	for (it = currentHierarchy.begin(); it
			!= currentHierarchy.end(); it++) {
		rootComboStrings << (*it)->text(0);
	}

	while (rootCombo->count()) {
		rootCombo->removeItem(0);
	}

	rootCombo->addItems(rootComboStrings);

	if (currentRoot) {
		currentRootIndex = currentHierarchy.size()
				- reverseCurrentRootIndex;
		rootCombo->setCurrentIndex(currentRootIndex);
	}
}

void ModuleManager::setNewRoot(QTreeWidgetItem *newRoot) {
	QTreeWidgetItem *item = 0;

	list<QTreeWidgetItem*>::iterator it;
	for (it = hiddenTopLevelItems.begin(); it
			!= hiddenTopLevelItems.end(); it++) {
		(*it)->setHidden(false);
	}

	hiddenTopLevelItems.clear();

	QTreeWidgetItem *oldRoot = currentRoot;
	QTreeWidgetItem *oldRootParent = currentRootParent;
	QTreeWidgetItem *oldRootParentTop =
			currentRootParentTop;

	if (oldRoot) {
		if (oldRootParent) {
			treeWidget->takeTopLevelItem(treeWidget->indexOfTopLevelItem(oldRoot));
			oldRootParent->addChild(oldRoot);
			treeWidget->addTopLevelItem(oldRootParentTop);
		}
	}

	currentRoot = newRoot;
	currentRootParent = 0;
	currentRootParentTop = 0;

	if (newRoot) {
		QTreeWidgetItem *newRootParent =
				currentRootParent = newRoot->parent();

		if (newRootParent) {
			currentRootParent = newRootParent;
			newRootParent->removeChild(newRoot);
			currentRootParentTop = currentRootParent;
			while (currentRootParentTop->parent()) {
				currentRootParentTop
						= currentRootParentTop->parent();
			}

			treeWidget->takeTopLevelItem(treeWidget->indexOfTopLevelItem(currentRootParentTop));
		}

		for (int i = 0; i
				< treeWidget->topLevelItemCount(); i++) {
			item = treeWidget->topLevelItem(i);
			item->setHidden(true);
			hiddenTopLevelItems.push_back(item);
		}

		newRoot->setHidden(false);

		for (int i = 0; i < newRoot->childCount(); i++) {
			newRoot->child(i)->setHidden(false);
		}

		treeWidget->addTopLevelItem(newRoot);

		moduleSelected(newRoot);
	}

	treeWidget->expandToDepth(1);
}
