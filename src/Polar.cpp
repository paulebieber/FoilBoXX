
#include "Polar.h"
#include "thread"
#include <iostream>
#include <ostream>
#include <qnamespace.h>

Polar::Polar(std::vector<QwtCustomPlot*> plots, FoilMode* mode, QString& fileVersion):Analysis(mode),plots(plots),alpha1(2.0),
    alpha2(5.0),alphaDiscretization(0.1),re(1e6),nCrit(8),success(false),fileVersion(fileVersion),
    cl1(0.2),cl2(0.7),clDiscretization(0.02),borderTight(false){

    thread = new WorkerThread(this);

    calcMode = clCalc;

    //Plot when parallel proc. done
    connect(thread,&WorkerThread::resultReady,this,&Polar::plot,Qt::QueuedConnection);

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
    out << (int)polar.calcMode;
    if (polar.calcMode == Analysis::clCalc){
        out << polar.cl1 << polar.cl2;
    }else{
        out << polar.alpha1 << polar.alpha2;
    }
    out << polar.re << polar.nCrit;
    return out;
}

QDataStream& operator>>(QDataStream& in, Polar& polar){

    int calcModeInt;
    if(polar.fileVersion == QString("0.6.0")){
        in >> calcModeInt;
        polar.calcMode = (Polar::calcTypes)calcModeInt;
        if (polar.calcMode == Analysis::clCalc){
            in >> polar.cl1 >> polar.cl2;
            polar.ui.radioButton_calcModeCl->click();
        }else{
            in >> polar.alpha1 >> polar.alpha2;
            polar.ui.radioButton_calcModeAlpha->click();
        }
    }else{
        in >> polar.alpha1 >> polar.alpha2;
        polar.ui.radioButton_calcModeAlpha->click();
        //polar.calcMode = Polar::alphaCalc;
    }
    in >> polar.re >> polar.nCrit;
    polar.setItemText();
    polar.setInterfaceValues();
    return in;
}

void Polar::calcPolarParallel(){

    setAnalysis(re, nCrit, reCa1);
    success = calcPolar(calcMode == clCalc,calcMode == clCalc ? cl1 : alpha1,
            calcMode == clCalc ? cl2 : alpha2,
            calcMode == clCalc ? clDiscretization : alphaDiscretization);

    //Set the non-set alpha/ca values for smooth transition between cl and alpha borders
    //If min or max not converged: not bordertight
    borderTight = false;

    if(success){
        if(calcMode == alphaCalc){
            if(fabs(polar(0,2) - alpha1) <= alphaDiscretization/4){borderTight = true;}
            if(fabs(polar(polar.n_rows-1,2) - alpha2) <= alphaDiscretization/4){borderTight = true;}
        }

        if(calcMode == clCalc){
            if(fabs(polar(0,0) - cl1) <= alphaDiscretization/4){borderTight = true;}
            if(fabs(polar(polar.n_rows-1,0) - cl2) <= alphaDiscretization/4){borderTight = true;}
        }
    }

    if(borderTight){
        if(calcMode == clCalc){
            alpha1 = polar(0,2);
            alpha2 = polar(polar.n_rows-1,2);
        }else{
            cl1 = polar(0,0);
            cl2 = polar(polar.n_rows-1,0);
        }
    }

    //std::cout << "used re " << re << "and nCrit " << nCrit << "and reCa1" << reCa1 << std::endl;
    //std::cout << "got: " << polar << std::endl;
}

QThread* Polar::calcOnDemand(){
    //ui.pushButton_calcPolar->setEnabled(false);
    thread->start();
    needsUpdate(false);
    return thread;
}

void Polar::plot(){

    multipliedCd = arma::vec(polar.col(1)*1000);
    curveCLCD->setSamples(multipliedCd.memptr(),polar.colptr(0),polar.n_rows);
    curveCLAlpha->setSamples(polar.colptr(2),polar.colptr(0),polar.n_rows);
    curveCLXTrTop->setSamples(polar.colptr(3),polar.colptr(0),polar.n_rows);
    curveCLXTrBot->setSamples(polar.colptr(4),polar.colptr(0),polar.n_rows);
    curveCM->setSamples(polar.colptr(2),polar.colptr(5),polar.n_rows);

    for(QwtPlotCurve* curve : std::list<QwtPlotCurve*>{curveCM,curveCLCD,curveCLAlpha,curveCLXTrBot,curveCLXTrTop}){
        curve->setPen(pen);
    }
    
    for(QwtCustomPlot* plot: plots){plot->replot();}

    setItemText();
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
    if(calcMode == clCalc){treeItem->setText(0,QString("Polar: cl %1 - %2").arg(cl1).arg(cl2));}
    else{treeItem->setText(0,QString("Polar: a. %1 - %2").arg(alpha1).arg(alpha2));}
}

void Polar::setCurveColor(QColor color){
    pen.setColor(color);
    plot();
}

void Polar::needsUpdate(bool need) {
    if(need){
        treeItem->setForeground(0,Qt::red);
        ui.groupBox->setStyleSheet("QGroupBox:title {color: rgb(200, 10, 10);}");
    }else{
        treeItem->setForeground(0,Qt::black);
        ui.groupBox->setStyleSheet("QGroupBox:title {color: rgb(0, 0, 0);}");
    }
}

void Polar::setupInterface(){

    ui.setupUi(&widget);

    ui.doubleSpinBox_re->setRange(1e5,10e6);
    ui.doubleSpinBox_nCrit->setRange(3,14);
    
    setInterfaceValues();

    connect(ui.pushButton_calcPolar,&QPushButton::clicked,this,&Polar::calcOnDemand);

    connect(ui.doubleSpinBox_value1,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double value){
            if(calcMode == alphaCalc){alpha1 = value;}
            else{cl1 = value;}
            needsUpdate(true);
        });
    

    connect(ui.doubleSpinBox_value2,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double value){
            if(calcMode == alphaCalc){alpha2 = value;}
            else{cl2 = value;}
            needsUpdate(true);
        });

    connect(ui.radioButton_calcModeCl,&QRadioButton::toggled,[this](bool state){
            if(state){calcMode = clCalc;
                ui.label_lower->setText(QString("lower cl"));
                ui.label_upper->setText(QString("upper cl"));
            }
            else{calcMode = alphaCalc;
                ui.label_lower->setText(QString("lower alpha"));
                ui.label_upper->setText(QString("upper alpha"));
            }
            setInterfaceValues();
    });

    connect(ui.doubleSpinBox_re,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double re){
            this->re = re;
            needsUpdate(true);});
    connect(ui.doubleSpinBox_nCrit,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double nCrit){
            this->nCrit = nCrit;
            needsUpdate(true);});
    connect(ui.checkBox_reCa1,&QCheckBox::toggled,[this](bool reCa1){
            this->reCa1 = reCa1;
            needsUpdate(true);});

}

void Polar::setInterfaceValues(){
    
    ui.doubleSpinBox_value1->blockSignals(true);
    ui.doubleSpinBox_value2->blockSignals(true);

    if(calcMode == alphaCalc){
        ui.doubleSpinBox_value1->setRange(-20,30);
        ui.doubleSpinBox_value2->setRange(-20,30);
        ui.doubleSpinBox_value1->setValue(alpha1);
        ui.doubleSpinBox_value2->setValue(alpha2);
        ui.doubleSpinBox_value1->setSingleStep(0.2);
        ui.doubleSpinBox_value2->setSingleStep(0.2);
    }else{
        ui.doubleSpinBox_value1->setRange(-5,5);
        ui.doubleSpinBox_value2->setRange(-5,5);
        ui.doubleSpinBox_value1->setSingleStep(0.05);
        ui.doubleSpinBox_value2->setSingleStep(0.05);
        ui.doubleSpinBox_value1->setValue(cl1);
        ui.doubleSpinBox_value2->setValue(cl2);
    }

    ui.doubleSpinBox_value1->blockSignals(false);
    ui.doubleSpinBox_value2->blockSignals(false);

    ui.doubleSpinBox_re->setValue(re);
    ui.doubleSpinBox_nCrit->setValue(nCrit);
}
