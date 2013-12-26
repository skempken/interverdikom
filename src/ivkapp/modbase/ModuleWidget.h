#ifndef IVKMODULEWIDGET_H_
#define IVKMODULEWIDGET_H_

#include <QWidget>

#include <map>
#include <string>
#include <list>

#include <QHash>
#include <QDomElement>
#include <QPoint>

#include <real.hpp>
#include <interval.hpp>
#include <rmatrix.hpp>
#include <imatrix.hpp>
#include <rvector.hpp>
#include <ivector.hpp>
#include <intvector.hpp>

#include "ClassFactory.hpp"
#include "getter_setter_macros.h"

#include "computation/AbstractComputationBase.hpp"

#include "data/SSMProcess.h"
#include "data/SSMPQueue.h"

using cxsc::real;
using cxsc::interval;
using cxsc::rmatrix;
using cxsc::imatrix;
using cxsc::rvector;
using cxsc::ivector;

using ivk::AbstractComputationBase;
using ivk::SSMProcess;
using ivk::SSMPQueue;

#define FACTORY_DECLARATIONS_FOR(CLASS_NAME) \
	public: static ModuleWidget* createInstance() \
	{ return new CLASS_NAME(); } \
	protected: static QString type; \
	public: QString getType() { return type; }

#define FACTORY_DEFINITIONS_FOR(CLASS_NAME) \
	QString CLASS_NAME::type = ClassFactory<ModuleWidget>::registerClass( \
				#CLASS_NAME , CLASS_NAME::createInstance);

class ProjectFile;
class ModuleManager;
class QTreeWidgetItem;
class QMenu;

using namespace std;

class ModuleWidget : public QWidget
{
	Q_OBJECT

public:
	/// Constructor
	/**
	 * \param parent The parent widget
	 */
	ModuleWidget();

	/// Destructor
	virtual ~ModuleWidget();

	virtual QString getType() = 0;

	GETTER_R(subWidgets, list<ModuleWidget*>, getSubWidgets)

	GETTER_SETTER(moduleManager, ModuleManager*, getModuleManager, setModuleManager)

	GETTER_SETTER(treeWidgetItem, QTreeWidgetItem*, getTreeWidgetItem, setTreeWidgetItem)

	GETTER_SETTER(parentModule, ModuleWidget*, getParentModule, setParentModule)

	GETTER_SETTER_R(dataElement, QDomElement, getDataElement, setDataElement)

	GETTER_SETTER_R(rootElement, QDomElement, getRootElement, setRootElement)

	/// Initialises new module.
	void initPostCreation()
	{
		// Initialisation of object in tree structure
		initModel();

		// Create new sub widgets
		createDefaultSubWidgets();
		createFileElements();

		// Create special actions, add default
		createActions();
		createDefaultActions();

		// finalise Creation if necessary
		postCreation();

		// refresh GUI
		updateGUI();
	}

	/// Initialises saved module from file.
	void initPostLoad()
	{
		// Initialization of object in tree structure
		initModel();

		// Create special actions, add default
		createActions();
		createDefaultActions();

		// Load Data from file
		loadModel();

		// Finalize Load if necessary
		postLoad();

		// Refresh GUI
		updateGUI();
	}

	void initPostClone()
	{
		initModel();
		loadModel();
		postLoad();
		updateGUI();
	}

	QString getName();

	void addAction(QAction *action)
	{
		actions.push_back(action);
	}

	void displayContextMenu(const QPoint & pos);

	void updateActionsMenu(QMenu * menu);

	void updateModuleNameInFile(QString name);

	void setEnabled(bool enabled);

protected:

	/// Initialises the module widget (loaded from file).
	/**
	 * Is called after module is loaded from file. The module is attached in the tree structure.
	 * To do here: All initialisations that are relevant for new modules only.
	 * Example: Default values depending on actual data.
	 */
	virtual void postCreation()
	{}

	/// Initialises the module widget (loaded from file).
	/**
	 * Is called after module is loaded from file. The module is attached in the tree structure.
	 * To do here: All initialisations that depend on file data.
	 * Optional.
	 */
	virtual void postLoad()
	{}

	/// Initialises the module widget.
	/**
	 * Is called after module is constructed. The module is attached in the tree structure.
	 * To do here: All initialisations that depend on parent nodes.
	 */
	virtual void initModel()
	{}

	/// Inserts a new widget below this module
	/**
	 * \param widget Module widget to be inserted
	 * \param name Label for the module
	 */
	virtual void addSubWidget(ModuleWidget *widget, const QString &name);

	/// The module manager which manages this module
	ModuleManager *moduleManager;

	/// List of module widgets below this module
	list<ModuleWidget*> subWidgets;

	/// Module widget above this module
	ModuleWidget *parentModule;

	/// Initialises sub-widgets always present for the actual module on creation.
	/**
	 * Default sub-modules for newly created modules must be created here.
	 */
	virtual void createDefaultSubWidgets()
	{}

	/// Creates the XML elements corresponding to module data on creation.
	/**
	 * To do: call saveXXX for all relevant data.
	 */
	virtual void createFileElements()
	{}

	/// Creates a list of module-specific actions possible on this node.
	/**
	 * Example: TraceDisplay.
	 * call addAction() for each possible action.
	 */
	virtual void createActions() = 0;

	void createDefaultActions();

	GETTER(loadSuccessful, bool, loadSuccess);

	QDomElement loadElement(QString id);

	void saveElement(QString id, QDomElement element);

	QString loadString(QString id);

	void saveString(QString id, QString value, AbstractComputationBase *computation = 0);

	int loadInt(QString id);

	void saveInt(QString id, int value, AbstractComputationBase *computation = 0);

	real loadReal(QString id);

	void saveReal(QString id, const real & value, AbstractComputationBase *computation = 0);

	interval loadInterval(QString id);

	void saveInterval(QString id, const interval & value);

	rmatrix loadRmatrix(QString id);

	void saveRmatrix(QString id, const rmatrix & value);

	imatrix loadImatrix(QString id);

	void saveImatrix(QString id, imatrix & value);

	rvector loadRvector(QString id);

	void saveRvector(QString id, const rvector & value);

	ivector loadIvector(QString id);

	void saveIvector(QString id, const ivector & value);

	SSMProcess loadSSMProcess(QString id);

	void saveSSMProcess(QString id, const SSMProcess & value);

	SSMPQueue loadSSMPQueue(QString id);

	void saveSSMPQueue(QString id, const SSMPQueue & value);

	intvector loadIntVector(QString id);

	void saveIntVector(QString id, const intvector & value, AbstractComputationBase *computation = 0);

	/// Loads module data from file.
	/**
	 * To do here: Call loadXXX for relevant module data.
	 * Counterpart to createFileElements()
	 */
	virtual void loadModel() = 0;

	/// Updates the GUI from model data.
	/**
	 * To do here: Update GUI elements with data from the model / module data.
	 */
	virtual void updateGUI() {};

private:
	/// The module's tree item in the module selection widget
	QTreeWidgetItem *treeWidgetItem;

	QDomElement dataElement;

	QDomElement rootElement;

	list<QAction*> actions;

	QAction *defaultActionSeparator;

	QAction *duplicateAction;

	QAction *deleteAction;

	QAction *setAsRootAction;

	bool loadSuccessful;

private slots:
	void duplicateClicked();

	void deleteClicked();

	void setAsRootClicked();

friend class ModuleManager;
};

#endif /*IVKMODULEWIDGET_H_*/
