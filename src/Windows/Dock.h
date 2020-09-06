
#pragma once

#include <QDockWidget>

class Dock: public QDockWidget{
Q_OBJECT

public:
   Dock(QWidget* child, QString name = QString("Widget"), QWidget* parent = NULL);
};
