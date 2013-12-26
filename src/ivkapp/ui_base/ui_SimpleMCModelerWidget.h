/********************************************************************************
** Form generated from reading UI file 'SimpleMCModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEMCMODELERWIDGET_H
#define UI_SIMPLEMCMODELERWIDGET_H

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

class Ui_SimpleMCModelerWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSlider *sliderDSteps;
    QSpinBox *numdstepsEdit;
    QLabel *label_2;
    QSlider *sliderStates;
    QSpinBox *numstatesEdit;
    QSpacerItem *spacerItem;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;

    void setupUi(QWidget *SimpleMCModelerWidget)
    {
        if (SimpleMCModelerWidget->objectName().isEmpty())
            SimpleMCModelerWidget->setObjectName(QString::fromUtf8("SimpleMCModelerWidget"));
        SimpleMCModelerWidget->resize(472, 354);
        gridLayout = new QGridLayout(SimpleMCModelerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(SimpleMCModelerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sliderDSteps = new QSlider(SimpleMCModelerWidget);
        sliderDSteps->setObjectName(QString::fromUtf8("sliderDSteps"));
        sliderDSteps->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDSteps, 0, 1, 1, 1);

        numdstepsEdit = new QSpinBox(SimpleMCModelerWidget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));
        numdstepsEdit->setMinimum(1);

        gridLayout->addWidget(numdstepsEdit, 0, 3, 1, 1);

        label_2 = new QLabel(SimpleMCModelerWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        sliderStates = new QSlider(SimpleMCModelerWidget);
        sliderStates->setObjectName(QString::fromUtf8("sliderStates"));
        sliderStates->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderStates, 1, 1, 1, 1);

        numstatesEdit = new QSpinBox(SimpleMCModelerWidget);
        numstatesEdit->setObjectName(QString::fromUtf8("numstatesEdit"));
        numstatesEdit->setMinimum(1);

        gridLayout->addWidget(numstatesEdit, 1, 3, 1, 1);

        spacerItem = new QSpacerItem(61, 145, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 2, 0, 1, 1);

        progressBar = new QProgressBar(SimpleMCModelerWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 3, 0, 1, 2);

        computeButton = new QPushButton(SimpleMCModelerWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 3, 2, 1, 2);

        progressLabel = new QLabel(SimpleMCModelerWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 4, 0, 1, 2);


        retranslateUi(SimpleMCModelerWidget);
        QObject::connect(sliderDSteps, SIGNAL(valueChanged(int)), numdstepsEdit, SLOT(setValue(int)));
        QObject::connect(numdstepsEdit, SIGNAL(valueChanged(int)), sliderDSteps, SLOT(setValue(int)));
        QObject::connect(sliderStates, SIGNAL(valueChanged(int)), numstatesEdit, SLOT(setValue(int)));
        QObject::connect(numstatesEdit, SIGNAL(valueChanged(int)), sliderStates, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(SimpleMCModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *SimpleMCModelerWidget)
    {
        SimpleMCModelerWidget->setWindowTitle(QApplication::translate("SimpleMCModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SimpleMCModelerWidget", "Number of discretization steps", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SimpleMCModelerWidget", "Number of states for discretization", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("SimpleMCModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SimpleMCModelerWidget: public Ui_SimpleMCModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEMCMODELERWIDGET_H
