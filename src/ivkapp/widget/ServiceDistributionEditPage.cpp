#include "ServiceDistributionEditPage.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QDoubleSpinBox>

#include "MainWindow.h"
#include "ProjectFile.h"

ServiceDistributionEditPage::ServiceDistributionEditPage(QWidget *parent) : QWidget(parent)
{
	informationLabel = new QLabel(tr("You may modify the service process by entering a new average load capacity below.\nThis will write the new value to the model file and invalidate previous computation results."), this);
	informationLabel->setWordWrap(true);
	
	averageEdit = new QLineEdit("10.00", this);
	averageEdit->setEnabled(false);
	
	plusLabel = new QLabel(tr("+"), this);
	
	deviationEdit = new QLineEdit("2.0", this);
	deviationEdit->setEnabled(false);
	
	timesLabel = new QLabel(tr("x"), this);
	
	factorSpin = new QDoubleSpinBox(this);
	
	equalsLabel = new QLabel(tr("="), this);
	
	resultEdit = new QLineEdit("10.00", this);
	
	editLineLayout = new QHBoxLayout();
	editLineLayout->addWidget(averageEdit);
	editLineLayout->addWidget(plusLabel);
	editLineLayout->addWidget(factorSpin);
	editLineLayout->addWidget(timesLabel);
	editLineLayout->addWidget(deviationEdit);
	editLineLayout->addWidget(equalsLabel);
	editLineLayout->addWidget(resultEdit);
	
	saveButton = new QPushButton(tr("Save new capacity"), this);
	
	layout = new QVBoxLayout(this);
	layout->addWidget(informationLabel);
	layout->addLayout(editLineLayout);
	layout->addWidget(saveButton);
	layout->addStretch(1);
	setLayout(layout);
	
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
	connect(factorSpin, SIGNAL(valueChanged(double)), this, SLOT(updateFactorValue(double)));
	connect(resultEdit, SIGNAL(textChanged(QString)), this, SLOT(updateResultValue(QString)));
}

ServiceDistributionEditPage::~ServiceDistributionEditPage() {}

void ServiceDistributionEditPage::updateFactorValue(double newValue)
{
	double average = averageEdit->text().toDouble();
	double deviation = deviationEdit->text().toDouble();
	
	resultEdit->setText(QString("%1").arg(average + newValue * deviation));
}

void ServiceDistributionEditPage::updateResultValue(QString newValue)
{
	double average = averageEdit->text().toDouble();
	double deviation = deviationEdit->text().toDouble();
	double result = newValue.toDouble();
	
	factorSpin->setValue((result - average) / deviation);
}

void ServiceDistributionEditPage::updateValuesFromFile(ivk::QueueFile *file)
{
	averageEdit->setText("10.00"); // TODO calculate average value
	deviationEdit->setText("2.0"); // TODO calculate deviation
}

void ServiceDistributionEditPage::saveToFile()
{
	// TODO REIMPLEMENT
	/*
	QString fileName = QString::fromStdString(MainWindow::getLastInstance()->getFile().getFileName());
	
	ProjectFile::addServiceProcessToFile(fileName, resultEdit->text().toDouble());
	
	if (MainWindow::getLastInstance()->getFile().open(MainWindow::getLastInstance()->getFile().getFileName()))
		MainWindow::getLastInstance()->performOpenSuccessUpdate(fileName);
	*/
}
