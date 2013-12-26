/********************************************************************************
** Form generated from reading UI file 'PolyFacWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLYFACWIDGET_H
#define UI_POLYFACWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "HelpButton.h"

QT_BEGIN_NAMESPACE

class Ui_PolyFacWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *rootBox;
    QVBoxLayout *vboxLayout;
    QRadioButton *muellerOption;
    QRadioButton *bauhuberOption;
    QRadioButton *mpsolveOption;
    QGroupBox *determinantBox;
    QVBoxLayout *vboxLayout1;
    QRadioButton *laplaceOption;
    QRadioButton *faddeevOption;
    QSpacerItem *spacerItem;
    QLabel *computationTextLabel;
    QPushButton *computeButton;
    QProgressBar *computationProgressBar;
    HelpButton *pushButton;

    void setupUi(QWidget *PolyFacWidget)
    {
        if (PolyFacWidget->objectName().isEmpty())
            PolyFacWidget->setObjectName(QString::fromUtf8("PolyFacWidget"));
        PolyFacWidget->resize(446, 376);
        gridLayout = new QGridLayout(PolyFacWidget);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        rootBox = new QGroupBox(PolyFacWidget);
        rootBox->setObjectName(QString::fromUtf8("rootBox"));
        vboxLayout = new QVBoxLayout(rootBox);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        muellerOption = new QRadioButton(rootBox);
        muellerOption->setObjectName(QString::fromUtf8("muellerOption"));
        muellerOption->setChecked(true);

        vboxLayout->addWidget(muellerOption);

        bauhuberOption = new QRadioButton(rootBox);
        bauhuberOption->setObjectName(QString::fromUtf8("bauhuberOption"));

        vboxLayout->addWidget(bauhuberOption);

        mpsolveOption = new QRadioButton(rootBox);
        mpsolveOption->setObjectName(QString::fromUtf8("mpsolveOption"));

        vboxLayout->addWidget(mpsolveOption);


        gridLayout->addWidget(rootBox, 2, 0, 1, 2);

        determinantBox = new QGroupBox(PolyFacWidget);
        determinantBox->setObjectName(QString::fromUtf8("determinantBox"));
        vboxLayout1 = new QVBoxLayout(determinantBox);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        laplaceOption = new QRadioButton(determinantBox);
        laplaceOption->setObjectName(QString::fromUtf8("laplaceOption"));
        laplaceOption->setChecked(true);

        vboxLayout1->addWidget(laplaceOption);

        faddeevOption = new QRadioButton(determinantBox);
        faddeevOption->setObjectName(QString::fromUtf8("faddeevOption"));

        vboxLayout1->addWidget(faddeevOption);


        gridLayout->addWidget(determinantBox, 1, 0, 1, 2);

        spacerItem = new QSpacerItem(191, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 0, 1, 1);

        computationTextLabel = new QLabel(PolyFacWidget);
        computationTextLabel->setObjectName(QString::fromUtf8("computationTextLabel"));
        computationTextLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(computationTextLabel, 4, 0, 1, 2);

        computeButton = new QPushButton(PolyFacWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(computeButton->sizePolicy().hasHeightForWidth());
        computeButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(computeButton, 3, 1, 1, 1);

        computationProgressBar = new QProgressBar(PolyFacWidget);
        computationProgressBar->setObjectName(QString::fromUtf8("computationProgressBar"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(computationProgressBar->sizePolicy().hasHeightForWidth());
        computationProgressBar->setSizePolicy(sizePolicy1);
        computationProgressBar->setValue(0);
        computationProgressBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(computationProgressBar, 3, 0, 1, 1);

        pushButton = new HelpButton(PolyFacWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);


        retranslateUi(PolyFacWidget);

        QMetaObject::connectSlotsByName(PolyFacWidget);
    } // setupUi

    void retranslateUi(QWidget *PolyFacWidget)
    {
        PolyFacWidget->setWindowTitle(QApplication::translate("PolyFacWidget", "Form", 0, QApplication::UnicodeUTF8));
        rootBox->setTitle(QApplication::translate("PolyFacWidget", "Root approximation method", 0, QApplication::UnicodeUTF8));
        muellerOption->setText(QApplication::translate("PolyFacWidget", "Mueller method", 0, QApplication::UnicodeUTF8));
        bauhuberOption->setText(QApplication::translate("PolyFacWidget", "Bauhuber method", 0, QApplication::UnicodeUTF8));
        mpsolveOption->setText(QApplication::translate("PolyFacWidget", "MPSolve", 0, QApplication::UnicodeUTF8));
        determinantBox->setTitle(QApplication::translate("PolyFacWidget", "Determinant method", 0, QApplication::UnicodeUTF8));
        laplaceOption->setText(QApplication::translate("PolyFacWidget", "Laplace method", 0, QApplication::UnicodeUTF8));
        faddeevOption->setText(QApplication::translate("PolyFacWidget", "Faddeev method", 0, QApplication::UnicodeUTF8));
        computationTextLabel->setText(QApplication::translate("PolyFacWidget", "Waiting for task text...", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("PolyFacWidget", "Compute", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        pushButton->setWhatsThis(QApplication::translate("PolyFacWidget", "oly_fac.htm", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushButton->setText(QApplication::translate("PolyFacWidget", "?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PolyFacWidget: public Ui_PolyFacWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLYFACWIDGET_H
