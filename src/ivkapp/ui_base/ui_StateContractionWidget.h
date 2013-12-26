/********************************************************************************
** Form generated from reading ui file 'StateContractionWidget.ui'
**
** Created: Thu Dec 11 15:37:38 2008
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STATECONTRACTIONWIDGET_H
#define UI_STATECONTRACTIONWIDGET_H

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

class Ui_StateContractionWidget
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

    void setupUi(QWidget *StateContractionWidget)
    {
    if (StateContractionWidget->objectName().isEmpty())
        StateContractionWidget->setObjectName(QString::fromUtf8("StateContractionWidget"));
    StateContractionWidget->resize(472, 354);
    gridLayout = new QGridLayout(StateContractionWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(StateContractionWidget);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem, 0, 2, 1, 1);

    numContractions = new QSpinBox(StateContractionWidget);
    numContractions->setObjectName(QString::fromUtf8("numContractions"));
    numContractions->setMinimum(1);

    gridLayout->addWidget(numContractions, 0, 3, 1, 1);

    spacerItem1 = new QSpacerItem(131, 91, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem1, 2, 0, 1, 3);

    progressBar = new QProgressBar(StateContractionWidget);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setValue(0);

    gridLayout->addWidget(progressBar, 3, 0, 1, 2);

    computeButton = new QPushButton(StateContractionWidget);
    computeButton->setObjectName(QString::fromUtf8("computeButton"));

    gridLayout->addWidget(computeButton, 3, 2, 1, 2);

    progressLabel = new QLabel(StateContractionWidget);
    progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

    gridLayout->addWidget(progressLabel, 4, 0, 1, 2);

    sliderContractions = new QSlider(StateContractionWidget);
    sliderContractions->setObjectName(QString::fromUtf8("sliderContractions"));
    sliderContractions->setOrientation(Qt::Horizontal);

    gridLayout->addWidget(sliderContractions, 0, 1, 1, 1);


    retranslateUi(StateContractionWidget);
    QObject::connect(sliderContractions, SIGNAL(valueChanged(int)), numContractions, SLOT(setValue(int)));
    QObject::connect(numContractions, SIGNAL(valueChanged(int)), sliderContractions, SLOT(setValue(int)));

    QMetaObject::connectSlotsByName(StateContractionWidget);
    } // setupUi

    void retranslateUi(QWidget *StateContractionWidget)
    {
    StateContractionWidget->setWindowTitle(QApplication::translate("StateContractionWidget", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("StateContractionWidget", "Number of state contractions", 0, QApplication::UnicodeUTF8));
    computeButton->setText(QApplication::translate("StateContractionWidget", "Compute", 0, QApplication::UnicodeUTF8));
    progressLabel->setText(QString());
    Q_UNUSED(StateContractionWidget);
    } // retranslateUi

};

namespace Ui {
    class StateContractionWidget: public Ui_StateContractionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATECONTRACTIONWIDGET_H
