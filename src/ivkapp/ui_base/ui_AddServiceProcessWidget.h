/********************************************************************************
** Form generated from reading UI file 'AddServiceProcessWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSERVICEPROCESSWIDGET_H
#define UI_ADDSERVICEPROCESSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddServiceProcessWidget
{
public:
    QVBoxLayout *vboxLayout;
    QSpacerItem *spacerItem;
    QLabel *label_8;
    QGridLayout *gridLayout;
    QLineEdit *expectationValueEdit;
    QLabel *label;
    QDoubleSpinBox *factorSpin;
    QLabel *label_2;
    QLineEdit *standardDeviationEdit;
    QLabel *label_3;
    QDoubleSpinBox *capacitySpin;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem1;
    QPushButton *addButton;
    QSpacerItem *spacerItem2;
    QSpacerItem *spacerItem3;

    void setupUi(QWidget *AddServiceProcessWidget)
    {
        if (AddServiceProcessWidget->objectName().isEmpty())
            AddServiceProcessWidget->setObjectName(QString::fromUtf8("AddServiceProcessWidget"));
        AddServiceProcessWidget->resize(709, 588);
        vboxLayout = new QVBoxLayout(AddServiceProcessWidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        spacerItem = new QSpacerItem(691, 161, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        label_8 = new QLabel(AddServiceProcessWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        vboxLayout->addWidget(label_8);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        expectationValueEdit = new QLineEdit(AddServiceProcessWidget);
        expectationValueEdit->setObjectName(QString::fromUtf8("expectationValueEdit"));
        expectationValueEdit->setEnabled(false);

        gridLayout->addWidget(expectationValueEdit, 0, 0, 1, 1);

        label = new QLabel(AddServiceProcessWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        factorSpin = new QDoubleSpinBox(AddServiceProcessWidget);
        factorSpin->setObjectName(QString::fromUtf8("factorSpin"));
        factorSpin->setMinimumSize(QSize(95, 0));
        factorSpin->setDecimals(5);

        gridLayout->addWidget(factorSpin, 0, 2, 1, 2);

        label_2 = new QLabel(AddServiceProcessWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 4, 1, 1);

        standardDeviationEdit = new QLineEdit(AddServiceProcessWidget);
        standardDeviationEdit->setObjectName(QString::fromUtf8("standardDeviationEdit"));
        standardDeviationEdit->setEnabled(false);

        gridLayout->addWidget(standardDeviationEdit, 0, 5, 1, 1);

        label_3 = new QLabel(AddServiceProcessWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 6, 1, 1);

        capacitySpin = new QDoubleSpinBox(AddServiceProcessWidget);
        capacitySpin->setObjectName(QString::fromUtf8("capacitySpin"));
        capacitySpin->setDecimals(5);

        gridLayout->addWidget(capacitySpin, 0, 7, 1, 1);

        label_4 = new QLabel(AddServiceProcessWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(AddServiceProcessWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 3, 1, 1);

        label_6 = new QLabel(AddServiceProcessWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 5, 1, 1);

        label_7 = new QLabel(AddServiceProcessWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 7, 1, 1);


        vboxLayout->addLayout(gridLayout);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);

        addButton = new QPushButton(AddServiceProcessWidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        hboxLayout->addWidget(addButton);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem2);


        vboxLayout->addLayout(hboxLayout);

        spacerItem3 = new QSpacerItem(691, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem3);


        retranslateUi(AddServiceProcessWidget);

        QMetaObject::connectSlotsByName(AddServiceProcessWidget);
    } // setupUi

    void retranslateUi(QWidget *AddServiceProcessWidget)
    {
        AddServiceProcessWidget->setWindowTitle(QApplication::translate("AddServiceProcessWidget", "Form", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("AddServiceProcessWidget", "Please enter a capacity for the service process:", 0, QApplication::UnicodeUTF8));
        expectationValueEdit->setText(QApplication::translate("AddServiceProcessWidget", "10.0", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddServiceProcessWidget", "+", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddServiceProcessWidget", "x", 0, QApplication::UnicodeUTF8));
        standardDeviationEdit->setText(QApplication::translate("AddServiceProcessWidget", "10.0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AddServiceProcessWidget", "=", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AddServiceProcessWidget", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">(Expectation Value)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QString());
        label_6->setText(QApplication::translate("AddServiceProcessWidget", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">(Standard Deviation)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("AddServiceProcessWidget", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">(Service Process Capacity)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("AddServiceProcessWidget", "Add Service Process", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddServiceProcessWidget: public Ui_AddServiceProcessWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSERVICEPROCESSWIDGET_H
