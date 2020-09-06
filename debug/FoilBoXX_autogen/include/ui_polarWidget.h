/********************************************************************************
** Form generated from reading UI file 'polarWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLARWIDGET_H
#define UI_POLARWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_polarWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_31;
    QLabel *label_33;
    QDoubleSpinBox *doubleSpinBox_alpha1;
    QDoubleSpinBox *doubleSpinBox_alpha2;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *doubleSpinBox_nCrit;
    QLabel *label_32;
    QDoubleSpinBox *doubleSpinBox_re;
    QLabel *label_30;
    QCheckBox *checkBox_reCa1;
    QPushButton *pushButton_calcPolar;

    void setupUi(QWidget *polarWidget)
    {
        if (polarWidget->objectName().isEmpty())
            polarWidget->setObjectName(QString::fromUtf8("polarWidget"));
        polarWidget->resize(314, 362);
        polarWidget->setMaximumSize(QSize(16777215, 400));
        gridLayout = new QGridLayout(polarWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(polarWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        groupBox->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_31 = new QLabel(groupBox);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setKerning(true);
        label_31->setFont(font1);
        label_31->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_31->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_31, 0, 0, 1, 1);

        label_33 = new QLabel(groupBox);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setFont(font1);
        label_33->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_33->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_33, 1, 0, 1, 1);

        doubleSpinBox_alpha1 = new QDoubleSpinBox(groupBox);
        doubleSpinBox_alpha1->setObjectName(QString::fromUtf8("doubleSpinBox_alpha1"));
        doubleSpinBox_alpha1->setMaximumSize(QSize(100, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Source Code Pro"));
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setItalic(true);
        font2.setWeight(50);
        doubleSpinBox_alpha1->setFont(font2);

        gridLayout_3->addWidget(doubleSpinBox_alpha1, 0, 1, 1, 1);

        doubleSpinBox_alpha2 = new QDoubleSpinBox(groupBox);
        doubleSpinBox_alpha2->setObjectName(QString::fromUtf8("doubleSpinBox_alpha2"));
        doubleSpinBox_alpha2->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_alpha2->setFont(font2);

        gridLayout_3->addWidget(doubleSpinBox_alpha2, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 3);

        groupBox_11 = new QGroupBox(polarWidget);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font3.setPointSize(10);
        font3.setItalic(false);
        groupBox_11->setFont(font3);
        gridLayout_2 = new QGridLayout(groupBox_11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        doubleSpinBox_nCrit = new QDoubleSpinBox(groupBox_11);
        doubleSpinBox_nCrit->setObjectName(QString::fromUtf8("doubleSpinBox_nCrit"));
        doubleSpinBox_nCrit->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_nCrit->setFont(font2);

        gridLayout_2->addWidget(doubleSpinBox_nCrit, 2, 1, 1, 1);

        label_32 = new QLabel(groupBox_11);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setFont(font1);
        label_32->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_32->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_32, 0, 0, 1, 1);

        doubleSpinBox_re = new QDoubleSpinBox(groupBox_11);
        doubleSpinBox_re->setObjectName(QString::fromUtf8("doubleSpinBox_re"));
        doubleSpinBox_re->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_re->setFont(font2);

        gridLayout_2->addWidget(doubleSpinBox_re, 0, 1, 1, 1);

        label_30 = new QLabel(groupBox_11);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font1);
        label_30->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_30->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_30, 2, 0, 1, 1);

        checkBox_reCa1 = new QCheckBox(groupBox_11);
        checkBox_reCa1->setObjectName(QString::fromUtf8("checkBox_reCa1"));
        checkBox_reCa1->setEnabled(true);

        gridLayout_2->addWidget(checkBox_reCa1, 1, 0, 1, 2);


        gridLayout->addWidget(groupBox_11, 1, 0, 1, 3);

        pushButton_calcPolar = new QPushButton(polarWidget);
        pushButton_calcPolar->setObjectName(QString::fromUtf8("pushButton_calcPolar"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_calcPolar->sizePolicy().hasHeightForWidth());
        pushButton_calcPolar->setSizePolicy(sizePolicy);
        pushButton_calcPolar->setMinimumSize(QSize(100, 0));
        pushButton_calcPolar->setMaximumSize(QSize(100, 16777215));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font4.setPointSize(9);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        pushButton_calcPolar->setFont(font4);

        gridLayout->addWidget(pushButton_calcPolar, 2, 0, 1, 2);


        retranslateUi(polarWidget);

        QMetaObject::connectSlotsByName(polarWidget);
    } // setupUi

    void retranslateUi(QWidget *polarWidget)
    {
        polarWidget->setWindowTitle(QCoreApplication::translate("polarWidget", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("polarWidget", "Polar", nullptr));
        label_31->setText(QCoreApplication::translate("polarWidget", "lower \316\261", nullptr));
        label_33->setText(QCoreApplication::translate("polarWidget", "upper \316\261", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("polarWidget", "Viscous", nullptr));
        label_32->setText(QCoreApplication::translate("polarWidget", "Re", nullptr));
        label_30->setText(QCoreApplication::translate("polarWidget", "Ncrit", nullptr));
        checkBox_reCa1->setText(QCoreApplication::translate("polarWidget", "Re at ca=1 (const. Lift)", nullptr));
        pushButton_calcPolar->setText(QCoreApplication::translate("polarWidget", "Calc Polar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class polarWidget: public Ui_polarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLARWIDGET_H
