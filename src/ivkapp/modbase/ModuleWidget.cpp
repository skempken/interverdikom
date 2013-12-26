#include "ModuleWidget.h"

#include <iostream>

#include <QMessageBox>

#include "ProjectFile.h"
#include "MainWindow.h"
#include "ModuleManager.h"
#include "XMLUtil.h"

#include "computation/ComputationParameters.h"

using namespace std;

using ivk::ComputationParameters;

ModuleWidget::ModuleWidget() :
	QWidget(MainWindow::getLastInstance()), parentModule(0), treeWidgetItem(0)
{
}

ModuleWidget::~ModuleWidget()
{
}

void ModuleWidget::addSubWidget(ModuleWidget *widget, const QString &name)
{
	moduleManager->addModule(widget, name, this);
}

QString ModuleWidget::getName()
{
	return treeWidgetItem->text(0);
}

void ModuleWidget::updateModuleNameInFile(QString name)
{
	rootElement.setAttribute("name", name);
}

void ModuleWidget::updateActionsMenu(QMenu * menu)
{
	menu->clear();

	// Ignore request if no actions were defined
	if (!actions.size())
	{
		menu->setEnabled(false);
		return;
	}

	list<QAction*>::iterator it;
	for (it = actions.begin(); it != actions.end(); it++)
	{
		menu->addAction(*it);
	}

	menu->setEnabled(true);
}

void ModuleWidget::createDefaultActions()
{
	if (actions.size() > 0)
	{
		defaultActionSeparator = new QAction(this);
		defaultActionSeparator->setSeparator(true);
		addAction(defaultActionSeparator);
	}

	duplicateAction = new QAction(tr("Duplicate module"), this);
	connect(duplicateAction, SIGNAL(triggered()), this,
			SLOT(duplicateClicked()));
	addAction(duplicateAction);

	deleteAction = new QAction(tr("Delete module..."), this);
	connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteClicked()));
	addAction(deleteAction);

	setAsRootAction = new QAction(tr("Set as root"), this);
	connect(setAsRootAction, SIGNAL(triggered()), this, SLOT(setAsRootClicked()));
	addAction(setAsRootAction);
}

void ModuleWidget::duplicateClicked()
{
	moduleManager->duplicateModule(this);
}

void ModuleWidget::setAsRootClicked()
{
	moduleManager->setNewRoot(treeWidgetItem);
}

void ModuleWidget::deleteClicked()
{
	if (QMessageBox::question(this, tr("Delete module"),
			tr("Do you really want to delete the module?"), QMessageBox::Yes
					| QMessageBox::No, QMessageBox::No) != QMessageBox::Yes)
	{
		return;
	}

	rootElement.parentNode().removeChild(rootElement);
	delete treeWidgetItem;

	moduleManager->moduleSelected();

	// TODO recursive delete, free object
}

void ModuleWidget::setEnabled(bool enabled)
{
	QWidget::setEnabled(enabled);

	if (enabled)
	{
		rootElement.setAttribute("enabled", "true");
	}
	else
	{
		rootElement.setAttribute("enabled", "false");
	}
}

QDomElement ModuleWidget::loadElement(QString id)
{
	QDomElement result = dataElement.firstChildElement(id).firstChildElement();
	if (result.isNull())
	{
		loadSuccessful = false;
	}
	else
	{
		loadSuccessful = true;
	}

	return result;
}

QString ModuleWidget::loadString(QString id)
{
	return loadElement(id).text();
}

void ModuleWidget::saveString(QString id, QString value,
		AbstractComputationBase *computation)
{
	if (computation)
	{
		ComputationParameters params = computation->getParameters();
		params.setString(id.toStdString(), value.toStdString());
		computation->setParameters(params);
	}

	QDomElement valueElement = dataElement.ownerDocument().createElement("StringData");
	valueElement.appendChild(dataElement.ownerDocument().createTextNode(value));
	saveElement(id, valueElement);
}

int ModuleWidget::loadInt(QString id)
{
	return loadElement(id).text().toInt(&loadSuccessful);
}

void ModuleWidget::saveInt(QString id, int value,
		AbstractComputationBase *computation)
{
	if (computation)
	{
		ComputationParameters params = computation->getParameters();
		params.setInt(id.toStdString(), value);
		computation->setParameters(params);
	}

	QDomElement valueElement = dataElement.ownerDocument().createElement("IntegerData");
	valueElement.appendChild(dataElement.ownerDocument().createTextNode(QString("%1").arg(value)));
	saveElement(id, valueElement);
}

void ModuleWidget::saveElement(QString id, QDomElement element)
{
	QDomElement fieldElement = XMLUtil::getOrCreateChild(
			dataElement.ownerDocument(), dataElement, id);

	while (!fieldElement.firstChild().isNull())
	{
		fieldElement.removeChild(fieldElement.firstChild());
	}

	fieldElement.appendChild(element);

	MainWindow::getLastInstance()->getFile().wasModified();
}

real ModuleWidget::loadReal(QString id)
{
	return XMLUtil::xmlToReal(loadElement(id));
}

void ModuleWidget::saveReal(QString id, const real & value,
		AbstractComputationBase *computation)
{
	if (computation)
	{
		ComputationParameters params = computation->getParameters();
		params.setReal(id.toStdString(), value);
		computation->setParameters(params);
	}

	saveElement(id, XMLUtil::realToXml(value, dataElement.ownerDocument()));
}

interval ModuleWidget::loadInterval(QString id)
{
	return XMLUtil::xmlToInterval(loadElement(id));
}

void ModuleWidget::saveInterval(QString id, const interval & value)
{
	saveElement(id, XMLUtil::intervalToXml(value, dataElement.ownerDocument()));
}

rmatrix ModuleWidget::loadRmatrix(QString id)
{
	return XMLUtil::xmlToRmatrix(loadElement(id));
}

void ModuleWidget::saveRmatrix(QString id, const rmatrix & value)
{
	saveElement(id, XMLUtil::rmatrixToXml(value, dataElement.ownerDocument()));
}

imatrix ModuleWidget::loadImatrix(QString id)
{
	return XMLUtil::xmlToImatrix(loadElement(id));
}

void ModuleWidget::saveImatrix(QString id, imatrix & value)
{
	saveElement(id, XMLUtil::imatrixToXml(value, dataElement.ownerDocument()));
}

rvector ModuleWidget::loadRvector(QString id)
{
	return XMLUtil::xmlToRvector(loadElement(id));
}

void ModuleWidget::saveRvector(QString id, const rvector & value)
{
	saveElement(id, XMLUtil::rvectorToXml(value, dataElement.ownerDocument()));
}

intvector ModuleWidget::loadIntVector(QString id)
{
	return XMLUtil::xmlToIntvector(loadElement(id));
}

void ModuleWidget::saveIntVector(QString id, const intvector & value,
		AbstractComputationBase *computation)
{
	if (computation)
	{
		ComputationParameters params = computation->getParameters();
		params.setIntVector(id.toStdString(), value);
		computation->setParameters(params);
	}

	saveElement(id, XMLUtil::intvectorToXml(value, dataElement.ownerDocument()));
}

ivector ModuleWidget::loadIvector(QString id)
{
	return XMLUtil::xmlToIvector(loadElement(id));
}

void ModuleWidget::saveIvector(QString id, const ivector & value)
{
	saveElement(id, XMLUtil::ivectorToXml(value, dataElement.ownerDocument()));
}

SSMProcess ModuleWidget::loadSSMProcess(QString id)
{
	return XMLUtil::xmlToSSMProcess(loadElement(id));
}

void ModuleWidget::saveSSMProcess(QString id, const SSMProcess & value)
{
	saveElement(id, XMLUtil::ssmProcessToXml(value, dataElement.ownerDocument()));
}

SSMPQueue ModuleWidget::loadSSMPQueue(QString id)
{
	return XMLUtil::xmlToSSMPQueue(loadElement(id));
}

void ModuleWidget::saveSSMPQueue(QString id, const SSMPQueue & value)
{
	saveElement(id, XMLUtil::ssmpQueueToXml(value, dataElement.ownerDocument()));
}

void ModuleWidget::displayContextMenu(const QPoint & pos)
{
	// Ignore request if no actions were defined
	if (!actions.size())
	{
		return;
	}

	QMenu contextMenu(this);

	list<QAction*>::iterator it;
	for (it = actions.begin(); it != actions.end(); it++)
	{
		contextMenu.addAction(*it);
	}

	contextMenu.exec(pos);
}
