//
// Created by paul on 24.05.19.
//

#include "Airfoil.h"
#include <iostream>
#include <math.h>
#include "SplineFunctions.h"

Airfoil::Airfoil():
    teThickness(0.005),flapRelY(0.5),flapByRel(true),flapPivot({0.8,0.0}),
    noseY(0.0),fk(false),fkChordfactor(1.14), turbOn(false), turbBotPt({1.0,0}),turbTopPt({1.0,0}),
    yPlus(0.0),yMinus(0.0),changedN(false){

    setClassShapes();
    baseCoords();
}

Airfoil::~Airfoil(){

    for(ShapeFunction* shape: shapes){
        delete shape;
    }
}

void Airfoil::addShapeFunction(ShapeFunction* shape){

    shapes.push_back(shape);
    setClassShapes();
}

void Airfoil::changeShapeSpacings(){

    for(ShapeFunction* shape: shapes){
        if(shape->getSide() == ShapeFunction::top){shape->setSpacing(upperClassCoords.col(0));} //Do that on adding of Shape or change of fkChordfac!
        else{shape->setSpacing(lowerClassCoords.col(0));}
    }
}

void Airfoil::setClassShapes(){

    double noseEnd = 0.03;
    double nNose = 15;

    double delta = 0.03;
    double x1 = flapPivot(0);
    double nNoseTo1 = 35;
    double x2 = flapPivot(0);
    double n1To2 = 20;
    double nToEnd = 20;
    double nFk = 10;

    arma::vec spacingNose = pow(arma::linspace(0, 0.5, nNose),3)*noseEnd/pow(0.5,3);

    arma::vec spacingNoseTo1 = arma::linspace(noseEnd, x1-delta, nNoseTo1);
    spacingNoseTo1 = spacingNoseTo1.subvec(1,spacingNoseTo1.size()-1);

    arma::vec spacing2 = x1-delta + (pow(0.5,2)-pow(arma::linspace(0.5, 0.0, n1To2/2),2))*(flapPivot(0)-(x1-delta))/pow(0.5,2);
    spacing2 = spacing2.subvec(1,spacing2.size()-1);

    arma::vec spacing3 = flapPivot(0) + (pow(arma::linspace(0, 0.5, n1To2/2),2))*(x2+delta-flapPivot(0))/pow(0.5,2);
    spacing3 = spacing3.subvec(1,spacing3.size()-1);

    arma::vec spacingToEnd = flapPivot(0)+delta + (pow(0.5,2)-pow(arma::linspace(0.5, 0.0, nToEnd),2))*(1.0-x2-delta)/pow(0.5,2);
    spacingToEnd = spacingToEnd.subvec(1,spacingToEnd.size()-1);

    arma::vec spacingLower = arma::vec(spacingNose.size()+spacingNoseTo1.size()+spacing2.size()+spacing3.size()+spacingToEnd.size());

    spacingLower.head(spacingNose.size()) = spacingNose;
    spacingLower.subvec(spacingNose.size(), size(spacingNoseTo1)) = spacingNoseTo1;
    spacingLower.subvec(spacingNose.size()+spacingNoseTo1.size(), size(spacing2)) = spacing2;
    spacingLower.subvec(spacingNose.size()+spacingNoseTo1.size()+spacing2.size(), size(spacing3)) = spacing3;
    spacingLower.tail(spacingToEnd.size()) = spacingToEnd;

    //UpperSide (if fk, add some points for fk)
    arma::vec spacingFk = fk ? arma::linspace(flapPivot(0), fkChordfactor-(1-flapPivot(0))-delta, nFk) : arma::vec{} ;

    if(fk){
        spacingFk = spacingFk.subvec(1,spacingFk.size()-1);

        spacingNoseTo1 = arma::linspace(noseEnd, flapPivot(0), nNoseTo1);
        spacingNoseTo1 = spacingNoseTo1.subvec(1,spacingNoseTo1.size()-1);

        spacing2 += (fkChordfactor-1.0);
        spacing3 += (fkChordfactor-1.0);
        spacingToEnd += (fkChordfactor-1.0);
    }

    arma::vec spacingUpper = arma::vec(spacingNose.size()+spacingNoseTo1.size()+spacing2.size()+spacing3.size()+spacingToEnd.size()+spacingFk.size());

    spacingUpper.head(spacingNose.size()) = spacingNose;
    spacingUpper.subvec(spacingNose.size(), size(spacingNoseTo1)) = spacingNoseTo1;
    spacingUpper.subvec(spacingNose.size()+spacingNoseTo1.size(), size(spacingFk)) = spacingFk;
    spacingUpper.subvec(spacingNose.size()+spacingNoseTo1.size()+spacingFk.size(), size(spacing2)) = spacing2;
    spacingUpper.subvec(spacingNose.size()+spacingNoseTo1.size()+spacing2.size()+spacingFk.size(), size(spacing3)) = spacing3;
    spacingUpper.tail(spacingToEnd.size()) = spacingToEnd;

    upperClassCoords = arma::mat(spacingUpper.n_rows, 2);
    lowerClassCoords = arma::mat(spacingLower.n_rows, 2);
    upperClassCoords.col(0) = spacingUpper;
    lowerClassCoords.col(0) = spacingLower;
    upperClassCoords.col(1) = 0.15*pow(spacingUpper/spacingUpper.back(), 0.5) % pow(1 - spacingUpper/spacingUpper.back(), 1);
    lowerClassCoords.col(1) = -0.15*pow(spacingLower, 0.5) % pow(1 - spacingLower, 1);

    changeShapeSpacings();
    changedN = true;
}

void Airfoil::baseCoords() {

    upperBaseCoords = upperClassCoords;
    lowerBaseCoords = lowerClassCoords;

    //Multiply all Shapefunctions to BaseShape
    for(ShapeFunction* shape: shapes){
        if(shape->getSide() == ShapeFunction::top){
            upperBaseCoords.col(1) = upperBaseCoords.col(1) % shape->getShape();}
        else{
            lowerBaseCoords.col(1) = lowerBaseCoords.col(1) % shape->getShape();
        }
    }

    upperBaseCoords.col(1) += pow(upperBaseCoords.col(0)/upperBaseCoords(upperBaseCoords.n_rows-1,0),2)*(-yPlus+teThickness/2);
    lowerBaseCoords.col(1) += pow(lowerBaseCoords.col(0),2)*(yMinus-teThickness/2);

    //Add noseY
    double noseX = 0.75;
    arma::vec noseTop(upperBaseCoords.n_rows);
    for(int i = 0; i< upperBaseCoords.n_rows; i++){
        noseTop(i) = (upperBaseCoords(i,0) <= noseX) ? pow((noseX-upperBaseCoords(i,0))/noseX,2)*noseY : 0.0;
    }
    arma::vec noseBot(lowerBaseCoords.n_rows);
    for(int i = 0; i< lowerBaseCoords.n_rows; i++){
        noseBot(i) = (lowerBaseCoords(i,0) <= noseX) ? pow((noseX-lowerBaseCoords(i,0))/noseX,2)*noseY : 0.0;
    }

    upperBaseCoords.col(1) += noseTop;
    lowerBaseCoords.col(1) += noseBot;
    
    // Get lower YValue at X_Flap
    double lowerY = interpolate(lowerBaseCoords,flapPivot[0]);
    double upperY = interpolate(upperBaseCoords,flapPivot[0]);

    // Mainly Calculation of FlapPivot depending on flapRelY, and bool flapByRel
    if(flapByRel){ flapPivot(1) = lowerY+flapRelY*(upperY-lowerY);
    }else{flapRelY = (flapPivot(1)-lowerY)/(upperY-lowerY);}

    arma::vec upperEndPt{1.0,teThickness/2};
    arma::vec lowerEndPt{1.0,-teThickness/2};
    arma::mat tempFlapUpper, tempFlapLower;

    if (!fk){
        //Scale in x_Direction, so that remorphed Coords corresponding to eta = 0 end at x = 1.0
        double upperDist = distanceBetweenPoints(flapPivot,upperEndPt);
        double upperFac = flapPivot(0)+sqrt(pow(upperDist,2)-pow(flapPivot(1)-upperBaseCoords(upperBaseCoords.n_rows-1,1),2));
        upperBaseCoords.col(0)*=upperFac;
        upperFlapPtDesign = closestPointToPoint(upperBaseCoords,flapPivot,flapPivot(0)-0.4,2.0);
        etaDesignUpper = atan2(teThickness/2-flapPivot(1),1-flapPivot(0)) - atan2(upperBaseCoords(upperBaseCoords.n_rows-1,1)-flapPivot(1),upperBaseCoords(upperBaseCoords.n_rows-1,0)-flapPivot(0));
        tempFlapUpper = rotate(upperBaseCoords,flapPivot,etaDesignUpper);
    }else{
        upperFlapPtDesign = closestPointToPoint(upperBaseCoords,flapPivot,flapPivot(0)-0.4,2.0);
        double upperFlapPtDesignDer = interpolate(upperBaseCoords,upperFlapPtDesign(0),true);
        etaDesignUpper = searchEtaDesign(upperBaseCoords,upperFlapPtDesign,upperFlapPtDesignDer,flapPivot,upperEndPt);
        arma::vec upperEndPtEta = rotate(upperEndPt,flapPivot,-etaDesignUpper);

        //Translate to upperEndPtEta[-1]
        arma::vec delta = upperBaseCoords.row(upperBaseCoords.n_rows-1).t()-upperEndPtEta;
        tempFlapUpper = upperBaseCoords;
        for(int i=0; i<tempFlapUpper.n_rows; i++){
            tempFlapUpper.row(i) -= delta.t();
        }

        //Calc again the Angle to tilt, like in Optimzation:
        arma::vec radiusOnCoordsToTilt = intersect(tempFlapUpper,upperEndPtEta,distanceBetweenPoints(upperEndPtEta,upperFlapPtDesign));
        double toTilt = -(atan2(upperFlapPtDesign(1)-upperEndPtEta(1), upperEndPtEta(0)-upperFlapPtDesign(0))
                - atan2(radiusOnCoordsToTilt(1)-upperEndPtEta(1), upperEndPtEta(0)-radiusOnCoordsToTilt(0)));

        tempFlapUpper = rotate(tempFlapUpper,upperEndPtEta,toTilt);
        tempFlapUpper = rotate(tempFlapUpper,flapPivot,etaDesignUpper);

        fkFlapAngle = etaDesignUpper + toTilt;
    }

    double lowerDist = distanceBetweenPoints(flapPivot,lowerEndPt);
    double lowerFac = flapPivot(0)+sqrt(pow(lowerDist,2)-pow(flapPivot(1)-lowerBaseCoords(lowerBaseCoords.n_rows-1,1),2));
    lowerBaseCoords.col(0)*=lowerFac;

    lowerFlapPtDesign = closestPointToPoint(lowerBaseCoords,flapPivot,flapPivot(0)-0.4,2.0);
    etaDesignLower = atan2(-teThickness/2-flapPivot(1),1-flapPivot(0)) - atan2(lowerBaseCoords(lowerBaseCoords.n_rows-1,1)-flapPivot(1),
            lowerBaseCoords(lowerBaseCoords.n_rows-1,0)-flapPivot(0));
    tempFlapLower = rotate(lowerBaseCoords,flapPivot,etaDesignLower);

    lowerFlapPt = rotate(lowerFlapPtDesign.t(),flapPivot,etaDesignLower).t();
    upperFlapPt = rotate(upperFlapPtDesign.t(),flapPivot,etaDesignUpper).t();

    //Cutting Flap at start of radius (later added):
    tempFlapLower = coordsFromX(tempFlapLower,lowerFlapPt(0));
    tempFlapUpper = coordsFromX(tempFlapUpper,upperFlapPt(0));

    //Cutting Flosse at start of flap:
    //Loop for reversing order of coords and removing redundant 0,0-Point (int i = 1).
    arma::mat upperBaseCoordsRev = upperBaseCoords.submat(1,0,upperBaseCoords.n_rows-1,1);
    upperBaseCoordsRev = coordsFromX(upperBaseCoordsRev,upperFlapPt(0)-0.01,true,true);
    arma::mat tempInverse = upperBaseCoordsRev;

    for (int i = 0; i < tempInverse.n_rows; ++i) {
        upperBaseCoordsRev.row(tempInverse.n_rows - 1 - i) = tempInverse.row(i);
    }

    flosse = arma::join_cols(upperBaseCoordsRev, coordsFromX(lowerBaseCoords,lowerFlapPt(0)-0.01,true,true));

    // Creation of the Flap with Flapnose, depending on calculated flapPivot
    //Calculating Radii of flap nose for lower and upper noseside
    double r_top = distanceBetweenPoints(upperFlapPt,flapPivot);
    double r_bot = distanceBetweenPoints(lowerFlapPt,flapPivot);

    //Constructing Coords on Flapradius via Spacing over radians
    double alphastart = atan2((upperFlapPt(1)-flapPivot(1)),(upperFlapPt(0)-flapPivot(0)));
    arma::mat upperFlapRadius(20,2);
    upperFlapRadius.col(0) = arma::linspace(alphastart+1.2,alphastart,20);
    for (int j = 0; j < upperFlapRadius.n_rows; ++j) {
        upperFlapRadius(j,1) = flapPivot(1) + sin(upperFlapRadius(j,0))*r_top;
        upperFlapRadius(j,0) = flapPivot(0) + cos(upperFlapRadius(j,0))*r_top;
    }

    upperFlapCoords = arma::mat(upperFlapRadius.n_rows+tempFlapUpper.n_rows,2);
    upperFlapCoords.head_rows(upperFlapRadius.n_rows) = upperFlapRadius;
    upperFlapCoords.tail_rows(tempFlapUpper.n_rows) = tempFlapUpper;

    alphastart = atan2((lowerFlapPt(1)-flapPivot(1)),(lowerFlapPt(0)-flapPivot(0)));
    arma::mat lowerFlapRadius(20,2); lowerFlapRadius.col(0) = arma::linspace(alphastart-1.2,alphastart,20);
    for (int j = 0; j < lowerFlapRadius.n_rows; ++j) {
        lowerFlapRadius(j,1) = flapPivot(1) + sin(lowerFlapRadius(j,0))*r_bot;
        lowerFlapRadius(j,0) = flapPivot(0) + cos(lowerFlapRadius(j,0))*r_bot;
    }

    lowerFlapCoords = arma::mat(lowerFlapRadius.n_rows+tempFlapLower.n_rows,2);
    lowerFlapCoords.head_rows(lowerFlapRadius.n_rows) = lowerFlapRadius;
    lowerFlapCoords.tail_rows(tempFlapLower.n_rows) = tempFlapLower;

    //Get TurbulatorPositions before Rotation of Flap by Mode
    if (turbTopPt(0)>upperFlapPtDesign(0)){
        turbTopPt(1) = interpolate(upperFlapCoords,turbTopPt(0));
        turbTopOnFlap = true;
    }else{
        turbTopPt(1) = interpolate(upperBaseCoords,turbTopPt(0));
        turbTopOnFlap = false;
    }
    if (turbBotPt(0)>lowerFlapPtDesign(0)){
        turbBotPt(1) = interpolate(lowerFlapCoords,turbBotPt(0));
        turbBotOnFlap = true;
    }else{
        turbBotPt(1) = interpolate(lowerBaseCoords,turbBotPt(0));
        turbBotOnFlap = false;
    }

    if (fk) {

        //calc extracted Flap and Turbulator Position.
        arma::vec aim = upperBaseCoords.row(upperBaseCoords.n_rows-1).t();
        arma::vec delta = aim - upperFlapCoords.row(upperFlapCoords.n_rows-1).t();
        upperFlapCoordsExtracted = upperFlapCoords.each_row() + delta.t();
        lowerFlapCoordsExtracted = lowerFlapCoords.each_row() + delta.t();
        upperFlapCoordsExtracted = rotate(upperFlapCoordsExtracted,aim,-fkFlapAngle);
        lowerFlapCoordsExtracted = rotate(lowerFlapCoordsExtracted,aim,-fkFlapAngle);
        flapPivotExtracted = flapPivot + delta;
        flapPivotExtracted = rotate(flapPivotExtracted,aim,-fkFlapAngle);
        upperFlapPtDesignExtracted = upperFlapPtDesign + delta;
        lowerFlapPtDesignExtracted = lowerFlapPtDesign + delta;
        lowerFlapPtExtracted = lowerFlapPt + delta;
        upperFlapPtExtracted = upperFlapPt + delta;
        upperFlapPtDesignExtracted = rotate(upperFlapPtDesignExtracted,aim,-fkFlapAngle);
        lowerFlapPtDesignExtracted = rotate(lowerFlapPtDesignExtracted,aim,-fkFlapAngle);
        lowerFlapPtExtracted = rotate(lowerFlapPtExtracted,aim,-fkFlapAngle);
        upperFlapPtExtracted = rotate(upperFlapPtExtracted,aim,-fkFlapAngle);

        //Also look for Turbs:
        if(turbTopOnFlap){
            turbTopPtExtracted = turbTopPt + delta;
            turbTopPtExtracted = rotate(turbTopPtExtracted, aim, -fkFlapAngle);
        } else{turbTopPtExtracted = turbTopPt;}

        if(turbBotOnFlap){
            turbBotPtExtracted = turbBotPt + delta;
            turbBotPtExtracted = rotate(turbBotPtExtracted, aim, -fkFlapAngle);
        }else{turbBotPtExtracted = turbBotPt;}

        //Cut BaseCoors on upperside -> upperside FK
        fkCoordsTop = coordsFromX(upperBaseCoords,upperFlapPtDesignExtracted(0)-0.01,true,true);
        fkCoordsTop = coordsFromX(fkCoordsTop,upperFlapPtDesign(0)+0.005,false,true);

        fkThickness = r_top+r_bot;
        fkCoordsBot = upperBaseCoords;
        for (int i = 1; i < fkCoordsBot.n_rows-2; ++i) {

            arma::vec2 deltaOrtho{-(upperBaseCoords(i+1,1)-upperBaseCoords(i-1,1)),upperBaseCoords(i+1,0)-upperBaseCoords(i-1,0)};
            double norm = sqrt(pow(deltaOrtho(0),2)+pow(deltaOrtho(1),2));
            deltaOrtho /= norm;
            arma::vec camb = upperBaseCoords.row(i).t();
            fkCoordsBot.row(i) = (camb-fkThickness*deltaOrtho).t();
        }

        fkCoordsBot = coordsFromX(fkCoordsBot,lowerFlapPtDesignExtracted(0)-0.0225,true,true);
        fkCoordsBot = coordsFromX(fkCoordsBot,lowerFlapPtDesign(0)+0.005,false,true);

        //Calculate Retracted FK
        fkCoordsTopRetracted = arma::mat{0.0};
        fkCoordsBotRetracted = arma::mat{0.0};
    }

    changedBaseCoords(changedN);
    changedN = false;
}

std::tuple<std::vector<arma::mat>,arma::vec, arma::vec> Airfoil::getModeCoords(bool fkExtracted, double eta){

    eta *= M_PI/180;
    //if (fkExtracted != fk){
    //    fk = fkExtracted;
    //    baseCoords();
    //}

    arma::vec flapPivotFinal;
    arma::mat upperFlapCoordsFinal;
    arma::mat lowerFlapCoordsFinal;
    arma::mat coordsFinal;
    arma::mat flosseFinal;
    arma::mat coordsSecondary;
    arma::mat coordsFinalTop;
    arma::mat coordsFinalBot;
    arma::vec turbTopPtFinal;
    arma::vec turbBotPtFinal;
    arma::mat fkCoordsTopFinal;
    arma::mat fkCoordsBotFinal;
    arma::vec lowerFlapCut;
    arma::vec upperFlapCut;

    if (fkExtracted && fk) {
        upperFlapCoordsFinal = upperFlapCoordsExtracted;
        lowerFlapCoordsFinal = lowerFlapCoordsExtracted;
        turbTopPtFinal = turbTopPtExtracted;
        turbBotPtFinal = turbBotPtExtracted;
        flapPivotFinal = flapPivotExtracted;
        lowerFlapCut = lowerFlapPtDesignExtracted-0.01;
        upperFlapCut = upperFlapPtDesignExtracted+0.005;

        //Change Order of upper FkCoords
        arma::mat fkCoordsTopRev = fkCoordsTop;
        for (int i = 0; i < fkCoordsTopRev.n_rows; ++i) {
            fkCoordsTopRev.row(fkCoordsTop.n_rows - 1 - i) = fkCoordsTop.row(i);
        }
        flosseFinal = arma::mat(flosse.n_rows+fkCoordsTopRev.n_rows+fkCoordsBot.n_rows,2);
    
        flosseFinal.head_rows(fkCoordsTopRev.n_rows) = fkCoordsTopRev;
        flosseFinal.submat(fkCoordsTopRev.n_rows, 0, size(flosse)) = flosse;
        flosseFinal.tail_rows(fkCoordsBot.n_rows) = fkCoordsBot;

        fkCoordsTopFinal = fkCoordsTop;
        fkCoordsBotFinal = fkCoordsBot;

    } else{
        upperFlapCoordsFinal = upperFlapCoords;
        lowerFlapCoordsFinal = lowerFlapCoords;
        turbTopPtFinal = turbTopPt;
        turbBotPtFinal = turbBotPt;
        flapPivotFinal = flapPivot;
        lowerFlapCut = lowerFlapPtDesign;
        upperFlapCut = upperFlapPtDesign;
        flosseFinal = flosse;

        if (fk){
            fkCoordsTopFinal = fkCoordsTopRetracted;
            fkCoordsBotFinal = fkCoordsBotRetracted;
        }else{
            fkCoordsTopFinal = arma::mat();
            fkCoordsBotFinal = arma::mat();
        }
    }

    //rotate and scale to new chordlength (xTransitionPosition are one of the few parameters, that XFoil treats as x/chord not x/1)
    if(turbTopOnFlap){
        turbTopPtFinal = rotate(turbTopPtFinal,flapPivotFinal,-eta);
    }
    if (turbBotOnFlap){
        turbBotPtFinal = rotate(turbBotPtFinal,flapPivotFinal,-eta);
    }

    //Rotate Flap adequate
    upperFlapCoordsFinal = rotate(upperFlapCoordsFinal,flapPivotFinal,-eta);
    lowerFlapCoordsFinal = rotate(lowerFlapCoordsFinal,flapPivotFinal,-eta);

    arma::mat upperFlapAtAir;
    upperFlapAtAir = coordsFromX(upperFlapCoordsFinal,upperFlapCut(0), false,true,true);

    arma::mat lowerFlapAtAir;
    lowerFlapAtAir = coordsFromX(lowerFlapCoordsFinal,lowerFlapCut(0),false,true,false);

    coordsFinal = arma::mat(flosseFinal.n_rows + lowerFlapAtAir.n_rows + upperFlapAtAir.n_rows, 2);
    coordsFinal.head_rows(upperFlapAtAir.n_rows) = upperFlapAtAir;
    coordsFinal.submat(upperFlapAtAir.n_rows, 0, size(flosseFinal)) = flosseFinal;
    coordsFinal.tail_rows(lowerFlapAtAir.n_rows) = lowerFlapAtAir;

    if(!turbOn){
        turbTopPtFinal = upperFlapCoordsFinal.row(upperFlapCoordsFinal.n_rows-1).t();
        turbBotPtFinal = lowerFlapCoordsFinal.row(lowerFlapCoordsFinal.n_rows-1).t();
    }

    return std::tuple<std::vector<arma::mat>,arma::vec,arma::vec>{std::vector<arma::mat>{coordsFinal,fkCoordsTopFinal,fkCoordsBotFinal,upperFlapCoordsFinal,
                                  lowerFlapCoordsFinal},turbTopPtFinal,turbBotPtFinal};
}

template <typename T> void Airfoil::setAttribute(attributes kind, T value, bool recalc){
    
    switch(kind){
        case setYPlus: yPlus = value; break;
        case setYMinus: yMinus = value; break;
        case setNoseY: noseY = value; break;
        case setFlapYAbsolute: flapPivot(1) = value;flapByRel=false; break;
        case setFlapYRelative: flapRelY = value;flapByRel = true; break;
        case setTurbTop: turbTopPt(0) = value; break;
        case setTurbBot: turbBotPt(0) = value; break;
        case setTurbOn: turbOn = value; break;

        case setFlapX: 
            flapPivot(0) = value;
            setClassShapes();
            break;

        case setFkChordFactor:
            setClassShapes();
            fkChordfactor = value;
            break;

        case setFk:
            fk=value;
            setClassShapes();
            break;
    }
        if(recalc){baseCoords();}
}

template void Airfoil::setAttribute<double>(attributes kind, double value, bool recalc);
template void Airfoil::setAttribute<bool>(attributes kind, bool value, bool recalc);
template void Airfoil::setAttribute<int>(attributes kind, int value, bool recalc);
