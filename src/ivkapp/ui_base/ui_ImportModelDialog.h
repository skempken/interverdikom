/********************************************************************************
** Form generated from reading UI file 'ImportModelDialog.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTMODELDIALOG_H
#define UI_IMPORTMODELDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ImportModelDialog
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
    QRadioButton *radioTimeslotted;
    QRadioButton *radioInterarrival;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ImportModelDialog)
    {
        if (ImportModelDialog->objectName().isEmpty())
            ImportModelDialog->setObjectName(QString::fromUtf8("ImportModelDialog"));
        ImportModelDialog->resize(493, 221);
        vboxLayout = new QVBoxLayout(ImportModelDialog);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBox = new QGroupBox(ImportModelDialog);
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

        groupBox_2 = new QGroupBox(ImportModelDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        vboxLayout2 = new QVBoxLayout(groupBox_2);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setContentsMargins(9, 9, 9, 9);
        radioTimeslotted = new QRadioButton(groupBox_2);
        radioTimeslotted->setObjectName(QString::fromUtf8("radioTimeslotted"));
        radioTimeslotted->setChecked(false);

        vboxLayout2->addWidget(radioTimeslotted);

        radioInterarrival = new QRadioButton(groupBox_2);
        radioInterarrival->setObjectName(QString::fromUtf8("radioInterarrival"));
        radioInterarrival->setChecked(true);

        vboxLayout2->addWidget(radioInterarrival);


        vboxLayout->addWidget(groupBox_2);

        buttonBox = new QDialogButtonBox(ImportModelDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(ImportModelDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ImportModelDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ImportModelDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImportModelDialog);
    } // setupUi

    void retranslateUi(QDialog *ImportModelDialog)
    {
        ImportModelDialog->setWindowTitle(QApplication::translate("ImportModelDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ImportModelDialog", "File", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("ImportModelDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ImportModelDialog", "Options", 0, QApplication::UnicodeUTF8));
        radioTimeslotted->setText(QApplication::translate("ImportModelDialog", "Time-Slotted System", 0, QApplication::UnicodeUTF8));
        radioInterarrival->setText(QApplication::translate("ImportModelDialog", "Interarrival and service times", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImportModelDialog: public Ui_ImportModelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTMODELDIALOG_H
