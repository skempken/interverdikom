/********************************************************************************
** Form generated from reading UI file 'TraceDisplay.ui'
**
** Created: Thu Dec 26 15:32:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACEDISPLAY_H
#define UI_TRACEDISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "widget/IvkPlot.h"
#include "widget/IvkTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_TraceDisplay
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *widget;
    QVBoxLayout *vboxLayout1;
    IvkPlot *valuePlot;
    IvkTableWidget *valueTable;
    QWidget *tab;
    QGridLayout *gridLayout;
    IvkPlot *histogramPlot;
    QLabel *label_6;
    QSlider *groupSlider;
    QSpinBox *groupSpin;
    QWidget *tab_2;
    QGridLayout *gridLayout1;
    IvkPlot *autocorrelationPlot;
    QLabel *label;
    QSlider *upToSlider;
    QSpinBox *upToSpin;
    QGroupBox *groupBox;
    QGridLayout *gridLayout2;
    QLabel *label_2;
    QSpacerItem *spacerItem;
    QLineEdit *sampleCountEdit;
    QSpacerItem *spacerItem1;
    QLabel *label_5;
    QSpacerItem *spacerItem2;
    QLineEdit *varianceEdit;
    QLabel *label_3;
    QSpacerItem *spacerItem3;
    QLineEdit *averageSizeEdit;
    QSpacerItem *spacerItem4;
    QLabel *label_4;
    QSpacerItem *spacerItem5;
    QLineEdit *standardDeviationEdit;

    void setupUi(QWidget *TraceDisplay)
    {
        if (TraceDisplay->objectName().isEmpty())
            TraceDisplay->setObjectName(QString::fromUtf8("TraceDisplay"));
        TraceDisplay->resize(844, 531);
        vboxLayout = new QVBoxLayout(TraceDisplay);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        tabWidget = new QTabWidget(TraceDisplay);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        vboxLayout1 = new QVBoxLayout(widget);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        valuePlot = new IvkPlot(widget);
        valuePlot->setObjectName(QString::fromUtf8("valuePlot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(valuePlot->sizePolicy().hasHeightForWidth());
        valuePlot->setSizePolicy(sizePolicy);

        vboxLayout1->addWidget(valuePlot);

        valueTable = new IvkTableWidget(widget);
        if (valueTable->rowCount() < 2)
            valueTable->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        valueTable->setVerticalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        valueTable->setVerticalHeaderItem(1, __qtablewidgetitem1);
        valueTable->setObjectName(QString::fromUtf8("valueTable"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(valueTable->sizePolicy().hasHeightForWidth());
        valueTable->setSizePolicy(sizePolicy1);
        valueTable->setBaseSize(QSize(0, 60));
        valueTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        valueTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        valueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        valueTable->setAlternatingRowColors(true);
        valueTable->setSelectionMode(QAbstractItemView::NoSelection);
        valueTable->setWordWrap(false);

        vboxLayout1->addWidget(valueTable);

        tabWidget->addTab(widget, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        histogramPlot = new IvkPlot(tab);
        histogramPlot->setObjectName(QString::fromUtf8("histogramPlot"));

        gridLayout->addWidget(histogramPlot, 0, 0, 1, 3);

        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        groupSlider = new QSlider(tab);
        groupSlider->setObjectName(QString::fromUtf8("groupSlider"));
        groupSlider->setMinimum(1);
        groupSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(groupSlider, 1, 1, 1, 1);

        groupSpin = new QSpinBox(tab);
        groupSpin->setObjectName(QString::fromUtf8("groupSpin"));
        groupSpin->setMinimum(1);

        gridLayout->addWidget(groupSpin, 1, 2, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout1 = new QGridLayout(tab_2);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        autocorrelationPlot = new IvkPlot(tab_2);
        autocorrelationPlot->setObjectName(QString::fromUtf8("autocorrelationPlot"));

        gridLayout1->addWidget(autocorrelationPlot, 0, 0, 1, 3);

        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout1->addWidget(label, 1, 0, 1, 1);

        upToSlider = new QSlider(tab_2);
        upToSlider->setObjectName(QString::fromUtf8("upToSlider"));
        upToSlider->setMinimum(1);
        upToSlider->setOrientation(Qt::Horizontal);

        gridLayout1->addWidget(upToSlider, 1, 1, 1, 1);

        upToSpin = new QSpinBox(tab_2);
        upToSpin->setObjectName(QString::fromUtf8("upToSpin"));
        upToSpin->setMinimum(1);

        gridLayout1->addWidget(upToSpin, 1, 2, 1, 1);

        tabWidget->addTab(tab_2, QString());

        vboxLayout->addWidget(tabWidget);

        groupBox = new QGroupBox(TraceDisplay);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout2 = new QGridLayout(groupBox);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout2->addWidget(label_2, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem, 0, 1, 1, 1);

        sampleCountEdit = new QLineEdit(groupBox);
        sampleCountEdit->setObjectName(QString::fromUtf8("sampleCountEdit"));
        sampleCountEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(sampleCountEdit, 0, 2, 1, 1);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem1, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout2->addWidget(label_5, 0, 4, 1, 1);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem2, 0, 5, 1, 1);

        varianceEdit = new QLineEdit(groupBox);
        varianceEdit->setObjectName(QString::fromUtf8("varianceEdit"));
        varianceEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(varianceEdit, 0, 6, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout2->addWidget(label_3, 1, 0, 1, 1);

        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem3, 1, 1, 1, 1);

        averageSizeEdit = new QLineEdit(groupBox);
        averageSizeEdit->setObjectName(QString::fromUtf8("averageSizeEdit"));
        averageSizeEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(averageSizeEdit, 1, 2, 1, 1);

        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem4, 1, 3, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout2->addWidget(label_4, 1, 4, 1, 1);

        spacerItem5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem5, 1, 5, 1, 1);

        standardDeviationEdit = new QLineEdit(groupBox);
        standardDeviationEdit->setObjectName(QString::fromUtf8("standardDeviationEdit"));
        standardDeviationEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout2->addWidget(standardDeviationEdit, 1, 6, 1, 1);


        vboxLayout->addWidget(groupBox);


        retranslateUi(TraceDisplay);
        QObject::connect(upToSpin, SIGNAL(valueChanged(int)), upToSlider, SLOT(setValue(int)));
        QObject::connect(upToSlider, SIGNAL(sliderMoved(int)), upToSpin, SLOT(setValue(int)));
        QObject::connect(groupSlider, SIGNAL(valueChanged(int)), groupSpin, SLOT(setValue(int)));
        QObject::connect(groupSpin, SIGNAL(valueChanged(int)), groupSlider, SLOT(setValue(int)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TraceDisplay);
    } // setupUi

    void retranslateUi(QWidget *TraceDisplay)
    {
        TraceDisplay->setWindowTitle(QApplication::translate("TraceDisplay", "Form", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = valueTable->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TraceDisplay", "Sample #", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = valueTable->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TraceDisplay", "Size", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(widget), QApplication::translate("TraceDisplay", "Samples", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("TraceDisplay", "Group Count:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("TraceDisplay", "Histogram", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TraceDisplay", "Up to:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("TraceDisplay", "Autocorrelation", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TraceDisplay", "Significant values", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TraceDisplay", "Sample count:", 0, QApplication::UnicodeUTF8));
        sampleCountEdit->setText(QApplication::translate("TraceDisplay", "-", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("TraceDisplay", "Variance:", 0, QApplication::UnicodeUTF8));
        varianceEdit->setText(QApplication::translate("TraceDisplay", "-", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TraceDisplay", "Average Size:", 0, QApplication::UnicodeUTF8));
        averageSizeEdit->setStyleSheet(QApplication::translate("TraceDisplay", "background-color: #ccccee;", 0, QApplication::UnicodeUTF8));
        averageSizeEdit->setText(QApplication::translate("TraceDisplay", "-", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("TraceDisplay", "Standard Deviation:", 0, QApplication::UnicodeUTF8));
        standardDeviationEdit->setStyleSheet(QApplication::translate("TraceDisplay", "background-color: #cceecc", 0, QApplication::UnicodeUTF8));
        standardDeviationEdit->setText(QApplication::translate("TraceDisplay", "-", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TraceDisplay: public Ui_TraceDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACEDISPLAY_H
