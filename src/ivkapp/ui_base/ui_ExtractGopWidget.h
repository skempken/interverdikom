/********************************************************************************
** Form generated from reading UI file 'ExtractGopWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRACTGOPWIDGET_H
#define UI_EXTRACTGOPWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "widget/IvkPlot.h"

QT_BEGIN_NAMESPACE

class Ui_ExtractGopWidget
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    IvkPlot *plot;
    QLabel *label_3;
    QLabel *highestLabel;
    QSpacerItem *spacerItem;
    QLabel *label_5;
    QLabel *averageLabel;
    QPushButton *useAvgButton;
    QHBoxLayout *hboxLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QLabel *label;
    QSpinBox *lengthSpin;
    QSlider *lengthSlider;
    QLabel *label_2;
    QDoubleSpinBox *boundSpin;
    QSlider *boundSlider;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout2;
    QLabel *label_4;
    QPushButton *performButton;
    QSpinBox *intervalEdit;

    void setupUi(QWidget *ExtractGopWidget)
    {
        if (ExtractGopWidget->objectName().isEmpty())
            ExtractGopWidget->setObjectName(QString::fromUtf8("ExtractGopWidget"));
        ExtractGopWidget->resize(1010, 557);
        vboxLayout = new QVBoxLayout(ExtractGopWidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBox_3 = new QGroupBox(ExtractGopWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        plot = new IvkPlot(groupBox_3);
        plot->setObjectName(QString::fromUtf8("plot"));

        gridLayout->addWidget(plot, 0, 0, 1, 6);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        highestLabel = new QLabel(groupBox_3);
        highestLabel->setObjectName(QString::fromUtf8("highestLabel"));

        gridLayout->addWidget(highestLabel, 1, 1, 1, 1);

        spacerItem = new QSpacerItem(33, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 1, 2, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 3, 1, 1);

        averageLabel = new QLabel(groupBox_3);
        averageLabel->setObjectName(QString::fromUtf8("averageLabel"));

        gridLayout->addWidget(averageLabel, 1, 4, 1, 1);

        useAvgButton = new QPushButton(groupBox_3);
        useAvgButton->setObjectName(QString::fromUtf8("useAvgButton"));

        gridLayout->addWidget(useAvgButton, 1, 5, 1, 1);


        vboxLayout->addWidget(groupBox_3);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        groupBox = new QGroupBox(ExtractGopWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout1 = new QGridLayout(groupBox);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout1->addWidget(label, 0, 0, 1, 1);

        lengthSpin = new QSpinBox(groupBox);
        lengthSpin->setObjectName(QString::fromUtf8("lengthSpin"));

        gridLayout1->addWidget(lengthSpin, 0, 1, 1, 1);

        lengthSlider = new QSlider(groupBox);
        lengthSlider->setObjectName(QString::fromUtf8("lengthSlider"));
        lengthSlider->setOrientation(Qt::Horizontal);

        gridLayout1->addWidget(lengthSlider, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout1->addWidget(label_2, 1, 0, 1, 1);

        boundSpin = new QDoubleSpinBox(groupBox);
        boundSpin->setObjectName(QString::fromUtf8("boundSpin"));
        boundSpin->setMaximum(1);
        boundSpin->setSingleStep(0.01);

        gridLayout1->addWidget(boundSpin, 1, 1, 1, 1);

        boundSlider = new QSlider(groupBox);
        boundSlider->setObjectName(QString::fromUtf8("boundSlider"));
        boundSlider->setMaximum(100);
        boundSlider->setValue(50);
        boundSlider->setOrientation(Qt::Horizontal);

        gridLayout1->addWidget(boundSlider, 1, 2, 1, 1);


        hboxLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(ExtractGopWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        gridLayout2 = new QGridLayout(groupBox_2);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout2->addWidget(label_4, 0, 0, 1, 1);

        performButton = new QPushButton(groupBox_2);
        performButton->setObjectName(QString::fromUtf8("performButton"));

        gridLayout2->addWidget(performButton, 1, 0, 1, 2);

        intervalEdit = new QSpinBox(groupBox_2);
        intervalEdit->setObjectName(QString::fromUtf8("intervalEdit"));

        gridLayout2->addWidget(intervalEdit, 0, 1, 1, 1);


        hboxLayout->addWidget(groupBox_2);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(ExtractGopWidget);

        QMetaObject::connectSlotsByName(ExtractGopWidget);
    } // setupUi

    void retranslateUi(QWidget *ExtractGopWidget)
    {
        ExtractGopWidget->setWindowTitle(QApplication::translate("ExtractGopWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ExtractGopWidget", "Autocorrelation", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ExtractGopWidget", "Highest Max:", 0, QApplication::UnicodeUTF8));
        highestLabel->setText(QApplication::translate("ExtractGopWidget", "-", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ExtractGopWidget", "Avg Max:", 0, QApplication::UnicodeUTF8));
        averageLabel->setText(QApplication::translate("ExtractGopWidget", "-", 0, QApplication::UnicodeUTF8));
        useAvgButton->setText(QApplication::translate("ExtractGopWidget", "Use as bound", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ExtractGopWidget", "Settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ExtractGopWidget", "Sequence Length", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ExtractGopWidget", "Lower Bound", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ExtractGopWidget", "Result", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ExtractGopWidget", "Interval:", 0, QApplication::UnicodeUTF8));
        performButton->setText(QApplication::translate("ExtractGopWidget", "Perform Aggregation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExtractGopWidget: public Ui_ExtractGopWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRACTGOPWIDGET_H
