/********************************************************************************
** Form generated from reading UI file 'SSMPQueueDisplayWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SSMPQUEUEDISPLAYWIDGET_H
#define UI_SSMPQUEUEDISPLAYWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "widget/StochasticProcessWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SSMPQueueDisplayWidget
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QVBoxLayout *vboxLayout1;
    StochasticProcessWidget *resultWidget;
    QWidget *tab;
    QVBoxLayout *vboxLayout2;
    StochasticProcessWidget *arrivalWidget;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout3;
    StochasticProcessWidget *serviceWidget;

    void setupUi(QWidget *SSMPQueueDisplayWidget)
    {
        if (SSMPQueueDisplayWidget->objectName().isEmpty())
            SSMPQueueDisplayWidget->setObjectName(QString::fromUtf8("SSMPQueueDisplayWidget"));
        SSMPQueueDisplayWidget->resize(820, 597);
        vboxLayout = new QVBoxLayout(SSMPQueueDisplayWidget);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        tabWidget = new QTabWidget(SSMPQueueDisplayWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        vboxLayout1 = new QVBoxLayout(tab_3);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        resultWidget = new StochasticProcessWidget(tab_3);
        resultWidget->setObjectName(QString::fromUtf8("resultWidget"));

        vboxLayout1->addWidget(resultWidget);

        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        vboxLayout2 = new QVBoxLayout(tab);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        arrivalWidget = new StochasticProcessWidget(tab);
        arrivalWidget->setObjectName(QString::fromUtf8("arrivalWidget"));

        vboxLayout2->addWidget(arrivalWidget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        vboxLayout3 = new QVBoxLayout(tab_2);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        serviceWidget = new StochasticProcessWidget(tab_2);
        serviceWidget->setObjectName(QString::fromUtf8("serviceWidget"));

        vboxLayout3->addWidget(serviceWidget);

        tabWidget->addTab(tab_2, QString());

        vboxLayout->addWidget(tabWidget);


        retranslateUi(SSMPQueueDisplayWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SSMPQueueDisplayWidget);
    } // setupUi

    void retranslateUi(QWidget *SSMPQueueDisplayWidget)
    {
        SSMPQueueDisplayWidget->setWindowTitle(QApplication::translate("SSMPQueueDisplayWidget", "Form", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("SSMPQueueDisplayWidget", "Queue Model", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SSMPQueueDisplayWidget", "Arrival Process", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SSMPQueueDisplayWidget", "Service Process", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SSMPQueueDisplayWidget: public Ui_SSMPQueueDisplayWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SSMPQUEUEDISPLAYWIDGET_H
