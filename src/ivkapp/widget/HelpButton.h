#ifndef IVKHELPBUTTON_H_
#define IVKHELPBUTTON_H_

#include <QPushButton>

class HelpDialog;

class HelpButton : public QPushButton
{
	Q_OBJECT
	
public:
	HelpButton(QWidget *parent = 0);
	virtual ~HelpButton();
	
private slots:
	void showHelpDialog();
	
private:
	HelpDialog *dialog;
};

#endif /*IVKHELPBUTTON_H_*/
