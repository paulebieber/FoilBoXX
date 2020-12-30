// Created by paul on 24.05.19.

#pragma once

#include "armadillo"
#include "ShapeFunction.h"
#include "NoseBezier.h"

class Airfoil{

    //Nose Construction
    //NoseBezier* nose;
    //double nose_begin = 0.05;

    //flap
    arma::mat lowerFlapCoords, upperFlapCoords;
    arma::mat lowerFlapCoordsExtracted, upperFlapCoordsExtracted;
    arma::vec upperFlapPtDesign, lowerFlapPtDesign;
    arma::vec upperFlapPt, lowerFlapPt;
    arma::vec upperFlapPtExtracted, lowerFlapPtExtracted;
    arma::mat upperClassCoords, lowerClassCoords;
    arma::mat upperBaseCoords, lowerBaseCoords;
    arma::vec upperFlapPtDesignExtracted, lowerFlapPtDesignExtracted;

    arma::mat flosse;
    arma::mat flosseCut;
    arma::mat fkCoordsTop, fkCoordsBot;
    arma::mat fkCoordsTopRetracted, fkCoordsBotRetracted;
    arma::mat fkCoordsRetractedTop, fkCoordsRetractedBot;
    arma::vec fkOffset;
    arma::vec flapPivotExtracted;

    //Turbulator
    arma::vec turbTopPt, turbBotPt;
    arma::vec turbTopPtExtracted, turbBotPtExtracted;
    bool turbTopOnFlap, turbBotOnFlap;

    double fkFlapAngle;
    void setBase();
    void changeShapeSpacings();

    bool changedN;

protected:
    std::vector<ShapeFunction*> shapes;

    arma::vec flapPivot;
    double fkChordfactor;
    double fkThickness;
    double flapRelY;
    double etaDesignUpper;
    double etaDesignLower;
    bool fk;
    float teThickness;
    double yPlus;
    double noseY;
    double yMinus;
    bool flapByRel;
    bool turbOn;

public:
    Airfoil();
    ~Airfoil();
    
    enum foilType{full,coordsOnly,parametrization} type;
    enum analysisVersion{cP,cPVisc,hFac,rheTheta};

    void addShapeFunction(ShapeFunction* shape);
    void setClassShapes();
    void baseCoords();

    //Getters,Setters
    enum attributes{setNoseY,setYPlus,setYMinus,setFlapX,setFlapYRelative,setFlapYAbsolute,setFk,setTurbTop,setTurbBot,
                        setFkChordFactor,setTurbOn};
    template <typename T> void setAttribute(attributes kind, T value, bool recalc);

    
    double getEtaDesignUpper(){return etaDesignUpper*180/M_PI;}
    double getEtaDesignLower(){return etaDesignLower*180/M_PI;}
    double getNoseY(){return noseY;}
    double getYPlus(){return yPlus;}
    double getYMinus(){return yMinus;}
    double getTurbTopOnFlap(){return turbTopOnFlap;}
    double getTurbBotOnFlap(){return turbBotOnFlap;}
    double getFlapX(){return flapPivot(0);}
    double getFlapYRelative(){return flapRelY;}
    bool getBoolRelative(){return flapByRel;}
    double getFlapYAbsolute(){return flapPivot(1);}
    std::tuple<std::vector<arma::mat>,arma::vec,arma::vec> getModeCoords(bool fkExtracted, double eta);
    std::vector<double> getTurb() const {return std::vector<double>{turbTopPt(0),turbBotPt(0)};}
    double getFkChordfactor(){ return fkChordfactor;}
    double getFkThickness(){ return fkThickness;}
    double getFk(){return fk;}
    arma::mat& getFlosse(){return flosse;}
    arma::mat& getFlosseCut(){return flosseCut;}
    arma::mat& getUpperBaseCoords(){return upperBaseCoords;}
    arma::mat& getLowerBaseCoords(){return lowerBaseCoords;}

    void virtual changedBaseCoords(bool nChanged){};
};

