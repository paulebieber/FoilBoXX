#pragma once

#include <QMainWindow>
#include <qnamespace.h>
#include "QwtCustomPlot.h"
#include "QSplitter"
#include "QGridLayout"
#include "Dock.h"

class PolarPlotWidget: public QWidget{
        
Q_OBJECT

    //QwtLinearScaleEngine* scaleEngineCLCD = new QwtLinearScaleEngine();
    QwtCustomPlot* cLCD = new QwtCustomPlot(NULL,QString("cD"),QString("cL"),0);
    QwtCustomPlot* cLAlpha = new QwtCustomPlot(NULL,QString("alpha"),QString("cL/cM"),0);
    QwtCustomPlot* cLXTr = new QwtCustomPlot(NULL,QString("xTrans"),QString("cL"),0.0);

    double cm0atcl = 0.3;
    double cmpercl = 0.4;

    QHBoxLayout grid;
    QSplitter* hSplitter;

public:
    PolarPlotWidget(QWidget* parent = 0);
    std::vector<QwtCustomPlot*> getPlots(){return std::vector<QwtCustomPlot*>{cLCD,cLAlpha,cLXTr};}
};
