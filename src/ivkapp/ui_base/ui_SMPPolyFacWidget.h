/********************************************************************************
** Form generated from reading UI file 'SMPPolyFacWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMPPOLYFACWIDGET_H
#define UI_SMPPOLYFACWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SMPPolyFacWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *rootsCombo;
    QComboBox *determinantCombo;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QPushButton *computeButton;
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(QWidget *SMPPolyFacWidget)
    {
        if (SMPPolyFacWidget->objectName().isEmpty())
            SMPPolyFacWidget->setObjectName(QString::fromUtf8("SMPPolyFacWidget"));
        SMPPolyFacWidget->resize(662, 592);
        verticalLayout = new QVBoxLayout(SMPPolyFacWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(SMPPolyFacWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(SMPPolyFacWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        rootsCombo = new QComboBox(SMPPolyFacWidget);
        rootsCombo->setObjectName(QString::fromUtf8("rootsCombo"));

        gridLayout_2->addWidget(rootsCombo, 0, 1, 1, 1);

        determinantCombo = new QComboBox(SMPPolyFacWidget);
        determinantCombo->setObjectName(QString::fromUtf8("determinantCombo"));

        gridLayout_2->addWidget(determinantCombo, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer = new QSpacerItem(20, 444, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        computeButton = new QPushButton(SMPPolyFacWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 0, 1, 1, 1);

        progressBar = new QProgressBar(SMPPolyFacWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(1);
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 0, 0, 1, 1);

        label = new QLabel(SMPPolyFacWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(SMPPolyFacWidget);

        QMetaObject::connectSlotsByName(SMPPolyFacWidget);
    } // setupUi

    void retranslateUi(QWidget *SMPPolyFacWidget)
    {
        SMPPolyFacWidget->setWindowTitle(QApplication::translate("SMPPolyFacWidget", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SMPPolyFacWidget", "Roots algorithm:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SMPPolyFacWidget", "Determinant algorithm:", 0, QApplication::UnicodeUTF8));
        rootsCombo->clear();
        rootsCombo->insertItems(0, QStringList()
         << QApplication::translate("SMPPolyFacWidget", "M\303\274ller", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SMPPolyFacWidget", "Bauhuber", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SMPPolyFacWidget", "LAPACK", 0, QApplication::UnicodeUTF8)
        );
        determinantCombo->clear();
        determinantCombo->insertItems(0, QStringList()
         << QApplication::translate("SMPPolyFacWidget", "Laplace", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SMPPolyFacWidget", "Faddeev", 0, QApplication::UnicodeUTF8)
        );
        computeButton->setText(QApplication::translate("SMPPolyFacWidget", "Perform coefficient precomputation", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SMPPolyFacWidget: public Ui_SMPPolyFacWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMPPOLYFACWIDGET_H
