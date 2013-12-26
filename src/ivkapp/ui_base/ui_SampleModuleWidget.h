/********************************************************************************
** Form generated from reading UI file 'SampleModuleWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAMPLEMODULEWIDGET_H
#define UI_SAMPLEMODULEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "IvkPlot.h"
#include "IvkTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SampleModuleWidget
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *vboxLayout2;
    QLabel *sampleLabel;
    QTextEdit *textEdit;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout3;
    QVBoxLayout *vboxLayout4;
    QLabel *label;
    IvkTableWidget *tableWidget;
    QWidget *tab_3;
    QVBoxLayout *vboxLayout5;
    QVBoxLayout *vboxLayout6;
    QLabel *asdfg;
    IvkPlot *plotWidget;
    QWidget *widget;
    QVBoxLayout *vboxLayout7;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QVBoxLayout *vboxLayout8;
    QTextEdit *textEdit_2;
    QWidget *tab_5;
    QVBoxLayout *vboxLayout9;
    IvkTableWidget *linkDemoTable;
    IvkPlot *linkDemoPlot;
    QWidget *tab_6;
    QVBoxLayout *vboxLayout10;
    QSpacerItem *spacerItem;
    QLabel *label_2;
    QSpacerItem *spacerItem1;
    QProgressBar *computationProgressBar;
    QPushButton *computeButton;
    QLabel *computationTextLabel;
    QSpacerItem *spacerItem2;
    QWidget *tab_7;
    QVBoxLayout *vboxLayout11;
    QLabel *label_3;
    QSpacerItem *spacerItem3;

    void setupUi(QWidget *SampleModuleWidget)
    {
        if (SampleModuleWidget->objectName().isEmpty())
            SampleModuleWidget->setObjectName(QString::fromUtf8("SampleModuleWidget"));
        SampleModuleWidget->resize(556, 419);
        SampleModuleWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
        vboxLayout = new QVBoxLayout(SampleModuleWidget);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        tabWidget = new QTabWidget(SampleModuleWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        vboxLayout1 = new QVBoxLayout(tab);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout2 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
#endif
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        sampleLabel = new QLabel(tab);
        sampleLabel->setObjectName(QString::fromUtf8("sampleLabel"));

        vboxLayout2->addWidget(sampleLabel);

        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setReadOnly(true);

        vboxLayout2->addWidget(textEdit);


        vboxLayout1->addLayout(vboxLayout2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        vboxLayout3 = new QVBoxLayout(tab_2);
#ifndef Q_OS_MAC
        vboxLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout3->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        vboxLayout4 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout4->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout4->setContentsMargins(0, 0, 0, 0);
#endif
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        vboxLayout4->addWidget(label);

        tableWidget = new IvkTableWidget(tab_2);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem8);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setRowCount(3);
        tableWidget->setColumnCount(3);

        vboxLayout4->addWidget(tableWidget);


        vboxLayout3->addLayout(vboxLayout4);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        vboxLayout5 = new QVBoxLayout(tab_3);
#ifndef Q_OS_MAC
        vboxLayout5->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout5->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        vboxLayout6 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout6->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout6->setContentsMargins(0, 0, 0, 0);
#endif
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        asdfg = new QLabel(tab_3);
        asdfg->setObjectName(QString::fromUtf8("asdfg"));
        asdfg->setWordWrap(true);

        vboxLayout6->addWidget(asdfg);

        plotWidget = new IvkPlot(tab_3);
        plotWidget->setObjectName(QString::fromUtf8("plotWidget"));

        vboxLayout6->addWidget(plotWidget);


        vboxLayout5->addLayout(vboxLayout6);

        tabWidget->addTab(tab_3, QString());
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        vboxLayout7 = new QVBoxLayout(widget);
#ifndef Q_OS_MAC
        vboxLayout7->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout7->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
        tabWidget_2 = new QTabWidget(widget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        vboxLayout8 = new QVBoxLayout(tab_4);
#ifndef Q_OS_MAC
        vboxLayout8->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout8->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout8->setObjectName(QString::fromUtf8("vboxLayout8"));
        textEdit_2 = new QTextEdit(tab_4);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));

        vboxLayout8->addWidget(textEdit_2);

        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        vboxLayout9 = new QVBoxLayout(tab_5);
#ifndef Q_OS_MAC
        vboxLayout9->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout9->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout9->setObjectName(QString::fromUtf8("vboxLayout9"));
        linkDemoTable = new IvkTableWidget(tab_5);
        if (linkDemoTable->columnCount() < 3)
            linkDemoTable->setColumnCount(3);
        if (linkDemoTable->rowCount() < 5)
            linkDemoTable->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        linkDemoTable->setItem(0, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        linkDemoTable->setItem(0, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        linkDemoTable->setItem(0, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        linkDemoTable->setItem(1, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        linkDemoTable->setItem(1, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        linkDemoTable->setItem(1, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        linkDemoTable->setItem(2, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        linkDemoTable->setItem(2, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        linkDemoTable->setItem(2, 2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        linkDemoTable->setItem(3, 0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        linkDemoTable->setItem(3, 1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        linkDemoTable->setItem(3, 2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        linkDemoTable->setItem(4, 0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        linkDemoTable->setItem(4, 1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        linkDemoTable->setItem(4, 2, __qtablewidgetitem23);
        linkDemoTable->setObjectName(QString::fromUtf8("linkDemoTable"));
        linkDemoTable->setRowCount(5);
        linkDemoTable->setColumnCount(3);

        vboxLayout9->addWidget(linkDemoTable);

        linkDemoPlot = new IvkPlot(tab_5);
        linkDemoPlot->setObjectName(QString::fromUtf8("linkDemoPlot"));
        linkDemoPlot->setMinimumSize(QSize(100, 100));

        vboxLayout9->addWidget(linkDemoPlot);

        tabWidget_2->addTab(tab_5, QString());

        vboxLayout7->addWidget(tabWidget_2);

        tabWidget->addTab(widget, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        vboxLayout10 = new QVBoxLayout(tab_6);
#ifndef Q_OS_MAC
        vboxLayout10->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout10->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout10->setObjectName(QString::fromUtf8("vboxLayout10"));
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        vboxLayout10->addItem(spacerItem);

        label_2 = new QLabel(tab_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        vboxLayout10->addWidget(label_2);

        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        vboxLayout10->addItem(spacerItem1);

        computationProgressBar = new QProgressBar(tab_6);
        computationProgressBar->setObjectName(QString::fromUtf8("computationProgressBar"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(computationProgressBar->sizePolicy().hasHeightForWidth());
        computationProgressBar->setSizePolicy(sizePolicy);
        computationProgressBar->setValue(0);
        computationProgressBar->setOrientation(Qt::Horizontal);

        vboxLayout10->addWidget(computationProgressBar);

        computeButton = new QPushButton(tab_6);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(0));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(computeButton->sizePolicy().hasHeightForWidth());
        computeButton->setSizePolicy(sizePolicy1);

        vboxLayout10->addWidget(computeButton);

        computationTextLabel = new QLabel(tab_6);
        computationTextLabel->setObjectName(QString::fromUtf8("computationTextLabel"));
        computationTextLabel->setAlignment(Qt::AlignCenter);

        vboxLayout10->addWidget(computationTextLabel);

        spacerItem2 = new QSpacerItem(514, 131, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout10->addItem(spacerItem2);

        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        vboxLayout11 = new QVBoxLayout(tab_7);
#ifndef Q_OS_MAC
        vboxLayout11->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout11->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout11->setObjectName(QString::fromUtf8("vboxLayout11"));
        label_3 = new QLabel(tab_7);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        vboxLayout11->addWidget(label_3);

        spacerItem3 = new QSpacerItem(20, 231, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout11->addItem(spacerItem3);

        tabWidget->addTab(tab_7, QString());

        vboxLayout->addWidget(tabWidget);


        retranslateUi(SampleModuleWidget);

        tabWidget->setCurrentIndex(5);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SampleModuleWidget);
    } // setupUi

    void retranslateUi(QWidget *SampleModuleWidget)
    {
        SampleModuleWidget->setWindowTitle(QApplication::translate("SampleModuleWidget", "Sample Widget", 0, QApplication::UnicodeUTF8));
        sampleLabel->setText(QApplication::translate("SampleModuleWidget", "I am a sample widget. Create similar widgets like this:", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("SampleModuleWidget", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">1)</span> Create widget with QT designer and save to /src/gui/ui_xml.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">2) </span>Create subclass in /src/gui which inherits from Ui::ClassName and QWidget (see implementation of SampleModuleWidget).</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; m"
                        "argin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">3)</span> Add setupUi(this) to the constructor to initialize the widget contents.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">4)</span> Write your code for the widget.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">5)</span> Construct the widget and pass it to"
                        " ModuleManager::addModule() in MainWindow::setupModules().</p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SampleModuleWidget", "General", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SampleModuleWidget", "In the designer, promote normal QTableWidgets to IvkTableWidgets with header IvkTableWidget.h\" to get an exportable table like this:", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = tableWidget->item(0, 0);
        ___qtablewidgetitem->setText(QApplication::translate("SampleModuleWidget", "oppp", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->item(0, 1);
        ___qtablewidgetitem1->setText(QApplication::translate("SampleModuleWidget", "tz", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->item(0, 2);
        ___qtablewidgetitem2->setText(QApplication::translate("SampleModuleWidget", "gh", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(1, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("SampleModuleWidget", "ijkl", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(1, 1);
        ___qtablewidgetitem4->setText(QApplication::translate("SampleModuleWidget", "dffdsgsdfg", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(1, 2);
        ___qtablewidgetitem5->setText(QApplication::translate("SampleModuleWidget", "32423", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(2, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("SampleModuleWidget", "afdyxc", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(2, 1);
        ___qtablewidgetitem7->setText(QApplication::translate("SampleModuleWidget", "sdfgvcx", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(2, 2);
        ___qtablewidgetitem8->setText(QApplication::translate("SampleModuleWidget", "324", 0, QApplication::UnicodeUTF8));
        tableWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SampleModuleWidget", "Table", 0, QApplication::UnicodeUTF8));
        asdfg->setText(QApplication::translate("SampleModuleWidget", "In the designer, promote a normal \"Widget\" to an IvkPlot widget with header \"IvkPlot.h\" to get a custom plot widget like this:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("SampleModuleWidget", "Plot", 0, QApplication::UnicodeUTF8));
        textEdit_2->setHtml(QApplication::translate("SampleModuleWidget", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">(see SampleModuleWidget::setupTablePlotLink() for the demonstration code)</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">1)</span> Create the table and plot widgets you want to link and make sure you have pointer access to them.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-r"
                        "ight:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">2)</span> Call <span style=\" font-weight:600;\">pointerTable-&gt;attachPlot(pointerPlot)</span>. As of now, one table can only have one attached plot.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">3) </span>Specify which informat"
                        "ion should be exported to the Plot. You do this by calling <span style=\" font-weight:600;\">pointerTable-&gt;addAttachedPlotCurve()</span> and passing two <span style=\" font-weight:600;\">TablePlotLink</span> objects. The first one specifies what should be used as the x coordinates, the second one specifies the values for the y coordinates.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">TablePlotLink</span> objects are <span style=\" font-weight:600;\">constructed with 2 parameters:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-in"
                        "dent:0; text-indent:0px;\">The <span style=\" font-weight:600;\">first parameter</span> specifies which <span style=\" font-weight:600;\">kind of information</span> to use and can be one of <span style=\" font-weight:600;\">TablePlotLink::colIndex</span>, <span style=\" font-weight:600;\">TablePlotLink::colValues</span>, <span style=\" font-weight:600;\">TablePlotLink::rowIndex</span> or <span style=\" font-weight:600;\">TablePlotLink::rowValues</span>.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The <span style=\" font-weight:600;\">second parameter</span> offers <span style=\" font-weight:600;\">additional settings</span>:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- If you are using <spa"
                        "n style=\" font-weight:600;\">row or column indices:</span> It is <span style=\" font-weight:600;\">optional</span> and gives a <span style=\" font-weight:600;\">factor</span> by which to multiply the indices.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- If you are using<span style=\" font-weight:600;\"> row or column values:</span> It is <span style=\" font-weight:600;\">required</span> and gives the <span style=\" font-weight:600;\">row or column ID</span> from which the values should be taken.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\""
                        "><span style=\" font-weight:600;\">4)</span> Update the plot by manually calling <span style=\" font-weight:600;\">tablePointer-&gt;updatePlot()</span>, by connecting signals to the <span style=\" font-weight:600;\">table's updatePlot()</span> <span style=\" font-weight:600;\">slot</span> or by enabling auto update when the table contents change with a call of <span style=\" font-weight:600;\">tablePointer-&gt;setAutoUpdatePlot(true)</span>.</p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("SampleModuleWidget", "Howto", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = linkDemoTable->isSortingEnabled();
        linkDemoTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem9 = linkDemoTable->item(0, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("SampleModuleWidget", "123", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = linkDemoTable->item(0, 1);
        ___qtablewidgetitem10->setText(QApplication::translate("SampleModuleWidget", "234", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = linkDemoTable->item(0, 2);
        ___qtablewidgetitem11->setText(QApplication::translate("SampleModuleWidget", "314", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = linkDemoTable->item(1, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("SampleModuleWidget", "345", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = linkDemoTable->item(1, 1);
        ___qtablewidgetitem13->setText(QApplication::translate("SampleModuleWidget", "546", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = linkDemoTable->item(1, 2);
        ___qtablewidgetitem14->setText(QApplication::translate("SampleModuleWidget", "253", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = linkDemoTable->item(2, 0);
        ___qtablewidgetitem15->setText(QApplication::translate("SampleModuleWidget", "165", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = linkDemoTable->item(2, 1);
        ___qtablewidgetitem16->setText(QApplication::translate("SampleModuleWidget", "265", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = linkDemoTable->item(2, 2);
        ___qtablewidgetitem17->setText(QApplication::translate("SampleModuleWidget", "467", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = linkDemoTable->item(3, 0);
        ___qtablewidgetitem18->setText(QApplication::translate("SampleModuleWidget", "346", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = linkDemoTable->item(3, 1);
        ___qtablewidgetitem19->setText(QApplication::translate("SampleModuleWidget", "412", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = linkDemoTable->item(3, 2);
        ___qtablewidgetitem20->setText(QApplication::translate("SampleModuleWidget", "235", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = linkDemoTable->item(4, 0);
        ___qtablewidgetitem21->setText(QApplication::translate("SampleModuleWidget", "132", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = linkDemoTable->item(4, 1);
        ___qtablewidgetitem22->setText(QApplication::translate("SampleModuleWidget", "698", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = linkDemoTable->item(4, 2);
        ___qtablewidgetitem23->setText(QApplication::translate("SampleModuleWidget", "287", 0, QApplication::UnicodeUTF8));
        linkDemoTable->setSortingEnabled(__sortingEnabled1);

        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("SampleModuleWidget", "Example", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(widget), QApplication::translate("SampleModuleWidget", "Table -> Plot", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SampleModuleWidget", "Please see  SampleModuleWidget::setupDemoComputationThread() and the definition of SampleComputation for the implementation details.", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("SampleModuleWidget", "Compute!", 0, QApplication::UnicodeUTF8));
        computationTextLabel->setText(QApplication::translate("SampleModuleWidget", "Waiting for task text...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("SampleModuleWidget", "Thread", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SampleModuleWidget", "TODO add description of XMLframework", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("SampleModuleWidget", "XML", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SampleModuleWidget: public Ui_SampleModuleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAMPLEMODULEWIDGET_H
