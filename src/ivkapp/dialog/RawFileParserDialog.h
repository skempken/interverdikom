#ifndef RAWFILEPARSERDIALOG_H_
#define RAWFILEPARSERDIALOG_H_

#include <QDialog>
#include "ui_base/ui_RawFileParserDialog.h"

/// Dialog for trace file generation options
class RawFileParserDialog : public QDialog, private Ui::RawFileParserDialog
{
	Q_OBJECT
	
public:
	/// Default constructor
	/**
	 * \param parent Parent widget
	 */
	RawFileParserDialog(QWidget *parent = 0);
	
	/// Destructor
	virtual ~RawFileParserDialog();
	
private slots:
	/// Autoslot for click event of "Browse..." button for input file path
	void on_inputFileBrowseButton_clicked();
	
	/// Autoslot for click event of "Browse..." button for video output file path
	void on_outputVideoBrowseButton_clicked();
	
	/// Autoslot for click event of "Browse..." button for audio output file path
	void on_outputAudioBrowseButton_clicked();
	
	/// Autoslot for click event of the "Parse" button
	void on_parseButton_clicked();
};

#endif /*RAWFILEPARSERDIALOG_H_*/
