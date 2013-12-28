#ifndef IVKQUEUEFILE_H_
#define IVKQUEUEFILE_H_

#include <QObject>

#include <QDomDocument>

#include "getter_setter_macros.h"

using namespace std;

class ModuleWidget;
class ModuleManager;

class ProjectFile : public QObject
{
public:
	/// Constructor
	ProjectFile();

	/// Destructor
	virtual ~ProjectFile();

	/// Write changes to file
	void write();
	
	/// Write changes to different file
	bool write(const QString & newFilePath);

	bool open(QString fileName);

	void createNewFile();
	
	bool loadModule(QDomElement &moduleElement, ModuleWidget *parent = 0, bool autoRename = false);

	GETTER(opened, bool, isOpened)
	
	GETTER(modified, bool, isModified)
	
	SETTER(moduleManager, ModuleManager*, setModuleManager)
	
	GETTER(domDocument, QDomDocument, getDocument)
	
	void wasModified()
	{
		modified = true;
	}
	
	bool hasPath()
	{
		return !filePath.isNull();
	}
	
	bool insertDataNodesForModule(ModuleWidget *module);
	
	QString getFileName();

private:
	QString filePath;

	bool opened;

	bool modified;

	QDomDocument domDocument;
	
	ModuleManager *moduleManager;
};

#endif /*IVKQUEUEFILE_H_*/
