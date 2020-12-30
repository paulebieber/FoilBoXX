
#include "PolarGoal.h"
#include <QDebug>
#include <iostream>
#include <iterator>

PolarGoal::PolarGoal(QwtCustomPlot* plot, Modes mode, Polar* polar, QString fileVersion):HierarchyElement(polar),
    plot(plot),polar(polar),mode(mode),verticalDiff(mode != cD),normalDiff(false),bias(1.0),fileVersion(fileVersion){

    curveArea->attach(plot);
    curveArea->setYAxis(QwtPlot::yRight);
    curveArea->setRenderHint(QwtPlotCurve::RenderAntialiased,true);

    arma::mat dragInit;
    if(mode==cLAlpha){
        dragInit = arma::mat{{6,1.0},{7,1.1},{10,1.2}};
    }else if(mode == cD){
        dragInit = arma::mat{{0.006,0.2},{0.007,0.4},{0.008,0.5}};
    }else{
        dragInit = arma::mat{{0.4,1.35},{0.45,1.325},{0.5,1.3}};
    }
    dragCurve = new DraggableCurve(plot,dragInit);

    connect(this,&PolarGoal::calced,this,&PolarGoal::plotDiff,Qt::QueuedConnection);
    connect(polar->thread,&WorkerThread::resultReady,this,&PolarGoal::calcDifferenceToPolar,Qt::DirectConnection);

    connect(dragCurve,&DraggableCurve::ptsChanged,this,&PolarGoal::calcDifferenceToPolar);

    pen.setWidth(1.0);
    pen.setColor(Qt::lightGray);
    curveArea->setPen(pen);
    setItemText("Goal");

    setUpInterface();
    calcDifferenceToPolar();
}

PolarGoal::~PolarGoal(){
    delete dragCurve;
    curveArea->detach(); delete curveArea;
}

QDataStream& operator<<(QDataStream& out, const PolarGoal& goal){

    if(goal.mode == PolarGoal::cLAlpha){
        out << QString("PolarGoalCLAlpha");
    }else if(goal.mode == PolarGoal::cD){
        out << QString("PolarGoalCD");
    }else if(goal.mode == PolarGoal::XTrTop){
        out << QString("PolarGoalXTrTop");
    }else if(goal.mode == PolarGoal::XTrBot){
        out << QString("PolarGoalXTrBot");
    }
    out << goal.bias;
    out << *goal.dragCurve;
    return out;
}

QDataStream& operator>>(QDataStream& in, PolarGoal& goal){

    if      (goal.fileVersion != QString("0.6.1") &&
            goal.fileVersion != QString("0.6.0") &&
            goal.fileVersion != QString("0.5.0") && 
            goal.fileVersion != QString("0.5.1")){
        in >> goal.bias;
    }
    in >> *goal.dragCurve;
    goal.setInterfaceValues();
    goal.plotDiff();

    return in;
}

void PolarGoal::calcDifferenceToPolar(){

    area = 0.0;

    int n_disc = 100;
    int count = 0;

    if(!polar->getSuccess()){return;}
    arma::mat& polarPts = polar->getPolar();
    arma::mat& goalPts = dragCurve->getPts();

    arma::mat cLCD(polarPts.n_rows,2);
    cLCD.col(0) = polarPts.col(0);
    if(mode == cD){
        cLCD.col(1) = polarPts.col(1);
    }else if(mode == cLAlpha){
        cLCD.col(1) = cLCD.col(0);
        cLCD.col(0) = polarPts.col(2);
    }else if(mode == XTrTop){
        for(int i = 0; i < cLCD.n_rows; i++){
            cLCD(i,1) =polarPts(cLCD.n_rows-(1+i),0);
            //turn araound order
            cLCD(i,0) = polarPts(cLCD.n_rows-(1+i),3);
        }
    }else if (mode == XTrBot){
        cLCD.col(1) = cLCD.col(0);
        cLCD.col(0) = polarPts.col(4);
    }

    //Coordinates for visualizing area
    if (cLCD.n_rows > 0){

        areaCoords = arma::mat((goalPts.n_rows-1)*n_disc*2,2);

        for(int i=1; i<goalPts.n_rows; i++){
            arma::mat pts(n_disc,2);
            pts.col(0) = arma::linspace(goalPts(i-1,0),goalPts(i,0),pts.n_rows);
            pts.col(1) = arma::linspace(goalPts(i-1,1),goalPts(i,1),pts.n_rows);
            double diff = distanceBetweenPoints(goalPts.row(i).t(),goalPts.row(i-1).t())/(pts.n_rows-1);
            for(int j=0; j<pts.n_rows; j++){

                arma::vec ptOnPolar;
                if(mode == cLAlpha || mode == XTrTop || mode == XTrBot){
                    double ptcL;
                    if(cLCD(cLCD.n_rows-1,0)<pts(j,0) || cLCD(0,0)>pts(j,0)){
                        ptcL = pts(j,1);
                    }else{
                        ptcL = interpolate(cLCD,pts(j,0));
                    }
                    ptOnPolar = arma::vec{pts(j,0),ptcL};
                    area += diff*distanceBetweenPoints(ptOnPolar,pts.row(j).t());
                }else{
                    double ptcD = interpolate(cLCD,pts(j,1));
                    if(pts(j,0) >= ptcD){
                        ptOnPolar = pts.row(j).t();
                    }else{
                        ptOnPolar = arma::vec{ptcD,pts(j,1)};
                    }
                    area += diff*distanceBetweenPoints(ptOnPolar,pts.row(j).t());
                }

                areaCoords.row(count) = pts.row(j);
                areaCoords.row(count+1)= ptOnPolar.t();
                count+=2;
            }
        }
        if(mode == cD){area*=200;} //Cd very small
        if(mode == XTrTop || mode == XTrBot){area*=10;}
        area *= bias;
        //std::cout << "area" << area << std::endl;
    }else{
        areaCoords = arma::mat(0,2);
    }
    emit calced();
}

void PolarGoal::onVisible(bool visible){

    //curveArea->setVisible(visible);
    dragCurve->setVisible(visible);

    plotDiff();
}

void PolarGoal::onActivation(bool active, bool recursively){

    dragCurve->setActive(active);
    plotDiff();
    if(active){emit activated(recursively);}
}

void PolarGoal::plotDiff(){

    curveArea->setSamples(areaCoords.colptr(0),areaCoords.colptr(1),
            areaCoords.n_rows);
    
    plot->replot();
}

void PolarGoal::setUpInterface(){
    ui.setupUi(&widget);

    ui.doubleSpinBox_multi->setRange(0.01,10.0);
    ui.doubleSpinBox_multi->setDecimals(3);
    ui.doubleSpinBox_multi->setSingleStep(0.1);

    connect(this,&PolarGoal::calced,this,[=](){ui.label_multi->setText(QString::number(area));},Qt::QueuedConnection);

    widget.show();

    //connect(ui.checkBox_verticalDiff,&QCheckBox::stateChanged,[this](bool state){verticalDiff = state;calcDifferenceToPolar();});
    connect(ui.doubleSpinBox_multi,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[=](double value){bias=value;calcDifferenceToPolar();});

    setInterfaceValues();
}

void PolarGoal::setInterfaceValues(){
    std::list<QObject*> toChange({ui.doubleSpinBox_multi});
    for(QObject* obj : toChange){obj->blockSignals(true);}
    ui.doubleSpinBox_multi->setValue(bias);
    for(QObject* obj : toChange){obj->blockSignals(false);}
}

void PolarGoal::setItemText(QString string){
    treeItem->setText(0,string);
}
