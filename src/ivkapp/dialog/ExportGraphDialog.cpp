#include "ExportGraphDialog.h"

#include <cmath>

#include <QFileDialog>
#include <QIntValidator>

#include "MainWindow.h"

ExportGraphDialog *ExportGraphDialog::instance = 0;

ExportGraphDialog::ExportGraphDialog(QWidget *parent) : QDialog(parent)
{	
	setupUi(this);
	
	intValidator = new QIntValidator(this);
	widthEdit->setValidator(intValidator);
	heightEdit->setValidator(intValidator);
	
	connect(cancelButton,SIGNAL(clicked()),this,SLOT(accept()));
}

ExportGraphDialog::~ExportGraphDialog()
{
	
}

ExportGraphDialog *ExportGraphDialog::getInstance(QWidget *parent)
{
	if (!instance)
		instance = new ExportGraphDialog(parent);
		
	return instance;
}

void ExportGraphDialog::on_exportButton_clicked()
{
	emit exportInitialized();
}

void ExportGraphDialog::setGraphDimensions(int width, int height)
{
	widthToHeightRatio = (static_cast<double>(width) / static_cast<double>(height));
	widthEdit->setText(QString("%1").arg(width));
	heightEdit->setText(QString("%1").arg(height));
}

void ExportGraphDialog::on_browseButton_clicked()
{
	QFileDialog fileDialog(this);
	fileDialog.setWindowTitle(tr("Specify output file"));
	
	QStringList filterList;
	filterList << "PNG Image (*.png)"
		<< "JPEG Image (*.jpg *.jpeg)"
		<< "Windows Bitmap (*.bmp)"
		<< "Portable Pixmap (*.ppm)"
		<< "X11 Bitmap (*.xbm *.xpm)";
	fileDialog.setFilters(filterList);
	
	fileDialog.setDirectory(QDir());
	fileDialog.setFileMode(QFileDialog::AnyFile);
	
	if (!fileDialog.exec())
		return;
		
	QString fileName = fileDialog.selectedFiles().at(0);
	if (!fileName.size())
		return;
	
	QString selectedFilterExtension = getExtensionOfFilter(fileDialog.selectedFilter());
	QString selectedPathExtension = getExtensionOfPath(fileName);
	if (selectedFilterExtension != selectedPathExtension)
		fileName += selectedFilterExtension;
		 
	pathEdit->setText(fileName);
}

QString ExportGraphDialog::getExtensionOfFilter(QString filterString) const
{
	QString extensionsString = filterString.mid(filterString.lastIndexOf(QChar('(')) + 1,filterString.size() - filterString.lastIndexOf(QChar(')')) - 2);
	int asteriskPosition = extensionsString.indexOf(QChar('*'));
	return extensionsString.mid(asteriskPosition+1,4);
}

QString ExportGraphDialog::getExtensionOfPath(QString pathString) const
{
	QString choppedString = pathString.right(4);
	if (choppedString[0] != QChar('.'))
		return QString();
	else
		return choppedString;
}

void ExportGraphDialog::on_widthEdit_textEdited()
{
	if (!ratioCheck->isChecked())
		return;
		
	int newWidth = widthEdit->text().toInt();
	if (newWidth)
	{
		int newHeight = static_cast<int>(ceil(static_cast<double>(newWidth) / widthToHeightRatio));
		heightEdit->setText(QString("%1").arg(newHeight));
	}
}

void ExportGraphDialog::on_heightEdit_textEdited()
{
	if (!ratioCheck->isChecked())
		return;
		
	int newHeight = heightEdit->text().toInt();
	if (newHeight)
	{
		int newWidth = static_cast<int>(ceil(static_cast<double>(newHeight) * widthToHeightRatio));
		widthEdit->setText(QString("%1").arg(newWidth));
	}	
}
