/********************************************************************************
** Form generated from reading UI file 'ExportGraphDialog.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTGRAPHDIALOG_H
#define UI_EXPORTGRAPHDIALOG_H

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
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExportGraphDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *outputFileGroup;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout;
    QLineEdit *pathEdit;
    QPushButton *browseButton;
    QLabel *outputFileNoteLabel;
    QGroupBox *sizeGroup;
    QVBoxLayout *vboxLayout3;
    QHBoxLayout *hboxLayout1;
    QLabel *widthLabel;
    QSpacerItem *spacerItem;
    QLineEdit *widthEdit;
    QSpacerItem *spacerItem1;
    QLabel *heightLabel;
    QSpacerItem *spacerItem2;
    QLineEdit *heightEdit;
    QSpacerItem *spacerItem3;
    QCheckBox *ratioCheck;
    QSpacerItem *spacerItem4;
    QHBoxLayout *hboxLayout2;
    QRadioButton *exportEntireGraphRadio;
    QSpacerItem *spacerItem5;
    QRadioButton *exportDisplayedAreaRadio;
    QSpacerItem *spacerItem6;
    QGroupBox *compressionGroup;
    QVBoxLayout *vboxLayout4;
    QVBoxLayout *vboxLayout5;
    QRadioButton *compressionAutoRadio;
    QRadioButton *compressionManualRadio;
    QSlider *compressionSlider;
    QHBoxLayout *hboxLayout3;
    QLabel *compressionSmallestSizeLabel;
    QSpacerItem *spacerItem7;
    QLabel *compressionBestQualityLabel;
    QSpacerItem *spacerItem8;
    QHBoxLayout *hboxLayout4;
    QPushButton *cancelButton;
    QPushButton *exportButton;

    void setupUi(QDialog *ExportGraphDialog)
    {
        if (ExportGraphDialog->objectName().isEmpty())
            ExportGraphDialog->setObjectName(QString::fromUtf8("ExportGraphDialog"));
        ExportGraphDialog->resize(557, 407);
        ExportGraphDialog->setModal(true);
        vboxLayout = new QVBoxLayout(ExportGraphDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        outputFileGroup = new QGroupBox(ExportGraphDialog);
        outputFileGroup->setObjectName(QString::fromUtf8("outputFileGroup"));
        vboxLayout1 = new QVBoxLayout(outputFileGroup);
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
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        pathEdit = new QLineEdit(outputFileGroup);
        pathEdit->setObjectName(QString::fromUtf8("pathEdit"));
        pathEdit->setEnabled(false);

        hboxLayout->addWidget(pathEdit);

        browseButton = new QPushButton(outputFileGroup);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));

        hboxLayout->addWidget(browseButton);


        vboxLayout2->addLayout(hboxLayout);

        outputFileNoteLabel = new QLabel(outputFileGroup);
        outputFileNoteLabel->setObjectName(QString::fromUtf8("outputFileNoteLabel"));

        vboxLayout2->addWidget(outputFileNoteLabel);


        vboxLayout1->addLayout(vboxLayout2);


        vboxLayout->addWidget(outputFileGroup);

        sizeGroup = new QGroupBox(ExportGraphDialog);
        sizeGroup->setObjectName(QString::fromUtf8("sizeGroup"));
        vboxLayout3 = new QVBoxLayout(sizeGroup);
#ifndef Q_OS_MAC
        vboxLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout3->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        widthLabel = new QLabel(sizeGroup);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));

        hboxLayout1->addWidget(widthLabel);

        spacerItem = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);

        widthEdit = new QLineEdit(sizeGroup);
        widthEdit->setObjectName(QString::fromUtf8("widthEdit"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widthEdit->sizePolicy().hasHeightForWidth());
        widthEdit->setSizePolicy(sizePolicy);

        hboxLayout1->addWidget(widthEdit);

        spacerItem1 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem1);

        heightLabel = new QLabel(sizeGroup);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));

        hboxLayout1->addWidget(heightLabel);

        spacerItem2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem2);

        heightEdit = new QLineEdit(sizeGroup);
        heightEdit->setObjectName(QString::fromUtf8("heightEdit"));
        sizePolicy.setHeightForWidth(heightEdit->sizePolicy().hasHeightForWidth());
        heightEdit->setSizePolicy(sizePolicy);

        hboxLayout1->addWidget(heightEdit);

        spacerItem3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem3);

        ratioCheck = new QCheckBox(sizeGroup);
        ratioCheck->setObjectName(QString::fromUtf8("ratioCheck"));
        ratioCheck->setChecked(true);

        hboxLayout1->addWidget(ratioCheck);

        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem4);


        vboxLayout3->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout2->setSpacing(6);
#endif
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        exportEntireGraphRadio = new QRadioButton(sizeGroup);
        exportEntireGraphRadio->setObjectName(QString::fromUtf8("exportEntireGraphRadio"));
        exportEntireGraphRadio->setChecked(true);

        hboxLayout2->addWidget(exportEntireGraphRadio);

        spacerItem5 = new QSpacerItem(16, 22, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem5);

        exportDisplayedAreaRadio = new QRadioButton(sizeGroup);
        exportDisplayedAreaRadio->setObjectName(QString::fromUtf8("exportDisplayedAreaRadio"));

        hboxLayout2->addWidget(exportDisplayedAreaRadio);

        spacerItem6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem6);


        vboxLayout3->addLayout(hboxLayout2);


        vboxLayout->addWidget(sizeGroup);

        compressionGroup = new QGroupBox(ExportGraphDialog);
        compressionGroup->setObjectName(QString::fromUtf8("compressionGroup"));
        vboxLayout4 = new QVBoxLayout(compressionGroup);
#ifndef Q_OS_MAC
        vboxLayout4->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout4->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        vboxLayout5 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout5->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout5->setContentsMargins(0, 0, 0, 0);
#endif
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        compressionAutoRadio = new QRadioButton(compressionGroup);
        compressionAutoRadio->setObjectName(QString::fromUtf8("compressionAutoRadio"));
        compressionAutoRadio->setChecked(true);

        vboxLayout5->addWidget(compressionAutoRadio);

        compressionManualRadio = new QRadioButton(compressionGroup);
        compressionManualRadio->setObjectName(QString::fromUtf8("compressionManualRadio"));

        vboxLayout5->addWidget(compressionManualRadio);

        compressionSlider = new QSlider(compressionGroup);
        compressionSlider->setObjectName(QString::fromUtf8("compressionSlider"));
        compressionSlider->setEnabled(false);
        compressionSlider->setMaximum(100);
        compressionSlider->setSingleStep(5);
        compressionSlider->setValue(80);
        compressionSlider->setOrientation(Qt::Horizontal);
        compressionSlider->setTickPosition(QSlider::TicksBelow);

        vboxLayout5->addWidget(compressionSlider);


        vboxLayout4->addLayout(vboxLayout5);

        hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout3->setSpacing(6);
#endif
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        compressionSmallestSizeLabel = new QLabel(compressionGroup);
        compressionSmallestSizeLabel->setObjectName(QString::fromUtf8("compressionSmallestSizeLabel"));
        compressionSmallestSizeLabel->setEnabled(false);

        hboxLayout3->addWidget(compressionSmallestSizeLabel);

        spacerItem7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacerItem7);

        compressionBestQualityLabel = new QLabel(compressionGroup);
        compressionBestQualityLabel->setObjectName(QString::fromUtf8("compressionBestQualityLabel"));
        compressionBestQualityLabel->setEnabled(false);

        hboxLayout3->addWidget(compressionBestQualityLabel);


        vboxLayout4->addLayout(hboxLayout3);


        vboxLayout->addWidget(compressionGroup);

        spacerItem8 = new QSpacerItem(539, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem8);

        hboxLayout4 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout4->setSpacing(6);
#endif
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        cancelButton = new QPushButton(ExportGraphDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout4->addWidget(cancelButton);

        exportButton = new QPushButton(ExportGraphDialog);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));

        hboxLayout4->addWidget(exportButton);


        vboxLayout->addLayout(hboxLayout4);

#ifndef QT_NO_SHORTCUT
        outputFileNoteLabel->setBuddy(pathEdit);
        widthLabel->setBuddy(widthEdit);
        heightLabel->setBuddy(heightEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(ExportGraphDialog);
        QObject::connect(ratioCheck, SIGNAL(toggled(bool)), exportDisplayedAreaRadio, SLOT(setEnabled(bool)));
        QObject::connect(ratioCheck, SIGNAL(toggled(bool)), exportEntireGraphRadio, SLOT(click()));
        QObject::connect(compressionManualRadio, SIGNAL(toggled(bool)), compressionSlider, SLOT(setEnabled(bool)));
        QObject::connect(compressionManualRadio, SIGNAL(toggled(bool)), compressionSmallestSizeLabel, SLOT(setEnabled(bool)));
        QObject::connect(compressionManualRadio, SIGNAL(toggled(bool)), compressionBestQualityLabel, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(ExportGraphDialog);
    } // setupUi

    void retranslateUi(QDialog *ExportGraphDialog)
    {
        ExportGraphDialog->setWindowTitle(QApplication::translate("ExportGraphDialog", "Export graph", 0, QApplication::UnicodeUTF8));
        outputFileGroup->setTitle(QApplication::translate("ExportGraphDialog", "Output file", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("ExportGraphDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        outputFileNoteLabel->setText(QApplication::translate("ExportGraphDialog", "Note: File extension determines output format.", 0, QApplication::UnicodeUTF8));
        sizeGroup->setTitle(QApplication::translate("ExportGraphDialog", "Size", 0, QApplication::UnicodeUTF8));
        widthLabel->setText(QApplication::translate("ExportGraphDialog", "Width:", 0, QApplication::UnicodeUTF8));
        heightLabel->setText(QApplication::translate("ExportGraphDialog", "Height:", 0, QApplication::UnicodeUTF8));
        ratioCheck->setText(QApplication::translate("ExportGraphDialog", "Keep current ratio", 0, QApplication::UnicodeUTF8));
        exportEntireGraphRadio->setText(QApplication::translate("ExportGraphDialog", "Export entire graph", 0, QApplication::UnicodeUTF8));
        exportDisplayedAreaRadio->setText(QApplication::translate("ExportGraphDialog", "Export currently displayed area", 0, QApplication::UnicodeUTF8));
        compressionGroup->setTitle(QApplication::translate("ExportGraphDialog", "Compression", 0, QApplication::UnicodeUTF8));
        compressionAutoRadio->setText(QApplication::translate("ExportGraphDialog", "Auto", 0, QApplication::UnicodeUTF8));
        compressionManualRadio->setText(QApplication::translate("ExportGraphDialog", "Specify compression level:", 0, QApplication::UnicodeUTF8));
        compressionSmallestSizeLabel->setText(QApplication::translate("ExportGraphDialog", "Smallest file size", 0, QApplication::UnicodeUTF8));
        compressionBestQualityLabel->setText(QApplication::translate("ExportGraphDialog", "Best quality", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ExportGraphDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        exportButton->setText(QApplication::translate("ExportGraphDialog", "Export", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportGraphDialog: public Ui_ExportGraphDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTGRAPHDIALOG_H
