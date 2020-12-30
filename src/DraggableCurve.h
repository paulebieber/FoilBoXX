
#pragma once

#include "QwtCustomPlot.h"
#include "armadillo"

class DraggableCurve: public QObject{

Q_OBJECT

friend QDataStream& operator<<(QDataStream& out, const DraggableCurve& drag); //For Serrialization
friend QDataStream& operator>>(QDataStream& in, DraggableCurve& drag); //For Serrialization

    arma::mat pts;

    int dragIndex;
    bool dragging;
    bool active;

    //Plotting
    QwtCustomPlot* plot;
    bool visible;

    QwtPlotCurve* curve = new QwtPlotCurve();
    //QwtPlotCurve* curveHandles = new QwtPlotCurve();

    QPen pen;
    QwtSymbol* symbol;

    //UI
    //void setCurveColor(QColor color);

    void modify(QPointF pt, QPointF delta);
    void checkForPoint(QPointF pt);
    void resetCurve();

public:
    DraggableCurve(QwtCustomPlot* plot, arma::mat initPts);
    ~DraggableCurve();
    arma::mat& getPts(){return pts;};
    void setActive(bool active=true){this->active=active;};
    void setVisible(bool visible=true);

signals:
    void ptsChanged();
};
