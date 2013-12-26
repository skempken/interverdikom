/********************************************************************************
** Form generated from reading UI file 'WorkloadDistributionWidget.ui'
**
** Created: Thu Dec 26 15:32:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKLOADDISTRIBUTIONWIDGET_H
#define UI_WORKLOADDISTRIBUTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "IvkPlot.h"

QT_BEGIN_NAMESPACE

class Ui_WorkloadDistributionWidget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *distGraphTab;
    QVBoxLayout *vboxLayout;
    QSplitter *splitter_2;
    IvkPlot *distGraph;
    QWidget *distTableTab;
    QGridLayout *gridLayout1;
    QTableWidget *distTable;

    void setupUi(QWidget *WorkloadDistributionWidget)
    {
        if (WorkloadDistributionWidget->objectName().isEmpty())
            WorkloadDistributionWidget->setObjectName(QString::fromUtf8("WorkloadDistributionWidget"));
        WorkloadDistributionWidget->resize(552, 532);
        gridLayout = new QGridLayout(WorkloadDistributionWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(WorkloadDistributionWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        distGraphTab = new QWidget();
        distGraphTab->setObjectName(QString::fromUtf8("distGraphTab"));
        vboxLayout = new QVBoxLayout(distGraphTab);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        splitter_2 = new QSplitter(distGraphTab);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        distGraph = new IvkPlot(splitter_2);
        distGraph->setObjectName(QString::fromUtf8("distGraph"));
        splitter_2->addWidget(distGraph);

        vboxLayout->addWidget(splitter_2);

        tabWidget->addTab(distGraphTab, QString());
        distTableTab = new QWidget();
        distTableTab->setObjectName(QString::fromUtf8("distTableTab"));
        gridLayout1 = new QGridLayout(distTableTab);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        distTable = new QTableWidget(distTableTab);
        if (distTable->columnCount() < 1)
            distTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        distTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        distTable->setObjectName(QString::fromUtf8("distTable"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(distTable->sizePolicy().hasHeightForWidth());
        distTable->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(8);
        distTable->setFont(font);

        gridLayout1->addWidget(distTable, 0, 0, 1, 1);

        tabWidget->addTab(distTableTab, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 2);


        retranslateUi(WorkloadDistributionWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WorkloadDistributionWidget);
    } // setupUi

    void retranslateUi(QWidget *WorkloadDistributionWidget)
    {
        WorkloadDistributionWidget->setWindowTitle(QApplication::translate("WorkloadDistributionWidget", "Form", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(distGraphTab), QApplication::translate("WorkloadDistributionWidget", "Distribution Graph", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = distTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("WorkloadDistributionWidget", "values", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(distTableTab), QApplication::translate("WorkloadDistributionWidget", "Distribution Table", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WorkloadDistributionWidget: public Ui_WorkloadDistributionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKLOADDISTRIBUTIONWIDGET_H
