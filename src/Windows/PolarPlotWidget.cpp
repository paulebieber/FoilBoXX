
#include "PolarPlotWidget.h"
#include <list>
#include <iostream>

PolarPlotWidget::PolarPlotWidget(QWidget* parent): QWidget(parent){
    
    setLayout(&grid);

    QwtPlotScaleItem *it = new QwtPlotScaleItem(QwtScaleDraw::LeftScale ,0.0);
    it->attach(cLAlpha);

    cLCD->setAxisScale(QwtPlot::yRight,0,1.5);
    cLCD->setAxisScale(QwtPlot::xBottom,0,25);
    cLCD->enableAxis(QwtPlot::yLeft,false);
    
    cLAlpha->setAxisScale(QwtPlot::yRight,0,1.5);
    cLAlpha->setAxisScale(QwtPlot::xBottom,-5,15);

    double lowcm = (cm0atcl)*cmpercl;
    double highcm = -(1.5-cm0atcl)*cmpercl;
    cLAlpha->setAxisScale(QwtPlot::yLeft,lowcm,highcm);
    cLAlpha->enableAxis(QwtPlot::yLeft,false);

    cLXTr->enableAxis( QwtPlot::yRight,true);
    cLXTr->setAxisScale(QwtPlot::yRight,0,1.5);
    cLXTr->setAxisScale(QwtPlot::xBottom,0,1);
    cLXTr->enableAxis(QwtPlot::yLeft,false);
    
    for(QwtCustomPlot* plot: std::vector<QwtCustomPlot*>{cLCD,cLAlpha,cLXTr}){
        plot->setMinimumWidth(100);
        plot->replot();
    }

    for(QwtCustomPlot* plot: std::list<QwtCustomPlot*>{cLCD,cLAlpha,cLXTr}){
        grid.addWidget(plot);
        connect(plot,&QwtCustomPlot::rangeChanged,[this,plot,it](int id, double min, double max){
        if(id == QwtPlot::yRight){
            for(QwtCustomPlot* plot2: std::list<QwtCustomPlot*>{cLCD,cLAlpha,cLXTr}){
                    double low = plot2->axisScaleDiv(QwtPlot::yRight).lowerBound();
                    double high = plot2->axisScaleDiv(QwtPlot::yRight).upperBound();
                    double low2 = plot2->axisScaleDiv(QwtPlot::xBottom).lowerBound();
                    double high2 = plot2->axisScaleDiv(QwtPlot::xBottom).upperBound();
                    double fac = (max-min)/(high-low);
                    plot2->setAxisScale(QwtPlot::yRight,min,max);
                    double delta = (high2-low2)/2;
                    double mid = low2+delta;

                    if(plot2 == cLAlpha){
                        //std::cout << "next should be "<< mid2+delta2*fac << "," << mid2-delta2*fac << ", " << mid2 << std::endl;
                        double rangeCl = max-min;
                        double percUpper = (max-cm0atcl)/rangeCl;
                        double rangeCm = rangeCl*cmpercl;
                        plot2->setAxisScale(QwtPlot::yLeft,rangeCm*(1-percUpper),-rangeCm*percUpper);
                    }

                    if (plot2 != plot){
                        if(plot2 != cLXTr){
                            plot2->setAxisScale(QwtPlot::xBottom,mid-delta*fac,mid+delta*fac);
                        }else{
                            plot2->setAxisScale(QwtPlot::xBottom,0.0,1.0);
                        }
                    }

                    plot2->replot();
            }
        }});
    }
}
