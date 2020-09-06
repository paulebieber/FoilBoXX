
#pragma once

#include <QWidget>
#include <QDockWidget>
#include <vector>
#include "QwtCustomPlot.h"

class FoilPlotWidget: public QwtCustomPlot{
Q_OBJECT

    QMetaObject::Connection* externalConnection;

public:
   FoilPlotWidget(QWidget* parent = NULL);
};
