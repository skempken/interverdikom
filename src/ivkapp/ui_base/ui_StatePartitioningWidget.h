/********************************************************************************
** Form generated from reading UI file 'StatePartitioningWidget.ui'
**
** Created: Thu Dec 26 15:32:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATEPARTITIONINGWIDGET_H
#define UI_STATEPARTITIONINGWIDGET_H

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

class Ui_StatePartitioningWidget
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

    void setupUi(QWidget *StatePartitioningWidget)
    {
        if (StatePartitioningWidget->objectName().isEmpty())
            StatePartitioningWidget->setObjectName(QString::fromUtf8("StatePartitioningWidget"));
        StatePartitioningWidget->resize(472, 354);
        gridLayout = new QGridLayout(StatePartitioningWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(StatePartitioningWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 2, 1, 1);

        numContractions = new QSpinBox(StatePartitioningWidget);
        numContractions->setObjectName(QString::fromUtf8("numContractions"));
        numContractions->setMinimum(1);

        gridLayout->addWidget(numContractions, 0, 3, 1, 1);

        spacerItem1 = new QSpacerItem(131, 91, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem1, 2, 0, 1, 3);

        progressBar = new QProgressBar(StatePartitioningWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 3, 0, 1, 2);

        computeButton = new QPushButton(StatePartitioningWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 3, 2, 1, 2);

        progressLabel = new QLabel(StatePartitioningWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 4, 0, 1, 2);

        sliderContractions = new QSlider(StatePartitioningWidget);
        sliderContractions->setObjectName(QString::fromUtf8("sliderContractions"));
        sliderContractions->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderContractions, 0, 1, 1, 1);


        retranslateUi(StatePartitioningWidget);
        QObject::connect(sliderContractions, SIGNAL(valueChanged(int)), numContractions, SLOT(setValue(int)));
        QObject::connect(numContractions, SIGNAL(valueChanged(int)), sliderContractions, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(StatePartitioningWidget);
    } // setupUi

    void retranslateUi(QWidget *StatePartitioningWidget)
    {
        StatePartitioningWidget->setWindowTitle(QApplication::translate("StatePartitioningWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StatePartitioningWidget", "Number of state contractions", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("StatePartitioningWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StatePartitioningWidget: public Ui_StatePartitioningWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATEPARTITIONINGWIDGET_H
