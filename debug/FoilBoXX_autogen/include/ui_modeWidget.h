/********************************************************************************
** Form generated from reading UI file 'modeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEWIDGET_H
#define UI_MODEWIDGET_H

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

class Ui_modeWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_14;
    QLabel *label_20;
    QPushButton *pushButton_designEtaUpper;
    QPushButton *pushButton_designEtaLower;
    QDoubleSpinBox *doubleSpinBox_eta;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox_fk;

    void setupUi(QWidget *modeWidget)
    {
        if (modeWidget->objectName().isEmpty())
            modeWidget->setObjectName(QString::fromUtf8("modeWidget"));
        modeWidget->resize(176, 324);
        modeWidget->setMinimumSize(QSize(0, 0));
        modeWidget->setMaximumSize(QSize(16777215, 400));
        gridLayout = new QGridLayout(modeWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_8 = new QGroupBox(modeWidget);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        QFont font;
        font.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        groupBox_8->setFont(font);
        gridLayout_14 = new QGridLayout(groupBox_8);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        label_20 = new QLabel(groupBox_8);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label_20->setFont(font1);
        label_20->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_20->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_14->addWidget(label_20, 0, 0, 1, 1);

        pushButton_designEtaUpper = new QPushButton(groupBox_8);
        pushButton_designEtaUpper->setObjectName(QString::fromUtf8("pushButton_designEtaUpper"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        pushButton_designEtaUpper->setFont(font2);
        pushButton_designEtaUpper->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));

        gridLayout_14->addWidget(pushButton_designEtaUpper, 1, 0, 1, 2);

        pushButton_designEtaLower = new QPushButton(groupBox_8);
        pushButton_designEtaLower->setObjectName(QString::fromUtf8("pushButton_designEtaLower"));
        pushButton_designEtaLower->setFont(font2);
        pushButton_designEtaLower->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));

        gridLayout_14->addWidget(pushButton_designEtaLower, 2, 0, 1, 2);

        doubleSpinBox_eta = new QDoubleSpinBox(groupBox_8);
        doubleSpinBox_eta->setObjectName(QString::fromUtf8("doubleSpinBox_eta"));
        doubleSpinBox_eta->setMaximumSize(QSize(100, 16777215));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Source Code Pro"));
        font3.setPointSize(9);
        font3.setBold(false);
        font3.setItalic(true);
        font3.setWeight(50);
        doubleSpinBox_eta->setFont(font3);

        gridLayout_14->addWidget(doubleSpinBox_eta, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_8, 0, 0, 1, 1);

        groupBox = new QGroupBox(modeWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 100));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font4.setPointSize(10);
        font4.setItalic(false);
        groupBox->setFont(font4);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBox_fk = new QCheckBox(groupBox);
        checkBox_fk->setObjectName(QString::fromUtf8("checkBox_fk"));
        checkBox_fk->setFont(font1);
        checkBox_fk->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(checkBox_fk, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);


        retranslateUi(modeWidget);

        QMetaObject::connectSlotsByName(modeWidget);
    } // setupUi

    void retranslateUi(QWidget *modeWidget)
    {
        modeWidget->setWindowTitle(QCoreApplication::translate("modeWidget", "Form", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("modeWidget", "FoilMode", nullptr));
        label_20->setText(QCoreApplication::translate("modeWidget", "Flap \316\267 \302\260", nullptr));
        pushButton_designEtaUpper->setText(QCoreApplication::translate("modeWidget", "smooth \316\267 upper", nullptr));
        pushButton_designEtaLower->setText(QCoreApplication::translate("modeWidget", "smooth \316\267 lower", nullptr));
        groupBox->setTitle(QCoreApplication::translate("modeWidget", "Wortman Flap", nullptr));
        checkBox_fk->setText(QCoreApplication::translate("modeWidget", "Extract", nullptr));
    } // retranslateUi

};

namespace Ui {
    class modeWidget: public Ui_modeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEWIDGET_H
