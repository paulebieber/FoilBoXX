#include "PressurePlotWidget.h"

PressurePlotWidget::PressurePlotWidget(QWidget* parent): QwtCustomPlot(parent,QString("x"),QString("cP"),0.3){

    enableAxis(QwtPlot::yLeft,false);
    enableAxis(QwtPlot::yRight,true);
    setAxisScale(QwtPlot::yRight, 2.0, -2.0);
    setAxisScale(QwtPlot::xBottom, -0.1, 1.1);
}
