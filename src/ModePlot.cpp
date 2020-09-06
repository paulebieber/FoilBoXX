
#include "ModePlot.h"

ModePlot::ModePlot(QwtCustomPlot* plot):plot(plot){

    turbSymbol = new QwtSymbol();
    aeroSymbol = new QwtSymbol();
    aeroSymbol->setSize(QSize(4,4));
    turbSymbol->setSize(QSize(6,11));
    aeroSymbol->setBrush(QBrush(Qt::black));
    turbSymbol->setBrush(QBrush(Qt::black));
    turbSymbol->setStyle(QwtSymbol::Diamond);
}

ModePlot::~ModePlot(){

    for(QwtPlotCurve* curve: aeroCurves){curve->detach();}
    for(QwtPlotCurve* curve: secondaryCurves){curve->detach();}
    for(QwtPlotCurve* curve: primaryCurves){curve->detach();}
    turbTopCurve->detach(); 
    turbBotCurve->detach(); 
    //delete aeroSymbol; delete turbSymbol;
}

void ModePlot::connectToMode(FoilMode* mode){

    this->mode = mode;

    aero = std::vector<arma::mat*>{&mode->coordsAero};
    secondary = std::vector<arma::mat*>{&mode->fkTop,&mode->fkBot,&mode->flapTop,&mode->flapBot};

    plot->enableAxis(QwtPlot::yLeft,false);
    plot->enableAxis(QwtPlot::yRight,true);


    for(int i=0; i<secondary.size();i++){
        secondaryCurves.push_back(new QwtPlotCurve());
        secondaryCurves[i]->setYAxis(QwtPlot::yRight);
        secondaryCurves[i]->attach(plot);
        secondaryCurves[i]->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    }

    for(int i=0; i<aero.size();i++){
        aeroCurves.push_back(new QwtPlotCurve());
        aeroCurves[i]->setYAxis(QwtPlot::yRight);
        aeroCurves[i]->attach(plot);
        aeroCurves[i]->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
        aeroCurves[i]->setSymbol(aeroSymbol);
    }

    for(int i=0; i<primary.size();i++){
        primaryCurves.push_back(new QwtPlotCurve());
        primaryCurves[i]->setYAxis(QwtPlot::yRight);
        primaryCurves[i]->attach(plot);
        primaryCurves[i]->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    }

    turbTopCurve = new QwtPlotCurve();
    turbBotCurve = new QwtPlotCurve();

    for(QwtPlotCurve* curve: std::vector<QwtPlotCurve*>{turbTopCurve,turbBotCurve}){
        curve->setYAxis(QwtPlot::yRight);
        curve->attach(plot);
        curve->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
        curve->setPen(Qt::transparent);
        curve->setSymbol(turbSymbol);
    }
}

void ModePlot::plotCoords(){

    for(int i=0; i<primary.size(); i++){
        primaryCurves[i]->setPen(primaryPen);
        primaryCurves[i]->setRawSamples(primary[i]->colptr(0),primary[i]->colptr(1),primary[i]->n_rows);
    }

    for(int i=0; i<aero.size(); i++){
        aeroCurves[i]->setRawSamples(aero[i]->colptr(0),aero[i]->colptr(1),aero[i]->n_rows);
        aeroCurves[i]->setPen(aeroPen);
    }

    if(mode->turbTop(0) < mode->coordsAero(0,0)){
        double* y = mode->turbTop.memptr();y++;
        turbTopCurve->setRawSamples(mode->turbTop.memptr(),y,1);
    }

    if(mode->turbBot(0) < mode->coordsAero(mode->coordsAero.n_rows-1,0)){
        double* y = mode->turbBot.memptr();y++;
        turbBotCurve->setRawSamples(mode->turbBot.memptr(),y,1);
    }

    if(mode->getModeType() == FoilMode::full){

        secondaryPen.setColor(mode->getColor());
        for(int i=0; i<secondary.size(); i++){
            secondaryCurves[i]->setPen(secondaryPen);
            secondaryCurves[i]->setRawSamples(secondary[i]->colptr(0),secondary[i]->colptr(1),secondary[i]->n_rows);
        }
    }

    plot->replot();
}

void ModePlot::setActive(bool active){

    double width = active ? 3.0 : 2.0;
    for(QPen* pen: std::list<QPen*>{&secondaryPen,&primaryPen}){
        pen->setWidth(width);
    }
    if(mode->getModeType() == FoilMode::full){aeroPen = QPen(Qt::transparent);}
    else{aeroPen = QPen(mode->getColor(),width);}

    if(active && mode->getModeType() == FoilMode::full){
        aeroSymbol->setStyle(QwtSymbol::Ellipse);
    }else{
        if(mode->getModeType() == FoilMode::full){aeroSymbol->setStyle(QwtSymbol::NoSymbol);}
    }

    plotCoords();
}

void ModePlot::setVisible(bool visible){

    for(int i=0; i<aero.size();i++){
        aeroCurves[i]->setVisible(visible);
    }

    for(int i=0; i<secondary.size();i++){
        secondaryCurves[i]->setVisible(visible);
    }

    for(QwtPlotCurve* curve: std::vector<QwtPlotCurve*>{turbTopCurve,turbBotCurve}){
        curve->setVisible(visible);
    }

    for(int i=0; i<primary.size();i++){
        primaryCurves[i]->setVisible(visible);
    }

    plot->replot();
}
