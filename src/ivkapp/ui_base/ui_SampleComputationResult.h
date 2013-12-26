/********************************************************************************
** Form generated from reading UI file 'SampleComputationResult.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAMPLECOMPUTATIONRESULT_H
#define UI_SAMPLECOMPUTATIONRESULT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SampleComputationResult
{
public:
    QLabel *label;
    QLabel *resultLabel;

    void setupUi(QWidget *SampleComputationResult)
    {
        if (SampleComputationResult->objectName().isEmpty())
            SampleComputationResult->setObjectName(QString::fromUtf8("SampleComputationResult"));
        SampleComputationResult->resize(671, 408);
        label = new QLabel(SampleComputationResult);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 90, 181, 16));
        resultLabel = new QLabel(SampleComputationResult);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setGeometry(QRect(190, 130, 111, 16));

        retranslateUi(SampleComputationResult);

        QMetaObject::connectSlotsByName(SampleComputationResult);
    } // setupUi

    void retranslateUi(QWidget *SampleComputationResult)
    {
        SampleComputationResult->setWindowTitle(QApplication::translate("SampleComputationResult", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SampleComputationResult", "And the result is:", 0, QApplication::UnicodeUTF8));
        resultLabel->setText(QApplication::translate("SampleComputationResult", "No result yet", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SampleComputationResult: public Ui_SampleComputationResult {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAMPLECOMPUTATIONRESULT_H
