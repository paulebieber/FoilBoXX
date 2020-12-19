

#pragma once

#include "QwtCustomPlot.h" 
#include "FoilMode.h"
#include "QObject"
#include <vector>

class FoilMode;

class ModePlot: public QObject{

Q_OBJECT

    QMetaObject::Connection modeConnection;

    std::vector<QwtPlotCurve*> secondaryCurves;
    std::vector<QwtPlotCurve*> aeroCurves;
    QwtPlotCurve* turbTopCurve;
    QwtPlotCurve* turbBotCurve;

    std::vector<arma::mat*> aero;
    std::vector<arma::mat*> secondary;

    QwtCustomPlot* plot;
    QPen secondaryPen, aeroPen;
    QwtSymbol* aeroSymbol; 
    QwtSymbol* turbSymbol;

    FoilMode* mode;

public:
    ModePlot(QwtCustomPlot* plot);
    ~ModePlot();
    void connectToMode(FoilMode* mode);
    void plotCoords();
    void setActive(bool active);
    void setVisible(bool visible);
    FoilMode* getMode(){return mode;}
};
