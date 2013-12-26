/********************************************************************************
** Form generated from reading UI file 'SMPVerifyEigWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMPVERIFYEIGWIDGET_H
#define UI_SMPVERIFYEIGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SMPVerifyEigWidget
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QLabel *label;
    QPushButton *computeButton;

    void setupUi(QWidget *SMPVerifyEigWidget)
    {
        if (SMPVerifyEigWidget->objectName().isEmpty())
            SMPVerifyEigWidget->setObjectName(QString::fromUtf8("SMPVerifyEigWidget"));
        SMPVerifyEigWidget->resize(608, 593);
        verticalLayout = new QVBoxLayout(SMPVerifyEigWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 240, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(SMPVerifyEigWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        verticalSpacer_2 = new QSpacerItem(20, 237, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        progressBar = new QProgressBar(SMPVerifyEigWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(1);
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 0, 0, 1, 1);

        label = new QLabel(SMPVerifyEigWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        computeButton = new QPushButton(SMPVerifyEigWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(SMPVerifyEigWidget);

        QMetaObject::connectSlotsByName(SMPVerifyEigWidget);
    } // setupUi

    void retranslateUi(QWidget *SMPVerifyEigWidget)
    {
        SMPVerifyEigWidget->setWindowTitle(QApplication::translate("SMPVerifyEigWidget", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SMPVerifyEigWidget", "(No parameters for this computation)", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        computeButton->setText(QApplication::translate("SMPVerifyEigWidget", "Perform coefficient precomputation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SMPVerifyEigWidget: public Ui_SMPVerifyEigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMPVERIFYEIGWIDGET_H
