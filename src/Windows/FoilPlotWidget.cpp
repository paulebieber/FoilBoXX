#include "FoilPlotWidget.h"

FoilPlotWidget::FoilPlotWidget(QWidget* parent): QwtCustomPlot(parent,QString("x"),QString("y"),1.0){

    setAxisScale(QwtPlot::xBottom, -0.1, 1.1);
    setAxisScale(QwtPlot::yRight, -1.0, 1.0);
}
