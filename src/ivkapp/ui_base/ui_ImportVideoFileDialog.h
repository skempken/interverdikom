/********************************************************************************
** Form generated from reading UI file 'ImportVideoFileDialog.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTVIDEOFILEDIALOG_H
#define UI_IMPORTVIDEOFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ImportVideoFileDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QLineEdit *pathEdit;
    QPushButton *browseButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *vboxLayout2;
    QCheckBox *importVideoCheck;
    QCheckBox *importAudioCheck;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ImportVideoFileDialog)
    {
        if (ImportVideoFileDialog->objectName().isEmpty())
            ImportVideoFileDialog->setObjectName(QString::fromUtf8("ImportVideoFileDialog"));
        ImportVideoFileDialog->resize(428, 250);
        vboxLayout = new QVBoxLayout(ImportVideoFileDialog);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBox = new QGroupBox(ImportVideoFileDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        vboxLayout1 = new QVBoxLayout(groupBox);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        pathEdit = new QLineEdit(groupBox);
        pathEdit->setObjectName(QString::fromUtf8("pathEdit"));

        hboxLayout->addWidget(pathEdit);

        browseButton = new QPushButton(groupBox);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));

        hboxLayout->addWidget(browseButton);


        vboxLayout1->addLayout(hboxLayout);


        vboxLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(ImportVideoFileDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        vboxLayout2 = new QVBoxLayout(groupBox_2);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setContentsMargins(9, 9, 9, 9);
        importVideoCheck = new QCheckBox(groupBox_2);
        importVideoCheck->setObjectName(QString::fromUtf8("importVideoCheck"));
        importVideoCheck->setChecked(true);

        vboxLayout2->addWidget(importVideoCheck);

        importAudioCheck = new QCheckBox(groupBox_2);
        importAudioCheck->setObjectName(QString::fromUtf8("importAudioCheck"));

        vboxLayout2->addWidget(importAudioCheck);


        vboxLayout->addWidget(groupBox_2);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        buttonBox = new QDialogButtonBox(ImportVideoFileDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(ImportVideoFileDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ImportVideoFileDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ImportVideoFileDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImportVideoFileDialog);
    } // setupUi

    void retranslateUi(QDialog *ImportVideoFileDialog)
    {
        ImportVideoFileDialog->setWindowTitle(QApplication::translate("ImportVideoFileDialog", "Import Video File", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ImportVideoFileDialog", "File", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("ImportVideoFileDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ImportVideoFileDialog", "Options", 0, QApplication::UnicodeUTF8));
        importVideoCheck->setText(QApplication::translate("ImportVideoFileDialog", "Import video data", 0, QApplication::UnicodeUTF8));
        importAudioCheck->setText(QApplication::translate("ImportVideoFileDialog", "Import audio data", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImportVideoFileDialog: public Ui_ImportVideoFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTVIDEOFILEDIALOG_H
