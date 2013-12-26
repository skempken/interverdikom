/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "LogTextField.h"
#include "NavigationPath.h"
#include "widget/ModuleList.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRaw_File_Parser;
    QAction *actionCreate_Model;
    QAction *actionOpen_Model;
    QAction *actionSave_model;
    QAction *actionSave_model_as;
    QAction *actionSave_Console_As;
    QAction *actionClear_Console;
    QAction *actionQuit;
    QAction *actionBatch_Process;
    QAction *actionAbout;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave1;
    QAction *actionSave_As1;
    QAction *actionImport_Video_File;
    QAction *actionImport_Trace;
    QAction *actionImport_Model;
    QAction *actionCreate_Trace_From_Video_File;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QComboBox *rootCombo;
    ModuleList *moduleSelect;
    QWidget *layoutWidget1;
    QVBoxLayout *vboxLayout2;
    NavigationPath *navigationPath;
    QLabel *moduleTitleLabel;
    QFrame *moduleContentFrame;
    QGridLayout *gridLayout;
    QStackedWidget *moduleContent;
    QWidget *welcomePage;
    QVBoxLayout *vboxLayout3;
    QLabel *label;
    QWidget *openedProjectFilePage;
    QVBoxLayout *vboxLayout4;
    QLabel *label_3;
    QWidget *newProjectFilePage;
    QVBoxLayout *vboxLayout5;
    QLabel *label_2;
    QWidget *allDeletedPage;
    QVBoxLayout *vboxLayout6;
    QLabel *label_4;
    LogTextField *outputConsole;
    QMenuBar *menuBar;
    QMenu *menuConsole;
    QMenu *menuHelp;
    QMenu *menuTools;
    QMenu *menuFile;
    QMenu *menuImport;
    QMenu *menuActions;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1040, 714);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(600, 500));
        actionRaw_File_Parser = new QAction(MainWindow);
        actionRaw_File_Parser->setObjectName(QString::fromUtf8("actionRaw_File_Parser"));
        actionCreate_Model = new QAction(MainWindow);
        actionCreate_Model->setObjectName(QString::fromUtf8("actionCreate_Model"));
        actionOpen_Model = new QAction(MainWindow);
        actionOpen_Model->setObjectName(QString::fromUtf8("actionOpen_Model"));
        actionSave_model = new QAction(MainWindow);
        actionSave_model->setObjectName(QString::fromUtf8("actionSave_model"));
        actionSave_model_as = new QAction(MainWindow);
        actionSave_model_as->setObjectName(QString::fromUtf8("actionSave_model_as"));
        actionSave_Console_As = new QAction(MainWindow);
        actionSave_Console_As->setObjectName(QString::fromUtf8("actionSave_Console_As"));
        actionClear_Console = new QAction(MainWindow);
        actionClear_Console->setObjectName(QString::fromUtf8("actionClear_Console"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionBatch_Process = new QAction(MainWindow);
        actionBatch_Process->setObjectName(QString::fromUtf8("actionBatch_Process"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave1 = new QAction(MainWindow);
        actionSave1->setObjectName(QString::fromUtf8("actionSave1"));
        actionSave1->setEnabled(false);
        actionSave_As1 = new QAction(MainWindow);
        actionSave_As1->setObjectName(QString::fromUtf8("actionSave_As1"));
        actionSave_As1->setEnabled(false);
        actionImport_Video_File = new QAction(MainWindow);
        actionImport_Video_File->setObjectName(QString::fromUtf8("actionImport_Video_File"));
        actionImport_Video_File->setEnabled(false);
        actionImport_Trace = new QAction(MainWindow);
        actionImport_Trace->setObjectName(QString::fromUtf8("actionImport_Trace"));
        actionImport_Trace->setEnabled(false);
        actionImport_Model = new QAction(MainWindow);
        actionImport_Model->setObjectName(QString::fromUtf8("actionImport_Model"));
        actionImport_Model->setEnabled(false);
        actionCreate_Trace_From_Video_File = new QAction(MainWindow);
        actionCreate_Trace_From_Video_File->setObjectName(QString::fromUtf8("actionCreate_Trace_From_Video_File"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(4);
        sizePolicy2.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy2);
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        vboxLayout1 = new QVBoxLayout(layoutWidget);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        rootCombo = new QComboBox(layoutWidget);
        rootCombo->setObjectName(QString::fromUtf8("rootCombo"));
        rootCombo->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(5);
        sizePolicy3.setHeightForWidth(rootCombo->sizePolicy().hasHeightForWidth());
        rootCombo->setSizePolicy(sizePolicy3);

        hboxLayout->addWidget(rootCombo);


        vboxLayout1->addLayout(hboxLayout);

        moduleSelect = new ModuleList(layoutWidget);
        moduleSelect->setObjectName(QString::fromUtf8("moduleSelect"));
        moduleSelect->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(moduleSelect->sizePolicy().hasHeightForWidth());
        moduleSelect->setSizePolicy(sizePolicy4);
        moduleSelect->setMinimumSize(QSize(100, 0));
        moduleSelect->setBaseSize(QSize(200, 0));
        moduleSelect->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        moduleSelect->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        moduleSelect->setRootIsDecorated(false);
        moduleSelect->setUniformRowHeights(true);
        moduleSelect->setItemsExpandable(true);
        moduleSelect->setAnimated(false);
        moduleSelect->setColumnCount(1);

        vboxLayout1->addWidget(moduleSelect);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        vboxLayout2 = new QVBoxLayout(layoutWidget1);
#ifndef Q_OS_MAC
        vboxLayout2->setSpacing(6);
#endif
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        navigationPath = new NavigationPath(layoutWidget1);
        navigationPath->setObjectName(QString::fromUtf8("navigationPath"));
        sizePolicy.setHeightForWidth(navigationPath->sizePolicy().hasHeightForWidth());
        navigationPath->setSizePolicy(sizePolicy);
        navigationPath->setMinimumSize(QSize(0, 20));

        vboxLayout2->addWidget(navigationPath);

        moduleTitleLabel = new QLabel(layoutWidget1);
        moduleTitleLabel->setObjectName(QString::fromUtf8("moduleTitleLabel"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(249);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(moduleTitleLabel->sizePolicy().hasHeightForWidth());
        moduleTitleLabel->setSizePolicy(sizePolicy5);
        moduleTitleLabel->setMinimumSize(QSize(100, 0));
        moduleTitleLabel->setStyleSheet(QString::fromUtf8("font:bold 20px;"));

        vboxLayout2->addWidget(moduleTitleLabel);

        moduleContentFrame = new QFrame(layoutWidget1);
        moduleContentFrame->setObjectName(QString::fromUtf8("moduleContentFrame"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(255);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(moduleContentFrame->sizePolicy().hasHeightForWidth());
        moduleContentFrame->setSizePolicy(sizePolicy6);
        moduleContentFrame->setMinimumSize(QSize(450, 16));
        moduleContentFrame->setBaseSize(QSize(0, 0));
        moduleContentFrame->setFrameShape(QFrame::StyledPanel);
        moduleContentFrame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(moduleContentFrame);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        moduleContent = new QStackedWidget(moduleContentFrame);
        moduleContent->setObjectName(QString::fromUtf8("moduleContent"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy7.setHorizontalStretch(5);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(moduleContent->sizePolicy().hasHeightForWidth());
        moduleContent->setSizePolicy(sizePolicy7);
        moduleContent->setFrameShape(QFrame::NoFrame);
        moduleContent->setFrameShadow(QFrame::Plain);
        moduleContent->setLineWidth(0);
        moduleContent->setMidLineWidth(0);
        welcomePage = new QWidget();
        welcomePage->setObjectName(QString::fromUtf8("welcomePage"));
        vboxLayout3 = new QVBoxLayout(welcomePage);
#ifndef Q_OS_MAC
        vboxLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout3->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        label = new QLabel(welcomePage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        vboxLayout3->addWidget(label);

        moduleContent->addWidget(welcomePage);
        openedProjectFilePage = new QWidget();
        openedProjectFilePage->setObjectName(QString::fromUtf8("openedProjectFilePage"));
        vboxLayout4 = new QVBoxLayout(openedProjectFilePage);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        label_3 = new QLabel(openedProjectFilePage);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(true);

        vboxLayout4->addWidget(label_3);

        moduleContent->addWidget(openedProjectFilePage);
        newProjectFilePage = new QWidget();
        newProjectFilePage->setObjectName(QString::fromUtf8("newProjectFilePage"));
        vboxLayout5 = new QVBoxLayout(newProjectFilePage);
#ifndef Q_OS_MAC
        vboxLayout5->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout5->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        label_2 = new QLabel(newProjectFilePage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        vboxLayout5->addWidget(label_2);

        moduleContent->addWidget(newProjectFilePage);
        allDeletedPage = new QWidget();
        allDeletedPage->setObjectName(QString::fromUtf8("allDeletedPage"));
        vboxLayout6 = new QVBoxLayout(allDeletedPage);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        label_4 = new QLabel(allDeletedPage);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        vboxLayout6->addWidget(label_4);

        moduleContent->addWidget(allDeletedPage);

        gridLayout->addWidget(moduleContent, 0, 0, 1, 1);


        vboxLayout2->addWidget(moduleContentFrame);

        splitter->addWidget(layoutWidget1);
        splitter_2->addWidget(splitter);
        outputConsole = new LogTextField(splitter_2);
        outputConsole->setObjectName(QString::fromUtf8("outputConsole"));
        QSizePolicy sizePolicy8(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(1);
        sizePolicy8.setHeightForWidth(outputConsole->sizePolicy().hasHeightForWidth());
        outputConsole->setSizePolicy(sizePolicy8);
        outputConsole->setMinimumSize(QSize(0, 0));
        outputConsole->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        outputConsole->setReadOnly(true);
        splitter_2->addWidget(outputConsole);

        vboxLayout->addWidget(splitter_2);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1040, 26));
        menuConsole = new QMenu(menuBar);
        menuConsole->setObjectName(QString::fromUtf8("menuConsole"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuImport = new QMenu(menuBar);
        menuImport->setObjectName(QString::fromUtf8("menuImport"));
        menuActions = new QMenu(menuBar);
        menuActions->setObjectName(QString::fromUtf8("menuActions"));
        menuActions->setEnabled(false);
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuActions->menuAction());
        menuBar->addAction(menuImport->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuConsole->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuConsole->addAction(actionSave_Console_As);
        menuConsole->addSeparator();
        menuConsole->addAction(actionClear_Console);
        menuHelp->addAction(actionAbout);
        menuTools->addAction(actionCreate_Trace_From_Video_File);
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuImport->addAction(actionImport_Video_File);
        menuImport->addAction(actionImport_Trace);
        menuImport->addAction(actionImport_Model);

        retranslateUi(MainWindow);

        moduleContent->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "InterVerdiKom [*]", 0, QApplication::UnicodeUTF8));
        actionRaw_File_Parser->setText(QApplication::translate("MainWindow", "Create Trace...", 0, QApplication::UnicodeUTF8));
        actionCreate_Model->setText(QApplication::translate("MainWindow", "Create Model...", 0, QApplication::UnicodeUTF8));
        actionCreate_Model->setIconText(QApplication::translate("MainWindow", "Create Model...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCreate_Model->setToolTip(QApplication::translate("MainWindow", "Create Model...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen_Model->setText(QApplication::translate("MainWindow", "Open Model...", 0, QApplication::UnicodeUTF8));
        actionSave_model->setText(QApplication::translate("MainWindow", "Save model", 0, QApplication::UnicodeUTF8));
        actionSave_model_as->setText(QApplication::translate("MainWindow", "Save model as...", 0, QApplication::UnicodeUTF8));
        actionSave_Console_As->setText(QApplication::translate("MainWindow", "Save As...", 0, QApplication::UnicodeUTF8));
        actionClear_Console->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionBatch_Process->setText(QApplication::translate("MainWindow", "Batch Process...", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About...", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As...", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open...", 0, QApplication::UnicodeUTF8));
        actionSave1->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_As1->setText(QApplication::translate("MainWindow", "Save As...", 0, QApplication::UnicodeUTF8));
        actionSave_As1->setShortcut(QString());
        actionImport_Video_File->setText(QApplication::translate("MainWindow", "Import Video File...", 0, QApplication::UnicodeUTF8));
        actionImport_Trace->setText(QApplication::translate("MainWindow", "Import Trace...", 0, QApplication::UnicodeUTF8));
        actionImport_Model->setText(QApplication::translate("MainWindow", "Import Model...", 0, QApplication::UnicodeUTF8));
        actionCreate_Trace_From_Video_File->setText(QApplication::translate("MainWindow", "Create Trace From Video File...", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = moduleSelect->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Modules", 0, QApplication::UnicodeUTF8));
        moduleTitleLabel->setText(QApplication::translate("MainWindow", "InterVerdiKom", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Welcome to InterVerdiKom!</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Please open or create a project file to start analyzing or importing data.</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">You just opened an existing project.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You can select a module from the tree view on the left to inspect data or perform various actions associated with the module.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You can also choose to import new data using the \"Import\" menu.</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">You just created a new project.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"><span style=\" font-weight:400;\">To proceed, import data by using the \"Import\" menu.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">All modules have been deleted.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        outputConsole->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#228b22;\">InterVerdiKom ready.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; color:#228b22;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        menuConsole->setTitle(QApplication::translate("MainWindow", "Console", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuImport->setTitle(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
        menuActions->setTitle(QApplication::translate("MainWindow", "Actions", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
