// Created by paul on 4/1/20.

#pragma once

#include "QObject"
#include "QWheelEvent"

#include "qwt_plot.h"
#include "qwt_plot_picker.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_scaleitem.h"
#include "qwt_plot_layout.h"
#include "qwt_scale_widget.h"
#include "qwt_plot_rescaler.h"
#include "qwt_picker_machine.h"
#include "qwt_plot_curve.h"
#include "qwt_symbol.h"
#include "qwt_plot_textlabel.h"
#include "qwt_curve_fitter.h"

class QwtCustomPlot: public QwtPlot{
Q_OBJECT

    QwtPlotGrid* grid;
    //QwtPlotPicker* picker;
    bool dragging;
    bool panning;
    QPointF draggingCheckpoint;
    QPointF panningCheckpoint;

    //labels
    QwtPlotTextLabel yLabel, xLabel;

    //CurveSmoothing
    QwtSplineCurveFitter fitter;

    double zoomStep;

    QwtScaleMap scaleMapX;
    QwtScaleMap scaleMapY;

public:
    QPointF transform(QPointF pt);
    QwtCustomPlot(QWidget* = NULL,QString xLabel = QString(""),QString yLabel = QString("") ,double ratio = 1.0);
    //void setScale(int axisId, double min, double max);
    void fitCurve(QwtPlotCurve* curve);
    void rescale(){rescaler->rescale();};
    void connectToAxis(QwtCustomPlot* plot);

signals:
    void mouseMoved(QPointF pt);
    void pressedUpDown(int sign);
    void dragged(QPointF pt, QPointF delta);
    void rangeChanged(int axisId, double min, double max);
protected:
    QwtPlotRescaler* rescaler;
    bool eventFilter(QObject* obj, QEvent* event);
};

