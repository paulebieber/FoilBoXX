
#include "BernsteinShapeInterface.h"
#include "iostream"
#include <ostream>
#include <qnamespace.h>
#include <vector>
#include <QVector>

BernsteinShapeInterface::BernsteinShapeInterface(HierarchyElement* airfoil, QwtCustomPlot* foilPlot, QwtCustomPlot* pressurePlot):
                                foilPlot(foilPlot),pressurePlot(pressurePlot), HierarchyElement(airfoil, true), width(0.2){

    shapeCurve = new QwtPlotCurve();
    shapeCurve->attach(foilPlot);
    shapeCurve->setYAxis(QwtPlot::yRight);
    pen.setStyle(Qt::DashDotLine);

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
    out << shape.side;
    out << QVector<double>(shape.coefficients.begin(),shape.coefficients.end());
    return out;

}

QDataStream& operator>>(QDataStream& in, BernsteinShapeInterface& shape){

    in >> shape.side;
    QVector<double> vec;
    in >> vec;
    std::vector<double> vec2(vec.begin(),vec.end());
    arma::vec coefs(arma::conv_to<arma::vec>::from(vec2));

    shape.changed(true);
    shape.setCoefficients(coefs);
    shape.setPlot();
    shape.setItemText();
    
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

    calcVisualizationShape();

    for(QwtPlotCurve* curve: bernsteinCurves){
        curve->detach();
    }

    bernsteinCurves = std::vector<QwtPlotCurve*>{};

    for(int i=0; i < distributions.size(); i++){
        bernsteinCurves.push_back(new QwtPlotCurve());
        bernsteinCurves[i]->attach(foilPlot);
        bernsteinCurves[i]->setYAxis(QwtPlot::yRight);
        bernsteinCurves[i]->setPen(penBernstein);
    }

    for(int i=0;i<distributions.size();i++){
        bernsteinCurves[i]->setRawSamples(spacing.colptr(0),distributions[i].colptr(0),distributions[i].col(0).n_elem);
    }

    shapeCurve->setRawSamples(spacing.colptr(0),scaledShape.colptr(0),scaledShape.col(0).n_elem);
    shapeCurve->setPen(pen);
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

void BernsteinShapeInterface::modify(QPointF pt, QPointF delta, bool negative){

    if(!modifying){return;}

    double weight = 0.2;
    arma::vec addCoefs = xs;
    for(int i = 0; i<xs.n_elem; ++i){
        if(abs(pt.x()-xs[i])<width){
           addCoefs[i] = weight*(1+cos(M_PI*(pt.x()-xs[i])/width));
        }else{addCoefs[i] = 0.0;}
    }
    addCoefs = coefficients + delta.y()*addCoefs*((negative | (!negative && side == top))?1:-1);
    setCoefficients(addCoefs);
    calcVisualizationShape();
    emit changed();
}

void BernsteinShapeInterface::calcVisualizationShape(){

    scaledShape = shape;
    scaledShape += -1;
    scaledShape *= (side == top) ? 1 : -1;
}

void BernsteinShapeInterface::setSide(BernsteinShape::sideType side){

    BernsteinShape::setSide(side);
    setItemText();
    calcVisualizationShape();
    emit changed(true);
}

void BernsteinShapeInterface::setupInterface(){

    ui.setupUi(&widget);
    widget.show();
    connect(ui.radioButton_top,&QRadioButton::toggled,[this](bool on){
            setSide(on ? top : bottom);
        });
    ui.doubleSpinBox_dragWidth->setRange(0.05,0.5);
    ui.doubleSpinBox_dragWidth->setSingleStep(0.01);
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
