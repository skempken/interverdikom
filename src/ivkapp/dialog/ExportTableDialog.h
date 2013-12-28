#ifndef EXPORTTABLEDIALOG_H_
#define EXPORTTABLEDIALOG_H_

#include <QDialog>
#include "ui_base/ui_ExportTableDialog.h"

/// Dialog with table export options
class ExportTableDialog : public QDialog, private Ui::ExportTableDialog
{
	Q_OBJECT
	
public:
	/// Default constructor
	/**
	 * \param parent Parent widget
	 */
	ExportTableDialog(QWidget *parent = 0);
	
	/// Destructor
	virtual ~ExportTableDialog();
	
private slots:
	/// Autoslot for click event of the "Browse..." button
	void on_browseButton_clicked(); 
	
	/// Autoslot for the click event of the "Export" button
	void on_exportButton_clicked();
	
	friend class IvkTableWidget;
	
signals:
	/// Signal notifying associated IvkTableWidget that "Export" button was clicked
	void exportInitialized();
};

#endif /*EXPORTTABLEDIALOG_H_*/
