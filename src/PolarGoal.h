
#pragma once

#include "QwtCustomPlot.h"
#include "armadillo"
#include "Polar.h"
#include "DraggableCurve.h"

class PolarGoal: public HierarchyElement{

Q_OBJECT

friend QDataStream& operator<<(QDataStream& out, const PolarGoal& goal); //For Serrialization
friend QDataStream& operator>>(QDataStream& in, PolarGoal& goal); //For Serrialization

    arma::mat goalPts;

    int dragIndex;
    bool dragging;
    bool normalDiff;
    double area;

    //Plotting
    arma::mat areaCoords;
    arma::mat multipliedAreaCoords;
    QwtCustomPlot* plot;
    DraggableCurve* dragCurve;

    QwtPlotCurve* curveArea = new QwtPlotCurve();

    Polar* polar;

    QPen pen;

    //UI
    void setCurveColor(QColor color);

    void onActivation(bool active, bool recursively = false); //Gets called if Hierarchyelement gets activated
    void onVisible(bool visible);
    void setItemText(QString text);

public:
    PolarGoal(QwtCustomPlot* plot, Polar* polar);
    ~PolarGoal();
    void calcDifferenceToPolar();
    double getArea(){return area;};
    Polar* getPolar(){return polar;}
    void plotDiff();

signals:
    void activated(bool recursively);
    void calced();
};
