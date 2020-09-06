//
// Created by paul on 15.06.19.
//

#pragma once

#include "armadillo"
#include "XFoil.h"
#include <vector>

class XfoilSession {

    XFoil* foil = new XFoil();
    int s_IterLim;
    int m_Iterations;
    bool m_bErrors;
    bool s_bAutoInitBL;

    double *x, *y;
    double nx[600], ny[600];
    int nPoints;
    bool iterate();

protected:

    void setCoordsReference(arma::mat* coords);

    arma::mat& coords;
    double& turbTop;
    double& turbBot;
    arma::vec xs;
    arma::vec pressure;
    arma::vec velocity;
    arma::vec pressureVisc;
    arma::mat polar = arma::mat(0,6);
    arma::mat hFacTop,hFacBot;

    bool setAnalysis(double re, double nCrit, bool reCa1);
    void calcSingle(bool cl, double value, bool visc = false);
    bool calcPolar(bool cl, double min, double max, double delta);
    std::tuple<arma::mat,arma::mat> getHFac();

    double xfoilAlpha(){return foil->alpha() * 180/3.14159;}
    double xfoilCM(){return foil->cm;}
    double xfoilCA(){return foil->cl;}
    double xfoilThickness(){return foil->thickb;}

public:
    XfoilSession(arma::mat& coords, double& turbTop, double& turbBot);
};
