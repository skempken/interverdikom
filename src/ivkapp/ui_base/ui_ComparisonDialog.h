/********************************************************************************
** Form generated from reading UI file 'ComparisonDialog.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPARISONDIALOG_H
#define UI_COMPARISONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QSplitter>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComparisonDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QStackedWidget *stackedWidget1;
    QWidget *page;
    QWidget *page_2;
    QStackedWidget *stackedWidget2;
    QWidget *page_3;
    QWidget *page_4;

    void setupUi(QDialog *ComparisonDialog)
    {
        if (ComparisonDialog->objectName().isEmpty())
            ComparisonDialog->setObjectName(QString::fromUtf8("ComparisonDialog"));
        ComparisonDialog->resize(926, 638);
        verticalLayout = new QVBoxLayout(ComparisonDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(ComparisonDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        stackedWidget1 = new QStackedWidget(splitter);
        stackedWidget1->setObjectName(QString::fromUtf8("stackedWidget1"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget1->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget1->addWidget(page_2);
        splitter->addWidget(stackedWidget1);
        stackedWidget2 = new QStackedWidget(splitter);
        stackedWidget2->setObjectName(QString::fromUtf8("stackedWidget2"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        stackedWidget2->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        stackedWidget2->addWidget(page_4);
        splitter->addWidget(stackedWidget2);

        verticalLayout->addWidget(splitter);


        retranslateUi(ComparisonDialog);

        QMetaObject::connectSlotsByName(ComparisonDialog);
    } // setupUi

    void retranslateUi(QDialog *ComparisonDialog)
    {
        ComparisonDialog->setWindowTitle(QApplication::translate("ComparisonDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ComparisonDialog: public Ui_ComparisonDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPARISONDIALOG_H
