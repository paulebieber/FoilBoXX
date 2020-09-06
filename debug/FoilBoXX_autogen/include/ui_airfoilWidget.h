/********************************************************************************
** Form generated from reading UI file 'airfoilWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AIRFOILWIDGET_H
#define UI_AIRFOILWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_airfoilWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_fk;
    QGridLayout *gridLayout_8;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBox_fkChordFactor;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_12;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_yPlus;
    QDoubleSpinBox *doubleSpinBox_yMinus;
    QDoubleSpinBox *doubleSpinBox_flapY;
    QDoubleSpinBox *doubleSpinBox_flapX;
    QDoubleSpinBox *doubleSpinBox_yNose;
    QDoubleSpinBox *doubleSpinBox_flapY_rel;
    QLabel *label_24;
    QLabel *label_11;
    QLabel *label_17;
    QLabel *label_thickness;
    QLabel *thickness;
    QGroupBox *groupBox_Turb;
    QGridLayout *gridLayout_15;
    QLabel *label_28;
    QLabel *label_29;
    QDoubleSpinBox *doubleSpinBox_turbTop;
    QDoubleSpinBox *doubleSpinBox_turbBot;
    QPushButton *pushButton_calcPolarAll;

    void setupUi(QWidget *airfoilWidget)
    {
        if (airfoilWidget->objectName().isEmpty())
            airfoilWidget->setObjectName(QString::fromUtf8("airfoilWidget"));
        airfoilWidget->resize(247, 505);
        airfoilWidget->setMaximumSize(QSize(16777215, 600));
        gridLayout = new QGridLayout(airfoilWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_fk = new QGroupBox(airfoilWidget);
        groupBox_fk->setObjectName(QString::fromUtf8("groupBox_fk"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(groupBox_fk->sizePolicy().hasHeightForWidth());
        groupBox_fk->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        groupBox_fk->setFont(font);
        groupBox_fk->setFlat(false);
        groupBox_fk->setCheckable(true);
        groupBox_fk->setChecked(false);
        gridLayout_8 = new QGridLayout(groupBox_fk);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_16 = new QLabel(groupBox_fk);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(2);
        sizePolicy1.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy1);
        label_16->setMinimumSize(QSize(105, 0));
        label_16->setMaximumSize(QSize(125, 16777215));
        label_16->setFont(font);
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_16->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_16, 0, 0, 1, 1);

        doubleSpinBox_fkChordFactor = new QDoubleSpinBox(groupBox_fk);
        doubleSpinBox_fkChordFactor->setObjectName(QString::fromUtf8("doubleSpinBox_fkChordFactor"));
        doubleSpinBox_fkChordFactor->setEnabled(false);
        doubleSpinBox_fkChordFactor->setMaximumSize(QSize(100, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Source Code Pro"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setItalic(true);
        font1.setWeight(50);
        doubleSpinBox_fkChordFactor->setFont(font1);

        gridLayout_8->addWidget(doubleSpinBox_fkChordFactor, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_fk, 4, 0, 1, 1);

        groupBox_7 = new QGroupBox(airfoilWidget);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(3);
        sizePolicy2.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        groupBox_7->setFont(font2);
        groupBox_7->setFlat(false);
        gridLayout_12 = new QGridLayout(groupBox_7);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_9 = new QLabel(groupBox_7);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);
        label_9->setMinimumSize(QSize(0, 30));
        label_9->setMaximumSize(QSize(125, 30));
        label_9->setFont(font);
        label_9->setLayoutDirection(Qt::LeftToRight);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_12->addWidget(label_9, 6, 0, 1, 1);

        label_10 = new QLabel(groupBox_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy3.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy3);
        label_10->setMinimumSize(QSize(0, 30));
        label_10->setMaximumSize(QSize(125, 30));
        label_10->setFont(font);
        label_10->setLayoutDirection(Qt::LeftToRight);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_12->addWidget(label_10, 7, 0, 1, 1);

        label_12 = new QLabel(groupBox_7);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy3.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy3);
        label_12->setMinimumSize(QSize(0, 30));
        label_12->setMaximumSize(QSize(125, 30));
        label_12->setFont(font);
        label_12->setLayoutDirection(Qt::LeftToRight);
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_12->addWidget(label_12, 5, 0, 1, 1);

        doubleSpinBox_yPlus = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_yPlus->setObjectName(QString::fromUtf8("doubleSpinBox_yPlus"));
        doubleSpinBox_yPlus->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_yPlus->setFont(font1);

        gridLayout_12->addWidget(doubleSpinBox_yPlus, 6, 1, 1, 1);

        doubleSpinBox_yMinus = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_yMinus->setObjectName(QString::fromUtf8("doubleSpinBox_yMinus"));
        doubleSpinBox_yMinus->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_yMinus->setFont(font1);

        gridLayout_12->addWidget(doubleSpinBox_yMinus, 7, 1, 1, 1);

        doubleSpinBox_flapY = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_flapY->setObjectName(QString::fromUtf8("doubleSpinBox_flapY"));
        doubleSpinBox_flapY->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_flapY->setFont(font1);

        gridLayout_12->addWidget(doubleSpinBox_flapY, 2, 1, 1, 1);

        doubleSpinBox_flapX = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_flapX->setObjectName(QString::fromUtf8("doubleSpinBox_flapX"));
        doubleSpinBox_flapX->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_flapX->setFont(font1);

        gridLayout_12->addWidget(doubleSpinBox_flapX, 1, 1, 1, 1);

        doubleSpinBox_yNose = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_yNose->setObjectName(QString::fromUtf8("doubleSpinBox_yNose"));
        doubleSpinBox_yNose->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_yNose->setFont(font1);

        gridLayout_12->addWidget(doubleSpinBox_yNose, 5, 1, 1, 1);

        doubleSpinBox_flapY_rel = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_flapY_rel->setObjectName(QString::fromUtf8("doubleSpinBox_flapY_rel"));
        doubleSpinBox_flapY_rel->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_flapY_rel->setFont(font1);

        gridLayout_12->addWidget(doubleSpinBox_flapY_rel, 3, 1, 1, 1);

        label_24 = new QLabel(groupBox_7);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(2);
        sizePolicy4.setVerticalStretch(2);
        sizePolicy4.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy4);
        label_24->setMinimumSize(QSize(0, 20));
        label_24->setMaximumSize(QSize(125, 20));
        label_24->setFont(font);
        label_24->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_24->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_12->addWidget(label_24, 1, 0, 1, 1);

        label_11 = new QLabel(groupBox_7);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy4.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy4);
        label_11->setMinimumSize(QSize(0, 20));
        label_11->setMaximumSize(QSize(125, 20));
        label_11->setFont(font);
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_11->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_12->addWidget(label_11, 2, 0, 1, 1);

        label_17 = new QLabel(groupBox_7);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(2);
        sizePolicy5.setVerticalStretch(2);
        sizePolicy5.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy5);
        label_17->setMinimumSize(QSize(0, 25));
        label_17->setMaximumSize(QSize(125, 25));
        label_17->setFont(font);
        label_17->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_17->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_12->addWidget(label_17, 3, 0, 1, 1);

        label_thickness = new QLabel(groupBox_7);
        label_thickness->setObjectName(QString::fromUtf8("label_thickness"));
        sizePolicy4.setHeightForWidth(label_thickness->sizePolicy().hasHeightForWidth());
        label_thickness->setSizePolicy(sizePolicy4);
        label_thickness->setMinimumSize(QSize(0, 20));
        label_thickness->setMaximumSize(QSize(125, 20));
        label_thickness->setFont(font);
        label_thickness->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_thickness->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_12->addWidget(label_thickness, 0, 0, 1, 1);

        thickness = new QLabel(groupBox_7);
        thickness->setObjectName(QString::fromUtf8("thickness"));
        sizePolicy4.setHeightForWidth(thickness->sizePolicy().hasHeightForWidth());
        thickness->setSizePolicy(sizePolicy4);
        thickness->setMinimumSize(QSize(0, 25));
        thickness->setMaximumSize(QSize(125, 25));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font3.setPointSize(13);
        font3.setBold(true);
        font3.setItalic(true);
        font3.setWeight(75);
        thickness->setFont(font3);
        thickness->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        thickness->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout_12->addWidget(thickness, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_7, 0, 0, 2, 1);

        groupBox_Turb = new QGroupBox(airfoilWidget);
        groupBox_Turb->setObjectName(QString::fromUtf8("groupBox_Turb"));
        sizePolicy.setHeightForWidth(groupBox_Turb->sizePolicy().hasHeightForWidth());
        groupBox_Turb->setSizePolicy(sizePolicy);
        groupBox_Turb->setFont(font);
        groupBox_Turb->setFlat(false);
        groupBox_Turb->setCheckable(true);
        groupBox_Turb->setChecked(false);
        gridLayout_15 = new QGridLayout(groupBox_Turb);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        label_28 = new QLabel(groupBox_Turb);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(2);
        sizePolicy6.setVerticalStretch(2);
        sizePolicy6.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy6);
        label_28->setMaximumSize(QSize(125, 1600000));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setUnderline(false);
        font4.setWeight(50);
        font4.setKerning(true);
        label_28->setFont(font4);
        label_28->setLayoutDirection(Qt::LeftToRight);
        label_28->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_28->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_15->addWidget(label_28, 0, 0, 1, 1);

        label_29 = new QLabel(groupBox_Turb);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        sizePolicy6.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy6);
        label_29->setMaximumSize(QSize(125, 1600000));
        label_29->setFont(font4);
        label_29->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_29->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_15->addWidget(label_29, 1, 0, 1, 1);

        doubleSpinBox_turbTop = new QDoubleSpinBox(groupBox_Turb);
        doubleSpinBox_turbTop->setObjectName(QString::fromUtf8("doubleSpinBox_turbTop"));
        doubleSpinBox_turbTop->setEnabled(false);
        doubleSpinBox_turbTop->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_turbTop->setFont(font1);

        gridLayout_15->addWidget(doubleSpinBox_turbTop, 0, 1, 1, 1);

        doubleSpinBox_turbBot = new QDoubleSpinBox(groupBox_Turb);
        doubleSpinBox_turbBot->setObjectName(QString::fromUtf8("doubleSpinBox_turbBot"));
        doubleSpinBox_turbBot->setEnabled(false);
        doubleSpinBox_turbBot->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_turbBot->setFont(font1);

        gridLayout_15->addWidget(doubleSpinBox_turbBot, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox_Turb, 3, 0, 1, 1);

        pushButton_calcPolarAll = new QPushButton(airfoilWidget);
        pushButton_calcPolarAll->setObjectName(QString::fromUtf8("pushButton_calcPolarAll"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(1);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(pushButton_calcPolarAll->sizePolicy().hasHeightForWidth());
        pushButton_calcPolarAll->setSizePolicy(sizePolicy7);
        pushButton_calcPolarAll->setMinimumSize(QSize(100, 0));
        pushButton_calcPolarAll->setMaximumSize(QSize(100, 16777215));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Noto Serif Thai Med"));
        font5.setPointSize(9);
        font5.setBold(false);
        font5.setItalic(false);
        font5.setWeight(50);
        pushButton_calcPolarAll->setFont(font5);

        gridLayout->addWidget(pushButton_calcPolarAll, 5, 0, 1, 1);


        retranslateUi(airfoilWidget);

        QMetaObject::connectSlotsByName(airfoilWidget);
    } // setupUi

    void retranslateUi(QWidget *airfoilWidget)
    {
        airfoilWidget->setWindowTitle(QCoreApplication::translate("airfoilWidget", "Form", nullptr));
        groupBox_fk->setTitle(QCoreApplication::translate("airfoilWidget", "Wortman Flap", nullptr));
        label_16->setText(QCoreApplication::translate("airfoilWidget", "Chordfactor", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("airfoilWidget", "Airfoil", nullptr));
        label_9->setText(QCoreApplication::translate("airfoilWidget", "y_Plus", nullptr));
        label_10->setText(QCoreApplication::translate("airfoilWidget", "y_Minus", nullptr));
        label_12->setText(QCoreApplication::translate("airfoilWidget", "nose Y", nullptr));
        label_24->setText(QCoreApplication::translate("airfoilWidget", "flap X", nullptr));
        label_11->setText(QCoreApplication::translate("airfoilWidget", "flap Y", nullptr));
        label_17->setText(QCoreApplication::translate("airfoilWidget", "flap Y rel.", nullptr));
        label_thickness->setText(QCoreApplication::translate("airfoilWidget", "thickness", nullptr));
        thickness->setText(QString());
        groupBox_Turb->setTitle(QCoreApplication::translate("airfoilWidget", "Turbulator", nullptr));
        label_28->setText(QCoreApplication::translate("airfoilWidget", "Top", nullptr));
        label_29->setText(QCoreApplication::translate("airfoilWidget", "Bottom", nullptr));
        pushButton_calcPolarAll->setText(QCoreApplication::translate("airfoilWidget", "Calc all Polars", nullptr));
    } // retranslateUi

};

namespace Ui {
    class airfoilWidget: public Ui_airfoilWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AIRFOILWIDGET_H
