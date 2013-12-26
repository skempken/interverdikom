/********************************************************************************
** Form generated from reading UI file 'PFResultWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PFRESULTWIDGET_H
#define UI_PFRESULTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "IvkTableWidget.h"
#include "widget/IvkPlot.h"

QT_BEGIN_NAMESPACE

class Ui_PFResultWidget
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *vboxLayout1;
    IvkPlot *plot;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout2;
    IvkTableWidget *table;

    void setupUi(QWidget *PFResultWidget)
    {
        if (PFResultWidget->objectName().isEmpty())
            PFResultWidget->setObjectName(QString::fromUtf8("PFResultWidget"));
        PFResultWidget->resize(983, 751);
        vboxLayout = new QVBoxLayout(PFResultWidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        tabWidget = new QTabWidget(PFResultWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        vboxLayout1 = new QVBoxLayout(tab);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        plot = new IvkPlot(tab);
        plot->setObjectName(QString::fromUtf8("plot"));

        vboxLayout1->addWidget(plot);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        vboxLayout2 = new QVBoxLayout(tab_2);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        table = new IvkTableWidget(tab_2);
        if (table->columnCount() < 1)
            table->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        table->setObjectName(QString::fromUtf8("table"));

        vboxLayout2->addWidget(table);

        tabWidget->addTab(tab_2, QString());

        vboxLayout->addWidget(tabWidget);


        retranslateUi(PFResultWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PFResultWidget);
    } // setupUi

    void retranslateUi(QWidget *PFResultWidget)
    {
        PFResultWidget->setWindowTitle(QApplication::translate("PFResultWidget", "Form", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("PFResultWidget", "Eigenvalue Graph", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PFResultWidget", "Eigenvalue", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("PFResultWidget", "Table", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PFResultWidget: public Ui_PFResultWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PFRESULTWIDGET_H
