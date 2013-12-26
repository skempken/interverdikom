/********************************************************************************
** Form generated from reading UI file 'SPEA2ModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPEA2MODELERWIDGET_H
#define UI_SPEA2MODELERWIDGET_H

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

class Ui_SPEA2ModelerWidget
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
    QSlider *sliderPopSize;
    QSpinBox *popSize;
    QLabel *label_4;
    QSlider *sliderArchiveSize;
    QSpinBox *archiveSize;
    QLabel *label_5;
    QSlider *sliderNumIterations;
    QSpinBox *numIterations;
    QLabel *label_6;
    QSlider *sliderAutocorrelation;
    QSpinBox *autocorrelation;
    QLabel *label_7;
    QDoubleSpinBox *mutCrossover;
    QLabel *label_8;
    QDoubleSpinBox *mutBlock;
    QLabel *label_9;
    QDoubleSpinBox *mutInverse;
    QLabel *label_10;
    QDoubleSpinBox *mutShuffle;
    QLabel *label_11;
    QDoubleSpinBox *mutSwap;
    QSpacerItem *spacerItem;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;

    void setupUi(QWidget *SPEA2ModelerWidget)
    {
        if (SPEA2ModelerWidget->objectName().isEmpty())
            SPEA2ModelerWidget->setObjectName(QString::fromUtf8("SPEA2ModelerWidget"));
        SPEA2ModelerWidget->resize(517, 460);
        gridLayout = new QGridLayout(SPEA2ModelerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(SPEA2ModelerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sliderDSteps = new QSlider(SPEA2ModelerWidget);
        sliderDSteps->setObjectName(QString::fromUtf8("sliderDSteps"));
        sliderDSteps->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDSteps, 0, 1, 1, 1);

        numdstepsEdit = new QSpinBox(SPEA2ModelerWidget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));
        numdstepsEdit->setMinimum(1);

        gridLayout->addWidget(numdstepsEdit, 0, 3, 1, 1);

        label_2 = new QLabel(SPEA2ModelerWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        sliderStates = new QSlider(SPEA2ModelerWidget);
        sliderStates->setObjectName(QString::fromUtf8("sliderStates"));
        sliderStates->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderStates, 1, 1, 1, 1);

        numstatesEdit = new QSpinBox(SPEA2ModelerWidget);
        numstatesEdit->setObjectName(QString::fromUtf8("numstatesEdit"));
        numstatesEdit->setMinimum(1);

        gridLayout->addWidget(numstatesEdit, 1, 3, 1, 1);

        label_3 = new QLabel(SPEA2ModelerWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        sliderPopSize = new QSlider(SPEA2ModelerWidget);
        sliderPopSize->setObjectName(QString::fromUtf8("sliderPopSize"));
        sliderPopSize->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderPopSize, 2, 1, 1, 1);

        popSize = new QSpinBox(SPEA2ModelerWidget);
        popSize->setObjectName(QString::fromUtf8("popSize"));

        gridLayout->addWidget(popSize, 2, 3, 1, 1);

        label_4 = new QLabel(SPEA2ModelerWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        sliderArchiveSize = new QSlider(SPEA2ModelerWidget);
        sliderArchiveSize->setObjectName(QString::fromUtf8("sliderArchiveSize"));
        sliderArchiveSize->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderArchiveSize, 3, 1, 1, 1);

        archiveSize = new QSpinBox(SPEA2ModelerWidget);
        archiveSize->setObjectName(QString::fromUtf8("archiveSize"));

        gridLayout->addWidget(archiveSize, 3, 3, 1, 1);

        label_5 = new QLabel(SPEA2ModelerWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        sliderNumIterations = new QSlider(SPEA2ModelerWidget);
        sliderNumIterations->setObjectName(QString::fromUtf8("sliderNumIterations"));
        sliderNumIterations->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderNumIterations, 4, 1, 1, 1);

        numIterations = new QSpinBox(SPEA2ModelerWidget);
        numIterations->setObjectName(QString::fromUtf8("numIterations"));

        gridLayout->addWidget(numIterations, 4, 3, 1, 1);

        label_6 = new QLabel(SPEA2ModelerWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        sliderAutocorrelation = new QSlider(SPEA2ModelerWidget);
        sliderAutocorrelation->setObjectName(QString::fromUtf8("sliderAutocorrelation"));
        sliderAutocorrelation->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderAutocorrelation, 5, 1, 1, 1);

        autocorrelation = new QSpinBox(SPEA2ModelerWidget);
        autocorrelation->setObjectName(QString::fromUtf8("autocorrelation"));

        gridLayout->addWidget(autocorrelation, 5, 3, 1, 1);

        label_7 = new QLabel(SPEA2ModelerWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        mutCrossover = new QDoubleSpinBox(SPEA2ModelerWidget);
        mutCrossover->setObjectName(QString::fromUtf8("mutCrossover"));
        mutCrossover->setMaximum(1);
        mutCrossover->setSingleStep(0.01);
        mutCrossover->setValue(0.01);

        gridLayout->addWidget(mutCrossover, 6, 3, 1, 1);

        label_8 = new QLabel(SPEA2ModelerWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        mutBlock = new QDoubleSpinBox(SPEA2ModelerWidget);
        mutBlock->setObjectName(QString::fromUtf8("mutBlock"));
        mutBlock->setMaximum(1);
        mutBlock->setSingleStep(0.01);
        mutBlock->setValue(0.01);

        gridLayout->addWidget(mutBlock, 7, 3, 1, 1);

        label_9 = new QLabel(SPEA2ModelerWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        mutInverse = new QDoubleSpinBox(SPEA2ModelerWidget);
        mutInverse->setObjectName(QString::fromUtf8("mutInverse"));
        mutInverse->setMaximum(1);
        mutInverse->setSingleStep(0.01);
        mutInverse->setValue(0.01);

        gridLayout->addWidget(mutInverse, 8, 3, 1, 1);

        label_10 = new QLabel(SPEA2ModelerWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 9, 0, 1, 1);

        mutShuffle = new QDoubleSpinBox(SPEA2ModelerWidget);
        mutShuffle->setObjectName(QString::fromUtf8("mutShuffle"));
        mutShuffle->setMinimum(0);
        mutShuffle->setMaximum(1);
        mutShuffle->setSingleStep(0.01);
        mutShuffle->setValue(0.01);

        gridLayout->addWidget(mutShuffle, 9, 3, 1, 1);

        label_11 = new QLabel(SPEA2ModelerWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 10, 0, 1, 1);

        mutSwap = new QDoubleSpinBox(SPEA2ModelerWidget);
        mutSwap->setObjectName(QString::fromUtf8("mutSwap"));
        mutSwap->setMaximum(1);
        mutSwap->setSingleStep(0.01);
        mutSwap->setValue(0.01);

        gridLayout->addWidget(mutSwap, 10, 3, 1, 1);

        spacerItem = new QSpacerItem(393, 201, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 11, 0, 1, 3);

        progressBar = new QProgressBar(SPEA2ModelerWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 12, 0, 1, 2);

        computeButton = new QPushButton(SPEA2ModelerWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 12, 2, 1, 2);

        progressLabel = new QLabel(SPEA2ModelerWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 13, 0, 1, 2);


        retranslateUi(SPEA2ModelerWidget);
        QObject::connect(sliderDSteps, SIGNAL(valueChanged(int)), numdstepsEdit, SLOT(setValue(int)));
        QObject::connect(numdstepsEdit, SIGNAL(valueChanged(int)), sliderDSteps, SLOT(setValue(int)));
        QObject::connect(sliderStates, SIGNAL(valueChanged(int)), numstatesEdit, SLOT(setValue(int)));
        QObject::connect(numstatesEdit, SIGNAL(valueChanged(int)), sliderStates, SLOT(setValue(int)));
        QObject::connect(popSize, SIGNAL(valueChanged(int)), sliderPopSize, SLOT(setValue(int)));
        QObject::connect(sliderPopSize, SIGNAL(valueChanged(int)), popSize, SLOT(setValue(int)));
        QObject::connect(sliderArchiveSize, SIGNAL(valueChanged(int)), archiveSize, SLOT(setValue(int)));
        QObject::connect(archiveSize, SIGNAL(valueChanged(int)), sliderArchiveSize, SLOT(setValue(int)));
        QObject::connect(sliderNumIterations, SIGNAL(valueChanged(int)), numIterations, SLOT(setValue(int)));
        QObject::connect(numIterations, SIGNAL(valueChanged(int)), sliderNumIterations, SLOT(setValue(int)));
        QObject::connect(sliderAutocorrelation, SIGNAL(valueChanged(int)), autocorrelation, SLOT(setValue(int)));
        QObject::connect(autocorrelation, SIGNAL(valueChanged(int)), sliderAutocorrelation, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(SPEA2ModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *SPEA2ModelerWidget)
    {
        SPEA2ModelerWidget->setWindowTitle(QApplication::translate("SPEA2ModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SPEA2ModelerWidget", "Number of discretization steps", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SPEA2ModelerWidget", "Number of states", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SPEA2ModelerWidget", "Size of Population", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SPEA2ModelerWidget", "Size of Archive", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SPEA2ModelerWidget", "Number of Iterations", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SPEA2ModelerWidget", "Number of Autocorrelation coefficients to consider", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SPEA2ModelerWidget", "Probability of \"Crossover\" Mutator", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SPEA2ModelerWidget", "Probability of \"Block\" Mutator", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("SPEA2ModelerWidget", "Probability of \"Reverse\" Mutator", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("SPEA2ModelerWidget", "Probability of \"Shuffle\" Mutator", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("SPEA2ModelerWidget", "Probability of \"Swap\" Mutator", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("SPEA2ModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SPEA2ModelerWidget: public Ui_SPEA2ModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPEA2MODELERWIDGET_H
