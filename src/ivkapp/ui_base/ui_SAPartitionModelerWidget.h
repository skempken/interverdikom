/********************************************************************************
** Form generated from reading UI file 'SAPartitionModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAPARTITIONMODELERWIDGET_H
#define UI_SAPARTITIONMODELERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SAPartitionModelerWidget
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSlider *sliderDSteps;
    QSpinBox *numdstepsEdit;
    QLabel *label_2;
    QSlider *sliderStates;
    QSpinBox *numstatesEdit;
    QLabel *label_6;
    QSlider *sliderAutoc;
    QSpinBox *autoc;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QDoubleSpinBox *initTemp;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *abortTemp;
    QDoubleSpinBox *alpha;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;

    void setupUi(QWidget *SAPartitionModelerWidget)
    {
        if (SAPartitionModelerWidget->objectName().isEmpty())
            SAPartitionModelerWidget->setObjectName(QString::fromUtf8("SAPartitionModelerWidget"));
        SAPartitionModelerWidget->resize(514, 354);
        gridLayout_2 = new QGridLayout(SAPartitionModelerWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(SAPartitionModelerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        sliderDSteps = new QSlider(SAPartitionModelerWidget);
        sliderDSteps->setObjectName(QString::fromUtf8("sliderDSteps"));
        sliderDSteps->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderDSteps, 0, 1, 1, 1);

        numdstepsEdit = new QSpinBox(SAPartitionModelerWidget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));
        numdstepsEdit->setMinimum(1);

        gridLayout_2->addWidget(numdstepsEdit, 0, 2, 1, 1);

        label_2 = new QLabel(SAPartitionModelerWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        sliderStates = new QSlider(SAPartitionModelerWidget);
        sliderStates->setObjectName(QString::fromUtf8("sliderStates"));
        sliderStates->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderStates, 1, 1, 1, 1);

        numstatesEdit = new QSpinBox(SAPartitionModelerWidget);
        numstatesEdit->setObjectName(QString::fromUtf8("numstatesEdit"));
        numstatesEdit->setMinimum(1);

        gridLayout_2->addWidget(numstatesEdit, 1, 2, 1, 1);

        label_6 = new QLabel(SAPartitionModelerWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        sliderAutoc = new QSlider(SAPartitionModelerWidget);
        sliderAutoc->setObjectName(QString::fromUtf8("sliderAutoc"));
        sliderAutoc->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderAutoc, 2, 1, 1, 1);

        autoc = new QSpinBox(SAPartitionModelerWidget);
        autoc->setObjectName(QString::fromUtf8("autoc"));

        gridLayout_2->addWidget(autoc, 2, 2, 1, 1);

        groupBox = new QGroupBox(SAPartitionModelerWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(260, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        initTemp = new QDoubleSpinBox(groupBox);
        initTemp->setObjectName(QString::fromUtf8("initTemp"));
        initTemp->setDecimals(1);
        initTemp->setSingleStep(10);

        gridLayout->addWidget(initTemp, 0, 2, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 2, 1);

        horizontalSpacer_2 = new QSpacerItem(260, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        abortTemp = new QDoubleSpinBox(groupBox);
        abortTemp->setObjectName(QString::fromUtf8("abortTemp"));
        abortTemp->setDecimals(6);
        abortTemp->setMinimum(0);
        abortTemp->setSingleStep(0.001);
        abortTemp->setValue(0);

        gridLayout->addWidget(abortTemp, 1, 2, 1, 1);

        alpha = new QDoubleSpinBox(groupBox);
        alpha->setObjectName(QString::fromUtf8("alpha"));

        gridLayout->addWidget(alpha, 2, 2, 2, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(260, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 3, 0, 1, 3);

        verticalSpacer = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 4, 0, 1, 1);

        progressBar = new QProgressBar(SAPartitionModelerWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout_2->addWidget(progressBar, 5, 0, 1, 2);

        computeButton = new QPushButton(SAPartitionModelerWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout_2->addWidget(computeButton, 5, 2, 1, 1);

        progressLabel = new QLabel(SAPartitionModelerWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout_2->addWidget(progressLabel, 6, 0, 1, 2);


        retranslateUi(SAPartitionModelerWidget);
        QObject::connect(sliderDSteps, SIGNAL(valueChanged(int)), numdstepsEdit, SLOT(setValue(int)));
        QObject::connect(numdstepsEdit, SIGNAL(valueChanged(int)), sliderDSteps, SLOT(setValue(int)));
        QObject::connect(sliderStates, SIGNAL(valueChanged(int)), numstatesEdit, SLOT(setValue(int)));
        QObject::connect(numstatesEdit, SIGNAL(valueChanged(int)), sliderStates, SLOT(setValue(int)));
        QObject::connect(sliderAutoc, SIGNAL(valueChanged(int)), autoc, SLOT(setValue(int)));
        QObject::connect(autoc, SIGNAL(valueChanged(int)), sliderAutoc, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(SAPartitionModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *SAPartitionModelerWidget)
    {
        SAPartitionModelerWidget->setWindowTitle(QApplication::translate("SAPartitionModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SAPartitionModelerWidget", "Number of discretization steps", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SAPartitionModelerWidget", "Number of states for discretization", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SAPartitionModelerWidget", "Number of autocorrelation coefficients to consider", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SAPartitionModelerWidget", "Parameters for Simulated Annealing step", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SAPartitionModelerWidget", "Initial temperature", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SAPartitionModelerWidget", "Abort temperature", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SAPartitionModelerWidget", "Cooldown coefficient", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("SAPartitionModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SAPartitionModelerWidget: public Ui_SAPartitionModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAPARTITIONMODELERWIDGET_H
