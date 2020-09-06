//
// Created by paul on 3/27/20.
//

#pragma once

#include <vector>
#include <qwt_plot_curve.h>
#include "Airfoil.h"
#include "QwtCustomPlot.h"

class AirfoilPlot {

    QwtCustomPlot* plot;

    Airfoil* foil;
    arma::mat* coords;
    arma::mat* flosse;
    arma::mat* flapTop;
    arma::mat* flapBot;

    QwtPlotCurve* coordsCurve;
    QwtPlotCurve* flosseCurve;
    QwtPlotCurve* flapTopCurve;
    QwtPlotCurve* flapBotCurve;

    std::vector<QwtPlotCurve*> curves;

public: AirfoilPlot(Airfoil* foil, QwtCustomPlot* plot);

    //Plotting Calls:
    void plotCoords();
};
