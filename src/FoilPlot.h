
#pragma once

#include "QwtCustomPlot.h" 
#include "Airfoil.h"

class FoilPlot: public QObject{

Q_OBJECT

    std::vector<QwtPlotCurve*> baseCurves;
    std::vector<arma::mat*> baseCoords;

    QwtCustomPlot* plot;
    QPen basePen;

    Airfoil* airfoil;
    bool permanentInvisible;

public:
    FoilPlot(QwtCustomPlot* plot);
    ~FoilPlot();
    void connectToFoil(Airfoil* airfoil);
    void plotCoords();
    void setActive(bool active);
    void setVisible(bool visible);
    void setPermanentInvisible(bool invisible);
    Airfoil* getAirfoil(){return airfoil;}
};
