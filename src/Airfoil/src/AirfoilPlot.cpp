//
// Created by paul on 3/27/20.
//

#include "qwt_symbol.h"
#include "AirfoilPlot.h"

AirfoilPlot::AirfoilPlot(Airfoil* foil, QwtCustomPlot* plot): foil(foil), plot(plot){

    plotCoords();
}

void AirfoilPlot::plotCoords(){

    std::vector<arma::mat> modeCoords = foil->getModeCoords(false,10);

    flosse = new arma::mat({foil->getFlosse()});
    coords = new arma::mat({modeCoords[0]});
    flapTop = new arma::mat({modeCoords[3]});
    flapBot = new arma::mat({modeCoords[4]});
	
	coordsCurve = new QwtPlotCurve();
    flosseCurve = new QwtPlotCurve();
    flapTopCurve = new QwtPlotCurve();
    flapBotCurve = new QwtPlotCurve();

	curves = std::vector<QwtPlotCurve*>({coordsCurve,flosseCurve,flapTopCurve,flapBotCurve});

    coordsCurve->setRawSamples(coords->colptr(0),coords->colptr(1),coords->n_rows);
    flosseCurve->setRawSamples(flosse->colptr(0),flosse->colptr(1),flosse->n_rows);
    flapTopCurve->setRawSamples(flapTop->colptr(0),flapTop->colptr(1),flapTop->n_rows);
    flapBotCurve->setRawSamples(flapBot->colptr(0),flapBot->colptr(1),flapBot->n_rows);

    coordsCurve->setPen(Qt::transparent);
    QwtSymbol* symbol = new QwtSymbol(QwtSymbol::Cross,QBrush(Qt::black),QPen(Qt::black),QSize(5,5));
    coordsCurve->setSymbol(symbol);
    flosseCurve->setPen(QPen(Qt::blue,2.5));

    flapTopCurve->setPen(QPen(Qt::cyan,2.5));
    flapBotCurve->setPen(QPen(Qt::cyan,2.5));

    //coordsCurve.attach(plot);
    coordsCurve->attach(plot);
    flosseCurve->attach(plot);
    flapTopCurve->attach(plot);
    flapBotCurve->attach(plot);
}
