
#include "DraggableCurve.h"
#include <QDebug>

DraggableCurve::DraggableCurve(QwtCustomPlot* plot, arma::mat initPts):plot(plot),
    pts(initPts),visible(true){

    curve->attach(plot);
    //curveHandles->attach(plot);
    curve->setYAxis(QwtPlot::yRight);
    //curveHandles->setYAxis(QwtPlot::yRight);
    curve->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
    //curveHandles->setRenderHint(QwtPlotCurve::RenderAntialiased,true);

    connect(plot,&QwtCustomPlot::dragged,[this](QPointF pt, QPointF delta){modify(pt,delta);});
    connect(plot,&QwtCustomPlot::startDrag,this,&DraggableCurve::checkForPoint);
    connect(plot,&QwtCustomPlot::dragFinished,[this](){dragging=false;});

    symbol = new QwtSymbol(QwtSymbol::Ellipse);
    symbol->setSize(QSize(6,6));
    curve->setSymbol(symbol);
    //curveHandles->setPen(Qt::transparent);
    //curveHandles->setSymbol(symbol);

    pen.setWidth(2.0);
    pen.setColor(Qt::gray);
    pen.setStyle(Qt::DashLine);

    resetCurve();
}

DraggableCurve::~DraggableCurve(){
    curve->detach(); delete curve;
}

QDataStream& operator<<(QDataStream& out, const DraggableCurve& drag){

    out << QVector<double>::fromStdVector(arma::conv_to<std::vector<double>>::from(drag.pts.col(0)));
    out << QVector<double>::fromStdVector(arma::conv_to<std::vector<double>>::from(drag.pts.col(1)));
    return out;
}

QDataStream& operator>>(QDataStream& in, DraggableCurve& drag){

    QVector<double> vec,vec2;
    in >> vec;
    in >> vec2;
    std::vector<double> xs(vec.begin(),vec.end());
    std::vector<double> ys(vec2.begin(),vec2.end());
    arma::mat pts(xs.size(),2);
    pts.col(0) = arma::conv_to<arma::vec>::from(xs);
    pts.col(1) = arma::conv_to<arma::vec>::from(ys);

    drag.pts = pts;
    return in;
}

void DraggableCurve::checkForPoint(QPointF pt){

    for(int i = 0; i<pts.n_rows; ++i){
        arma::vec ptA{pt.x(),pt.y()};
        arma::vec ptB = pts.row(i).t();
        double dragDeltaY = plot->axisScaleDiv(QwtPlot::yRight).range()/60;
        double dragDeltaX = plot->axisScaleDiv(QwtPlot::xBottom).range()/60;
        if(fabs(ptB(0)-ptA(0)) < dragDeltaX && fabs(ptB(1)-ptA(1)) < dragDeltaY){
            dragIndex = i;  
            dragging = true;
            break;
        }
    }
}

void DraggableCurve::modify(QPointF pt, QPointF delta){

    if(!active || !dragging || !visible){return;}
    arma::vec deltaA{delta.x(),delta.y()};
    pts.row(dragIndex) += deltaA.t();
    plot->replot();
    emit ptsChanged();
}

void DraggableCurve::setVisible(bool visible){

    curve->setVisible(visible);
    //curveHandles->setVisible(visible);
    //plotCurve();
}

void DraggableCurve::resetCurve(){

    curve->setRawSamples(pts.colptr(0),pts.colptr(1),pts.n_rows);
    //curveHandles->setRawSamples(pts.memptr(),pts.colptr(0),pts.n_rows);
    curve->setPen(pen);
    
    plot->replot();
}
