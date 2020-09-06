/********************************************************************************
** Form generated from reading UI file 'shapeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAPEWIDGET_H
#define UI_SHAPEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_shapeWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton_top;
    QRadioButton *radioButton_bot;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QSpinBox *spinBox_nDisc;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_dragWidth;

    void setupUi(QWidget *shapeWidget)
    {
        if (shapeWidget->objectName().isEmpty())
            shapeWidget->setObjectName(QString::fromUtf8("shapeWidget"));
        shapeWidget->resize(223, 300);
        shapeWidget->setMaximumSize(QSize(16777215, 300));
        gridLayout = new QGridLayout(shapeWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(shapeWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setAutoFillBackground(false);
        groupBox->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButton_top = new QRadioButton(groupBox);
        radioButton_top->setObjectName(QString::fromUtf8("radioButton_top"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        radioButton_top->setFont(font1);
        radioButton_top->setChecked(true);

        gridLayout_2->addWidget(radioButton_top, 0, 0, 1, 1);

        radioButton_bot = new QRadioButton(groupBox);
        radioButton_bot->setObjectName(QString::fromUtf8("radioButton_bot"));
        radioButton_bot->setFont(font1);

        gridLayout_2->addWidget(radioButton_bot, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(shapeWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font2.setPointSize(10);
        font2.setItalic(false);
        groupBox_2->setFont(font2);
        groupBox_2->setAutoFillBackground(false);
        groupBox_2->setStyleSheet(QString::fromUtf8(""));
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        spinBox_nDisc = new QSpinBox(groupBox_2);
        spinBox_nDisc->setObjectName(QString::fromUtf8("spinBox_nDisc"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Source Code Pro"));
        font3.setPointSize(9);
        font3.setItalic(false);
        spinBox_nDisc->setFont(font3);

        gridLayout_3->addWidget(spinBox_nDisc, 0, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font2);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font2);

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        doubleSpinBox_dragWidth = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_dragWidth->setObjectName(QString::fromUtf8("doubleSpinBox_dragWidth"));
        doubleSpinBox_dragWidth->setFont(font3);

        gridLayout_3->addWidget(doubleSpinBox_dragWidth, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(shapeWidget);

        QMetaObject::connectSlotsByName(shapeWidget);
    } // setupUi

    void retranslateUi(QWidget *shapeWidget)
    {
        shapeWidget->setWindowTitle(QCoreApplication::translate("shapeWidget", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("shapeWidget", "ShapeFunction", nullptr));
        radioButton_top->setText(QCoreApplication::translate("shapeWidget", "Top", nullptr));
        radioButton_bot->setText(QCoreApplication::translate("shapeWidget", "Bottom", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("shapeWidget", "Discretization", nullptr));
        label->setText(QCoreApplication::translate("shapeWidget", "n Coefficients", nullptr));
        label_2->setText(QCoreApplication::translate("shapeWidget", "drag Width", nullptr));
    } // retranslateUi

};

namespace Ui {
    class shapeWidget: public Ui_shapeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAPEWIDGET_H
