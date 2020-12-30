// Created by paul on 4/5/20.

#pragma once

#include "AirfoilInterface.h"
#include "ModePlot.h"
#include "ui_modeWidget.h"
#include "ui_coordsModeWidget.h"

class ModePlot;

class FoilMode: public HierarchyElement{ 

Q_OBJECT

friend QDataStream& operator<<(QDataStream& out, const FoilMode& mode); //For Serrialization, (saving the Airfoil)
friend QDataStream& operator>>(QDataStream& in, FoilMode& mode); //For Serrialization, (loading the Airfoil)

    friend class ModePlot;
    
    AirfoilInterface* airfoil;
    QMetaObject::Connection airfoilConnection;

    double eta = 0.0;
    bool fk = false;
    bool smoothUpper = false;
    bool smoothLower = false;

    public: enum modeTypes{full,coords};
    private: modeTypes modeType;

    //Coords
    arma::mat coordsAero;
    arma::mat flapTop;
    arma::mat flapBot;
    arma::mat fkTop;
    arma::mat fkBot;
    arma::vec turbTop{1.0,0};
    arma::vec turbBot{1.0,0};

    //For loaded Coords
    arma::mat lowerSide;
    arma::mat upperSide;

    //UI
    void setupInterface();
    void setInterfaceValues();
    Ui_modeWidget ui;
    Ui_coordsModeWidget uiCoords;
    QColor color;
    ModePlot* modePlot;
    void onActivation(bool active, bool recursively=false);
    void onVisible(bool visible);

    void setFK(bool on, bool recalc = true);

public:
    FoilMode(AirfoilInterface* foil, ModePlot* modePlot);
    FoilMode(AirfoilInterface* foil, QTextStream& in, ModePlot* modePlot);
    ~FoilMode();

    void setTurbsFromAero();
    void calcCoords();
    void saveCoords(QTextStream& out);
    void saveFlap(QTextStream& out);
    QString getCoordsName();
    void connectToFoil(AirfoilInterface* foil);
    void plotCoords();
    void setItemText(QString string);
    void setEta(double eta, bool recalc = true);

    //Getters
    AirfoilInterface* getAirfoil(){return airfoil;};
    double getEta(){return eta;}
    arma::mat& getCoords(){return coordsAero;}
    double& getTurbTop(){return turbTop(0);}
    double& getTurbBot(){return turbBot(0);}
    bool getFk(){return fk;}
    modeTypes getModeType(){return modeType;}
    bool getSmoothUpper(){return smoothUpper;}
    bool getSmoothLower(){return smoothLower;}
    arma::mat* getAero(){return &coordsAero;}
    QColor& getColor(){return color;}

public slots:
    void setItemText();

signals:
    void activated(bool recursively);
    void changed();
    void reInterface();
};
