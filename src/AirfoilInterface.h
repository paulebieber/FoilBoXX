//
// Created by paul on 3/12/20.
//

#pragma once

#include <QFile>
#include <qnamespace.h>
#include <vector>
#include "Airfoil.h"
#include "QTreeWidgetItem"
#include "HierarchyElement.h"
#include "ui_airfoilWidget.h"
#include "BernsteinShapeInterface.h"
#include "FoilPlot.h"

class AirfoilInterface: public HierarchyElement, public Airfoil{

Q_OBJECT

friend QDataStream& operator<<(QDataStream& out, AirfoilInterface& airfoil); //For Serrialization, (saving the Airfoil)
friend QDataStream& operator>>(QDataStream& in, AirfoilInterface& airfoil); //For Serrialization, (loading the Airfoil)

    QFile file;
    QString name;

public: enum foilType{full, coords};
private: foilType type;

    //UI
    void setupInterface();
    void setInterfaceValues();
    Ui_airfoilWidget ui;
    FoilPlot* foilPlot;

    //Plotting
    std::vector<QColor> colors = std::vector<QColor>{Qt::blue,Qt::red,Qt::green,Qt::cyan,Qt::darkYellow,Qt::darkRed,Qt::darkGreen};
    int nCol = 0;
    void onActivation(bool active, bool recursively);
    void onVisible(bool active);

    void changedBaseCoords();
    bool hasFile;

public:
    AirfoilInterface(QTreeWidget* tree, QString name, FoilPlot* foilPlot);
    ~AirfoilInterface();

    QFile& getFile(){return file;}

    void parametrize();
    void saveFoil(bool as);
    void saveCoords(QString folderPath);
    void setName(QString string);
    QString getName(){return name;}
    bool getHasFile(){return hasFile;}
    void setFoilType(foilType type){this->type = type;foilPlot->setPermanentInvisible(type==coords ? true : false);}
    foilType getFoilType(){return type;}

    QColor* getColor(){
        return &colors[nCol++];
    };

public slots:
    void setThickness(double thickness);

signals:
    void changed();
    void activated(bool recursively);
    void calcAllPolars();
};
