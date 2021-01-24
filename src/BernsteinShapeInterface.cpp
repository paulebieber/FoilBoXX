
#include "BernsteinShapeInterface.h"
#include "iostream"
#include <ostream>
#include <qnamespace.h>
#include <vector>
#include <QVector>

BernsteinShapeInterface::BernsteinShapeInterface(HierarchyElement* airfoil, QwtCustomPlot* foilPlot, QwtCustomPlot* pressurePlot, QString fileVersion):
                                foilPlot(foilPlot),pressurePlot(pressurePlot), HierarchyElement(airfoil, true), width(0.05), fileVersion(fileVersion){

    shapeCurve = new QwtPlotCurve();
    shapeCurve->attach(foilPlot);
    shapeCurve->setYAxis(QwtPlot::yRight);
    pen.setStyle(Qt::DashDotLine);
    shapeCurve->setPen(pen);

    connect(foilPlot,&QwtCustomPlot::dragged,this,[=](QPointF pt, QPointF delta){modify(pt,delta,false);},Qt::QueuedConnection);
    connect(pressurePlot,&QwtCustomPlot::dragged,this,[=](QPointF pt, QPointF delta){modify(pt,delta,true);},Qt::QueuedConnection);
    connect(this,&BernsteinShapeInterface::changed,this,&BernsteinShapeInterface::plot,Qt::QueuedConnection);

    setItemText();
    setBold(true);
    setupInterface();
    savedCoefs = coefficients;
}

BernsteinShapeInterface::~BernsteinShapeInterface(){

    shapeCurve->detach(); delete shapeCurve;
    for(QwtPlotCurve* curve: bernsteinCurves){
        curve->detach(); delete curve;
    }
}

QDataStream& operator<<(QDataStream& out, const BernsteinShapeInterface& shape){

    out << QString("BernsteinShape");
    out << (int)shape.side;
    out << shape.modifying;
    out << QVector<double>::fromStdVector(arma::conv_to<std::vector<double>>::from(shape.coefficients));
    return out;

}

QDataStream& operator>>(QDataStream& in, BernsteinShapeInterface& shape){

    int sideInt;
    in >> sideInt;
    shape.side = (BernsteinShapeInterface::sideType)sideInt;
    if(shape.fileVersion != QString("0.5.0") && shape.fileVersion != QString("0.5.1")){
        bool modi; in >> modi; shape.setModifying(modi,true);
    }
    QVector<double> vec;
    in >> vec;
    std::vector<double> vec2(vec.begin(),vec.end());
    arma::vec coefs(arma::conv_to<arma::vec>::from(vec2));

    shape.changed(true);
    shape.setPlot();
    shape.setItemText();
    shape.setCoefficients(coefs,true);
    
    return in;
}

void BernsteinShapeInterface::setItemText(){
    treeItem->setText(0,((side == top) ? "Top" : "Bottom"));
}

void BernsteinShapeInterface::onChangeFromAirfoil(){
    setPlot();
}

void BernsteinShapeInterface::changeNCoefs(int n){

    if (n>3){
        arma::vec oldCoefs = coefficients;
        arma::vec newCoefs = coefficients;
        int delta = n-oldCoefs.n_rows;
        if(oldCoefs.size() < n){
            for(int i=1; i<=delta; i++){
                if(savedCoefs.n_rows >= oldCoefs.n_rows+i){
                    newCoefs.resize(newCoefs.n_rows+1);
                    newCoefs.back() = savedCoefs(newCoefs.n_rows-1);
                }else{
                    newCoefs.resize(newCoefs.n_rows+1);
                    newCoefs.back() = newCoefs(newCoefs.n_rows-2);
                }
            }
        }else{
            if(oldCoefs.size() > savedCoefs.size()){
                savedCoefs.resize(oldCoefs.size());
                savedCoefs = oldCoefs;
            }else{
                //savedCoefs(n) = oldCoefs(n);
                arma::vec sub = oldCoefs.tail_rows(abs(delta));
                savedCoefs.subvec(n-1,size(sub)) = sub;
                newCoefs = oldCoefs.head_rows(n);
            }
        }
        setCoefficients(newCoefs);
        setPlot();
        emit changed();
    }
}

void BernsteinShapeInterface::setPlot(){

    for(QwtPlotCurve* curve: bernsteinCurves){
        curve->detach();
        delete curve;
    }

    bernsteinCurves.clear();

    for(int i=0; i < distributions.size(); i++){
        bernsteinCurves.push_back(new QwtPlotCurve());
        bernsteinCurves[i]->attach(foilPlot);
        bernsteinCurves[i]->setYAxis(QwtPlot::yRight);
        bernsteinCurves[i]->setPen(penBernstein);
    }
}

void BernsteinShapeInterface::plot(bool newSpacing){

    if (newSpacing){setPlot();}
    scaledShape = shape;
    scaledShape += -1;
    scaledShape *= (side == top) ? 1 : -1;
    for(int i=0;i<distributions.size();i++){
        bernsteinCurves[i]->setSamples(spacing.colptr(0),distributions[i].colptr(0),distributions[i].col(0).n_elem);
    }

    shapeCurve->setSamples(spacing.colptr(0),scaledShape.colptr(0),scaledShape.col(0).n_elem);
    foilPlot->replot();
}

void BernsteinShapeInterface::onActivation(bool active, bool recursively){
      
    pen.setWidth(active ? 3 : 1);
    penBernstein.setStyle(active ? Qt::SolidLine : Qt::NoPen);

    for(QwtPlotCurve* curve: bernsteinCurves){
        curve->setPen(penBernstein);
    }
    shapeCurve->setPen(pen);
    foilPlot->replot();
    if(active){emit activated(recursively);}
}

void BernsteinShapeInterface::onVisible(bool visible){

    shapeCurve->setVisible(visible);
    foilPlot->replot();
}

void BernsteinShapeInterface::setFirstCoefficient(double firstCoef){
    
    if(firstCoef != coefficients(0)){
        arma::vec tmpCoefficient = coefficients;
        tmpCoefficient(0) = firstCoef;
        setCoefficients(tmpCoefficient);
    }
}

void BernsteinShapeInterface::setCoefficients(arma::vec& newCoefficients, bool calcFoil){

    BernsteinShape::setCoefficients(newCoefficients);
    if(calcFoil){
        emit changed();
        emit changedCoefs(coefficients(0));
    }
}

void BernsteinShapeInterface::modify(QPointF pt, QPointF delta, bool negative){

    if(!modifying || !getParent()->active){return;}

    double weight = 0.2;
    arma::vec addCoefs = xs;
    for(int i = 0; i<xs.n_elem; ++i){
        if(fabs(pt.x()-xs[i])<width){
           addCoefs[i] = weight*(1+cos(M_PI*(pt.x()-xs[i])/width));
        }else{addCoefs[i] = 0.0;}
    }
    addCoefs = coefficients + delta.y()*addCoefs*((negative | (!negative && side == top))?1:-1);
    setCoefficients(addCoefs,true);
}

void BernsteinShapeInterface::setSide(BernsteinShape::sideType side){

    BernsteinShape::setSide(side);
    setItemText();
    emit changed(true);
}

void BernsteinShapeInterface::setupInterface(){

    ui.setupUi(&widget);
    widget.show();
    connect(ui.radioButton_top,&QRadioButton::toggled,[this](bool on){
            setSide(on ? top : bottom);
        });
    ui.spinBox_nDisc->setRange(4,500);
    ui.doubleSpinBox_dragWidth->setRange(0.001,0.5);
    ui.doubleSpinBox_dragWidth->setDecimals(3);
    ui.doubleSpinBox_dragWidth->setSingleStep(0.001);
    setInterfaceValues();
    connect(ui.spinBox_nDisc,QOverload<int>::of(&QSpinBox::valueChanged),this,&BernsteinShapeInterface::changeNCoefs);
    connect(ui.doubleSpinBox_dragWidth,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double value){width = value;});
}

void BernsteinShapeInterface::setInterfaceValues(){

    ui.spinBox_nDisc->blockSignals(true);
    ui.spinBox_nDisc->setValue(coefficients.size());
    ui.doubleSpinBox_dragWidth->setValue(width);
    ui.spinBox_nDisc->blockSignals(false);
}
