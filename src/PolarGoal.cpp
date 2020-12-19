
#include "PolarGoal.h"
#include <qnamespace.h>
#include <QDebug>

PolarGoal::PolarGoal(QwtCustomPlot* plot, Polar* polar):HierarchyElement(polar),plot(plot),polar(polar),
    goalPts(arma::mat{{0.2,0.006},{0.4,0.007},{0.5,0.008}}),normalDiff(false){

    curve->attach(plot);
    curveArea->attach(plot);
    curveHandles->attach(plot);
    curve->setYAxis(QwtPlot::yRight);
    curveHandles->setYAxis(QwtPlot::yRight);
    curveArea->setYAxis(QwtPlot::yRight);
    curve->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    curveArea->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    curveHandles->setRenderHint(QwtPlotCurve::RenderAntialiased,true);

    connect(plot,&QwtCustomPlot::dragged,[this](QPointF pt, QPointF delta){modify(pt,delta);});
    connect(plot,&QwtCustomPlot::startDrag,this,&PolarGoal::checkForPoint);
    connect(plot,&QwtCustomPlot::dragFinished,[this](){dragging=false;});

    connect(this,&PolarGoal::calced,this,&PolarGoal::plotGoal,Qt::QueuedConnection);
    connect(polar->thread,&WorkerThread::resultReady,this,&PolarGoal::calcDifferenceToPolar,Qt::DirectConnection);

    symbol = new QwtSymbol(QwtSymbol::Ellipse);
    symbol->setSize(QSize(6,6));
    curveHandles->setPen(Qt::transparent);
    curveHandles->setSymbol(symbol);

    pen.setWidth(1.0);
    pen.setColor(Qt::lightGray);
    goalPen.setWidth(2.0);
    goalPen.setColor(Qt::gray);
    goalPen.setStyle(Qt::DashLine);
    setItemText("Goal");

    calcDifferenceToPolar();
}

PolarGoal::~PolarGoal(){
    curve->detach(); delete curve;
    curveArea->detach(); delete curveArea;
}

QDataStream& operator<<(QDataStream& out, const PolarGoal& goal){

    out << QString("PolarGoal");
    out << QVector<double>::fromStdVector(arma::conv_to<std::vector<double>>::from(goal.goalPts.col(0)));
    out << QVector<double>::fromStdVector(arma::conv_to<std::vector<double>>::from(goal.goalPts.col(1)));
    return out;
}

QDataStream& operator>>(QDataStream& in, PolarGoal& goal){

    QVector<double> vec,vec2;
    in >> vec;
    in >> vec2;
    std::vector<double> xs(vec.begin(),vec.end());
    std::vector<double> ys(vec2.begin(),vec2.end());
    arma::mat pts(xs.size(),2);
    pts.col(0) = arma::conv_to<arma::vec>::from(xs);
    pts.col(1) = arma::conv_to<arma::vec>::from(ys);

    goal.goalPts = pts;
    goal.plotGoal();

    return in;
}

void PolarGoal::calcDifferenceToPolar(){

    area = 0.0;

    int n_disc = 100;
    int count = 0;
    int viewRatio = 40;

    if(!polar->getSuccess()){return;}
    arma::mat& polarPts = polar->getPolar();

    arma::mat cLCD(polarPts.n_rows,2);
    cLCD.col(0) = polarPts.col(0);
    cLCD.col(1) = polarPts.col(1);

    //Coordinates for visualizing area
    if (cLCD.n_rows > 0){

        areaCoords = arma::mat((goalPts.n_rows-1)*n_disc*2,2);

        if(normalDiff){
            cLCD.col(1) *= viewRatio;

            for(int i=1; i<goalPts.n_rows; i++){
                arma::mat pts(n_disc,2);
                pts.col(0) = arma::linspace(goalPts(i-1,0),goalPts(i,0),pts.n_rows);
                pts.col(1) = arma::linspace(viewRatio*goalPts(i-1,1),viewRatio*goalPts(i,1),pts.n_rows);
                double diff =  (goalPts(i,1)-goalPts(i-1,1))/(pts.n_rows-1);
                for(int j=0; j<pts.n_rows; j++){
                    arma::vec ptOnPolar = closestPointToPoint(cLCD,pts.row(j).t(),cLCD(0,0),cLCD.tail_rows(1)(0));
                    ptOnPolar(1) *= 1000/viewRatio;
                    pts(j,1) *= 1000/viewRatio;

                    area += diff*distanceBetweenPoints(ptOnPolar,pts.row(j).t());

                    areaCoords.row(count) = pts.row(j);
                    areaCoords.row(count+1)= ptOnPolar.t();
                    count+=2;
                }
            }
        }else{
            for(int i=1; i<goalPts.n_rows; i++){
                arma::mat pts(n_disc,2);
                pts.col(0) = arma::linspace(goalPts(i-1,0),goalPts(i,0),pts.n_rows);
                pts.col(1) = arma::linspace(goalPts(i-1,1),goalPts(i,1),pts.n_rows);
                double diff =  distanceBetweenPoints(goalPts.row(i).t(),goalPts.row(i-1).t())/(pts.n_rows-1);
                for(int j=0; j<pts.n_rows; j++){
                    double ptcD = interpolate(cLCD,pts(j,0));
                    arma::vec ptOnPolar{pts(j,0),ptcD};
                    ptOnPolar(1) *= 1000;
                    pts(j,1) *= 1000;

                    area += diff*distanceBetweenPoints(ptOnPolar,pts.row(j).t());

                    areaCoords.row(count) = pts.row(j);
                    //std::cout  << ptOnPolar.t() << std::endl;
                    areaCoords.row(count+1)= ptOnPolar.t();
                    count+=2;
                }
            }
        }
    }else{
        areaCoords = arma::mat(0,2);
    }
    emit calced();
}

void PolarGoal::checkForPoint(QPointF pt){

    for(int i = 0; i<goalPts.n_rows; ++i){
        arma::vec ptA{pt.y(),pt.x()};
        arma::vec ptB = goalPts.row(i).t();
        ptB(1)=ptB(1)*1000;
        if(fabs(ptB(0)-ptA(0)) < 0.03 && fabs(ptB(1)-ptA(1)) < 0.3){
            dragIndex = i;  
            dragging = true;
            break;
        }
    }
}

void PolarGoal::modify(QPointF pt, QPointF delta){

    if(!active || !dragging){return;}
    arma::vec deltaA{delta.y(),delta.x()/1000};
    goalPts.row(dragIndex) += deltaA.t();

    calcDifferenceToPolar();
    plotGoal();
}

void PolarGoal::onVisible(bool visible){

    curve->setVisible(visible);
    curveArea->setVisible(visible);
    curveHandles->setVisible(visible);

    plotGoal();
}

void PolarGoal::onActivation(bool active, bool recursively){

    curveArea->setPen(goalPen);
    curve->setPen(goalPen);

    plotGoal();

    if(active){emit activated(recursively);}
}

void PolarGoal::plotGoal(){

    multipliedGoal = arma::vec(goalPts.col(1)*1000);
    curve->setSamples(multipliedGoal.memptr(),goalPts.colptr(0),goalPts.n_rows);
    curveHandles->setSamples(multipliedGoal.memptr(),goalPts.colptr(0),goalPts.n_rows);
    curveArea->setSamples(areaCoords.colptr(1),areaCoords.colptr(0),
            areaCoords.n_rows);
    curve->setPen(goalPen);
    curveArea->setPen(pen);
    
    plot->replot();
}

void PolarGoal::setItemText(QString string){
    treeItem->setText(0,string);
}
