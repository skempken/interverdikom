/********************************************************************************
** Form generated from reading ui file 'StateContractionOptimalWidget.ui'
**
** Created: Tue Jan 6 10:42:28 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STATECONTRACTIONOPTIMALWIDGET_H
#define UI_STATECONTRACTIONOPTIMALWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StateContractionOptimalWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *spacerItem;
    QSpinBox *numContractions;
    QSpacerItem *spacerItem1;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;
    QSlider *sliderContractions;

    void setupUi(QWidget *StateContractionOptimalWidget)
    {
    if (StateContractionOptimalWidget->objectName().isEmpty())
        StateContractionOptimalWidget->setObjectName(QString::fromUtf8("StateContractionOptimalWidget"));
    StateContractionOptimalWidget->resize(472, 354);
    gridLayout = new QGridLayout(StateContractionOptimalWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(StateContractionOptimalWidget);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem, 0, 2, 1, 1);

    numContractions = new QSpinBox(StateContractionOptimalWidget);
    numContractions->setObjectName(QString::fromUtf8("numContractions"));
    numContractions->setMinimum(1);

    gridLayout->addWidget(numContractions, 0, 3, 1, 1);

    spacerItem1 = new QSpacerItem(131, 91, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem1, 2, 0, 1, 3);

    progressBar = new QProgressBar(StateContractionOptimalWidget);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setValue(0);

    gridLayout->addWidget(progressBar, 3, 0, 1, 2);

    computeButton = new QPushButton(StateContractionOptimalWidget);
    computeButton->setObjectName(QString::fromUtf8("computeButton"));

    gridLayout->addWidget(computeButton, 3, 2, 1, 2);

    progressLabel = new QLabel(StateContractionOptimalWidget);
    progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

    gridLayout->addWidget(progressLabel, 4, 0, 1, 2);

    sliderContractions = new QSlider(StateContractionOptimalWidget);
    sliderContractions->setObjectName(QString::fromUtf8("sliderContractions"));
    sliderContractions->setOrientation(Qt::Horizontal);

    gridLayout->addWidget(sliderContractions, 0, 1, 1, 1);


    retranslateUi(StateContractionOptimalWidget);
    QObject::connect(sliderContractions, SIGNAL(valueChanged(int)), numContractions, SLOT(setValue(int)));
    QObject::connect(numContractions, SIGNAL(valueChanged(int)), sliderContractions, SLOT(setValue(int)));

    QMetaObject::connectSlotsByName(StateContractionOptimalWidget);
    } // setupUi

    void retranslateUi(QWidget *StateContractionOptimalWidget)
    {
    StateContractionOptimalWidget->setWindowTitle(QApplication::translate("StateContractionOptimalWidget", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("StateContractionOptimalWidget", "Number of state contractions", 0, QApplication::UnicodeUTF8));
    computeButton->setText(QApplication::translate("StateContractionOptimalWidget", "Compute", 0, QApplication::UnicodeUTF8));
    progressLabel->setText(QString());
    Q_UNUSED(StateContractionOptimalWidget);
    } // retranslateUi

};

namespace Ui {
    class StateContractionOptimalWidget: public Ui_StateContractionOptimalWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATECONTRACTIONOPTIMALWIDGET_H
