
#include "FoilPlot.h"

FoilPlot::FoilPlot(QwtCustomPlot* plot):plot(plot),permanentInvisible(false){}

FoilPlot::~FoilPlot(){

    for(QwtPlotCurve* curve: baseCurves){curve->detach();}
}

void FoilPlot::connectToFoil(Airfoil* airfoil){

    this->airfoil = airfoil;

    baseCoords = std::vector<arma::mat*>{airfoil->getLowerBaseCoords(),airfoil->getUpperBaseCoords()};

    plot->enableAxis(QwtPlot::yLeft,false);
    plot->enableAxis(QwtPlot::yRight,true);

    for(int i=0; i<baseCoords.size();i++){
        baseCurves.push_back(new QwtPlotCurve());
        baseCurves[i]->setYAxis(QwtPlot::yRight);
        baseCurves[i]->attach(plot);
        baseCurves[i]->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    }

}

void FoilPlot::plotCoords(){

    for(int i=0; i<baseCoords.size(); i++){
        baseCurves[i]->setPen(basePen);
        baseCurves[i]->setRawSamples(baseCoords[i]->colptr(0),baseCoords[i]->colptr(1),baseCoords[i]->n_rows);
    }

    plot->replot();
}

void FoilPlot::setActive(bool active){

    double width = active ? 3.0 : 2.0;
    for(QPen* pen: std::list<QPen*>{&basePen}){
        pen->setWidth(width);
    }

    plotCoords();
}

void FoilPlot::setPermanentInvisible(bool invisible){
    
    setVisible(!invisible);
    permanentInvisible = invisible;
}

void FoilPlot::setVisible(bool visible){

    if(!permanentInvisible){
        for(int i=0; i<baseCoords.size();i++){
            baseCurves[i]->setVisible(visible);
        }
        plot->replot();
    }
}
