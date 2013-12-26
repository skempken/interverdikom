/*
 * ComparisonDialog.cpp
 *
 *  Created on: 18.12.2008
 *      Author: ivkdev
 */

#include "ComparisonDialog.h"

ComparisonDialog::ComparisonDialog(QWidget *parent) : QDialog(parent) {
	setupUi(this);

}

ComparisonDialog::~ComparisonDialog() {
}

void ComparisonDialog::addWidgets(QWidget * widget1, QWidget * widget2) {
	stackedWidget1->addWidget(widget1);
	stackedWidget1->setCurrentIndex(stackedWidget1->indexOf(widget1));
	stackedWidget2->addWidget(widget2);
	stackedWidget2->setCurrentIndex(stackedWidget2->indexOf(widget2));
}
