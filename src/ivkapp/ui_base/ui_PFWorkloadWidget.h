/********************************************************************************
** Form generated from reading UI file 'PFWorkloadWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PFWORKLOADWIDGET_H
#define UI_PFWORKLOADWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PFWorkloadWidget
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QSpinBox *upToSpin;
    QPushButton *computeButton;

    void setupUi(QWidget *PFWorkloadWidget)
    {
        if (PFWorkloadWidget->objectName().isEmpty())
            PFWorkloadWidget->setObjectName(QString::fromUtf8("PFWorkloadWidget"));
        PFWorkloadWidget->resize(502, 340);
        vboxLayout = new QVBoxLayout(PFWorkloadWidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label = new QLabel(PFWorkloadWidget);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        upToSpin = new QSpinBox(PFWorkloadWidget);
        upToSpin->setObjectName(QString::fromUtf8("upToSpin"));
        upToSpin->setMinimum(1);
        upToSpin->setMaximum(99999);
        upToSpin->setValue(10);

        hboxLayout->addWidget(upToSpin);


        vboxLayout->addLayout(hboxLayout);

        computeButton = new QPushButton(PFWorkloadWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        vboxLayout->addWidget(computeButton);


        retranslateUi(PFWorkloadWidget);

        QMetaObject::connectSlotsByName(PFWorkloadWidget);
    } // setupUi

    void retranslateUi(QWidget *PFWorkloadWidget)
    {
        PFWorkloadWidget->setWindowTitle(QApplication::translate("PFWorkloadWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PFWorkloadWidget", "Calculate workload up to ", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("PFWorkloadWidget", "Start Computation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PFWorkloadWidget: public Ui_PFWorkloadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PFWORKLOADWIDGET_H
