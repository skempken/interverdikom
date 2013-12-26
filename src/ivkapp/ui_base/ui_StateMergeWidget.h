/********************************************************************************
** Form generated from reading UI file 'StateMergeWidget.ui'
**
** Created: Thu Dec 26 15:32:05 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATEMERGEWIDGET_H
#define UI_STATEMERGEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StateMergeWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSlider *sliderContractions;
    QSpacerItem *spacerItem;
    QSpinBox *numContractions;
    QRadioButton *statProb;
    QRadioButton *means;
    QTableWidget *contractTable;
    QSpacerItem *spacerItem1;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;

    void setupUi(QWidget *StateMergeWidget)
    {
        if (StateMergeWidget->objectName().isEmpty())
            StateMergeWidget->setObjectName(QString::fromUtf8("StateMergeWidget"));
        StateMergeWidget->resize(472, 354);
        gridLayout = new QGridLayout(StateMergeWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(StateMergeWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sliderContractions = new QSlider(StateMergeWidget);
        sliderContractions->setObjectName(QString::fromUtf8("sliderContractions"));
        sliderContractions->setMinimum(2);
        sliderContractions->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderContractions, 0, 1, 1, 2);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 3, 1, 1);

        numContractions = new QSpinBox(StateMergeWidget);
        numContractions->setObjectName(QString::fromUtf8("numContractions"));
        numContractions->setMinimum(2);

        gridLayout->addWidget(numContractions, 0, 4, 1, 1);

        statProb = new QRadioButton(StateMergeWidget);
        statProb->setObjectName(QString::fromUtf8("statProb"));
        statProb->setChecked(true);

        gridLayout->addWidget(statProb, 1, 0, 1, 2);

        means = new QRadioButton(StateMergeWidget);
        means->setObjectName(QString::fromUtf8("means"));

        gridLayout->addWidget(means, 1, 2, 1, 2);

        contractTable = new QTableWidget(StateMergeWidget);
        if (contractTable->columnCount() < 3)
            contractTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        contractTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        contractTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        contractTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (contractTable->rowCount() < 1)
            contractTable->setRowCount(1);
        contractTable->setObjectName(QString::fromUtf8("contractTable"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(contractTable->sizePolicy().hasHeightForWidth());
        contractTable->setSizePolicy(sizePolicy);
        contractTable->setRowCount(1);

        gridLayout->addWidget(contractTable, 2, 0, 1, 5);

        spacerItem1 = new QSpacerItem(354, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem1, 3, 0, 1, 4);

        progressBar = new QProgressBar(StateMergeWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 4, 0, 1, 3);

        computeButton = new QPushButton(StateMergeWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 4, 3, 1, 2);

        progressLabel = new QLabel(StateMergeWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 5, 0, 1, 3);


        retranslateUi(StateMergeWidget);
        QObject::connect(sliderContractions, SIGNAL(valueChanged(int)), numContractions, SLOT(setValue(int)));
        QObject::connect(numContractions, SIGNAL(valueChanged(int)), sliderContractions, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(StateMergeWidget);
    } // setupUi

    void retranslateUi(QWidget *StateMergeWidget)
    {
        StateMergeWidget->setWindowTitle(QApplication::translate("StateMergeWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StateMergeWidget", "Number of state contractions", 0, QApplication::UnicodeUTF8));
        statProb->setText(QApplication::translate("StateMergeWidget", "Stationary probabilities", 0, QApplication::UnicodeUTF8));
        means->setText(QApplication::translate("StateMergeWidget", "State means", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = contractTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("StateMergeWidget", "#state", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = contractTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("StateMergeWidget", "stat prob", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = contractTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("StateMergeWidget", "mean", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("StateMergeWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StateMergeWidget: public Ui_StateMergeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATEMERGEWIDGET_H
