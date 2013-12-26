/********************************************************************************
** Form generated from reading UI file 'MMCModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MMCMODELERWIDGET_H
#define UI_MMCMODELERWIDGET_H

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

class Ui_MMCModelerWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *numdstepsEdit;
    QLabel *label_3;
    QSpinBox *wEdit;
    QLabel *label_4;
    QSpinBox *MaEdit;
    QLabel *label_5;
    QSpinBox *MsEdit;
    QSpacerItem *spacerItem;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;
    QSlider *sliderW;
    QSlider *sliderDSteps;
    QSlider *sliderMa;
    QSlider *sliderMs;

    void setupUi(QWidget *MMCModelerWidget)
    {
        if (MMCModelerWidget->objectName().isEmpty())
            MMCModelerWidget->setObjectName(QString::fromUtf8("MMCModelerWidget"));
        MMCModelerWidget->resize(509, 344);
        gridLayout = new QGridLayout(MMCModelerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(MMCModelerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        numdstepsEdit = new QSpinBox(MMCModelerWidget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));
        numdstepsEdit->setMinimum(1);

        gridLayout->addWidget(numdstepsEdit, 0, 3, 1, 1);

        label_3 = new QLabel(MMCModelerWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        wEdit = new QSpinBox(MMCModelerWidget);
        wEdit->setObjectName(QString::fromUtf8("wEdit"));
        wEdit->setMinimum(1);
        wEdit->setMaximum(99);

        gridLayout->addWidget(wEdit, 1, 3, 1, 1);

        label_4 = new QLabel(MMCModelerWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        MaEdit = new QSpinBox(MMCModelerWidget);
        MaEdit->setObjectName(QString::fromUtf8("MaEdit"));
        MaEdit->setMinimum(1);

        gridLayout->addWidget(MaEdit, 2, 3, 1, 1);

        label_5 = new QLabel(MMCModelerWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        MsEdit = new QSpinBox(MMCModelerWidget);
        MsEdit->setObjectName(QString::fromUtf8("MsEdit"));
        MsEdit->setMinimum(1);

        gridLayout->addWidget(MsEdit, 3, 3, 1, 1);

        spacerItem = new QSpacerItem(271, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 4, 0, 1, 4);

        progressBar = new QProgressBar(MMCModelerWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 5, 0, 1, 2);

        computeButton = new QPushButton(MMCModelerWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 5, 2, 1, 2);

        progressLabel = new QLabel(MMCModelerWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 6, 0, 1, 2);

        sliderW = new QSlider(MMCModelerWidget);
        sliderW->setObjectName(QString::fromUtf8("sliderW"));
        sliderW->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderW, 1, 1, 1, 2);

        sliderDSteps = new QSlider(MMCModelerWidget);
        sliderDSteps->setObjectName(QString::fromUtf8("sliderDSteps"));
        sliderDSteps->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDSteps, 0, 1, 1, 2);

        sliderMa = new QSlider(MMCModelerWidget);
        sliderMa->setObjectName(QString::fromUtf8("sliderMa"));
        sliderMa->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderMa, 2, 1, 1, 2);

        sliderMs = new QSlider(MMCModelerWidget);
        sliderMs->setObjectName(QString::fromUtf8("sliderMs"));
        sliderMs->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderMs, 3, 1, 1, 2);


        retranslateUi(MMCModelerWidget);
        QObject::connect(sliderDSteps, SIGNAL(valueChanged(int)), numdstepsEdit, SLOT(setValue(int)));
        QObject::connect(numdstepsEdit, SIGNAL(valueChanged(int)), sliderDSteps, SLOT(setValue(int)));
        QObject::connect(sliderW, SIGNAL(valueChanged(int)), wEdit, SLOT(setValue(int)));
        QObject::connect(wEdit, SIGNAL(valueChanged(int)), sliderW, SLOT(setValue(int)));
        QObject::connect(sliderMa, SIGNAL(valueChanged(int)), MaEdit, SLOT(setValue(int)));
        QObject::connect(MaEdit, SIGNAL(valueChanged(int)), sliderMa, SLOT(setValue(int)));
        QObject::connect(sliderMs, SIGNAL(valueChanged(int)), MsEdit, SLOT(setValue(int)));
        QObject::connect(MsEdit, SIGNAL(valueChanged(int)), sliderMs, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(MMCModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *MMCModelerWidget)
    {
        MMCModelerWidget->setWindowTitle(QApplication::translate("MMCModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MMCModelerWidget", "Number of discretization steps", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("MMCModelerWidget", "Number of values to consider for Moving Average\n"
"", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("MMCModelerWidget", "Number of values to consider for moving average", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MMCModelerWidget", "Number of states for moving average", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MMCModelerWidget", "Number of states for discretization", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("MMCModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MMCModelerWidget: public Ui_MMCModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MMCMODELERWIDGET_H
