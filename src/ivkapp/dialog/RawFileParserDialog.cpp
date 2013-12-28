#include "RawFileParserDialog.h"

#include <iostream>
#include <fstream>

#include <QFileDialog>

#include "ContainerFormatParser.h"

using namespace std;

RawFileParserDialog::RawFileParserDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
	parseProgressBar->setVisible(false);
}

RawFileParserDialog::~RawFileParserDialog() {}

void RawFileParserDialog::on_inputFileBrowseButton_clicked()
{
	QString fname = QFileDialog::getOpenFileName(this, tr("Select video file"), QString(), tr("Movies (*.3gp *.avi *.mov *.wmv *.mpg)"));
	if (fname.size())
		inputFileEdit->setText(fname);
}

void RawFileParserDialog::on_outputVideoBrowseButton_clicked()
{
	QString fname = QFileDialog::getSaveFileName(this, tr("Specify video stream output file"));
	if (fname.size())
		outputVideoEdit->setText(fname);
}

void RawFileParserDialog::on_outputAudioBrowseButton_clicked()
{
	QString fname = QFileDialog::getSaveFileName(this, tr("Specify audio stream output file"));
	if (fname.size())
		outputAudioEdit->setText(fname);
}

void RawFileParserDialog::on_parseButton_clicked()
{
	cout << "Invoking raw file parser... ";
	ifstream input_file((inputFileEdit->text()).toAscii());
	if (!input_file.good())
	{
		cerr << "Bad file :" << (inputFileEdit->text()).toStdString() << "." << endl;
		return;
	}
	
	// TODO FIXME
	ContainerFormatParser *parser = ContainerFormatParser::getParserForFile(input_file);
	if (parser == 0)
	{
		cerr << "Unsupported file format." << endl;
		return;
	}
	
	parser->setDumpTimeIndex(timeIndexCheck->isChecked());
	
	cout << "parsing... ";
	parser->parseFile(input_file);
	cout << "writing output... "; 
	
	ofstream video_output_file, audio_output_file;
	string video_filename = outputVideoEdit->text().toStdString();
	string audio_filename = outputAudioEdit->text().toStdString();
	
	if (outputVideoCheck->checkState() == Qt::Checked)
	{
		video_output_file.open(video_filename.c_str());
		if (!video_output_file.good())
		{
			cerr << "Invalid video output file " << video_filename << endl;
			return;
		}
	}
	else
	{
		video_output_file.open("/dev/null");
	}
		
	if (outputAudioCheck->checkState() == Qt::Checked)
	{
		audio_output_file.open(audio_filename.c_str());
		if (!audio_output_file.good())
		{
			cerr << "Invalid audio output file " << audio_filename << endl;
			return;
		}
	}
	else
	{
		audio_output_file.open("/dev/null");
	}
	

	parser->writeOutputFiles(video_output_file, audio_output_file);
	
	cout << "trace generation finished." << endl;
	close();
}
