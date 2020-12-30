
#pragma once

#include <QObject>
#include "QwtCustomPlot.h"
#include "BernsteinShape.h"
#include "HierarchyElement.h"
#include "ui_shapeWidget.h"

class BernsteinShapeInterface: public HierarchyElement, public BernsteinShape{

Q_OBJECT

friend QDataStream& operator<<(QDataStream& out, const BernsteinShapeInterface& shape);
friend QDataStream& operator>>(QDataStream& in, BernsteinShapeInterface& shape);
    QString fileVersion;

    QwtCustomPlot* foilPlot;
    QwtCustomPlot* pressurePlot;
    QwtPlotCurve product;

    std::vector<QwtPlotCurve*> bernsteinCurves;
    QwtPlotCurve* shapeCurve;

    void onChangeFromAirfoil();
    double width;
    void setItemText();

    arma::vec scaledShape;
    arma::vec savedCoefs;
    void changeNCoefs(int n);

    //Plotting
    void setPlot();
    QPen pen;
    QPen penBernstein;

    //UI
    void setInterfaceValues();
    void setupInterface();
    void calcVisualizationShape();
    void onActivation(bool activate, bool recursively);
    void onVisible(bool visible);
    Ui_shapeWidget ui;

public:

    BernsteinShapeInterface(HierarchyElement* airfoil, QwtCustomPlot* foilPlot, QwtCustomPlot* pressurePlot, QString fileVersion = QString(""));
    ~BernsteinShapeInterface();
    void modify(QPointF pt, QPointF delta, bool negative);
    void setCoefficients(arma::vec& newCoefficients, bool calcFoil = true);
    void setSide(BernsteinShape::sideType side);
    void update();

signals:
    void changed(bool needsNewSpacing=false);
    void activated(bool recursively);
};
