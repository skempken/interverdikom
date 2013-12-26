/********************************************************************************
** Form generated from reading UI file 'ArrivalProcessDisplay.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARRIVALPROCESSDISPLAY_H
#define UI_ARRIVALPROCESSDISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "StochasticProcessWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ArrivalProcessDisplay
{
public:
    QVBoxLayout *vboxLayout;
    StochasticProcessWidget *widget;

    void setupUi(QWidget *ArrivalProcessDisplay)
    {
        if (ArrivalProcessDisplay->objectName().isEmpty())
            ArrivalProcessDisplay->setObjectName(QString::fromUtf8("ArrivalProcessDisplay"));
        ArrivalProcessDisplay->resize(778, 593);
        vboxLayout = new QVBoxLayout(ArrivalProcessDisplay);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        widget = new StochasticProcessWidget(ArrivalProcessDisplay);
        widget->setObjectName(QString::fromUtf8("widget"));

        vboxLayout->addWidget(widget);


        retranslateUi(ArrivalProcessDisplay);

        QMetaObject::connectSlotsByName(ArrivalProcessDisplay);
    } // setupUi

    void retranslateUi(QWidget *ArrivalProcessDisplay)
    {
        ArrivalProcessDisplay->setWindowTitle(QApplication::translate("ArrivalProcessDisplay", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ArrivalProcessDisplay: public Ui_ArrivalProcessDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARRIVALPROCESSDISPLAY_H
