/********************************************************************************
** Form generated from reading UI file 'GeneticModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENETICMODELERWIDGET_H
#define UI_GENETICMODELERWIDGET_H

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

class Ui_GeneticModelerWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSlider *sliderDSteps;
    QSpinBox *numdstepsEdit;
    QLabel *label_2;
    QSlider *sliderStates;
    QSpinBox *numstatesEdit;
    QLabel *label_3;
    QSlider *sliderAutoc;
    QSpinBox *numautocEdit;
    QLabel *label_4;
    QSlider *sliderIterations;
    QSpinBox *numiterationsEdit;
    QLabel *label_5;
    QSlider *sliderPool;
    QSpinBox *numpoolEdit;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QSpacerItem *spacerItem;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;
    QDoubleSpinBox *mutBlock;
    QDoubleSpinBox *mutInverse;
    QDoubleSpinBox *mutShuffle;
    QDoubleSpinBox *mutSwap;
    QDoubleSpinBox *mutCrossover;

    void setupUi(QWidget *GeneticModelerWidget)
    {
        if (GeneticModelerWidget->objectName().isEmpty())
            GeneticModelerWidget->setObjectName(QString::fromUtf8("GeneticModelerWidget"));
        GeneticModelerWidget->resize(472, 427);
        gridLayout = new QGridLayout(GeneticModelerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(GeneticModelerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sliderDSteps = new QSlider(GeneticModelerWidget);
        sliderDSteps->setObjectName(QString::fromUtf8("sliderDSteps"));
        sliderDSteps->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDSteps, 0, 1, 1, 1);

        numdstepsEdit = new QSpinBox(GeneticModelerWidget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));
        numdstepsEdit->setMinimum(1);

        gridLayout->addWidget(numdstepsEdit, 0, 3, 1, 1);

        label_2 = new QLabel(GeneticModelerWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        sliderStates = new QSlider(GeneticModelerWidget);
        sliderStates->setObjectName(QString::fromUtf8("sliderStates"));
        sliderStates->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderStates, 1, 1, 1, 1);

        numstatesEdit = new QSpinBox(GeneticModelerWidget);
        numstatesEdit->setObjectName(QString::fromUtf8("numstatesEdit"));
        numstatesEdit->setMinimum(1);

        gridLayout->addWidget(numstatesEdit, 1, 3, 1, 1);

        label_3 = new QLabel(GeneticModelerWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        sliderAutoc = new QSlider(GeneticModelerWidget);
        sliderAutoc->setObjectName(QString::fromUtf8("sliderAutoc"));
        sliderAutoc->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderAutoc, 2, 1, 1, 1);

        numautocEdit = new QSpinBox(GeneticModelerWidget);
        numautocEdit->setObjectName(QString::fromUtf8("numautocEdit"));
        numautocEdit->setMinimum(1);

        gridLayout->addWidget(numautocEdit, 2, 3, 1, 1);

        label_4 = new QLabel(GeneticModelerWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        sliderIterations = new QSlider(GeneticModelerWidget);
        sliderIterations->setObjectName(QString::fromUtf8("sliderIterations"));
        sliderIterations->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderIterations, 3, 1, 1, 1);

        numiterationsEdit = new QSpinBox(GeneticModelerWidget);
        numiterationsEdit->setObjectName(QString::fromUtf8("numiterationsEdit"));
        numiterationsEdit->setMinimum(1);

        gridLayout->addWidget(numiterationsEdit, 3, 3, 1, 1);

        label_5 = new QLabel(GeneticModelerWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        sliderPool = new QSlider(GeneticModelerWidget);
        sliderPool->setObjectName(QString::fromUtf8("sliderPool"));
        sliderPool->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderPool, 4, 1, 1, 1);

        numpoolEdit = new QSpinBox(GeneticModelerWidget);
        numpoolEdit->setObjectName(QString::fromUtf8("numpoolEdit"));
        numpoolEdit->setMinimum(1);

        gridLayout->addWidget(numpoolEdit, 4, 3, 1, 1);

        label_6 = new QLabel(GeneticModelerWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 2);

        label_7 = new QLabel(GeneticModelerWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 2);

        label_8 = new QLabel(GeneticModelerWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 2);

        label_9 = new QLabel(GeneticModelerWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 2);

        label_10 = new QLabel(GeneticModelerWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 9, 0, 1, 2);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 10, 0, 1, 1);

        progressBar = new QProgressBar(GeneticModelerWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 11, 0, 1, 2);

        computeButton = new QPushButton(GeneticModelerWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 11, 2, 1, 2);

        progressLabel = new QLabel(GeneticModelerWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 12, 0, 1, 2);

        mutBlock = new QDoubleSpinBox(GeneticModelerWidget);
        mutBlock->setObjectName(QString::fromUtf8("mutBlock"));
        mutBlock->setMaximum(1);
        mutBlock->setSingleStep(0.01);

        gridLayout->addWidget(mutBlock, 5, 3, 1, 1);

        mutInverse = new QDoubleSpinBox(GeneticModelerWidget);
        mutInverse->setObjectName(QString::fromUtf8("mutInverse"));
        mutInverse->setMaximum(1);
        mutInverse->setSingleStep(0.01);

        gridLayout->addWidget(mutInverse, 6, 3, 1, 1);

        mutShuffle = new QDoubleSpinBox(GeneticModelerWidget);
        mutShuffle->setObjectName(QString::fromUtf8("mutShuffle"));
        mutShuffle->setMaximum(1);
        mutShuffle->setSingleStep(0.01);

        gridLayout->addWidget(mutShuffle, 7, 3, 1, 1);

        mutSwap = new QDoubleSpinBox(GeneticModelerWidget);
        mutSwap->setObjectName(QString::fromUtf8("mutSwap"));
        mutSwap->setMaximum(1);
        mutSwap->setSingleStep(0.01);

        gridLayout->addWidget(mutSwap, 8, 3, 1, 1);

        mutCrossover = new QDoubleSpinBox(GeneticModelerWidget);
        mutCrossover->setObjectName(QString::fromUtf8("mutCrossover"));
        mutCrossover->setMaximum(1);
        mutCrossover->setSingleStep(0.01);

        gridLayout->addWidget(mutCrossover, 9, 3, 1, 1);


        retranslateUi(GeneticModelerWidget);
        QObject::connect(sliderDSteps, SIGNAL(sliderMoved(int)), numdstepsEdit, SLOT(setValue(int)));
        QObject::connect(numdstepsEdit, SIGNAL(valueChanged(int)), sliderDSteps, SLOT(setValue(int)));
        QObject::connect(sliderStates, SIGNAL(valueChanged(int)), numstatesEdit, SLOT(setValue(int)));
        QObject::connect(numstatesEdit, SIGNAL(valueChanged(int)), sliderStates, SLOT(setValue(int)));
        QObject::connect(sliderAutoc, SIGNAL(valueChanged(int)), numautocEdit, SLOT(setValue(int)));
        QObject::connect(numautocEdit, SIGNAL(valueChanged(int)), sliderAutoc, SLOT(setValue(int)));
        QObject::connect(sliderIterations, SIGNAL(valueChanged(int)), numiterationsEdit, SLOT(setValue(int)));
        QObject::connect(numiterationsEdit, SIGNAL(valueChanged(int)), sliderIterations, SLOT(setValue(int)));
        QObject::connect(sliderPool, SIGNAL(valueChanged(int)), numpoolEdit, SLOT(setValue(int)));
        QObject::connect(numpoolEdit, SIGNAL(valueChanged(int)), sliderPool, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(GeneticModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *GeneticModelerWidget)
    {
        GeneticModelerWidget->setWindowTitle(QApplication::translate("GeneticModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GeneticModelerWidget", "Number of discretization steps", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GeneticModelerWidget", "Number of states for discretization", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GeneticModelerWidget", "Number of autocorrelation coefficients to consider", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("GeneticModelerWidget", "Number of Iterations", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("GeneticModelerWidget", "Size of population", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("GeneticModelerWidget", "Probability of \"Block\" Mutator", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("GeneticModelerWidget", "Probability of \"Reverse\" Mutator", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("GeneticModelerWidget", "Probability of \"Shuffle\" Mutator", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("GeneticModelerWidget", "Probability of \"Swap\" Mutator", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("GeneticModelerWidget", "Probabilty of \"Crossover\" Mutator", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("GeneticModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GeneticModelerWidget: public Ui_GeneticModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENETICMODELERWIDGET_H
