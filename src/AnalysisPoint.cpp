// Created by paul on 4/5/20.

#include "AnalysisPoint.h"
#include <qnamespace.h>
#include <vector>

AnalysisPoint::AnalysisPoint(FoilMode* mode, QwtCustomPlot* pressurePlot):Analysis(mode),cl(0.2),pressurePlot(pressurePlot),viscous(false){

    setCurveColor(mode->getColor());

    calcMode = clCalc;

    for(QwtPlotCurve* cu: std::vector<QwtPlotCurve*>{curve,viscCurve}){
        cu->attach(pressurePlot);
        cu->setYAxis(QwtPlot::yRight);
        cu->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    }

    setItemText();
    setupInterface();
}

AnalysisPoint::~AnalysisPoint() {

    curve->detach();
    viscCurve->detach();
}

QDataStream& operator<<(QDataStream& out, const AnalysisPoint& analysis){

    out << QString("AnalysisPoint");
    out << analysis.alpha << analysis.re << analysis.nCrit;
    return out;
}

QDataStream& operator>>(QDataStream& in, AnalysisPoint& analysis){

    in >> analysis.alpha >> analysis.re >> analysis.nCrit;
    analysis.setItemText();
    analysis.setInterfaceValues();
    analysis.calc();
    return in;
}

void AnalysisPoint::calc(){

    setAnalysis(re, nCrit, reCa1);

    if(calcMode == alphaCalc){
        calcSingle(false,alpha,viscous);
        cl = xfoilCA();
        
        ui.doubleSpinBox_caDesign->blockSignals(true);
        ui.doubleSpinBox_caDesign->setValue(cl);
        ui.doubleSpinBox_caDesign->blockSignals(false);

        ui.doubleSpinBox_alphaDesign->setStyleSheet("color: black");
        ui.doubleSpinBox_caDesign->setStyleSheet("color: darkGray");
    }else{
        calcSingle(true,cl,viscous);
        alpha = xfoilAlpha();

        ui.doubleSpinBox_alphaDesign->blockSignals(true);
        ui.doubleSpinBox_alphaDesign->setValue(alpha);
        ui.doubleSpinBox_alphaDesign->blockSignals(false);

        ui.doubleSpinBox_caDesign->setStyleSheet("color: black");
        ui.doubleSpinBox_alphaDesign->setStyleSheet("color: darkGray");
    }
    
    emit thickness(xfoilThickness());
    setItemText();
    plot();
    setItemText();
}

void AnalysisPoint::plot(){

    curve->setRawSamples(xs.memptr(),pressure.memptr(),
        pressure.n_rows);

    if(viscous){
        viscCurve->setRawSamples(xs.memptr(),pressureVisc.memptr(),
            pressureVisc.n_rows);

    }
    pressurePlot->replot();
}

void AnalysisPoint::onActivation(bool active, bool recursively){

    smallPen.setWidth(active?2:1);
    bigPen.setWidth(active?3:2);

    setViscous(viscous);

    if(active){emit activated(recursively);}
}

void AnalysisPoint::setViscous(bool viscous){

    if(viscous){
        curve->setPen(smallPen);
        viscCurve->setPen(bigPen);
        viscCurve->setVisible(true);
    }else{
        curve->setPen(bigPen);
        viscCurve->setPen(smallPen);
        viscCurve->setVisible(false);
    }

    if(this->viscous != viscous){
        this->viscous = viscous;
        calc();
    }else{
        plot();
    }
}

void AnalysisPoint::onVisible(bool visible){

    curve->setVisible(visible);
    viscCurve->setVisible(visible);
    pressurePlot->replot();
}

void AnalysisPoint::setupInterface(){

    ui.setupUi(&widget);

    ui.doubleSpinBox_caDesign->setRange(-1.0,3.0);
    ui.doubleSpinBox_caDesign->setSingleStep(0.02);
    ui.doubleSpinBox_alphaDesign->setRange(-20,30);
    ui.doubleSpinBox_alphaDesign->setSingleStep(0.1);
    ui.doubleSpinBox_nCrit->setRange(3,14);
    ui.doubleSpinBox_nCrit->setSingleStep(0.25);
    ui.doubleSpinBox_re->setRange(1e4,10e6);
    ui.doubleSpinBox_re->setSingleStep(1e4);

    for(QDoubleSpinBox* spin: std::list<QDoubleSpinBox*>{ui.doubleSpinBox_nCrit,ui.doubleSpinBox_alphaDesign,ui.doubleSpinBox_caDesign}){
        spin->setDecimals(3);
    }

    setInterfaceValues();

    connect(ui.checkBox_reCa1,&QCheckBox::toggled,[this](bool reCa1){this->reCa1 = reCa1; calc();});
    connect(ui.doubleSpinBox_alphaDesign,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double alpha){this->alpha = alpha; calcMode = alphaCalc; calc();});
    connect(ui.doubleSpinBox_caDesign,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double cl){this->cl = cl; calcMode = clCalc; calc();});
    connect(ui.groupBox_Viscous,&QGroupBox::toggled,[this](bool on){setViscous(on);});

    connect(ui.doubleSpinBox_nCrit,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double nCrit){this->nCrit = nCrit; calc();});
    connect(ui.doubleSpinBox_re,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double re){this->re = re; calc();});
}

void AnalysisPoint::setInterfaceValues(){

    ui.doubleSpinBox_alphaDesign->setValue(alpha);
    ui.doubleSpinBox_caDesign->setValue(cl);
    ui.doubleSpinBox_re->setValue(re);
    ui.doubleSpinBox_nCrit->setValue(nCrit);
}

void AnalysisPoint::setItemText(){

    if(calcMode == clCalc){
        treeItem->setText(0,QString("cl %1").arg(cl));
    }else{
        treeItem->setText(0,QString("alpha %1").arg(alpha));
    }
}

void AnalysisPoint::setCurveColor(QColor color){

    bigPen.setColor(color);
    smallPen.setColor(color);
}
