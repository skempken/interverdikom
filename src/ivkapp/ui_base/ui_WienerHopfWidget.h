/********************************************************************************
** Form generated from reading UI file 'WienerHopfWidget.ui'
**
** Created: Thu Dec 26 15:32:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIENERHOPFWIDGET_H
#define UI_WIENERHOPFWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#include "HelpButton.h"

QT_BEGIN_NAMESPACE

class Ui_WienerHopfWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *epsilon;
    QSpacerItem *spacerItem;
    HelpButton *pushButton;
    QLabel *label_3;
    QSpinBox *numIterations;
    QSpacerItem *spacerItem1;
    QLabel *label_4;
    QSpinBox *relaxationSpin;
    QSpacerItem *spacer;
    QSpacerItem *spacerItem2;
    QProgressBar *computationProgressBar;
    QPushButton *computeButton;
    QLabel *computationTextLabel;

    void setupUi(QWidget *WienerHopfWidget)
    {
        if (WienerHopfWidget->objectName().isEmpty())
            WienerHopfWidget->setObjectName(QString::fromUtf8("WienerHopfWidget"));
        WienerHopfWidget->resize(446, 274);
        gridLayout = new QGridLayout(WienerHopfWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(WienerHopfWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        epsilon = new QSpinBox(WienerHopfWidget);
        epsilon->setObjectName(QString::fromUtf8("epsilon"));
        epsilon->setMinimum(-16);
        epsilon->setMaximum(0);

        gridLayout->addWidget(epsilon, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 2, 1, 1);

        pushButton = new HelpButton(WienerHopfWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 3, 1, 1);

        label_3 = new QLabel(WienerHopfWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        numIterations = new QSpinBox(WienerHopfWidget);
        numIterations->setObjectName(QString::fromUtf8("numIterations"));
        numIterations->setMaximum(99999);

        gridLayout->addWidget(numIterations, 1, 1, 1, 1);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem1, 1, 2, 1, 1);

        label_4 = new QLabel(WienerHopfWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        relaxationSpin = new QSpinBox(WienerHopfWidget);
        relaxationSpin->setObjectName(QString::fromUtf8("relaxationSpin"));
        relaxationSpin->setMaximum(99);

        gridLayout->addWidget(relaxationSpin, 2, 1, 1, 1);

        spacer = new QSpacerItem(116, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacer, 2, 2, 1, 1);

        spacerItem2 = new QSpacerItem(20, 201, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem2, 3, 2, 1, 1);

        computationProgressBar = new QProgressBar(WienerHopfWidget);
        computationProgressBar->setObjectName(QString::fromUtf8("computationProgressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(computationProgressBar->sizePolicy().hasHeightForWidth());
        computationProgressBar->setSizePolicy(sizePolicy);
        computationProgressBar->setValue(0);
        computationProgressBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(computationProgressBar, 4, 0, 1, 3);

        computeButton = new QPushButton(WienerHopfWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(computeButton->sizePolicy().hasHeightForWidth());
        computeButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(computeButton, 4, 3, 1, 1);

        computationTextLabel = new QLabel(WienerHopfWidget);
        computationTextLabel->setObjectName(QString::fromUtf8("computationTextLabel"));
        computationTextLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(computationTextLabel, 5, 0, 1, 4);


        retranslateUi(WienerHopfWidget);

        QMetaObject::connectSlotsByName(WienerHopfWidget);
    } // setupUi

    void retranslateUi(QWidget *WienerHopfWidget)
    {
        WienerHopfWidget->setWindowTitle(QApplication::translate("WienerHopfWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WienerHopfWidget", "Parameter Epsilon:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        pushButton->setWhatsThis(QApplication::translate("WienerHopfWidget", "wiener_hopf_epsilon.htm", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushButton->setText(QApplication::translate("WienerHopfWidget", "?", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WienerHopfWidget", "Number of iterations:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("WienerHopfWidget", "Recompute relaxation after:", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("WienerHopfWidget", "Compute", 0, QApplication::UnicodeUTF8));
        computationTextLabel->setText(QApplication::translate("WienerHopfWidget", "Waiting for task text...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WienerHopfWidget: public Ui_WienerHopfWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIENERHOPFWIDGET_H
