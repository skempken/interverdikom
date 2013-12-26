/********************************************************************************
** Form generated from reading UI file 'WHResultWidget.ui'
**
** Created: Thu Dec 26 15:32:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHRESULTWIDGET_H
#define UI_WHRESULTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WHResultWidget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *distGraphTab;
    QGridLayout *gridLayout1;
    QTableWidget *idleDist;
    QWidget *distTableTab;
    QGridLayout *gridLayout2;
    QTableWidget *phaseDist;

    void setupUi(QWidget *WHResultWidget)
    {
        if (WHResultWidget->objectName().isEmpty())
            WHResultWidget->setObjectName(QString::fromUtf8("WHResultWidget"));
        WHResultWidget->resize(544, 379);
        gridLayout = new QGridLayout(WHResultWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(WHResultWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setTabShape(QTabWidget::Rounded);
        distGraphTab = new QWidget();
        distGraphTab->setObjectName(QString::fromUtf8("distGraphTab"));
        gridLayout1 = new QGridLayout(distGraphTab);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        idleDist = new QTableWidget(distGraphTab);
        idleDist->setObjectName(QString::fromUtf8("idleDist"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(idleDist->sizePolicy().hasHeightForWidth());
        idleDist->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(8);
        idleDist->setFont(font);

        gridLayout1->addWidget(idleDist, 0, 0, 1, 1);

        tabWidget->addTab(distGraphTab, QString());
        distTableTab = new QWidget();
        distTableTab->setObjectName(QString::fromUtf8("distTableTab"));
        gridLayout2 = new QGridLayout(distTableTab);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        phaseDist = new QTableWidget(distTableTab);
        phaseDist->setObjectName(QString::fromUtf8("phaseDist"));
        sizePolicy.setHeightForWidth(phaseDist->sizePolicy().hasHeightForWidth());
        phaseDist->setSizePolicy(sizePolicy);
        phaseDist->setFont(font);

        gridLayout2->addWidget(phaseDist, 0, 0, 1, 1);

        tabWidget->addTab(distTableTab, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 2);


        retranslateUi(WHResultWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WHResultWidget);
    } // setupUi

    void retranslateUi(QWidget *WHResultWidget)
    {
        WHResultWidget->setWindowTitle(QApplication::translate("WHResultWidget", "Wiener-Hopf results", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(distGraphTab), QApplication::translate("WHResultWidget", "Idle Distribution", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(distTableTab), QApplication::translate("WHResultWidget", "Phase Distribution", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WHResultWidget: public Ui_WHResultWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHRESULTWIDGET_H
