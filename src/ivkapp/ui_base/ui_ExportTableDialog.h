/********************************************************************************
** Form generated from reading UI file 'ExportTableDialog.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTTABLEDIALOG_H
#define UI_EXPORTTABLEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExportTableDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *formatGroup;
    QVBoxLayout *vboxLayout1;
    QRadioButton *csvRadio;
    QRadioButton *matlabRadio;
    QGroupBox *pathGroup;
    QHBoxLayout *hboxLayout;
    QLineEdit *pathEdit;
    QPushButton *browseButton;
    QGroupBox *sdfdsf;
    QVBoxLayout *vboxLayout2;
    QRadioButton *exportAdditionalRowRadio;
    QHBoxLayout *hboxLayout1;
    QRadioButton *replaceLineBreakRadio;
    QLineEdit *replaceLineBreakEdit;
    QSpacerItem *spacerItem;
    QGroupBox *csvOptionsGroup;
    QVBoxLayout *vboxLayout3;
    QGridLayout *gridLayout;
    QLineEdit *columnSeparatorEdit;
    QLineEdit *rowSeparatorEdit;
    QLabel *rowSeparatorLabel;
    QLabel *columnSeparatorLabel;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;
    QCheckBox *horizontalHeadingsCheck;
    QCheckBox *verticalHeadingsCheck;
    QSpacerItem *spacerItem3;
    QHBoxLayout *hboxLayout2;
    QPushButton *closeButton;
    QPushButton *exportButton;

    void setupUi(QDialog *ExportTableDialog)
    {
        if (ExportTableDialog->objectName().isEmpty())
            ExportTableDialog->setObjectName(QString::fromUtf8("ExportTableDialog"));
        ExportTableDialog->resize(520, 473);
        vboxLayout = new QVBoxLayout(ExportTableDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        formatGroup = new QGroupBox(ExportTableDialog);
        formatGroup->setObjectName(QString::fromUtf8("formatGroup"));
        vboxLayout1 = new QVBoxLayout(formatGroup);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
        csvRadio = new QRadioButton(formatGroup);
        csvRadio->setObjectName(QString::fromUtf8("csvRadio"));

        vboxLayout1->addWidget(csvRadio);

        matlabRadio = new QRadioButton(formatGroup);
        matlabRadio->setObjectName(QString::fromUtf8("matlabRadio"));

        vboxLayout1->addWidget(matlabRadio);


        vboxLayout->addWidget(formatGroup);

        pathGroup = new QGroupBox(ExportTableDialog);
        pathGroup->setObjectName(QString::fromUtf8("pathGroup"));
        hboxLayout = new QHBoxLayout(pathGroup);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(9, 9, 9, 9);
        pathEdit = new QLineEdit(pathGroup);
        pathEdit->setObjectName(QString::fromUtf8("pathEdit"));
        pathEdit->setEnabled(false);

        hboxLayout->addWidget(pathEdit);

        browseButton = new QPushButton(pathGroup);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setEnabled(false);

        hboxLayout->addWidget(browseButton);


        vboxLayout->addWidget(pathGroup);

        sdfdsf = new QGroupBox(ExportTableDialog);
        sdfdsf->setObjectName(QString::fromUtf8("sdfdsf"));
        vboxLayout2 = new QVBoxLayout(sdfdsf);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setContentsMargins(9, 9, 9, 9);
        exportAdditionalRowRadio = new QRadioButton(sdfdsf);
        exportAdditionalRowRadio->setObjectName(QString::fromUtf8("exportAdditionalRowRadio"));
        exportAdditionalRowRadio->setChecked(true);

        vboxLayout2->addWidget(exportAdditionalRowRadio);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        replaceLineBreakRadio = new QRadioButton(sdfdsf);
        replaceLineBreakRadio->setObjectName(QString::fromUtf8("replaceLineBreakRadio"));

        hboxLayout1->addWidget(replaceLineBreakRadio);

        replaceLineBreakEdit = new QLineEdit(sdfdsf);
        replaceLineBreakEdit->setObjectName(QString::fromUtf8("replaceLineBreakEdit"));
        replaceLineBreakEdit->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(replaceLineBreakEdit->sizePolicy().hasHeightForWidth());
        replaceLineBreakEdit->setSizePolicy(sizePolicy);

        hboxLayout1->addWidget(replaceLineBreakEdit);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);


        vboxLayout2->addLayout(hboxLayout1);


        vboxLayout->addWidget(sdfdsf);

        csvOptionsGroup = new QGroupBox(ExportTableDialog);
        csvOptionsGroup->setObjectName(QString::fromUtf8("csvOptionsGroup"));
        vboxLayout3 = new QVBoxLayout(csvOptionsGroup);
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        vboxLayout3->setContentsMargins(9, 9, 9, 9);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        columnSeparatorEdit = new QLineEdit(csvOptionsGroup);
        columnSeparatorEdit->setObjectName(QString::fromUtf8("columnSeparatorEdit"));
        sizePolicy.setHeightForWidth(columnSeparatorEdit->sizePolicy().hasHeightForWidth());
        columnSeparatorEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(columnSeparatorEdit, 0, 2, 1, 1);

        rowSeparatorEdit = new QLineEdit(csvOptionsGroup);
        rowSeparatorEdit->setObjectName(QString::fromUtf8("rowSeparatorEdit"));
        sizePolicy.setHeightForWidth(rowSeparatorEdit->sizePolicy().hasHeightForWidth());
        rowSeparatorEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(rowSeparatorEdit, 1, 2, 1, 1);

        rowSeparatorLabel = new QLabel(csvOptionsGroup);
        rowSeparatorLabel->setObjectName(QString::fromUtf8("rowSeparatorLabel"));

        gridLayout->addWidget(rowSeparatorLabel, 1, 0, 1, 1);

        columnSeparatorLabel = new QLabel(csvOptionsGroup);
        columnSeparatorLabel->setObjectName(QString::fromUtf8("columnSeparatorLabel"));

        gridLayout->addWidget(columnSeparatorLabel, 0, 0, 1, 1);

        spacerItem1 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem1, 0, 1, 2, 1);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem2, 0, 3, 2, 1);

        horizontalHeadingsCheck = new QCheckBox(csvOptionsGroup);
        horizontalHeadingsCheck->setObjectName(QString::fromUtf8("horizontalHeadingsCheck"));
        horizontalHeadingsCheck->setChecked(true);

        gridLayout->addWidget(horizontalHeadingsCheck, 2, 0, 1, 4);

        verticalHeadingsCheck = new QCheckBox(csvOptionsGroup);
        verticalHeadingsCheck->setObjectName(QString::fromUtf8("verticalHeadingsCheck"));
        verticalHeadingsCheck->setChecked(true);

        gridLayout->addWidget(verticalHeadingsCheck, 3, 0, 1, 4);


        vboxLayout3->addLayout(gridLayout);


        vboxLayout->addWidget(csvOptionsGroup);

        spacerItem3 = new QSpacerItem(502, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem3);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        closeButton = new QPushButton(ExportTableDialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        hboxLayout2->addWidget(closeButton);

        exportButton = new QPushButton(ExportTableDialog);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setEnabled(false);

        hboxLayout2->addWidget(exportButton);


        vboxLayout->addLayout(hboxLayout2);


        retranslateUi(ExportTableDialog);
        QObject::connect(closeButton, SIGNAL(clicked()), ExportTableDialog, SLOT(close()));
        QObject::connect(csvRadio, SIGNAL(clicked(bool)), pathEdit, SLOT(setEnabled(bool)));
        QObject::connect(csvRadio, SIGNAL(clicked(bool)), browseButton, SLOT(setEnabled(bool)));
        QObject::connect(matlabRadio, SIGNAL(clicked(bool)), pathEdit, SLOT(setEnabled(bool)));
        QObject::connect(matlabRadio, SIGNAL(clicked(bool)), browseButton, SLOT(setEnabled(bool)));
        QObject::connect(replaceLineBreakRadio, SIGNAL(toggled(bool)), replaceLineBreakEdit, SLOT(setEnabled(bool)));
        QObject::connect(csvRadio, SIGNAL(clicked(bool)), exportButton, SLOT(setEnabled(bool)));
        QObject::connect(pathGroup, SIGNAL(clicked(bool)), exportButton, SLOT(setEnabled(bool)));
        QObject::connect(csvRadio, SIGNAL(toggled(bool)), csvOptionsGroup, SLOT(setShown(bool)));

        QMetaObject::connectSlotsByName(ExportTableDialog);
    } // setupUi

    void retranslateUi(QDialog *ExportTableDialog)
    {
        ExportTableDialog->setWindowTitle(QApplication::translate("ExportTableDialog", "Export Options", 0, QApplication::UnicodeUTF8));
        formatGroup->setTitle(QApplication::translate("ExportTableDialog", "Format", 0, QApplication::UnicodeUTF8));
        csvRadio->setText(QApplication::translate("ExportTableDialog", "Comma-seperated values (CSV)", 0, QApplication::UnicodeUTF8));
        matlabRadio->setText(QApplication::translate("ExportTableDialog", "MATLAB format", 0, QApplication::UnicodeUTF8));
        pathGroup->setTitle(QApplication::translate("ExportTableDialog", "Path", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("ExportTableDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        sdfdsf->setTitle(QApplication::translate("ExportTableDialog", "Multi-line cells", 0, QApplication::UnicodeUTF8));
        exportAdditionalRowRadio->setText(QApplication::translate("ExportTableDialog", "Export additional row(s) when a cell contains a line break", 0, QApplication::UnicodeUTF8));
        replaceLineBreakRadio->setText(QApplication::translate("ExportTableDialog", "Replace the line break with", 0, QApplication::UnicodeUTF8));
        replaceLineBreakEdit->setText(QApplication::translate("ExportTableDialog", " // ", 0, QApplication::UnicodeUTF8));
        csvOptionsGroup->setTitle(QApplication::translate("ExportTableDialog", "CSV Options", 0, QApplication::UnicodeUTF8));
        columnSeparatorEdit->setText(QApplication::translate("ExportTableDialog", ";", 0, QApplication::UnicodeUTF8));
        rowSeparatorEdit->setText(QApplication::translate("ExportTableDialog", "\\n", 0, QApplication::UnicodeUTF8));
        rowSeparatorLabel->setText(QApplication::translate("ExportTableDialog", "Row separator:", 0, QApplication::UnicodeUTF8));
        columnSeparatorLabel->setText(QApplication::translate("ExportTableDialog", "Column separator:", 0, QApplication::UnicodeUTF8));
        horizontalHeadingsCheck->setText(QApplication::translate("ExportTableDialog", "Export horizontal table headings", 0, QApplication::UnicodeUTF8));
        verticalHeadingsCheck->setText(QApplication::translate("ExportTableDialog", "Export vertical table headings", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("ExportTableDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        exportButton->setText(QApplication::translate("ExportTableDialog", "Export", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportTableDialog: public Ui_ExportTableDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTTABLEDIALOG_H
