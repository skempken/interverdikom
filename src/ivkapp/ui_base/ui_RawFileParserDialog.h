/********************************************************************************
** Form generated from reading UI file 'RawFileParserDialog.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAWFILEPARSERDIALOG_H
#define UI_RAWFILEPARSERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RawFileParserDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *inputFileEdit;
    QPushButton *inputFileBrowseButton;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *vboxLayout1;
    QCheckBox *outputVideoCheck;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem;
    QLineEdit *outputVideoEdit;
    QPushButton *outputVideoBrowseButton;
    QCheckBox *outputAudioCheck;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem1;
    QLineEdit *outputAudioEdit;
    QPushButton *outputAudioBrowseButton;
    QGroupBox *groupBox_3;
    QVBoxLayout *vboxLayout2;
    QCheckBox *timeIndexCheck;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout3;
    QProgressBar *parseProgressBar;
    QPushButton *cancelButton;
    QPushButton *parseButton;

    void setupUi(QDialog *RawFileParserDialog)
    {
        if (RawFileParserDialog->objectName().isEmpty())
            RawFileParserDialog->setObjectName(QString::fromUtf8("RawFileParserDialog"));
        RawFileParserDialog->setWindowModality(Qt::WindowModal);
        RawFileParserDialog->resize(642, 369);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RawFileParserDialog->sizePolicy().hasHeightForWidth());
        RawFileParserDialog->setSizePolicy(sizePolicy);
        RawFileParserDialog->setModal(true);
        vboxLayout = new QVBoxLayout(RawFileParserDialog);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBox = new QGroupBox(RawFileParserDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 60));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 601, 28));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        inputFileEdit = new QLineEdit(layoutWidget);
        inputFileEdit->setObjectName(QString::fromUtf8("inputFileEdit"));

        hboxLayout->addWidget(inputFileEdit);

        inputFileBrowseButton = new QPushButton(layoutWidget);
        inputFileBrowseButton->setObjectName(QString::fromUtf8("inputFileBrowseButton"));

        hboxLayout->addWidget(inputFileBrowseButton);


        vboxLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(RawFileParserDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 150));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 21, 601, 122));
        vboxLayout1 = new QVBoxLayout(layoutWidget1);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        outputVideoCheck = new QCheckBox(layoutWidget1);
        outputVideoCheck->setObjectName(QString::fromUtf8("outputVideoCheck"));
        outputVideoCheck->setChecked(true);

        vboxLayout1->addWidget(outputVideoCheck);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);

        outputVideoEdit = new QLineEdit(layoutWidget1);
        outputVideoEdit->setObjectName(QString::fromUtf8("outputVideoEdit"));

        hboxLayout1->addWidget(outputVideoEdit);

        outputVideoBrowseButton = new QPushButton(layoutWidget1);
        outputVideoBrowseButton->setObjectName(QString::fromUtf8("outputVideoBrowseButton"));

        hboxLayout1->addWidget(outputVideoBrowseButton);


        vboxLayout1->addLayout(hboxLayout1);

        outputAudioCheck = new QCheckBox(layoutWidget1);
        outputAudioCheck->setObjectName(QString::fromUtf8("outputAudioCheck"));
        outputAudioCheck->setEnabled(true);

        vboxLayout1->addWidget(outputAudioCheck);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        spacerItem1 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem1);

        outputAudioEdit = new QLineEdit(layoutWidget1);
        outputAudioEdit->setObjectName(QString::fromUtf8("outputAudioEdit"));
        outputAudioEdit->setEnabled(false);

        hboxLayout2->addWidget(outputAudioEdit);

        outputAudioBrowseButton = new QPushButton(layoutWidget1);
        outputAudioBrowseButton->setObjectName(QString::fromUtf8("outputAudioBrowseButton"));
        outputAudioBrowseButton->setEnabled(false);

        hboxLayout2->addWidget(outputAudioBrowseButton);


        vboxLayout1->addLayout(hboxLayout2);


        vboxLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(RawFileParserDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        vboxLayout2 = new QVBoxLayout(groupBox_3);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        timeIndexCheck = new QCheckBox(groupBox_3);
        timeIndexCheck->setObjectName(QString::fromUtf8("timeIndexCheck"));

        vboxLayout2->addWidget(timeIndexCheck);


        vboxLayout->addWidget(groupBox_3);

        spacerItem2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        parseProgressBar = new QProgressBar(RawFileParserDialog);
        parseProgressBar->setObjectName(QString::fromUtf8("parseProgressBar"));
        parseProgressBar->setEnabled(true);
        parseProgressBar->setValue(0);
        parseProgressBar->setTextVisible(true);
        parseProgressBar->setOrientation(Qt::Horizontal);

        hboxLayout3->addWidget(parseProgressBar);

        cancelButton = new QPushButton(RawFileParserDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout3->addWidget(cancelButton);

        parseButton = new QPushButton(RawFileParserDialog);
        parseButton->setObjectName(QString::fromUtf8("parseButton"));
        parseButton->setMinimumSize(QSize(120, 0));

        hboxLayout3->addWidget(parseButton);


        vboxLayout->addLayout(hboxLayout3);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(inputFileEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(RawFileParserDialog);
        QObject::connect(outputVideoCheck, SIGNAL(toggled(bool)), outputVideoEdit, SLOT(setEnabled(bool)));
        QObject::connect(outputVideoCheck, SIGNAL(toggled(bool)), outputVideoBrowseButton, SLOT(setEnabled(bool)));
        QObject::connect(outputAudioCheck, SIGNAL(toggled(bool)), outputAudioEdit, SLOT(setEnabled(bool)));
        QObject::connect(outputAudioCheck, SIGNAL(toggled(bool)), outputAudioBrowseButton, SLOT(setEnabled(bool)));
        QObject::connect(cancelButton, SIGNAL(clicked()), RawFileParserDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(RawFileParserDialog);
    } // setupUi

    void retranslateUi(QDialog *RawFileParserDialog)
    {
        RawFileParserDialog->setWindowTitle(QApplication::translate("RawFileParserDialog", "Create trace", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RawFileParserDialog", "Input", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RawFileParserDialog", "Video File:", 0, QApplication::UnicodeUTF8));
        inputFileBrowseButton->setText(QApplication::translate("RawFileParserDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("RawFileParserDialog", "Output", 0, QApplication::UnicodeUTF8));
        outputVideoCheck->setText(QApplication::translate("RawFileParserDialog", "Trace video stream", 0, QApplication::UnicodeUTF8));
        outputVideoBrowseButton->setText(QApplication::translate("RawFileParserDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        outputAudioCheck->setText(QApplication::translate("RawFileParserDialog", "Trace audio stream", 0, QApplication::UnicodeUTF8));
        outputAudioBrowseButton->setText(QApplication::translate("RawFileParserDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("RawFileParserDialog", "Options", 0, QApplication::UnicodeUTF8));
        timeIndexCheck->setText(QApplication::translate("RawFileParserDialog", "Export time index", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("RawFileParserDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        parseButton->setText(QApplication::translate("RawFileParserDialog", "Parse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RawFileParserDialog: public Ui_RawFileParserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAWFILEPARSERDIALOG_H
