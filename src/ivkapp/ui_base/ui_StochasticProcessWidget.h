/********************************************************************************
** Form generated from reading UI file 'StochasticProcessWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCHASTICPROCESSWIDGET_H
#define UI_STOCHASTICPROCESSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "IvkPlot.h"
#include "IvkTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_StochasticProcessWidget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *distGraphTab;
    QVBoxLayout *vboxLayout;
    QSplitter *splitter;
    IvkPlot *distGraph;
    QTableWidget *distGraphTable;
    QWidget *distTableTab;
    QGridLayout *gridLayout1;
    IvkTableWidget *distTable;
    QWidget *quantileTab;
    QGridLayout *gridLayout2;
    IvkTableWidget *quantileTable;
    QLabel *label_2;
    QLineEdit *quantileEdit;
    QPushButton *addQuantileButton;
    QSpacerItem *spacerItem;
    QWidget *transitionTab;
    QVBoxLayout *vboxLayout1;
    IvkTableWidget *transitionTable;
    QWidget *autocorrelationTab;
    QGridLayout *gridLayout3;
    IvkPlot *autocorrelationPlot;
    QLabel *label;
    QSpinBox *upToSpin;
    QSlider *horizontalSlider;

    void setupUi(QWidget *StochasticProcessWidget)
    {
        if (StochasticProcessWidget->objectName().isEmpty())
            StochasticProcessWidget->setObjectName(QString::fromUtf8("StochasticProcessWidget"));
        StochasticProcessWidget->resize(508, 550);
        gridLayout = new QGridLayout(StochasticProcessWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        tabWidget = new QTabWidget(StochasticProcessWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        distGraphTab = new QWidget();
        distGraphTab->setObjectName(QString::fromUtf8("distGraphTab"));
        vboxLayout = new QVBoxLayout(distGraphTab);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        splitter = new QSplitter(distGraphTab);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        distGraph = new IvkPlot(splitter);
        distGraph->setObjectName(QString::fromUtf8("distGraph"));
        splitter->addWidget(distGraph);
        distGraphTable = new QTableWidget(splitter);
        if (distGraphTable->columnCount() < 1)
            distGraphTable->setColumnCount(1);
        if (distGraphTable->rowCount() < 6)
            distGraphTable->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        distGraphTable->setVerticalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        distGraphTable->setVerticalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        distGraphTable->setVerticalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        distGraphTable->setVerticalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        distGraphTable->setVerticalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        distGraphTable->setVerticalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        distGraphTable->setItem(0, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        distGraphTable->setItem(1, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        distGraphTable->setItem(2, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        distGraphTable->setItem(3, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        distGraphTable->setItem(5, 0, __qtablewidgetitem10);
        distGraphTable->setObjectName(QString::fromUtf8("distGraphTable"));
        splitter->addWidget(distGraphTable);

        vboxLayout->addWidget(splitter);

        tabWidget->addTab(distGraphTab, QString());
        distTableTab = new QWidget();
        distTableTab->setObjectName(QString::fromUtf8("distTableTab"));
        gridLayout1 = new QGridLayout(distTableTab);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setHorizontalSpacing(6);
        gridLayout1->setVerticalSpacing(6);
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        distTable = new IvkTableWidget(distTableTab);
        distTable->setObjectName(QString::fromUtf8("distTable"));

        gridLayout1->addWidget(distTable, 0, 0, 1, 1);

        tabWidget->addTab(distTableTab, QString());
        quantileTab = new QWidget();
        quantileTab->setObjectName(QString::fromUtf8("quantileTab"));
        gridLayout2 = new QGridLayout(quantileTab);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        quantileTable = new IvkTableWidget(quantileTab);
        if (quantileTable->columnCount() < 1)
            quantileTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        quantileTable->setHorizontalHeaderItem(0, __qtablewidgetitem11);
        quantileTable->setObjectName(QString::fromUtf8("quantileTable"));

        gridLayout2->addWidget(quantileTable, 0, 0, 1, 4);

        label_2 = new QLabel(quantileTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout2->addWidget(label_2, 1, 0, 1, 1);

        quantileEdit = new QLineEdit(quantileTab);
        quantileEdit->setObjectName(QString::fromUtf8("quantileEdit"));

        gridLayout2->addWidget(quantileEdit, 1, 1, 1, 1);

        addQuantileButton = new QPushButton(quantileTab);
        addQuantileButton->setObjectName(QString::fromUtf8("addQuantileButton"));

        gridLayout2->addWidget(addQuantileButton, 1, 2, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem, 1, 3, 1, 1);

        tabWidget->addTab(quantileTab, QString());
        transitionTab = new QWidget();
        transitionTab->setObjectName(QString::fromUtf8("transitionTab"));
        vboxLayout1 = new QVBoxLayout(transitionTab);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        transitionTable = new IvkTableWidget(transitionTab);
        transitionTable->setObjectName(QString::fromUtf8("transitionTable"));

        vboxLayout1->addWidget(transitionTable);

        tabWidget->addTab(transitionTab, QString());
        autocorrelationTab = new QWidget();
        autocorrelationTab->setObjectName(QString::fromUtf8("autocorrelationTab"));
        gridLayout3 = new QGridLayout(autocorrelationTab);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        autocorrelationPlot = new IvkPlot(autocorrelationTab);
        autocorrelationPlot->setObjectName(QString::fromUtf8("autocorrelationPlot"));

        gridLayout3->addWidget(autocorrelationPlot, 0, 0, 1, 3);

        label = new QLabel(autocorrelationTab);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout3->addWidget(label, 1, 0, 1, 1);

        upToSpin = new QSpinBox(autocorrelationTab);
        upToSpin->setObjectName(QString::fromUtf8("upToSpin"));

        gridLayout3->addWidget(upToSpin, 1, 1, 1, 1);

        horizontalSlider = new QSlider(autocorrelationTab);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout3->addWidget(horizontalSlider, 1, 2, 1, 1);

        tabWidget->addTab(autocorrelationTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(StochasticProcessWidget);
        QObject::connect(upToSpin, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));
        QObject::connect(horizontalSlider, SIGNAL(sliderMoved(int)), upToSpin, SLOT(setValue(int)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StochasticProcessWidget);
    } // setupUi

    void retranslateUi(QWidget *StochasticProcessWidget)
    {
        StochasticProcessWidget->setWindowTitle(QApplication::translate("StochasticProcessWidget", "Form", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = distGraphTable->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("StochasticProcessWidget", "State #", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = distGraphTable->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("StochasticProcessWidget", "Mean", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = distGraphTable->verticalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("StochasticProcessWidget", "StdDev", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = distGraphTable->verticalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("StochasticProcessWidget", "StatProb", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = distGraphTable->verticalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("StochasticProcessWidget", "Range", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = distGraphTable->isSortingEnabled();
        distGraphTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem5 = distGraphTable->item(0, 0);
        ___qtablewidgetitem5->setText(QApplication::translate("StochasticProcessWidget", "Show all", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = distGraphTable->item(1, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("StochasticProcessWidget", "Show all", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = distGraphTable->item(2, 0);
        ___qtablewidgetitem7->setText(QApplication::translate("StochasticProcessWidget", "Show all", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = distGraphTable->item(3, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("StochasticProcessWidget", "Scale", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = distGraphTable->item(5, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("StochasticProcessWidget", "Show all", 0, QApplication::UnicodeUTF8));
        distGraphTable->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(distGraphTab), QApplication::translate("StochasticProcessWidget", "Distribution Graph", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(distTableTab), QApplication::translate("StochasticProcessWidget", "Distribution Table", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = quantileTable->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("StochasticProcessWidget", "Limit", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("StochasticProcessWidget", "Limit:", 0, QApplication::UnicodeUTF8));
        quantileEdit->setText(QApplication::translate("StochasticProcessWidget", "0.1", 0, QApplication::UnicodeUTF8));
        addQuantileButton->setText(QApplication::translate("StochasticProcessWidget", "Calculate", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(quantileTab), QApplication::translate("StochasticProcessWidget", "Distribution Quantiles", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(transitionTab), QApplication::translate("StochasticProcessWidget", "Transitions", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StochasticProcessWidget", "Up To:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(autocorrelationTab), QApplication::translate("StochasticProcessWidget", "Autocorrelation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StochasticProcessWidget: public Ui_StochasticProcessWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCHASTICPROCESSWIDGET_H
