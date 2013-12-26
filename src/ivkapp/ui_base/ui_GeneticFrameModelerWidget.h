/********************************************************************************
** Form generated from reading UI file 'GeneticFrameModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENETICFRAMEMODELERWIDGET_H
#define UI_GENETICFRAMEMODELERWIDGET_H

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

class Ui_GeneticFrameModelerWidget
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
    QLabel *label_11;
    QSpinBox *framelevel;
    QSlider *framelevelSlider;

    void setupUi(QWidget *GeneticFrameModelerWidget)
    {
        if (GeneticFrameModelerWidget->objectName().isEmpty())
            GeneticFrameModelerWidget->setObjectName(QString::fromUtf8("GeneticFrameModelerWidget"));
        GeneticFrameModelerWidget->resize(472, 460);
        gridLayout = new QGridLayout(GeneticFrameModelerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(GeneticFrameModelerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sliderDSteps = new QSlider(GeneticFrameModelerWidget);
        sliderDSteps->setObjectName(QString::fromUtf8("sliderDSteps"));
        sliderDSteps->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDSteps, 0, 1, 1, 1);

        numdstepsEdit = new QSpinBox(GeneticFrameModelerWidget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));
        numdstepsEdit->setMinimum(1);

        gridLayout->addWidget(numdstepsEdit, 0, 3, 1, 1);

        label_2 = new QLabel(GeneticFrameModelerWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        sliderStates = new QSlider(GeneticFrameModelerWidget);
        sliderStates->setObjectName(QString::fromUtf8("sliderStates"));
        sliderStates->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderStates, 1, 1, 1, 1);

        numstatesEdit = new QSpinBox(GeneticFrameModelerWidget);
        numstatesEdit->setObjectName(QString::fromUtf8("numstatesEdit"));
        numstatesEdit->setMinimum(1);

        gridLayout->addWidget(numstatesEdit, 1, 3, 1, 1);

        label_3 = new QLabel(GeneticFrameModelerWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        sliderAutoc = new QSlider(GeneticFrameModelerWidget);
        sliderAutoc->setObjectName(QString::fromUtf8("sliderAutoc"));
        sliderAutoc->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderAutoc, 2, 1, 1, 1);

        numautocEdit = new QSpinBox(GeneticFrameModelerWidget);
        numautocEdit->setObjectName(QString::fromUtf8("numautocEdit"));
        numautocEdit->setMinimum(1);

        gridLayout->addWidget(numautocEdit, 2, 3, 1, 1);

        label_4 = new QLabel(GeneticFrameModelerWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        sliderIterations = new QSlider(GeneticFrameModelerWidget);
        sliderIterations->setObjectName(QString::fromUtf8("sliderIterations"));
        sliderIterations->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderIterations, 3, 1, 1, 1);

        numiterationsEdit = new QSpinBox(GeneticFrameModelerWidget);
        numiterationsEdit->setObjectName(QString::fromUtf8("numiterationsEdit"));
        numiterationsEdit->setMinimum(1);

        gridLayout->addWidget(numiterationsEdit, 3, 3, 1, 1);

        label_5 = new QLabel(GeneticFrameModelerWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        sliderPool = new QSlider(GeneticFrameModelerWidget);
        sliderPool->setObjectName(QString::fromUtf8("sliderPool"));
        sliderPool->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderPool, 4, 1, 1, 1);

        numpoolEdit = new QSpinBox(GeneticFrameModelerWidget);
        numpoolEdit->setObjectName(QString::fromUtf8("numpoolEdit"));
        numpoolEdit->setMinimum(1);

        gridLayout->addWidget(numpoolEdit, 4, 3, 1, 1);

        label_6 = new QLabel(GeneticFrameModelerWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 2);

        label_7 = new QLabel(GeneticFrameModelerWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 2);

        label_8 = new QLabel(GeneticFrameModelerWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 2);

        label_9 = new QLabel(GeneticFrameModelerWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 2);

        label_10 = new QLabel(GeneticFrameModelerWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 9, 0, 1, 2);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 11, 0, 1, 1);

        progressBar = new QProgressBar(GeneticFrameModelerWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 12, 0, 1, 2);

        computeButton = new QPushButton(GeneticFrameModelerWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 12, 2, 1, 2);

        progressLabel = new QLabel(GeneticFrameModelerWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 13, 0, 1, 2);

        mutBlock = new QDoubleSpinBox(GeneticFrameModelerWidget);
        mutBlock->setObjectName(QString::fromUtf8("mutBlock"));
        mutBlock->setMaximum(1);
        mutBlock->setSingleStep(0.01);

        gridLayout->addWidget(mutBlock, 5, 3, 1, 1);

        mutInverse = new QDoubleSpinBox(GeneticFrameModelerWidget);
        mutInverse->setObjectName(QString::fromUtf8("mutInverse"));
        mutInverse->setMaximum(1);
        mutInverse->setSingleStep(0.01);

        gridLayout->addWidget(mutInverse, 6, 3, 1, 1);

        mutShuffle = new QDoubleSpinBox(GeneticFrameModelerWidget);
        mutShuffle->setObjectName(QString::fromUtf8("mutShuffle"));
        mutShuffle->setMaximum(1);
        mutShuffle->setSingleStep(0.01);

        gridLayout->addWidget(mutShuffle, 7, 3, 1, 1);

        mutSwap = new QDoubleSpinBox(GeneticFrameModelerWidget);
        mutSwap->setObjectName(QString::fromUtf8("mutSwap"));
        mutSwap->setMaximum(1);
        mutSwap->setSingleStep(0.01);

        gridLayout->addWidget(mutSwap, 8, 3, 1, 1);

        mutCrossover = new QDoubleSpinBox(GeneticFrameModelerWidget);
        mutCrossover->setObjectName(QString::fromUtf8("mutCrossover"));
        mutCrossover->setMaximum(1);
        mutCrossover->setSingleStep(0.01);

        gridLayout->addWidget(mutCrossover, 9, 3, 1, 1);

        label_11 = new QLabel(GeneticFrameModelerWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 10, 0, 1, 1);

        framelevel = new QSpinBox(GeneticFrameModelerWidget);
        framelevel->setObjectName(QString::fromUtf8("framelevel"));
        framelevel->setMinimum(1);

        gridLayout->addWidget(framelevel, 10, 3, 1, 1);

        framelevelSlider = new QSlider(GeneticFrameModelerWidget);
        framelevelSlider->setObjectName(QString::fromUtf8("framelevelSlider"));
        framelevelSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(framelevelSlider, 10, 1, 1, 1);


        retranslateUi(GeneticFrameModelerWidget);
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
        QObject::connect(framelevelSlider, SIGNAL(valueChanged(int)), framelevel, SLOT(setValue(int)));
        QObject::connect(framelevel, SIGNAL(valueChanged(int)), framelevelSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(GeneticFrameModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *GeneticFrameModelerWidget)
    {
        GeneticFrameModelerWidget->setWindowTitle(QApplication::translate("GeneticFrameModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GeneticFrameModelerWidget", "Number of discretization steps", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GeneticFrameModelerWidget", "Number of states for discretization", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GeneticFrameModelerWidget", "Number of autocorrelation steps to consider", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("GeneticFrameModelerWidget", "Number of iterations", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("GeneticFrameModelerWidget", "Size of population", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("GeneticFrameModelerWidget", "Probability of \"Block\" Mutator", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("GeneticFrameModelerWidget", "Probability of \"Reverse\" Mutator", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("GeneticFrameModelerWidget", "Probability of \"Shuffle\" Mutator", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("GeneticFrameModelerWidget", "Probability of \"Swap\" Mutator", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("GeneticFrameModelerWidget", "Probabilty of  \"Crossover\" Mutator", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("GeneticFrameModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
        label_11->setText(QApplication::translate("GeneticFrameModelerWidget", "Size of Group of Pictures / Cycle Period", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GeneticFrameModelerWidget: public Ui_GeneticFrameModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENETICFRAMEMODELERWIDGET_H
