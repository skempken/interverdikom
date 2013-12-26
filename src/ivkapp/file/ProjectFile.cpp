#include "ProjectFile.h"

#include <iostream>
#include <QFile>
#include <QBuffer>
#include <QTextStream>

#include "ClassFactory.hpp"
#include "StringUtil.h"
#include "XMLUtil.h"

#include "ModuleManager.h"
#include "ModuleWidget.h"

using namespace std;

ProjectFile::ProjectFile() :
	opened(false), modified(false)
{
}

ProjectFile::~ProjectFile()
{
}

bool ProjectFile::insertDataNodesForModule(ModuleWidget *module)
{
	QDomElement moduleListElement;
	if (module->getParentModule())
	{
		QDomElement parentElement = module->getParentModule()->getRootElement();
		moduleListElement = XMLUtil::getOrCreateChild(domDocument,
				parentElement, "SubModuleList");
	}
	else
	{
		moduleListElement = XMLUtil::getOrCreateChild(domDocument,
				domDocument.documentElement(), "ModuleList");
	}

	QDomElement newRootElement = domDocument.createElement("Module");
	QDomElement newDataElement = domDocument.createElement("ModuleData");

	newRootElement.setAttribute("type", module->getType());
	newRootElement.setAttribute("name", module->getName());
	newRootElement.setAttribute("enabled", "true");

	moduleListElement.appendChild(newRootElement);
	newRootElement.appendChild(newDataElement);
	newRootElement.appendChild(domDocument.createElement("SubModuleList"));

	module->setRootElement(newRootElement);
	module->setDataElement(newDataElement);

	modified = true;

	return true;
}

QString ProjectFile::getFileName()
{
	if (filePath.isNull())
	{
		if (isOpened())
		{
			return tr("Untitled");
		}
		else
		{
			return QString();
		}
	}
	else
	{
		return StringUtil::extractFileNameFromPath(filePath);
	}
}

void ProjectFile::createNewFile()
{
	filePath = QString();

	moduleManager->clearModuleList();

	domDocument = QDomDocument("IVKProject");
	domDocument.appendChild(domDocument.createElement("IVKProject"));
	modified = true;
	opened = true;
}

bool ProjectFile::open(QString fileName)
{
	QFile xmlFile(fileName);
	if (!xmlFile.open(QIODevice::ReadOnly))
	{
		cerr << tr("Failed to open file %1.").toStdString() << endl;
		return false;
	}

	if (!domDocument.setContent(&xmlFile))
	{
		cerr << tr("Could not parse file %1.").toStdString() << endl;
		return false;
	}

	moduleManager->clearModuleList();

	QDomElement moduleList = XMLUtil::getOrCreateChild(domDocument,
			domDocument.documentElement(), "ModuleList");

	QDomElement elementIt = moduleList.firstChildElement();
	while (!elementIt.isNull())
	{
		if (elementIt.tagName() == "Module")
		{
			loadModule(elementIt, 0);
		}

		elementIt = elementIt.nextSiblingElement();
	}

	filePath = fileName;
	opened = true;

	return true;
}

bool ProjectFile::loadModule(QDomElement &moduleElement, ModuleWidget *parent,
		bool autoRename)
{
	QString moduleType = moduleElement.attribute("type");
	if (moduleType.isNull())
	{
		return false;
	}

	ModuleWidget
			*newModule = ClassFactory<ModuleWidget>::createInstance(moduleType);

	newModule->setRootElement(moduleElement);
	newModule->setDataElement(XMLUtil::getOrCreateChild(domDocument,
			moduleElement, "ModuleData"));

	if ((moduleElement.attribute("enabled") == "false") && !autoRename)
	{
		newModule->setEnabled(false);
	}
	
	moduleManager->addModule(newModule, moduleElement.attribute("name",
			moduleType), parent, false, autoRename);

	newModule->initPostLoad();
	
	QDomElement elementIt = XMLUtil::getOrCreateChild(domDocument,
			moduleElement, "SubModuleList").firstChildElement();
	while (!elementIt.isNull())
	{
		if (elementIt.tagName() == "Module")
		{
			loadModule(elementIt, newModule);
		}

		elementIt = elementIt.nextSiblingElement();
	}

	return true;
}

bool ProjectFile::write(const QString & newFilePath)
{
	filePath = newFilePath;

	write();

	return true;
}

void ProjectFile::write()
{
	QFile outputFile(filePath);
	if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		cerr << tr("Couldn't save to file '%1' (Error code %2)").arg(filePath).arg(outputFile.error()).toStdString() << endl;
		return;
	}

	QTextStream outputStream(&outputFile);
	outputStream << domDocument.toString(2);
	outputFile.close();

	cout << tr("Saved data to '%1'.").arg(filePath).toStdString() << endl;

	modified = false;
}
