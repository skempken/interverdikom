#include "ModuleList.h"

#include <iostream>

#include <QMimeData>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QSplitter>

#include "ModuleManager.h"
#include "ModuleWidget.h"
#include "MainWindow.h"

#include "dialog/ComparisonDialog.h"

using namespace std;

ModuleList::ModuleList(QWidget * parent) :
	QTreeWidget(parent) {
	setDragEnabled(true);
	viewport()->setAcceptDrops(true);
}

ModuleList::~ModuleList() {
	// TODO Auto-generated destructor stub
}

void ModuleList::dragMoveEvent(QDragMoveEvent * event) {
	QTreeWidget::dragMoveEvent(event);
	//event->accept();
}

void ModuleList::mousePressEvent(QMouseEvent *event) {
	QTreeWidget::mousePressEvent(event);
}

void ModuleList::mouseMoveEvent(QMouseEvent *event) {
	QTreeWidget::mouseMoveEvent(event);
}

bool ModuleList::dropMimeData(QTreeWidgetItem *parent, int index,
		const QMimeData *data, Qt::DropAction action) {
	cout << "DROP! Formats: " << data->formats().join(";").toStdString()
			<< endl;

	if (!parent) {
		return false;
	}

	MyMimeData *mmd = (MyMimeData*) data;
	QTreeWidgetItem * draggedItem = mmd->indexes().first();
	QTreeWidgetItem * targetItem = parent;

	ModuleManager * mm = MainWindow::getLastInstance()->getModuleManager();
	ComparisonDialog dia;
	if ((mm->getMatchingModule(draggedItem))->getModuleManager() == mm) {
		cout << "Ja! 1" << endl;
	}
	if ((mm->getMatchingModule(targetItem))->getModuleManager() == mm) {
		cout << "Ja! 2" << endl;
	}
	dia.addWidgets(ModuleManager::cloneModule(
			mm->getMatchingModule(draggedItem)), ModuleManager::cloneModule(
			mm->getMatchingModule(targetItem)));
	dia.setModal(true);
	dia.exec();

	return true;
}

QMimeData * ModuleList::mimeData(const QList<QTreeWidgetItem *> items) const {
	return new MyMimeData(items);
}

void ModuleList::dragEnterEvent(QDragEnterEvent *event) {
	QTreeWidget::dragEnterEvent(event);
	// event->accept();
}

void ModuleList::dropEvent(QDropEvent * event) {
	QTreeWidget::dropEvent(event);
}

