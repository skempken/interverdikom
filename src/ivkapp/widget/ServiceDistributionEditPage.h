#ifndef SERVICEDISTRIBUTIONEDITPAGE_H_
#define SERVICEDISTRIBUTIONEDITPAGE_H_

#include <QWidget>

namespace ivk { class QueueFile; }

class QLabel;
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class QDoubleValidator;
class QHBoxLayout;
class QDoubleSpinBox;

class ServiceDistributionEditPage : public QWidget
{
	Q_OBJECT
	
public:
	ServiceDistributionEditPage(QWidget *parent = 0);
	
	virtual ~ServiceDistributionEditPage();
	
	void updateValuesFromFile(ivk::QueueFile *file);
	
	
protected:
	void loadModel();
	
private slots:
	void updateFactorValue(double newValue);
	
	void updateResultValue(QString newValue);
	
private:
	QLabel *informationLabel;
	
	QLineEdit *averageEdit;
	
	QLabel *plusLabel;
	
	QDoubleSpinBox *factorSpin;
	
	QLabel *timesLabel;
	
	QLineEdit *deviationEdit;
	
	QLabel *equalsLabel;
	
	QLineEdit *resultEdit;
	
	QPushButton *saveButton;
	
	QVBoxLayout *layout;
	
	QHBoxLayout *editLineLayout;
	
	QDoubleValidator *valueValidator;
	
private slots:
	void saveToFile();
};

#endif /*SERVICEDISTRIBUTIONEDITPAGE_H_*/
