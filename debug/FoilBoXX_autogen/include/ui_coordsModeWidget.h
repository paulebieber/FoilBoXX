/********************************************************************************
** Form generated from reading UI file 'coordsModeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COORDSMODEWIDGET_H
#define UI_COORDSMODEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_coordsModeWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_Turb;
    QGridLayout *gridLayout_15;
    QLabel *label_29;
    QLabel *label_28;
    QDoubleSpinBox *doubleSpinBox_turbTop;
    QDoubleSpinBox *doubleSpinBox_turbBot;

    void setupUi(QWidget *coordsModeWidget)
    {
        if (coordsModeWidget->objectName().isEmpty())
            coordsModeWidget->setObjectName(QString::fromUtf8("coordsModeWidget"));
        coordsModeWidget->resize(195, 146);
        coordsModeWidget->setMaximumSize(QSize(16777215, 200));
        gridLayout = new QGridLayout(coordsModeWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_Turb = new QGroupBox(coordsModeWidget);
        groupBox_Turb->setObjectName(QString::fromUtf8("groupBox_Turb"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(groupBox_Turb->sizePolicy().hasHeightForWidth());
        groupBox_Turb->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        groupBox_Turb->setFont(font);
        groupBox_Turb->setCheckable(true);
        groupBox_Turb->setChecked(false);
        gridLayout_15 = new QGridLayout(groupBox_Turb);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        label_29 = new QLabel(groupBox_Turb);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(2);
        sizePolicy1.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy1);
        label_29->setMaximumSize(QSize(70, 1600000));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setKerning(true);
        label_29->setFont(font1);
        label_29->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_29->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_15->addWidget(label_29, 1, 0, 1, 1);

        label_28 = new QLabel(groupBox_Turb);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        sizePolicy1.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy1);
        label_28->setMaximumSize(QSize(50, 1600000));
        label_28->setFont(font1);
        label_28->setLayoutDirection(Qt::LeftToRight);
        label_28->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_28->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_15->addWidget(label_28, 0, 0, 1, 1);

        doubleSpinBox_turbTop = new QDoubleSpinBox(groupBox_Turb);
        doubleSpinBox_turbTop->setObjectName(QString::fromUtf8("doubleSpinBox_turbTop"));
        doubleSpinBox_turbTop->setEnabled(true);
        doubleSpinBox_turbTop->setMaximumSize(QSize(100, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Source Code Pro"));
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setItalic(true);
        font2.setWeight(50);
        doubleSpinBox_turbTop->setFont(font2);

        gridLayout_15->addWidget(doubleSpinBox_turbTop, 0, 1, 1, 1);

        doubleSpinBox_turbBot = new QDoubleSpinBox(groupBox_Turb);
        doubleSpinBox_turbBot->setObjectName(QString::fromUtf8("doubleSpinBox_turbBot"));
        doubleSpinBox_turbBot->setEnabled(true);
        doubleSpinBox_turbBot->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_turbBot->setFont(font2);

        gridLayout_15->addWidget(doubleSpinBox_turbBot, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox_Turb, 0, 0, 1, 1);


        retranslateUi(coordsModeWidget);

        QMetaObject::connectSlotsByName(coordsModeWidget);
    } // setupUi

    void retranslateUi(QWidget *coordsModeWidget)
    {
        coordsModeWidget->setWindowTitle(QCoreApplication::translate("coordsModeWidget", "Form", nullptr));
        groupBox_Turb->setTitle(QCoreApplication::translate("coordsModeWidget", "Turbulator", nullptr));
        label_29->setText(QCoreApplication::translate("coordsModeWidget", "Bottom", nullptr));
        label_28->setText(QCoreApplication::translate("coordsModeWidget", "Top", nullptr));
    } // retranslateUi

};

namespace Ui {
    class coordsModeWidget: public Ui_coordsModeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COORDSMODEWIDGET_H
