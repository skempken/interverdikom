/********************************************************************************
** Form generated from reading UI file 'RenewalModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENEWALMODELERWIDGET_H
#define UI_RENEWALMODELERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_RenewalModelerWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSlider *sliderDSteps;
    QSpinBox *numdstepsEdit;
    QSpacerItem *spacerItem;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;

    void setupUi(QWidget *RenewalModelerWidget)
    {
        if (RenewalModelerWidget->objectName().isEmpty())
            RenewalModelerWidget->setObjectName(QString::fromUtf8("RenewalModelerWidget"));
        RenewalModelerWidget->resize(473, 355);
        gridLayout = new QGridLayout(RenewalModelerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(RenewalModelerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sliderDSteps = new QSlider(RenewalModelerWidget);
        sliderDSteps->setObjectName(QString::fromUtf8("sliderDSteps"));
        sliderDSteps->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDSteps, 0, 1, 1, 1);

        numdstepsEdit = new QSpinBox(RenewalModelerWidget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));

        gridLayout->addWidget(numdstepsEdit, 0, 3, 1, 1);

        spacerItem = new QSpacerItem(231, 231, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 1, 1, 1, 3);

        progressBar = new QProgressBar(RenewalModelerWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        progressBar->setInvertedAppearance(false);

        gridLayout->addWidget(progressBar, 2, 0, 1, 2);

        computeButton = new QPushButton(RenewalModelerWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 2, 2, 1, 2);

        progressLabel = new QLabel(RenewalModelerWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 3, 0, 1, 2);


        retranslateUi(RenewalModelerWidget);
        QObject::connect(sliderDSteps, SIGNAL(valueChanged(int)), numdstepsEdit, SLOT(setValue(int)));
        QObject::connect(numdstepsEdit, SIGNAL(valueChanged(int)), sliderDSteps, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(RenewalModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *RenewalModelerWidget)
    {
        RenewalModelerWidget->setWindowTitle(QApplication::translate("RenewalModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RenewalModelerWidget", "Number of discretization steps", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("RenewalModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RenewalModelerWidget: public Ui_RenewalModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENEWALMODELERWIDGET_H
