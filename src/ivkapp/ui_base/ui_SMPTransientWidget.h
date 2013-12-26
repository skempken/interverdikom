/********************************************************************************
** Form generated from reading UI file 'SMPTransientWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMPTRANSIENTWIDGET_H
#define UI_SMPTRANSIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SMPTransientWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSlider *sliderIterations;
    QSpacerItem *spacerItem;
    QSpinBox *iterations;
    QLabel *label_3;
    QDoubleSpinBox *threshold;
    QSpacerItem *spacerItem1;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;

    void setupUi(QWidget *SMPTransientWidget)
    {
        if (SMPTransientWidget->objectName().isEmpty())
            SMPTransientWidget->setObjectName(QString::fromUtf8("SMPTransientWidget"));
        SMPTransientWidget->resize(472, 354);
        gridLayout = new QGridLayout(SMPTransientWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(SMPTransientWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sliderIterations = new QSlider(SMPTransientWidget);
        sliderIterations->setObjectName(QString::fromUtf8("sliderIterations"));
        sliderIterations->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderIterations, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(31, 27, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 2, 1, 1);

        iterations = new QSpinBox(SMPTransientWidget);
        iterations->setObjectName(QString::fromUtf8("iterations"));
        iterations->setMinimum(1);
        iterations->setMaximum(9999);

        gridLayout->addWidget(iterations, 0, 3, 1, 1);

        label_3 = new QLabel(SMPTransientWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        threshold = new QDoubleSpinBox(SMPTransientWidget);
        threshold->setObjectName(QString::fromUtf8("threshold"));
        threshold->setDecimals(3);
        threshold->setMinimum(0.001);
        threshold->setMaximum(1);
        threshold->setSingleStep(0.001);

        gridLayout->addWidget(threshold, 1, 3, 1, 1);

        spacerItem1 = new QSpacerItem(271, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem1, 2, 0, 1, 4);

        progressBar = new QProgressBar(SMPTransientWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 3, 0, 1, 2);

        computeButton = new QPushButton(SMPTransientWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 3, 2, 1, 2);

        progressLabel = new QLabel(SMPTransientWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 4, 0, 1, 2);


        retranslateUi(SMPTransientWidget);
        QObject::connect(sliderIterations, SIGNAL(valueChanged(int)), iterations, SLOT(setValue(int)));
        QObject::connect(iterations, SIGNAL(valueChanged(int)), sliderIterations, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(SMPTransientWidget);
    } // setupUi

    void retranslateUi(QWidget *SMPTransientWidget)
    {
        SMPTransientWidget->setWindowTitle(QApplication::translate("SMPTransientWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SMPTransientWidget", "Number of iterations", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SMPTransientWidget", "Threshold", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("SMPTransientWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SMPTransientWidget: public Ui_SMPTransientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMPTRANSIENTWIDGET_H
