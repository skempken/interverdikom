/********************************************************************************
** Form generated from reading UI file 'TraceCreationWidget.ui'
**
** Created: Thu Dec 26 15:32:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACECREATIONWIDGET_H
#define UI_TRACECREATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RawFileParserDialog
{
public:
    QVBoxLayout *vboxLayout;
    QCheckBox *outputVideoCheck;
    QCheckBox *outputAudioCheck;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout;
    QProgressBar *parseProgressBar;
    QPushButton *cancelButton;
    QPushButton *parseButton;

    void setupUi(QDialog *RawFileParserDialog)
    {
        if (RawFileParserDialog->objectName().isEmpty())
            RawFileParserDialog->setObjectName(QString::fromUtf8("RawFileParserDialog"));
        RawFileParserDialog->setWindowModality(Qt::WindowModal);
        RawFileParserDialog->resize(642, 281);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RawFileParserDialog->sizePolicy().hasHeightForWidth());
        RawFileParserDialog->setSizePolicy(sizePolicy);
        RawFileParserDialog->setModal(true);
        vboxLayout = new QVBoxLayout(RawFileParserDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        outputVideoCheck = new QCheckBox(RawFileParserDialog);
        outputVideoCheck->setObjectName(QString::fromUtf8("outputVideoCheck"));
        outputVideoCheck->setChecked(true);

        vboxLayout->addWidget(outputVideoCheck);

        outputAudioCheck = new QCheckBox(RawFileParserDialog);
        outputAudioCheck->setObjectName(QString::fromUtf8("outputAudioCheck"));
        outputAudioCheck->setEnabled(true);

        vboxLayout->addWidget(outputAudioCheck);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        parseProgressBar = new QProgressBar(RawFileParserDialog);
        parseProgressBar->setObjectName(QString::fromUtf8("parseProgressBar"));
        parseProgressBar->setEnabled(true);
        parseProgressBar->setValue(0);
        parseProgressBar->setTextVisible(true);
        parseProgressBar->setOrientation(Qt::Horizontal);

        hboxLayout->addWidget(parseProgressBar);

        cancelButton = new QPushButton(RawFileParserDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        parseButton = new QPushButton(RawFileParserDialog);
        parseButton->setObjectName(QString::fromUtf8("parseButton"));
        parseButton->setMinimumSize(QSize(120, 0));

        hboxLayout->addWidget(parseButton);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(RawFileParserDialog);
        QObject::connect(cancelButton, SIGNAL(clicked()), RawFileParserDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(RawFileParserDialog);
    } // setupUi

    void retranslateUi(QDialog *RawFileParserDialog)
    {
        RawFileParserDialog->setWindowTitle(QApplication::translate("RawFileParserDialog", "Create trace", 0, QApplication::UnicodeUTF8));
        outputVideoCheck->setText(QApplication::translate("RawFileParserDialog", "Trace video stream", 0, QApplication::UnicodeUTF8));
        outputAudioCheck->setText(QApplication::translate("RawFileParserDialog", "Trace audio stream", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("RawFileParserDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        parseButton->setText(QApplication::translate("RawFileParserDialog", "Parse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RawFileParserDialog: public Ui_RawFileParserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACECREATIONWIDGET_H
