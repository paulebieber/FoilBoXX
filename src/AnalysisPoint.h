// Created by paul on 4/5/20.

#pragma once

#include "Analysis.h"
#include "ui_analysisPointWidget.h"
#include "QwtCustomPlot.h"
#include "armadillo"

class AnalysisPoint: public Analysis{

Q_OBJECT

friend QDataStream& operator<<(QDataStream& out, const AnalysisPoint& analysis); //For Serrialization, (saving the Airfoil)
friend QDataStream& operator>>(QDataStream& in, AnalysisPoint& analysis); //For Serrialization, (loading the Airfoil)

    double alpha, cl;
    bool viscous;
     
    //Mode
    QMetaObject::Connection modeConnection;

    //Interface
    void setItemText();

    //Plotting
    QwtCustomPlot* pressurePlot;
    QwtCustomPlot* foilPlot;
    QwtPlotCurve* curve = new QwtPlotCurve();
    QwtPlotCurve* viscCurve = new QwtPlotCurve();
    QPen bigPen;
    QPen smallPen;
    double baseSize;

    //UI
    void setupInterface();
    void setInterfaceValues();
    Ui_analysisPointWidget ui;
    void onVisible(bool visible);
    void onActivation(bool active, bool recursively = false); //Gets called if Hierarchyelement gets activated

public:
    AnalysisPoint(FoilMode* mode, QwtCustomPlot* pressurePlot);
    ~AnalysisPoint();
    void calc();
    void plot();
    void setCurveColor(QColor);
    void connectToMode(FoilMode* mode);
    void setViscous(bool viscous);
    
    arma::vec getPressure(){return pressure;};
    arma::vec getXs(){return xs;};
    double getAlpha(){return alpha;}
    QWidget* getWidget(){return &widget;}

signals:

    void thickness(double thickess);
    void activated(bool recursively);
};
