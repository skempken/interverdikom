/*
 * ComparisonDialog.h
 *
 *  Created on: 18.12.2008
 *      Author: ivkdev
 */

#ifndef COMPARISONDIALOG_H_
#define COMPARISONDIALOG_H_

#include <QDialog>
#include "ui_base/ui_ComparisonDialog.h"

class ComparisonDialog : public QDialog, private Ui::ComparisonDialog {
public:
	ComparisonDialog(QWidget *parent = 0);

	virtual ~ComparisonDialog();

	void addWidgets(QWidget * widget1, QWidget * widget2);
};

#endif /* COMPARISONDIALOG_H_ */
