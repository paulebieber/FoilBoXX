
#pragma once

#include "Analysis.h"
#include "ui_polarWidget.h"
#include "QwtCustomPlot.h"
#include "armadillo"

class Polar: public Analysis{

Q_OBJECT

friend QDataStream& operator<<(QDataStream& out, const Polar& polar); //For Serrialization, (saving the Airfoil)
friend QDataStream& operator>>(QDataStream& in, Polar& polar); //For Serrialization, (loading the Airfoil)

    double alpha1=0.0, alpha2=15.0, alphaDiscretization = 0.1;

    double re=1e6, nCrit=8;
     
    //Plotting
    arma::vec multipliedCd;
    std::vector<QwtCustomPlot*> plots;
    QwtPlotCurve* curveCLCD = new QwtPlotCurve();
    QwtPlotCurve* curveCLAlpha = new QwtPlotCurve();
    QwtPlotCurve* curveCLXTrTop = new QwtPlotCurve();
    QwtPlotCurve* curveCLXTrBot = new QwtPlotCurve();
    QwtPlotCurve* curveCM = new QwtPlotCurve();
    QPen pen;

    //UI
    void setItemText();
    void needsUpdate();
    void setupInterface();
    void setInterfaceValues();
    Ui_polarWidget ui;

    void onActivation(bool active, bool recursively = false); //Gets called if Hierarchyelement gets activated
    void onVisible(bool visible);

public:
    Polar(std::vector<QwtCustomPlot*>, FoilMode* mode);
    ~Polar();
    void calc(){};
    void calcOnDemand();
    void plot();
    void setCurveColor(QColor color);

signals:
    void activated(bool recursively);
};
