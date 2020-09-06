
#pragma once

#include <QWidget>
#include <QDockWidget>
#include "QwtCustomPlot.h"

class PressurePlotWidget: public QwtCustomPlot{
Q_OBJECT

public:
   PressurePlotWidget(QWidget* parent = 0);
};
