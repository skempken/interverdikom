/********************************************************************************
** Form generated from reading UI file 'AutoSMPModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSMPMODELERWIDGET_H
#define UI_AUTOSMPMODELERWIDGET_H

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

class Ui_AutoSMPModelerWidget
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *spacerItem;
    QSpinBox *numdstepsEdit;
    QLabel *label_2;
    QSpinBox *numstatesEdit;
    QLabel *label_3;
    QSpinBox *confniveauEdit;
    QWidget *widget1;
    QGridLayout *gridLayout1;
    QSpacerItem *spacerItem1;
    QPushButton *computeButton;

    void setupUi(QWidget *AutoSMPModelerWidget)
    {
        if (AutoSMPModelerWidget->objectName().isEmpty())
            AutoSMPModelerWidget->setObjectName(QString::fromUtf8("AutoSMPModelerWidget"));
        AutoSMPModelerWidget->resize(658, 414);
        widget = new QWidget(AutoSMPModelerWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(110, 10, 301, 95));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(51, 27, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 1, 1, 1);

        numdstepsEdit = new QSpinBox(widget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));
        numdstepsEdit->setMinimum(1);

        gridLayout->addWidget(numdstepsEdit, 0, 2, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        numstatesEdit = new QSpinBox(widget);
        numstatesEdit->setObjectName(QString::fromUtf8("numstatesEdit"));
        numstatesEdit->setMinimum(1);

        gridLayout->addWidget(numstatesEdit, 1, 2, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        confniveauEdit = new QSpinBox(widget);
        confniveauEdit->setObjectName(QString::fromUtf8("confniveauEdit"));
        confniveauEdit->setMinimum(1);

        gridLayout->addWidget(confniveauEdit, 2, 2, 1, 1);

        widget1 = new QWidget(AutoSMPModelerWidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(110, 120, 301, 76));
        gridLayout1 = new QGridLayout(widget1);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        spacerItem1 = new QSpacerItem(261, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacerItem1, 0, 0, 1, 1);

        computeButton = new QPushButton(widget1);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout1->addWidget(computeButton, 1, 0, 1, 1);


        retranslateUi(AutoSMPModelerWidget);

        QMetaObject::connectSlotsByName(AutoSMPModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *AutoSMPModelerWidget)
    {
        AutoSMPModelerWidget->setWindowTitle(QApplication::translate("AutoSMPModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AutoSMPModelerWidget", "Number of discretizationsteps", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AutoSMPModelerWidget", "Number of states", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AutoSMPModelerWidget", "Confidence niveau", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("AutoSMPModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AutoSMPModelerWidget: public Ui_AutoSMPModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSMPMODELERWIDGET_H
