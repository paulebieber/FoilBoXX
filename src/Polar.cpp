
#include "Polar.h"

Polar::Polar(std::vector<QwtCustomPlot*> plots, FoilMode* mode):Analysis(mode),plots(plots),alpha1(0.0),alpha2(10.0),re(1e6),nCrit(8){

    setItemText();
    setCurveColor(mode->getColor());
    setupInterface();
    
    curveCLCD->attach(plots[0]);
    curveCLAlpha->attach(plots[1]);
    curveCLXTrTop->attach(plots[2]);
    curveCLXTrBot->attach(plots[2]);
    curveCLCD->setYAxis(QwtPlot::yRight);
    curveCLAlpha->setYAxis(QwtPlot::yRight);
    curveCLXTrBot->setYAxis(QwtPlot::yRight);
    curveCLXTrTop->setYAxis(QwtPlot::yRight);

    curveCM->attach(plots[1]);

    curveCLCD->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    curveCM->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    curveCLAlpha->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    curveCLXTrBot->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    curveCLXTrTop->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
}

Polar::~Polar() {

    curveCLCD->detach(); delete curveCLCD;
    curveCM->detach(); delete curveCM;
    curveCLAlpha->detach(); delete curveCLAlpha;
    curveCLXTrBot->detach(); delete curveCLXTrBot;
    curveCLXTrTop->detach(); delete curveCLXTrTop;
}

QDataStream& operator<<(QDataStream& out, const Polar& polar){

    out << QString("Polar");
    out << polar.alpha1 << polar.alpha2 << polar.re << polar.nCrit;
    return out;
}

QDataStream& operator>>(QDataStream& in, Polar& polar){

    in >> polar.alpha1 >> polar.alpha2 >> polar.re >> polar.nCrit;
    polar.setItemText();
    polar.setInterfaceValues();
    return in;
}

void Polar::calcOnDemand(){

    setAnalysis(re, nCrit, reCa1);
    calcPolar(false,alpha1,alpha2,alphaDiscretization);
    plot();
    setItemText();
}

void Polar::plot(){

    multipliedCd = arma::vec(polar.col(1)*1000);
    curveCLCD->setRawSamples(multipliedCd.memptr(),polar.colptr(0),polar.n_rows);
    curveCLAlpha->setRawSamples(polar.colptr(2),polar.colptr(0),polar.n_rows);
    curveCLXTrTop->setRawSamples(polar.colptr(3),polar.colptr(0),polar.n_rows);
    curveCLXTrBot->setRawSamples(polar.colptr(4),polar.colptr(0),polar.n_rows);
    curveCM->setRawSamples(polar.colptr(2),polar.colptr(5),polar.n_rows);

    for(QwtPlotCurve* curve : std::list<QwtPlotCurve*>{curveCM,curveCLCD,curveCLAlpha,curveCLXTrBot,curveCLXTrTop}){
        curve->setPen(pen);
    }
    
    for(QwtCustomPlot* plot: plots){plot->replot();}
}

void Polar::onActivation(bool active, bool recursively){

    pen.setWidth(active ? 2.0 : 1.0);
    curveCLCD->setPen(pen);
    curveCLAlpha->setPen(pen);
    curveCLXTrTop->setPen(pen);
    curveCLXTrBot->setPen(pen);
    curveCM->setPen(pen);

    plot();

    if(active){emit activated(recursively);}
}

void Polar::onVisible(bool visible){

    curveCLCD->setVisible(visible);
    curveCLAlpha->setVisible(visible);
    curveCLXTrTop->setVisible(visible);
    curveCLXTrBot->setVisible(visible);
    curveCM->setVisible(visible);

    plot();
}

void Polar::setItemText(){
    treeItem->setText(0,QString("Polar: a. %1 - %2").arg(alpha1).arg(alpha2));
}

void Polar::setCurveColor(QColor color){

    pen.setColor(color);
    plot();
}

void Polar::needsUpdate() {

}

void Polar::setupInterface(){

    ui.setupUi(&widget);


    ui.doubleSpinBox_alpha1->setRange(-20,30);
    ui.doubleSpinBox_alpha2->setRange(-20,30);
    ui.doubleSpinBox_re->setRange(1e5,10e6);
    ui.doubleSpinBox_nCrit->setRange(3,14);
    
    setInterfaceValues();

    connect(ui.pushButton_calcPolar,&QPushButton::clicked,this,&Polar::calcOnDemand);
    connect(ui.doubleSpinBox_alpha1,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double alpha){this->alpha1 = alpha;});
    connect(ui.doubleSpinBox_alpha2,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double alpha){this->alpha2 = alpha;});
    connect(ui.doubleSpinBox_re,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double re){this->re = re;});
    connect(ui.doubleSpinBox_nCrit,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double nCrit){this->nCrit = nCrit;});
    connect(ui.checkBox_reCa1,&QCheckBox::toggled,[this](bool reCa1){this->reCa1 = reCa1;});

}

void Polar::setInterfaceValues(){
    
    ui.doubleSpinBox_alpha1->setValue(alpha1);
    ui.doubleSpinBox_alpha2->setValue(alpha2);
    ui.doubleSpinBox_re->setValue(re);
    ui.doubleSpinBox_nCrit->setValue(nCrit);
}
