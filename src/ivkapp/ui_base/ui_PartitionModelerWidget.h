/********************************************************************************
** Form generated from reading UI file 'PartitionModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTITIONMODELERWIDGET_H
#define UI_PARTITIONMODELERWIDGET_H

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

class Ui_PartitionModelerWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *numdstepsEdit;
    QLabel *label_2;
    QSpinBox *numstatesEdit;
    QSpacerItem *spacerItem;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;
    QSlider *sliderDSteps;
    QSlider *sliderStates;

    void setupUi(QWidget *PartitionModelerWidget)
    {
        if (PartitionModelerWidget->objectName().isEmpty())
            PartitionModelerWidget->setObjectName(QString::fromUtf8("PartitionModelerWidget"));
        PartitionModelerWidget->resize(472, 354);
        gridLayout = new QGridLayout(PartitionModelerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(PartitionModelerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        numdstepsEdit = new QSpinBox(PartitionModelerWidget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));
        numdstepsEdit->setMinimum(1);

        gridLayout->addWidget(numdstepsEdit, 0, 3, 1, 1);

        label_2 = new QLabel(PartitionModelerWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        numstatesEdit = new QSpinBox(PartitionModelerWidget);
        numstatesEdit->setObjectName(QString::fromUtf8("numstatesEdit"));
        numstatesEdit->setMinimum(1);

        gridLayout->addWidget(numstatesEdit, 1, 3, 1, 1);

        spacerItem = new QSpacerItem(131, 91, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 2, 0, 1, 3);

        progressBar = new QProgressBar(PartitionModelerWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 3, 0, 1, 2);

        computeButton = new QPushButton(PartitionModelerWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 3, 2, 1, 2);

        progressLabel = new QLabel(PartitionModelerWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 4, 0, 1, 2);

        sliderDSteps = new QSlider(PartitionModelerWidget);
        sliderDSteps->setObjectName(QString::fromUtf8("sliderDSteps"));
        sliderDSteps->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDSteps, 0, 1, 1, 1);

        sliderStates = new QSlider(PartitionModelerWidget);
        sliderStates->setObjectName(QString::fromUtf8("sliderStates"));
        sliderStates->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderStates, 1, 1, 1, 1);


        retranslateUi(PartitionModelerWidget);
        QObject::connect(sliderDSteps, SIGNAL(valueChanged(int)), numdstepsEdit, SLOT(setValue(int)));
        QObject::connect(numdstepsEdit, SIGNAL(valueChanged(int)), sliderDSteps, SLOT(setValue(int)));
        QObject::connect(sliderStates, SIGNAL(valueChanged(int)), numstatesEdit, SLOT(setValue(int)));
        QObject::connect(numstatesEdit, SIGNAL(valueChanged(int)), sliderStates, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(PartitionModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *PartitionModelerWidget)
    {
        PartitionModelerWidget->setWindowTitle(QApplication::translate("PartitionModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PartitionModelerWidget", "Number of discretization steps", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PartitionModelerWidget", "Number of states for discretization", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("PartitionModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PartitionModelerWidget: public Ui_PartitionModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTITIONMODELERWIDGET_H
