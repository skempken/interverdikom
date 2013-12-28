#ifndef IVKNAVIGATIONPATH_H_
#define IVKNAVIGATIONPATH_H_

#include <QWidget>

#include <vector>
#include <utility>
#include <QString>

using namespace std;

class QLabel;

/// Widget displaying name of currently selected module in hierarchy
/**
 * This widget displays the position of the currently selected module
 * in the module hierarchy. It also allows the user to click on any
 * entry within the hierarchy to navigate to that specific module node.
 */
class NavigationPath : public QWidget
{
	Q_OBJECT
	
	/// Pair containing information about one hierarchy element
	typedef pair<class QLabel*, class QTreeWidgetItem*> NavPair;
	
public:
	/// Constructor
	/**
	 * \param parent The parent widget
	 */
	NavigationPath(QWidget *parent = 0);
	
	/// Destructor
	virtual ~NavigationPath();
	
	/// Sets the tree widget this path is associated with
	/**
	 * \param theWidget The tree widget
	 */
	void setTreeWidget(class QTreeWidget *theWidget);
	
public slots:
	/// Slot to be called when an item in the associated widget is selected
	/**
	 * This clears all labels and recreates them to reflect the
	 * hierarchy of the the newly selected widget.
	 * 
	 * \param item The item that was selected
	 */
	void moduleSelected(class QTreeWidgetItem *item);
	
signals:
	/// Signal emitted when label of a module is clicked
	/**
	 * This signal is emitted in the navigationLabelActivated() slot.
	 * It should be connected to the itemClicked() signal of the
	 * associated tree widget to correctly update all associated widgets.
	 * 
	 * \param item The item that was clicked
	 * \param columnID Index of the column in which the click took place
	 */
	void itemClicked(QTreeWidgetItem *item, int columnID);
	
private slots:
	/// Slot called when the user clicks on a module label
	/**
	 * The link text used for this slot is internally generated and
	 * a string representation of the corresponding navigation element's
	 * index within the navigation vector.
	 *  
	 * \param linkText Internally generated link text
	 */
	void navigationLabelActivated(QString linkText);
	
private:
	/// Vector containing abstract information about displayed hierarchy
	vector<NavPair> navigation;
	
	/// The tree widget that this navigation path is attached to
	class QTreeWidget *treeWidget;
	
	/// Horizontal layout organizing individual module labels 
	class QHBoxLayout *layout;
	
	/// Remove and delete all labels from the layout
	void clearLabels();
	
	/// Add a label for a specified tree widget item
	/**
	 * \param item Tree widget item to associate this label with
	 */
	void addNavigationLabel(QTreeWidgetItem *item);
	
	void addNavigationLabel(QString label);
	
	/// Add a seperator between the current and next label
	void addSeparator();
};

#endif /*IVKNAVIGATIONPATH_H_*/
