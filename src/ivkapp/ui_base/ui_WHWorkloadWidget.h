/********************************************************************************
** Form generated from reading UI file 'WHWorkloadWidget.ui'
**
** Created: Thu Dec 26 15:32:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHWORKLOADWIDGET_H
#define UI_WHWORKLOADWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WHWorkloadWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *spacerItem;
    QSpinBox *upTo;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;
    QPushButton *computeButton;

    void setupUi(QWidget *WHWorkloadWidget)
    {
        if (WHWorkloadWidget->objectName().isEmpty())
            WHWorkloadWidget->setObjectName(QString::fromUtf8("WHWorkloadWidget"));
        WHWorkloadWidget->resize(400, 300);
        gridLayout = new QGridLayout(WHWorkloadWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(WHWorkloadWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 1, 1, 1);

        upTo = new QSpinBox(WHWorkloadWidget);
        upTo->setObjectName(QString::fromUtf8("upTo"));

        gridLayout->addWidget(upTo, 0, 2, 1, 1);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem1, 1, 2, 1, 1);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem2, 2, 0, 1, 2);

        computeButton = new QPushButton(WHWorkloadWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 2, 2, 1, 1);


        retranslateUi(WHWorkloadWidget);

        QMetaObject::connectSlotsByName(WHWorkloadWidget);
    } // setupUi

    void retranslateUi(QWidget *WHWorkloadWidget)
    {
        WHWorkloadWidget->setWindowTitle(QApplication::translate("WHWorkloadWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WHWorkloadWidget", "Compute workloads up to:", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("WHWorkloadWidget", "Compute", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WHWorkloadWidget: public Ui_WHWorkloadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHWORKLOADWIDGET_H
