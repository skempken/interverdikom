/********************************************************************************
** Form generated from reading UI file 'ModuleOverview.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULEOVERVIEW_H
#define UI_MODULEOVERVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModuleOverview
{
public:
    QVBoxLayout *vboxLayout;
    QSpacerItem *spacerItem;
    QFrame *descriptionFrame;
    QVBoxLayout *vboxLayout1;
    QLabel *descriptionLabel;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem1;
    QTreeWidget *treeWidget;
    QSpacerItem *spacerItem2;
    QLabel *label;
    QSpacerItem *spacerItem3;

    void setupUi(QWidget *ModuleOverview)
    {
        if (ModuleOverview->objectName().isEmpty())
            ModuleOverview->setObjectName(QString::fromUtf8("ModuleOverview"));
        ModuleOverview->resize(495, 314);
        vboxLayout = new QVBoxLayout(ModuleOverview);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        descriptionFrame = new QFrame(ModuleOverview);
        descriptionFrame->setObjectName(QString::fromUtf8("descriptionFrame"));
        descriptionFrame->setFrameShape(QFrame::StyledPanel);
        descriptionFrame->setFrameShadow(QFrame::Raised);
        vboxLayout1 = new QVBoxLayout(descriptionFrame);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        descriptionLabel = new QLabel(descriptionFrame);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));
        descriptionLabel->setWordWrap(true);

        vboxLayout1->addWidget(descriptionLabel);


        vboxLayout->addWidget(descriptionFrame);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);

        treeWidget = new QTreeWidget(ModuleOverview);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setItemsExpandable(false);

        hboxLayout->addWidget(treeWidget);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem2);


        vboxLayout->addLayout(hboxLayout);

        label = new QLabel(ModuleOverview);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(label);

        spacerItem3 = new QSpacerItem(477, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem3);


        retranslateUi(ModuleOverview);

        QMetaObject::connectSlotsByName(ModuleOverview);
    } // setupUi

    void retranslateUi(QWidget *ModuleOverview)
    {
        ModuleOverview->setWindowTitle(QApplication::translate("ModuleOverview", "Form", 0, QApplication::UnicodeUTF8));
        ModuleOverview->setStyleSheet(QApplication::translate("ModuleOverview", "* {font-size:14px}", 0, QApplication::UnicodeUTF8));
        descriptionLabel->setText(QApplication::translate("ModuleOverview", "Description goes here", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("ModuleOverview", "Modules", 0, QApplication::UnicodeUTF8));
        treeWidget->setStyleSheet(QString());
        label->setText(QApplication::translate("ModuleOverview", "Double click on a module to navigate there.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ModuleOverview: public Ui_ModuleOverview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULEOVERVIEW_H
