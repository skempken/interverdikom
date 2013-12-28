#include "ImportModelDialog.h"
#include <QFileDialog>
#include <string>

#include <rmatrix.hpp>

#include "MainWindow.h"
#include "ModuleManager.h"
#include "StringUtil.h"
#include "SSMPQueueDisplayWidget.h"

using std::string;

ImportModelDialog::ImportModelDialog(QWidget* parent)
: QDialog(parent), Ui::ImportModelDialog()
{
	setupUi(this);
}

ImportModelDialog::~ImportModelDialog()
{
}

void ImportModelDialog::exec()
{
	on_browseButton_clicked();
	if (pathEdit->text() != "")
	{
		QDialog::exec();
	}
}

void ImportModelDialog::on_browseButton_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(this,
			tr("Select legacy model file"), QString(),
			tr("Legacy model files (*)"));

	if (!filePath.isNull())
	{
		pathEdit->setText(filePath);
	}
}

void ImportModelDialog::accept()
{
	// Get file name
	string path = pathEdit->text().toStdString();
	QString fileName = StringUtil::extractFileNameFromPath(pathEdit->text());

	// Open selected file
	ifstream stream(path.c_str());

	// Import arrival process
	SSMProcess* arrival = createSSMProcess(stream);

	// Import service process
	SSMProcess* service = createGIProcess(stream);

	// Close file
	stream.close();

	// Create SSMPQueue object
	bool isTimeSlotted = radioTimeslotted->isChecked();
	SSMPQueue* queue = 0;
	if(isTimeSlotted)
	{
		queue = SSMPQueue::constructTimeSlottedQueue(arrival, service);
	}
	else
	{
		queue = SSMPQueue::constructInterarrivalQueue(arrival, service);
	}

	// TODO: Add Widget
	SSMPQueueDisplayWidget* widget = new SSMPQueueDisplayWidget(queue);
	ModuleManager * moduleManager = MainWindow::getLastInstance()->getModuleManager();
	moduleManager->addModule(widget, tr("Model: %1").arg(fileName));
	this->close();
}

SSMProcess* ImportModelDialog::createSSMProcess(ifstream& stream)
{
	// read # of states
	int nStates; stream >> nStates;

	// read transition matrix
	rmatrix trans(1, nStates, 1, nStates);
	for(int i = Lb(trans,1); i<=Ub(trans,1); ++i)
	{
		rvector dist = readDistribution(stream, nStates);
		trans[i] = dist;
	}

	// Read distribution length
	int distLength; stream >> distLength;

	// Read distribution matrix, in file format always 0-based
	rmatrix dists(1, nStates, 0, distLength);
	for(int i = Lb(dists,1); i<=Ub(dists,1); ++i)
	{
		rvector dist = readDistribution(stream, distLength+1);
		SetLb(dist, 0);
		dists[i] = dist;
	}

	// Create SSMProcess object
	SSMProcess* ret = new SSMProcess(trans, dists);
	return ret;
}

GIProcess* ImportModelDialog::createGIProcess(ifstream& stream)
{
	// Read distribution length
	int distLength; stream >> distLength;

	// Read distribution matrix, in file format always 0-based
	rvector dist = readDistribution(stream, distLength+1);
	SetLb(dist, 0);

	// Create SSMProcess object
	GIProcess* ret = new GIProcess(dist);
	return ret;
}

rvector ImportModelDialog::readDistribution(ifstream& stream, int length)
{
	rvector data(1,length);
	for(int i = Lb(data); i<=Ub(data); ++i )
	{
		double d;
		stream >> d;
		data[i] = d;
	}
	return data;
}
