/********************************************************************************
** Form generated from reading UI file 'dock.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_H
#define UI_DOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "FoilPlotWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Dock
{
public:
    QAction *actionAbout;
    QAction *actionPreferences;
    QAction *actionfoilVisible;
    QAction *actionmodeVisible;
    QAction *actionFoilWindow;
    QAction *actionPressureWindow;
    QAction *actionPolarWindow;
    QAction *actionadd_FoilMode;
    QAction *actionColor;
    QAction *actionparametrize;
    QAction *actionAirfoils;
    QAction *actioncpPlot;
    QAction *actionPolars;
    QAction *actionsave;
    QAction *actionAirfoilfile;
    QAction *actionCoords;
    QAction *actiondelete_Airfoil;
    QAction *actiondelete_FoilMode;
    QAction *actionCheckOut_Parametrization;
    QAction *actionCheckOut_Coords;
    QAction *actionFocus_this_Mode;
    QAction *actionadd_AnalysisPoint;
    QAction *actionadd_ShapeFunction;
    QAction *actionadd_Polar;
    QAction *actionset_Name;
    QAction *actionsave_As;
    QAction *actionquit;
    QAction *actiondelete_AnalysisPoint;
    QAction *actiondelete_Polar;
    QAction *actioncalc_AllPolars;
    QAction *actiondelete_ShapeFunction;
    QAction *actionsave_Coords;
    QAction *actionsave_flapCoords;
    QWidget *centralwidget;
    QGridLayout *gridLayout_6;
    QSplitter *splitter;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeView;
    QFrame *frame;
    QGridLayout *gridLayout;
    FoilPlotWidget *foilPlotWidget;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollContents;
    QGridLayout *gridLayout_2;
    QFrame *frame_foil;
    QGridLayout *gridLayout_3;
    QVBoxLayout *layout_foil;
    QFrame *frame_analysis;
    QGridLayout *gridLayout_4;
    QVBoxLayout *layout_analysis;
    QFrame *frame_mode;
    QGridLayout *gridLayout_5;
    QVBoxLayout *layout_mode;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget_2;
    QMenuBar *menubar;
    QMenu *menuFoilBoXX;
    QMenu *menuadd_Airfoil_from;
    QMenu *menuAirfoil;
    QMenu *menuFoilMode;

    void setupUi(QMainWindow *Dock)
    {
        if (Dock->objectName().isEmpty())
            Dock->setObjectName(QString::fromUtf8("Dock"));
        Dock->setEnabled(true);
        Dock->resize(1684, 1163);
        Dock->setMinimumSize(QSize(0, 0));
        Dock->setDockNestingEnabled(true);
        actionAbout = new QAction(Dock);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionPreferences = new QAction(Dock);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        actionfoilVisible = new QAction(Dock);
        actionfoilVisible->setObjectName(QString::fromUtf8("actionfoilVisible"));
        actionfoilVisible->setCheckable(false);
        actionmodeVisible = new QAction(Dock);
        actionmodeVisible->setObjectName(QString::fromUtf8("actionmodeVisible"));
        actionFoilWindow = new QAction(Dock);
        actionFoilWindow->setObjectName(QString::fromUtf8("actionFoilWindow"));
        actionPressureWindow = new QAction(Dock);
        actionPressureWindow->setObjectName(QString::fromUtf8("actionPressureWindow"));
        actionPolarWindow = new QAction(Dock);
        actionPolarWindow->setObjectName(QString::fromUtf8("actionPolarWindow"));
        actionadd_FoilMode = new QAction(Dock);
        actionadd_FoilMode->setObjectName(QString::fromUtf8("actionadd_FoilMode"));
        actionColor = new QAction(Dock);
        actionColor->setObjectName(QString::fromUtf8("actionColor"));
        actionparametrize = new QAction(Dock);
        actionparametrize->setObjectName(QString::fromUtf8("actionparametrize"));
        actionparametrize->setEnabled(false);
        actionAirfoils = new QAction(Dock);
        actionAirfoils->setObjectName(QString::fromUtf8("actionAirfoils"));
        actionAirfoils->setCheckable(true);
        actionAirfoils->setChecked(true);
        actioncpPlot = new QAction(Dock);
        actioncpPlot->setObjectName(QString::fromUtf8("actioncpPlot"));
        actioncpPlot->setCheckable(true);
        actioncpPlot->setChecked(true);
        actionPolars = new QAction(Dock);
        actionPolars->setObjectName(QString::fromUtf8("actionPolars"));
        actionPolars->setCheckable(true);
        actionPolars->setChecked(true);
        actionsave = new QAction(Dock);
        actionsave->setObjectName(QString::fromUtf8("actionsave"));
        actionAirfoilfile = new QAction(Dock);
        actionAirfoilfile->setObjectName(QString::fromUtf8("actionAirfoilfile"));
        actionCoords = new QAction(Dock);
        actionCoords->setObjectName(QString::fromUtf8("actionCoords"));
        actiondelete_Airfoil = new QAction(Dock);
        actiondelete_Airfoil->setObjectName(QString::fromUtf8("actiondelete_Airfoil"));
        actiondelete_FoilMode = new QAction(Dock);
        actiondelete_FoilMode->setObjectName(QString::fromUtf8("actiondelete_FoilMode"));
        actionCheckOut_Parametrization = new QAction(Dock);
        actionCheckOut_Parametrization->setObjectName(QString::fromUtf8("actionCheckOut_Parametrization"));
        actionCheckOut_Parametrization->setEnabled(false);
        actionCheckOut_Coords = new QAction(Dock);
        actionCheckOut_Coords->setObjectName(QString::fromUtf8("actionCheckOut_Coords"));
        actionFocus_this_Mode = new QAction(Dock);
        actionFocus_this_Mode->setObjectName(QString::fromUtf8("actionFocus_this_Mode"));
        actionadd_AnalysisPoint = new QAction(Dock);
        actionadd_AnalysisPoint->setObjectName(QString::fromUtf8("actionadd_AnalysisPoint"));
        actionadd_ShapeFunction = new QAction(Dock);
        actionadd_ShapeFunction->setObjectName(QString::fromUtf8("actionadd_ShapeFunction"));
        actionadd_Polar = new QAction(Dock);
        actionadd_Polar->setObjectName(QString::fromUtf8("actionadd_Polar"));
        actionset_Name = new QAction(Dock);
        actionset_Name->setObjectName(QString::fromUtf8("actionset_Name"));
        actionsave_As = new QAction(Dock);
        actionsave_As->setObjectName(QString::fromUtf8("actionsave_As"));
        actionquit = new QAction(Dock);
        actionquit->setObjectName(QString::fromUtf8("actionquit"));
        actiondelete_AnalysisPoint = new QAction(Dock);
        actiondelete_AnalysisPoint->setObjectName(QString::fromUtf8("actiondelete_AnalysisPoint"));
        actiondelete_Polar = new QAction(Dock);
        actiondelete_Polar->setObjectName(QString::fromUtf8("actiondelete_Polar"));
        actioncalc_AllPolars = new QAction(Dock);
        actioncalc_AllPolars->setObjectName(QString::fromUtf8("actioncalc_AllPolars"));
        actiondelete_ShapeFunction = new QAction(Dock);
        actiondelete_ShapeFunction->setObjectName(QString::fromUtf8("actiondelete_ShapeFunction"));
        actionsave_Coords = new QAction(Dock);
        actionsave_Coords->setObjectName(QString::fromUtf8("actionsave_Coords"));
        actionsave_flapCoords = new QAction(Dock);
        actionsave_flapCoords->setObjectName(QString::fromUtf8("actionsave_flapCoords"));
        centralwidget = new QWidget(Dock);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_6 = new QGridLayout(centralwidget);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        horizontalLayoutWidget = new QWidget(splitter);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        treeView = new QTreeWidget(horizontalLayoutWidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);
        treeView->setMinimumSize(QSize(300, 0));
        treeView->setMaximumSize(QSize(300, 16777215));
        treeView->setStyleSheet(QString::fromUtf8("/*background-image: url(:/images/FoilBox_Logo15.png);\n"
"background-repeat: no-repeat;\n"
"background-attachment: fixed;\n"
"background-position: bottom left;\n"
"background-color: rgb(255, 255, 255);"));
        treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        treeView->setAlternatingRowColors(true);
        treeView->setIndentation(10);
        treeView->setRootIsDecorated(true);
        treeView->setSortingEnabled(true);
        treeView->setHeaderHidden(false);
        treeView->setColumnCount(3);
        treeView->header()->setVisible(true);
        treeView->header()->setCascadingSectionResizes(true);
        treeView->header()->setDefaultSectionSize(111);
        treeView->header()->setProperty("showSortIndicator", QVariant(false));
        treeView->header()->setStretchLastSection(false);

        horizontalLayout->addWidget(treeView);

        frame = new QFrame(horizontalLayoutWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        foilPlotWidget = new FoilPlotWidget(frame);
        foilPlotWidget->setObjectName(QString::fromUtf8("foilPlotWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(5);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(foilPlotWidget->sizePolicy().hasHeightForWidth());
        foilPlotWidget->setSizePolicy(sizePolicy2);
        foilPlotWidget->setMinimumSize(QSize(50, 50));

        gridLayout->addWidget(foilPlotWidget, 0, 0, 1, 1);


        horizontalLayout->addWidget(frame);

        splitter->addWidget(horizontalLayoutWidget);
        horizontalLayoutWidget_2 = new QWidget(splitter);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(horizontalLayoutWidget_2);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy3);
        scrollArea->setMinimumSize(QSize(300, 0));
        scrollArea->setMaximumSize(QSize(300, 16777215));
        scrollArea->setFocusPolicy(Qt::StrongFocus);
        scrollArea->setWidgetResizable(true);
        scrollContents = new QWidget();
        scrollContents->setObjectName(QString::fromUtf8("scrollContents"));
        scrollContents->setGeometry(QRect(0, 0, 294, 465));
        gridLayout_2 = new QGridLayout(scrollContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        frame_foil = new QFrame(scrollContents);
        frame_foil->setObjectName(QString::fromUtf8("frame_foil"));
        frame_foil->setAutoFillBackground(true);
        frame_foil->setStyleSheet(QString::fromUtf8(""));
        frame_foil->setFrameShape(QFrame::NoFrame);
        frame_foil->setFrameShadow(QFrame::Sunken);
        gridLayout_3 = new QGridLayout(frame_foil);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        layout_foil = new QVBoxLayout();
        layout_foil->setObjectName(QString::fromUtf8("layout_foil"));

        gridLayout_3->addLayout(layout_foil, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_foil, 1, 0, 1, 1);

        frame_analysis = new QFrame(scrollContents);
        frame_analysis->setObjectName(QString::fromUtf8("frame_analysis"));
        frame_analysis->setAutoFillBackground(true);
        frame_analysis->setStyleSheet(QString::fromUtf8(""));
        frame_analysis->setFrameShape(QFrame::NoFrame);
        frame_analysis->setFrameShadow(QFrame::Sunken);
        gridLayout_4 = new QGridLayout(frame_analysis);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        layout_analysis = new QVBoxLayout();
        layout_analysis->setObjectName(QString::fromUtf8("layout_analysis"));

        gridLayout_4->addLayout(layout_analysis, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_analysis, 3, 0, 1, 1);

        frame_mode = new QFrame(scrollContents);
        frame_mode->setObjectName(QString::fromUtf8("frame_mode"));
        frame_mode->setAutoFillBackground(true);
        frame_mode->setStyleSheet(QString::fromUtf8(""));
        frame_mode->setFrameShape(QFrame::NoFrame);
        frame_mode->setFrameShadow(QFrame::Sunken);
        gridLayout_5 = new QGridLayout(frame_mode);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        layout_mode = new QVBoxLayout();
        layout_mode->setObjectName(QString::fromUtf8("layout_mode"));

        gridLayout_5->addLayout(layout_mode, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_mode, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 4, 0, 1, 1);

        scrollArea->setWidget(scrollContents);

        horizontalLayout_2->addWidget(scrollArea);

        stackedWidget_2 = new QStackedWidget(horizontalLayoutWidget_2);
        stackedWidget_2->setObjectName(QString::fromUtf8("stackedWidget_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(6);
        sizePolicy4.setVerticalStretch(5);
        sizePolicy4.setHeightForWidth(stackedWidget_2->sizePolicy().hasHeightForWidth());
        stackedWidget_2->setSizePolicy(sizePolicy4);
        stackedWidget_2->setMinimumSize(QSize(100, 0));
        stackedWidget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        stackedWidget_2->setFrameShape(QFrame::Box);
        stackedWidget_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(stackedWidget_2);

        splitter->addWidget(horizontalLayoutWidget_2);

        gridLayout_6->addWidget(splitter, 0, 0, 1, 1);

        Dock->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Dock);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1684, 31));
        menuFoilBoXX = new QMenu(menubar);
        menuFoilBoXX->setObjectName(QString::fromUtf8("menuFoilBoXX"));
        menuadd_Airfoil_from = new QMenu(menuFoilBoXX);
        menuadd_Airfoil_from->setObjectName(QString::fromUtf8("menuadd_Airfoil_from"));
        menuAirfoil = new QMenu(menubar);
        menuAirfoil->setObjectName(QString::fromUtf8("menuAirfoil"));
        menuFoilMode = new QMenu(menubar);
        menuFoilMode->setObjectName(QString::fromUtf8("menuFoilMode"));
        Dock->setMenuBar(menubar);

        menubar->addAction(menuFoilBoXX->menuAction());
        menubar->addAction(menuAirfoil->menuAction());
        menubar->addAction(menuFoilMode->menuAction());
        menuFoilBoXX->addSeparator();
        menuFoilBoXX->addAction(menuadd_Airfoil_from->menuAction());
        menuFoilBoXX->addSeparator();
        menuFoilBoXX->addSeparator();
        menuFoilBoXX->addAction(actionquit);
        menuadd_Airfoil_from->addAction(actionAirfoilfile);
        menuadd_Airfoil_from->addAction(actionCoords);
        menuAirfoil->addSeparator();
        menuAirfoil->addAction(actionsave);
        menuAirfoil->addAction(actionsave_As);
        menuAirfoil->addAction(actiondelete_Airfoil);
        menuAirfoil->addSeparator();
        menuAirfoil->addAction(actionset_Name);
        menuAirfoil->addSeparator();
        menuAirfoil->addAction(actionadd_ShapeFunction);
        menuAirfoil->addAction(actiondelete_ShapeFunction);
        menuAirfoil->addAction(actionadd_FoilMode);
        menuAirfoil->addSeparator();
        menuFoilMode->addSeparator();
        menuFoilMode->addAction(actiondelete_FoilMode);
        menuFoilMode->addSeparator();
        menuFoilMode->addAction(actionadd_AnalysisPoint);
        menuFoilMode->addAction(actiondelete_AnalysisPoint);
        menuFoilMode->addSeparator();
        menuFoilMode->addAction(actionadd_Polar);
        menuFoilMode->addAction(actiondelete_Polar);
        menuFoilMode->addAction(actionsave_Coords);
        menuFoilMode->addAction(actionsave_flapCoords);

        retranslateUi(Dock);

        QMetaObject::connectSlotsByName(Dock);
    } // setupUi

    void retranslateUi(QMainWindow *Dock)
    {
        Dock->setWindowTitle(QCoreApplication::translate("Dock", "FoilBoXX", nullptr));
        actionAbout->setText(QCoreApplication::translate("Dock", "About", nullptr));
        actionPreferences->setText(QCoreApplication::translate("Dock", "Preferences", nullptr));
        actionfoilVisible->setText(QCoreApplication::translate("Dock", "Toggle Visible", nullptr));
#if QT_CONFIG(shortcut)
        actionfoilVisible->setShortcut(QCoreApplication::translate("Dock", "Ctrl+G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionmodeVisible->setText(QCoreApplication::translate("Dock", "Toggle Visible", nullptr));
#if QT_CONFIG(shortcut)
        actionmodeVisible->setShortcut(QCoreApplication::translate("Dock", "Ctrl+M", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFoilWindow->setText(QCoreApplication::translate("Dock", "FoilWindow", nullptr));
        actionPressureWindow->setText(QCoreApplication::translate("Dock", "PressureWindow", nullptr));
        actionPolarWindow->setText(QCoreApplication::translate("Dock", "PolarWindow", nullptr));
        actionadd_FoilMode->setText(QCoreApplication::translate("Dock", "add FoilMode", nullptr));
        actionColor->setText(QCoreApplication::translate("Dock", "Color", nullptr));
        actionparametrize->setText(QCoreApplication::translate("Dock", "parametrize", nullptr));
        actionAirfoils->setText(QCoreApplication::translate("Dock", "airfoils", nullptr));
        actioncpPlot->setText(QCoreApplication::translate("Dock", "cp-Plot", nullptr));
        actionPolars->setText(QCoreApplication::translate("Dock", "polars", nullptr));
        actionsave->setText(QCoreApplication::translate("Dock", "save Airfoil", nullptr));
        actionAirfoilfile->setText(QCoreApplication::translate("Dock", "Airfoilfile *.af", nullptr));
        actionCoords->setText(QCoreApplication::translate("Dock", "Coords *.dat", nullptr));
        actiondelete_Airfoil->setText(QCoreApplication::translate("Dock", "Delete Airfoil", nullptr));
        actiondelete_FoilMode->setText(QCoreApplication::translate("Dock", "Delete FoilMode", nullptr));
        actionCheckOut_Parametrization->setText(QCoreApplication::translate("Dock", "CheckOut Parametrization", nullptr));
        actionCheckOut_Coords->setText(QCoreApplication::translate("Dock", "CheckOut Coords", nullptr));
        actionFocus_this_Mode->setText(QCoreApplication::translate("Dock", "Focus this Mode", nullptr));
#if QT_CONFIG(shortcut)
        actionFocus_this_Mode->setShortcut(QCoreApplication::translate("Dock", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionadd_AnalysisPoint->setText(QCoreApplication::translate("Dock", "add AnalysisPoint", nullptr));
        actionadd_ShapeFunction->setText(QCoreApplication::translate("Dock", "add ShapeFunction", nullptr));
        actionadd_Polar->setText(QCoreApplication::translate("Dock", "add Polar", nullptr));
        actionset_Name->setText(QCoreApplication::translate("Dock", "set Name", nullptr));
        actionsave_As->setText(QCoreApplication::translate("Dock", "save Airfoil as...", nullptr));
        actionquit->setText(QCoreApplication::translate("Dock", "Quit", nullptr));
        actiondelete_AnalysisPoint->setText(QCoreApplication::translate("Dock", "delete AnalysisPoint", nullptr));
        actiondelete_Polar->setText(QCoreApplication::translate("Dock", "delete Polar", nullptr));
        actioncalc_AllPolars->setText(QCoreApplication::translate("Dock", "calc all Polars", nullptr));
        actiondelete_ShapeFunction->setText(QCoreApplication::translate("Dock", "delete ShapeFunction", nullptr));
        actionsave_Coords->setText(QCoreApplication::translate("Dock", "save Coords", nullptr));
        actionsave_flapCoords->setText(QCoreApplication::translate("Dock", "save flapCoords", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeView->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("Dock", "visible", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("Dock", "modify", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Dock", "Item", nullptr));
        menuFoilBoXX->setTitle(QCoreApplication::translate("Dock", "FoilBoXX", nullptr));
        menuadd_Airfoil_from->setTitle(QCoreApplication::translate("Dock", "add Airfoil from..", nullptr));
        menuAirfoil->setTitle(QCoreApplication::translate("Dock", "Airfoil", nullptr));
        menuFoilMode->setTitle(QCoreApplication::translate("Dock", "FoilMode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dock: public Ui_Dock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_H
