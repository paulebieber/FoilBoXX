
#pragma once

#include "QwtCustomPlot.h"
#include "armadillo"
#include "Polar.h"

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
    arma::vec multipliedGoal;
    arma::mat areaCoords;
    arma::mat multipliedAreaCoords;
    QwtCustomPlot* plot;

    QwtPlotCurve* curve = new QwtPlotCurve();
    QwtPlotCurve* curveHandles = new QwtPlotCurve();
    QwtPlotCurve* curveArea = new QwtPlotCurve();

    Polar* polar;

    QPen pen;
    QPen goalPen;
    QwtSymbol* symbol;

    //UI
    void setCurveColor(QColor color);

    void onActivation(bool active, bool recursively = false); //Gets called if Hierarchyelement gets activated
    void onVisible(bool visible);
    void setItemText(QString text);
    void modify(QPointF pt, QPointF delta);
    void checkForPoint(QPointF pt);

public:
    PolarGoal(QwtCustomPlot* plot, Polar* polar);
    ~PolarGoal();
    void calcDifferenceToPolar();
    double getArea(){return area;};
    Polar* getPolar(){return polar;}
    void plotGoal();

signals:
    void activated(bool recursively);
    void calced();
};
