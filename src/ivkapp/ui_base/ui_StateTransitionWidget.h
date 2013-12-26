/********************************************************************************
** Form generated from reading UI file 'StateTransitionWidget.ui'
**
** Created: Thu Dec 26 15:32:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATETRANSITIONWIDGET_H
#define UI_STATETRANSITIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include "IvkTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_StateTransitionWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout1;
    IvkTableWidget *tableSteady;
    QGroupBox *groupBox;
    QGridLayout *gridLayout2;
    IvkTableWidget *tableTransition;

    void setupUi(QWidget *StateTransitionWidget)
    {
        if (StateTransitionWidget->objectName().isEmpty())
            StateTransitionWidget->setObjectName(QString::fromUtf8("StateTransitionWidget"));
        StateTransitionWidget->resize(413, 456);
        gridLayout = new QGridLayout(StateTransitionWidget);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_2 = new QGroupBox(StateTransitionWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout1 = new QGridLayout(groupBox_2);
#ifndef Q_OS_MAC
        gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        tableSteady = new IvkTableWidget(groupBox_2);
        tableSteady->setObjectName(QString::fromUtf8("tableSteady"));

        gridLayout1->addWidget(tableSteady, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(StateTransitionWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(5);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout2 = new QGridLayout(groupBox);
#ifndef Q_OS_MAC
        gridLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout2->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        tableTransition = new IvkTableWidget(groupBox);
        tableTransition->setObjectName(QString::fromUtf8("tableTransition"));
        QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(13), static_cast<QSizePolicy::Policy>(13));
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableTransition->sizePolicy().hasHeightForWidth());
        tableTransition->setSizePolicy(sizePolicy2);

        gridLayout2->addWidget(tableTransition, 0, 0, 1, 2);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(StateTransitionWidget);

        QMetaObject::connectSlotsByName(StateTransitionWidget);
    } // setupUi

    void retranslateUi(QWidget *StateTransitionWidget)
    {
        StateTransitionWidget->setWindowTitle(QApplication::translate("StateTransitionWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("StateTransitionWidget", "Steady state probabilities", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("StateTransitionWidget", "Transition Matrix", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StateTransitionWidget: public Ui_StateTransitionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATETRANSITIONWIDGET_H
