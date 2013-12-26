/********************************************************************************
** Form generated from reading UI file 'SceneModelerWidget.ui'
**
** Created: Thu Dec 26 15:30:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENEMODELERWIDGET_H
#define UI_SCENEMODELERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SceneModelerWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSlider *sliderDSteps;
    QSpinBox *numdstepsEdit;
    QLabel *label_3;
    QDoubleSpinBox *epsilon;
    QSpacerItem *spacerItem;
    QProgressBar *progressBar;
    QPushButton *computeButton;
    QLabel *progressLabel;

    void setupUi(QWidget *SceneModelerWidget)
    {
        if (SceneModelerWidget->objectName().isEmpty())
            SceneModelerWidget->setObjectName(QString::fromUtf8("SceneModelerWidget"));
        SceneModelerWidget->resize(472, 352);
        gridLayout = new QGridLayout(SceneModelerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(SceneModelerWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sliderDSteps = new QSlider(SceneModelerWidget);
        sliderDSteps->setObjectName(QString::fromUtf8("sliderDSteps"));
        sliderDSteps->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDSteps, 0, 1, 1, 1);

        numdstepsEdit = new QSpinBox(SceneModelerWidget);
        numdstepsEdit->setObjectName(QString::fromUtf8("numdstepsEdit"));
        numdstepsEdit->setMinimum(1);

        gridLayout->addWidget(numdstepsEdit, 0, 3, 1, 1);

        label_3 = new QLabel(SceneModelerWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        epsilon = new QDoubleSpinBox(SceneModelerWidget);
        epsilon->setObjectName(QString::fromUtf8("epsilon"));
        epsilon->setSingleStep(0.01);

        gridLayout->addWidget(epsilon, 1, 3, 1, 1);

        spacerItem = new QSpacerItem(131, 91, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 2, 0, 1, 2);

        progressBar = new QProgressBar(SceneModelerWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 3, 0, 1, 2);

        computeButton = new QPushButton(SceneModelerWidget);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));

        gridLayout->addWidget(computeButton, 3, 2, 1, 2);

        progressLabel = new QLabel(SceneModelerWidget);
        progressLabel->setObjectName(QString::fromUtf8("progressLabel"));

        gridLayout->addWidget(progressLabel, 4, 0, 1, 2);


        retranslateUi(SceneModelerWidget);
        QObject::connect(sliderDSteps, SIGNAL(valueChanged(int)), numdstepsEdit, SLOT(setValue(int)));
        QObject::connect(numdstepsEdit, SIGNAL(valueChanged(int)), sliderDSteps, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(SceneModelerWidget);
    } // setupUi

    void retranslateUi(QWidget *SceneModelerWidget)
    {
        SceneModelerWidget->setWindowTitle(QApplication::translate("SceneModelerWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SceneModelerWidget", "Number of discretization steps", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SceneModelerWidget", "Threshold for scene detection", 0, QApplication::UnicodeUTF8));
        computeButton->setText(QApplication::translate("SceneModelerWidget", "Compute", 0, QApplication::UnicodeUTF8));
        progressLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SceneModelerWidget: public Ui_SceneModelerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENEMODELERWIDGET_H
