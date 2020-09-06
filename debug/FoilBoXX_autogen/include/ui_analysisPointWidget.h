/********************************************************************************
** Form generated from reading UI file 'analysisPointWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYSISPOINTWIDGET_H
#define UI_ANALYSISPOINTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_analysisPointWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_Viscous;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *doubleSpinBox_re;
    QLabel *label_32;
    QDoubleSpinBox *doubleSpinBox_nCrit;
    QLabel *label_30;
    QCheckBox *checkBox_reCa1;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_18;
    QLabel *label_31;
    QLabel *label_33;
    QDoubleSpinBox *doubleSpinBox_caDesign;
    QDoubleSpinBox *doubleSpinBox_alphaDesign;
    QComboBox *comboBox;

    void setupUi(QWidget *analysisPointWidget)
    {
        if (analysisPointWidget->objectName().isEmpty())
            analysisPointWidget->setObjectName(QString::fromUtf8("analysisPointWidget"));
        analysisPointWidget->resize(249, 342);
        analysisPointWidget->setMaximumSize(QSize(16777215, 400));
        gridLayout = new QGridLayout(analysisPointWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_Viscous = new QGroupBox(analysisPointWidget);
        groupBox_Viscous->setObjectName(QString::fromUtf8("groupBox_Viscous"));
        QFont font;
        font.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font.setPointSize(10);
        font.setItalic(false);
        groupBox_Viscous->setFont(font);
        groupBox_Viscous->setCheckable(true);
        groupBox_Viscous->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBox_Viscous);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        doubleSpinBox_re = new QDoubleSpinBox(groupBox_Viscous);
        doubleSpinBox_re->setObjectName(QString::fromUtf8("doubleSpinBox_re"));
        doubleSpinBox_re->setEnabled(false);
        doubleSpinBox_re->setMaximumSize(QSize(100, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Source Code Pro"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setItalic(true);
        font1.setWeight(50);
        doubleSpinBox_re->setFont(font1);

        gridLayout_2->addWidget(doubleSpinBox_re, 2, 1, 1, 1);

        label_32 = new QLabel(groupBox_Viscous);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setKerning(true);
        label_32->setFont(font2);
        label_32->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_32->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_32, 2, 0, 1, 1);

        doubleSpinBox_nCrit = new QDoubleSpinBox(groupBox_Viscous);
        doubleSpinBox_nCrit->setObjectName(QString::fromUtf8("doubleSpinBox_nCrit"));
        doubleSpinBox_nCrit->setEnabled(false);
        doubleSpinBox_nCrit->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_nCrit->setFont(font1);

        gridLayout_2->addWidget(doubleSpinBox_nCrit, 0, 1, 1, 1);

        label_30 = new QLabel(groupBox_Viscous);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font2);
        label_30->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_30->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_30, 0, 0, 1, 1);

        checkBox_reCa1 = new QCheckBox(groupBox_Viscous);
        checkBox_reCa1->setObjectName(QString::fromUtf8("checkBox_reCa1"));
        checkBox_reCa1->setEnabled(true);

        gridLayout_2->addWidget(checkBox_reCa1, 3, 0, 1, 2);


        gridLayout->addWidget(groupBox_Viscous, 2, 0, 1, 1);

        groupBox_10 = new QGroupBox(analysisPointWidget);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font3.setPointSize(16);
        font3.setBold(true);
        font3.setItalic(true);
        font3.setWeight(75);
        groupBox_10->setFont(font3);
        gridLayout_18 = new QGridLayout(groupBox_10);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        label_31 = new QLabel(groupBox_10);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setMaximumSize(QSize(125, 16777215));
        label_31->setFont(font2);
        label_31->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_31->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_18->addWidget(label_31, 1, 0, 1, 1);

        label_33 = new QLabel(groupBox_10);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setMaximumSize(QSize(125, 16777215));
        label_33->setFont(font2);
        label_33->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_33->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_18->addWidget(label_33, 0, 0, 1, 1);

        doubleSpinBox_caDesign = new QDoubleSpinBox(groupBox_10);
        doubleSpinBox_caDesign->setObjectName(QString::fromUtf8("doubleSpinBox_caDesign"));
        doubleSpinBox_caDesign->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_caDesign->setFont(font1);

        gridLayout_18->addWidget(doubleSpinBox_caDesign, 0, 1, 1, 1);

        doubleSpinBox_alphaDesign = new QDoubleSpinBox(groupBox_10);
        doubleSpinBox_alphaDesign->setObjectName(QString::fromUtf8("doubleSpinBox_alphaDesign"));
        doubleSpinBox_alphaDesign->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_alphaDesign->setFont(font1);

        gridLayout_18->addWidget(doubleSpinBox_alphaDesign, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox_10, 0, 0, 1, 1);

        comboBox = new QComboBox(analysisPointWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font4.setPointSize(9);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        comboBox->setFont(font4);

        gridLayout->addWidget(comboBox, 3, 0, 1, 1);


        retranslateUi(analysisPointWidget);

        QMetaObject::connectSlotsByName(analysisPointWidget);
    } // setupUi

    void retranslateUi(QWidget *analysisPointWidget)
    {
        analysisPointWidget->setWindowTitle(QCoreApplication::translate("analysisPointWidget", "Form", nullptr));
        groupBox_Viscous->setTitle(QCoreApplication::translate("analysisPointWidget", "Viscous", nullptr));
        label_32->setText(QCoreApplication::translate("analysisPointWidget", "Re", nullptr));
        label_30->setText(QCoreApplication::translate("analysisPointWidget", "Ncrit", nullptr));
        checkBox_reCa1->setText(QCoreApplication::translate("analysisPointWidget", "Re at ca=1 (const. Lift)", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("analysisPointWidget", "Analysis", nullptr));
        label_31->setText(QCoreApplication::translate("analysisPointWidget", "\316\261", nullptr));
        label_33->setText(QCoreApplication::translate("analysisPointWidget", "cA", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("analysisPointWidget", "Pressure", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("analysisPointWidget", "HFac", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("analysisPointWidget", "dStar", nullptr));

    } // retranslateUi

};

namespace Ui {
    class analysisPointWidget: public Ui_analysisPointWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSISPOINTWIDGET_H
