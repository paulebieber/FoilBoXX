//
// Created by paul on 4/1/20.
//

#include "QwtCustomPlot.h"
#include "math.h"
#include <list>
#include <qnamespace.h>

QwtCustomPlot::QwtCustomPlot(QWidget* widget, QString xString, QString yString, double ratio):QwtPlot(widget),
                dragging(false),zoomStep(1.0){

    //canvas()->setContentsMargins(0, 0, 0, 0);
    canvas()->setStyleSheet("QwtPlotCanvas {margin: 0; background-color: #ffffff;}");

    for(QwtScaleWidget* axis: std::list<QwtScaleWidget*>{axisWidget(QwtPlot::yRight),axisWidget(QwtPlot::xBottom),
            axisWidget(QwtPlot::yRight),axisWidget(QwtPlot::xTop)}){
        //axis->setMargin(20);
        //axis->setSpacing(0);
    }

    grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::darkGray,1,Qt::DotLine));
    grid->setYAxis(QwtPlot::yRight);
    grid->attach(this);
    //picker = new QwtPlotPicker(canvas());
    //picker->setTrackerMode(QwtPicker::AlwaysOn);
    //picker->setStateMachine(new QwtPicker);

    //setAxisLabelRotation(0,-90);
    if(ratio != 0){
        rescaler = new QwtPlotRescaler(canvas());
        rescaler->setReferenceAxis(QwtPlot::xBottom);
        rescaler->setAspectRatio(QwtPlot::yRight,ratio);
        rescaler->setRescalePolicy(QwtPlotRescaler::Fixed);
        rescaler->setExpandingDirection(QwtPlotRescaler::ExpandBoth);
        rescaler->setEnabled(true);
    }

    static_cast<QFrame*>(canvas())->setFrameShadow(QFrame::Plain);

    // Labels
    QFont font;
    font.setBold( true );
    font.setStyle(QFont::StyleItalic);
    font.setPointSize(12);
    
    QwtText xTitle(xString);
    QwtText yTitle(yString);
    xTitle.setRenderFlags( Qt::AlignLeft | Qt::AlignBottom );
    yTitle.setRenderFlags( Qt::AlignRight | Qt::AlignTop );

    for(QwtText* text: std::list<QwtText*>{&xTitle,&yTitle}){
        text->setFont( font );
        text->setColor(Qt::darkGray);
    }

    xLabel.setText(xTitle);
    yLabel.setText(yTitle);

    xLabel.attach(this);
    yLabel.attach(this);

    //Fitter
    fitter.setFitMode(QwtSplineCurveFitter::Spline);

    //canvas()->setFocusPolicy(Qt::StrongFocus);
    //canvas()->setMouseTracking(true);
    
    //Gives place for longer axis lables and prevents pincing of coordinate space
    axisWidget(QwtPlot::xBottom)->setMinBorderDist(20,20);
    axisWidget(QwtPlot::yRight)->setMinBorderDist(20,20);
}

void QwtCustomPlot::fitCurve(QwtPlotCurve* curve){

    curve->setCurveAttribute(QwtPlotCurve::Fitted,true);
    curve->setCurveFitter(&fitter);
    curve->setRenderHint(QwtPlotCurve::RenderAntialiased,true);
}

void QwtCustomPlot::connectToAxis(QwtCustomPlot* plot){

    scaleMapX = canvasMap(QwtPlot::xBottom);
    double x1 = scaleMapX.s1();
    double x2 = scaleMapX.s2();


    connect(plot,&QwtCustomPlot::rangeChanged,[this,plot](int id, double min, double max){
        if(id == QwtPlot::xBottom){
            setAxisScale(id,min,max);
            replot();
            rescaler->rescale();}
        });

    connect(this,&QwtCustomPlot::rangeChanged,[this,plot](int id, double min, double max){
        if(id == QwtPlot::xBottom){
            plot->setAxisScale(id,min,max);
            plot->replot();
            plot->rescale();}
        });

}

bool QwtCustomPlot::eventFilter(QObject* obj, QEvent* event) {

    scaleMapX = canvasMap(QwtPlot::xBottom);
    scaleMapY = canvasMap(QwtPlot::yRight);

    if(event->type() == QEvent::Wheel){
        
        //When Zooming via MouseWheel
        ////////////////////////////
        QWheelEvent* mouseEvent = static_cast<QWheelEvent*>(event);
        double step = 1-zoomStep*mouseEvent->angleDelta().y()/600.0;

        QPointF pos = transform(mouseEvent->pos());

        double x1 = scaleMapX.s1();
        double x2 = scaleMapX.s2();
        double y1 = scaleMapY.s1();
        double y2 = scaleMapY.s2();

        x1 = pos.x()-step*(pos.x()-x1);
        x2 = pos.x()+step*(x2-pos.x());
        y1 = pos.y()-step*(pos.y()-y1);
        y2 = pos.y()+step*(y2-pos.y());

        setAxisScale(QwtPlot::xBottom, x1, x2);
        setAxisScale(QwtPlot::yRight, y1, y2);
        emit rangeChanged(QwtPlot::yRight,y1,y2);
        emit rangeChanged(QwtPlot::xBottom,x1,x2);

        replot();

        return true;

    }
    else if(event->type() == QEvent::MouseButtonPress){

        //When LeftButton Presse: activate Dragging 
        ///////////////////////////////////////////
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() == Qt::RightButton){
            panning = true;
            panningCheckpoint = mouseEvent->pos();
        }
        if(mouseEvent->button() == Qt::LeftButton){
            dragging = true;
            draggingCheckpoint = mouseEvent->pos();
            if(dragging){emit startDrag(transform(mouseEvent->pos()));}
        }
    return true;
    
    }
    else if(event->type() == QEvent::MouseButtonRelease){

        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() == Qt::RightButton){
            panning = false;
            return true;
        }
        if(mouseEvent->button() == Qt::LeftButton){
            dragging = false;
            emit dragFinished();
            return true;
        }
    }
    else if(event->type() == QEvent::MouseMove){

        //When MouseMove: emit DeltaPt, that was moved
        //if dragging(Mouse clicked) or pan if rightClick
        ////////////////////////////////////////////////
        
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        
        QPointF pos = transform(mouseEvent->pos());
        draggingCheckpoint = transform(draggingCheckpoint);
        panningCheckpoint = transform(panningCheckpoint);

        if(!panning && !dragging){
            emit mouseMoved(pos);
            return true;

        }else if(dragging){
            QPointF delta = (pos - draggingCheckpoint);
            if(scaleMapY.s2() < scaleMapY.s1()){
                delta.setY(-1*delta.y());
            }
            emit dragged(pos,delta);
            draggingCheckpoint = mouseEvent->pos();

        }else{
            QPointF delta = panningCheckpoint - pos;
            setAxisScale(QwtPlot::xBottom, scaleMapX.s1()+delta.x(), scaleMapX.s2()+delta.x());
            setAxisScale(QwtPlot::yRight, scaleMapY.s1()+delta.y(), scaleMapY.s2()+delta.y());
            emit rangeChanged(QwtPlot::yRight, scaleMapY.s1()+delta.y(), scaleMapY.s2()+delta.y());
            emit rangeChanged(QwtPlot::xBottom, scaleMapX.s1()+delta.x(), scaleMapX.s2()+delta.x());
            panningCheckpoint = mouseEvent->pos();
            
            replot();
            return true;
        }
    }
    else if(event->type() == QEvent::KeyPress){

        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_W){
            emit pressedUpDown(1);
            return true;
        }
        if(keyEvent->key() == Qt::Key_S){
            emit pressedUpDown(-1);
            return true;
        }
    }
    return QObject::eventFilter(obj,event);
}

QPointF QwtCustomPlot::transform(QPointF pt){

    pt.setX(scaleMapX.invTransform(pt.x()));
    pt.setY(scaleMapY.invTransform(pt.y()));

    return pt;
}
