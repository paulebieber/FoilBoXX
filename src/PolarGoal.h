
#pragma once

#include "QwtCustomPlot.h"
#include "armadillo"
#include "Polar.h"
#include "DraggableCurve.h"
#include "ui_polarGoalWidget.h"

class PolarGoal: public HierarchyElement{

Q_OBJECT

friend QDataStream& operator<<(QDataStream& out, const PolarGoal& goal); //For Serrialization
friend QDataStream& operator>>(QDataStream& in, PolarGoal& goal); //For Serrialization
    QString fileVersion;

    arma::mat goalPts;

    int dragIndex;
    bool dragging;
    bool normalDiff;
    double area;
    double bias; //Reference on scale for Optimization;

    public:enum Modes{cD,cLAlpha,XTrTop};
    private:
    Modes mode;
    bool verticalDiff;

    //Plotting
    arma::mat areaCoords;
    arma::mat multipliedAreaCoords;
    QwtCustomPlot* plot;
    QwtCustomPlot* plotCLAlpha;
    DraggableCurve* dragCurve;
    QPen pen;

    QwtPlotCurve* curveArea = new QwtPlotCurve();

    Polar* polar;

    //UI
    Ui_polarGoalWidget ui;
    void setCurveColor(QColor color);
    void setUpInterface();
    void setInterfaceValues();

    void onActivation(bool active, bool recursively = false); //Gets called if Hierarchyelement gets activated
    void onVisible(bool visible);
    void setItemText(QString text);

public:
    PolarGoal(QwtCustomPlot* plot,Modes mode, Polar* polar, QString fileVersion = QString("0.0.0"));
    ~PolarGoal();
    void calcDifferenceToPolar();
    double getArea(){return area;}
    Polar* getPolar(){return polar;}
    void plotDiff();
    Modes getMode(){return mode;}

signals:
    void activated(bool recursively);
    void calced();
};
