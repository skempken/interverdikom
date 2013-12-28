#ifndef EXPORTGRAPHDIALOG_H_
#define EXPORTGRAPHDIALOG_H_

#include <QDialog>
#include "ui_base/ui_ExportGraphDialog.h"

/// Dialog with graph export options
class ExportGraphDialog : public QDialog, private Ui::ExportGraphDialog
{
	Q_OBJECT
	
public:
	/// Destructor
	virtual ~ExportGraphDialog();
	
	/// Singleton instance access method
	static ExportGraphDialog *getInstance(QWidget *parent = 0);
	
	/// Sets the original graph width and height.
	/**
	 * This should be called as soon as an action which displays
	 * the dialog is displayed. It initializes the dialog with
	 * the width and height of the corresponding graph widget.
	 * 
	 *  \param width Width in pixels
	 *  \param height Height in pixels
	 */
	void setGraphDimensions(int width, int height);
	
private slots:
	/// Autoslot for click event on "Export" button
	void on_exportButton_clicked();
	
	/// Autoslot for click event on "Browse..." button
	void on_browseButton_clicked();
	
	/// Autoslot for update event of width field
	void on_widthEdit_textEdited();
	
	/// Autoslot for update event of height field
	void on_heightEdit_textEdited();
	
private:
	/// Private constructor for singleton pattern
	/**
	 *  \param parent The parent widget
	 */
	ExportGraphDialog(QWidget *parent = 0);
	
	/// Instance pointer for singleton pattern
	static ExportGraphDialog *instance;
	
	/// Validator for width and height fields
	class QIntValidator *intValidator;
	
	/// Ratio of original graph width to height
	double widthToHeightRatio;
	
	/// Helper function to extract file extension from filter string
	/**
	 *  \param filterString The QFileDialog filter string
	 */
	QString getExtensionOfFilter(QString filterString) const;
	
	/// Helper function to extract file extension from fully qualified path
	/**
	 *  \param pathString The full path string
	 */
	QString getExtensionOfPath(QString pathString) const;
	
signals:
	/// Signal to notify the associated IvkPlot that the export button was pressed
	void exportInitialized();
	
	friend class IvkPlot;
};

#endif /*EXPORTGRAPHDIALOG_H_*/
