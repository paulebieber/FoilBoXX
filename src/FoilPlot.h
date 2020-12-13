
#pragma once

#include "QwtCustomPlot.h" 
#include "AirfoilInterface.h"

class FoilPlot: public QObject{

Q_OBJECT

    std::vector<QwtPlotCurve*> baseCurves;
    arma::mat& upperBaseCoords;
    arma::mat& lowerBaseCoords;

    QwtCustomPlot* plot;
    QPen basePen;

    AirfoilInterface* airfoil;
    bool permanentInvisible;

    std::vector<arma::mat*> baseCoords(){
        return std::vector<arma::mat*>{&upperBaseCoords,&lowerBaseCoords};};

public:
    FoilPlot(QwtCustomPlot* plot, AirfoilInterface* airfoil);
    ~FoilPlot();
    void connectToFoil(Airfoil* airfoil);
    void plotCoords();
    void setActive(bool active);
    void setVisible(bool visible);
    void setPermanentInvisible(bool invisible);
    Airfoil* getAirfoil(){return airfoil;}
};
