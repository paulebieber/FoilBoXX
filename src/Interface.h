// Created by paul on 3/11/20.

#pragma once 

#include <vector>
#include <QObject>
#include <QApplication>

#include "ui_dock.h"
#include "AirfoilInterface.h"
#include "FoilMode.h"
#include "FoilPlot.h"
#include "ModePlot.h"
#include "Polar.h"
#include "PolarGoal.h"
#include "AnalysisPoint.h"
#include "PolarPlotWidget.h"
#include "PressurePlotWidget.h"
#include "Optimization.h"

class Interface: public QMainWindow, public Ui_Dock{

Q_OBJECT

    enum loadType{Scratch,fromFile,fromCoords};
    enum saveType{af,coords};

    QString fileVersion;
    
    //Settings:
    //SettingsInterface* settingsInterface;
    //Settings* settings;
    
    QApplication& app;
    QString version;

    OptimizationThread optimizationThread;

    //Windows
    PolarPlotWidget* polarPlotWidget;
    PressurePlotWidget* pressurePlotWidget;

    //FoilManagement
    void connectBarGeneral();
    void connectBarAirfoil(AirfoilInterface* airfoil){};
    void newFoil(bool fromStart = false);
    void deleteAirfoil(AirfoilInterface* airfoil);
    void newPolar(FoilMode* mode);
    void newPolarGoal(Polar* polar);
    void newFoilMode(AirfoilInterface* airfoil, bool fromStart = false, QTextStream* in = nullptr);
    void deleteMode(FoilMode* mode);
    void deleteBernsteinShape(BernsteinShapeInterface* shape);
    void deleteAnalysisPt(AnalysisPoint* pt);
    void deletePolar(Polar* polar);
    void deletePolarGoal(PolarGoal* polarGoal);
    void newAnalysisPoint(FoilMode* mode);
    void setAirfoilName();
    void writeAirfoil(AirfoilInterface* airfoil);
    void saveCoords(FoilMode* mode);
    void saveFlap(FoilMode* mode);
    void saveAirfoil(AirfoilInterface* airfoil);
    void saveAirfoilAs(AirfoilInterface* airfoil);
    void loadAirfoil();
    void loadCoords();
    BernsteinShapeInterface* newBernsteinShape(AirfoilInterface* airfoil);

    //Optimization
    void optimizePolars(AirfoilInterface* airfoil);

    std::vector<AirfoilInterface*> airfoils;
    std::vector<FoilMode*> modes;
    std::vector<AnalysisPoint*> analysisPts;
    std::vector<Polar*> polars;
    std::vector<PolarGoal*> polarGoals;
    std::vector<FoilPlot*> foilPlots;
    std::vector<BernsteinShapeInterface*> bernsteinShapes;

    AirfoilInterface* activeAirfoil = nullptr;
    FoilMode* activeMode = nullptr;
    AnalysisPoint* activeAnalysisPt = nullptr;
    Polar* activePolar = nullptr;
    PolarGoal* activePolarGoal = nullptr;
    BernsteinShapeInterface* activeShape = nullptr;
    
    // Plotting:
    QString styleActive = QString("background-color: rgb(238,238,236);\ncolor: rgb(0,0,0);");
    QString styleInactive = QString("background-color: rgb(238,238,236);\ncolor: rgb(150,150,150);");
    void changeColor();

    // For Plotting while opt
    void plotShapes(BernsteinShape* shape);
    void plotPolar(Polar* polar);


public:
    Interface(QApplication& app, QString version);

};

