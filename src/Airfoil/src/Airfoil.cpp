//
// Created by paul on 24.05.19.
//

#include "Airfoil.h"
#include <iostream>
#include <math.h>
#include "SplineFunctions.h"

Airfoil::Airfoil():
    teThickness(0.003),flapRelY(0.5),flapByRel(true),flapPivot({0.8,0.0}),
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

    double noseEnd = 0.075;
    double nNose = 30;

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


   //upperClassCoords.col(0) = spacingUpper;
   lowerClassCoords.col(0) = spacingLower;
   //upperClassCoords.col(1) = 0.15*pow(spacingUpper/spacingUpper.back(), 0.5) % pow(1 - spacingUpper/spacingUpper.back(), 1);
   lowerClassCoords.col(1) = -0.15*pow(spacingLower, 0.5) % pow(1 - spacingLower, 1);

   upperClassCoords.resize(104,2);
    upperClassCoords.col(0) = arma::vec({
    1.000000    ,0.9940243    ,0.9857492    ,0.9761414    ,0.9656401    ,0.9546508    ,0.9434188    ,0.9320672,
    0.9206407    ,0.9091484    ,0.8975930    ,0.8859753    ,0.8742968    ,0.8625589    ,0.8507648    ,0.8389210,
    0.8270424    ,0.8151616    ,0.8033039    ,0.7915091    ,0.7797600    ,0.7680378    ,0.7563398    ,0.7446640,
    0.7330079    ,0.7213690    ,0.7097450    ,0.6981336    ,0.6865327    ,0.6749402    ,0.6633544    ,0.6517737,
    0.6401965    ,0.6286210    ,0.6170452    ,0.6054664    ,0.5938856    ,0.5823019    ,0.5707136    ,0.5591189,
    0.5475175    ,0.5359112    ,0.5243008    ,0.5126869    ,0.5010695    ,0.4894481    ,0.4778216    ,0.4661894,
    0.4545522    ,0.4429125    ,0.4312744    ,0.4196416    ,0.4080139    ,0.3963916    ,0.3847756    ,0.3731679,
    0.3615693    ,0.3499814    ,0.3384041    ,0.3268417    ,0.3152952    ,0.3037647    ,0.2922537    ,0.2807703,
    0.2693186    ,0.2579031    ,0.2465269    ,0.2351973    ,0.2239178    ,0.2126953    ,0.2015333    ,0.1904359,
    0.1794086    ,0.1684581    ,0.1575924    ,0.1468225    ,0.1361612    ,0.1256263    ,0.1152371    ,0.1050206,
    0.9500378e-01,0.8522424e-01,0.7572213e-01,0.6655010e-01,0.5778619e-01,0.4950319e-01,0.4179914e-01,0.3477745e-01,0.2854004e-01,0.2315028e-01,0.1860558e-01,0.1483854e-01,0.1174465e-01,0.9211676e-02,0.7137630e-02,0.5437760e-02,0.4045121e-02,0.2908437e-02,0.1989393e-02,0.1260366e-02,0.7029449e-03,0.3072560e-03,0.7097791e-04,0.0
    });

    upperClassCoords.col(1) = arma::vec({
    0.0,0.1053001e-02,0.2512185e-02,0.4309973e-02,0.6376210e-02,0.8651093e-02,0.1108631e-01,0.1365198e-01,0.1633383e-01,0.1912009e-01,0.2199861e-01,0.2495728e-01,0.2798414e-01,0.3106740e-01,0.3419522e-01,0.3735526e-01,0.4053369e-01,0.4371183e-01,0.4687665e-01,0.5001025e-01,0.5309608e-01,0.5613638e-01,0.5912699e-01,0.6206308e-01,0.6494002e-01,0.6775352e-01,0.7049955e-01,0.7317435e-01,0.7577440e-01,0.7829640e-01,0.8073727e-01,0.8309412e-01,0.8536425e-01,0.8754523e-01,0.8963482e-01,0.9163186e-01,0.9353444e-01,0.9534068e-01,0.9704916e-01,0.9865907e-01,0.1001699,
    0.1015805    ,0.1028896    ,0.1040960    ,0.1051988    ,0.1061970    ,0.1070900    ,0.1078778    ,0.1085604,
    0.1091376    ,0.1096087    ,0.1099722    ,0.1102265    ,0.1103707    ,0.1104041    ,0.1103258    ,0.1101345,
    0.1098291    ,0.1094090    ,0.1088734    ,0.1082204    ,0.1074492    ,0.1065596    ,0.1055503    ,0.1044191,
    0.1031632    ,0.1017806    ,0.1002686,
    0.9862399e-01,0.9684342e-01,0.9492268e-01,0.9285831e-01,0.9064668e-01,0.8828431e-01,0.8576802e-01,0.8309450e-01,0.8026104e-01,0.7726471e-01,0.7410305e-01,0.7077412e-01,0.6727551e-01,0.6360816e-01,0.5977315e-01,0.5578112e-01,0.5165186e-01,0.4740930e-01,0.4310422e-01,0.3881116e-01,0.3463082e-01,0.3066503e-01,0.2698813e-01,0.2363200e-01,0.2059287e-01,0.1784551e-01,0.1535549e-01,0.1308716e-01,0.1100767e-01,0.9088456e-02,0.7305452e-02,0.5638742e-02,0.4072025e-02,0.2592653e-02,0.1192190e-02,0.0
    });

    arma::mat upper_temp = upperClassCoords;
    for (int i = 0; i < upper_temp.n_rows; ++i) {
        upperClassCoords.row(i) = upper_temp.row(upper_temp.n_rows-1-i);
    }

    if(fk){upperClassCoords.col(0)*=fkChordfactor;}

    lowerClassCoords.resize(98,2);
    lowerClassCoords.col(0) = arma::vec({
    0.0,0.1041073e-05,0.1360191e-03,0.5993723e-03,0.1465355e-02,0.2632078e-02,0.4033761e-02,0.5662171e-02,0.7538298e-02,0.9705189e-02,0.1222886e-01,0.1520384e-01,0.1876248e-01,0.2308296e-01,0.2838556e-01,0.3489391e-01,0.4273237e-01,0.5184584e-01,0.6197246e-01,0.7277978e-01,0.8401714e-01,0.9552479e-01,0.1072059,
    0.1190026    ,0.1308796    ,0.1428158    ,0.1547961    ,0.1668118    ,0.1788565    ,0.1909266    ,0.2030194,
    0.2151325    ,0.2272639    ,0.2394120    ,0.2515749    ,0.2637506    ,0.2759378    ,0.2881351    ,0.3003416,
    0.3125565    ,0.3247790    ,0.3370085    ,0.3492443    ,0.3614859    ,0.3737327    ,0.3859838    ,0.3982381,
    0.4104949    ,0.4227532    ,0.4350119    ,0.4472706    ,0.4595289    ,0.4717861    ,0.4840422    ,0.4962973,
    0.5085519    ,0.5208060    ,0.5330601    ,0.5453145    ,0.5575697    ,0.5698258    ,0.5820826    ,0.5943400,
    0.6065974    ,0.6188544    ,0.6311100    ,0.6433630    ,0.6556123    ,0.6678570    ,0.6800959    ,0.6923278,
    0.7045517    ,0.7167670    ,0.7289727    ,0.7411683    ,0.7533535    ,0.7655269    ,0.7776907    ,0.7898397,
    0.8019722    ,0.8140847    ,0.8261695    ,0.8382173    ,0.8502147    ,0.8621456    ,0.8739917    ,0.8857351,
    0.8973615    ,0.9088642    ,0.9202475    ,0.9315272    ,0.9427280    ,0.9538623    ,0.9648831    ,0.9755798,
    0.9854769    ,0.9939787,
    1.000000});

    lowerClassCoords.col(1) = arma::vec({
    0.0,-0.1367783e-03, -0.1445027e-02, -0.2725971e-02, -0.3868662e-02, -0.4872813e-02, -0.5788734e-02, -0.6653433e-02,
    -0.7493647e-02, -0.8329657e-02, -0.9179293e-02, -0.1006002e-01, -0.1098938e-01, -0.1198475e-01, -0.1306017e-01,
    -0.1422083e-01, -0.1544091e-01, -0.1667266e-01, -0.1787380e-01, -0.1900244e-01, -0.2004289e-01, -0.2099498e-01,
    -0.2186661e-01, -0.2266481e-01, -0.2339692e-01, -0.2406888e-01, -0.2468572e-01, -0.2525161e-01, -0.2577010e-01,
    -0.2624451e-01, -0.2667789e-01, -0.2707313e-01, -0.2743280e-01, -0.2775932e-01, -0.2805492e-01, -0.2832148e-01,
    -0.2856068e-01, -0.2877401e-01, -0.2896282e-01, -0.2912837e-01, -0.2927181e-01, -0.2939421e-01, -0.2949658e-01,
    -0.2957977e-01, -0.2964466e-01, -0.2969202e-01, -0.2972236e-01, -0.2973613e-01, -0.2973368e-01, -0.2971510e-01,
    -0.2968036e-01, -0.2962944e-01, -0.2956226e-01, -0.2947854e-01, -0.2937812e-01, -0.2926091e-01, -0.2912685e-01,
    -0.2897591e-01, -0.2880815e-01, -0.2862367e-01, -0.2842271e-01, -0.2820546e-01, -0.2797211e-01, -0.2772276e-01,
    -0.2745749e-01, -0.2717631e-01, -0.2687900e-01, -0.2656514e-01, -0.2623414e-01, -0.2588538e-01, -0.2551793e-01,
    -0.2513074e-01, -0.2472263e-01, -0.2429233e-01, -0.2383842e-01, -0.2335948e-01, -0.2285414e-01, -0.2232057e-01,
    -0.2175826e-01, -0.2116465e-01, -0.2053800e-01, -0.1987590e-01, -0.1917486e-01, -0.1843013e-01, -0.1763522e-01,
    -0.1678120e-01, -0.1585662e-01, -0.1484758e-01, -0.1373799e-01, -0.1251094e-01, -0.1115027e-01, -0.9643951e-02,
    -0.7990634e-02, -0.6212426e-02, -0.4377994e-02, -0.2619650e-02, -0.1088854e-02,
    0.0
    });

    changeShapeSpacings();
    changedN = true;
}

void Airfoil::baseCoords() {

    upperBaseCoords = upperClassCoords;
    lowerBaseCoords = lowerClassCoords;

    //Multiply all Shapefunctions to BaseShape
    arma::vec topMulti = arma::zeros(upperBaseCoords.n_rows);
    arma::vec botMulti = arma::zeros(lowerBaseCoords.n_rows);

    for(ShapeFunction* shape: shapes){
        if(shape->getSide() == ShapeFunction::top){
            topMulti += shape->getShape();
        }else{
            botMulti += shape->getShape();
        }
    }
    upperBaseCoords.col(1) = upperBaseCoords.col(1) % topMulti;
    lowerBaseCoords.col(1) = lowerBaseCoords.col(1) % botMulti;

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

    // Calculation of FlapPivot depending on flapRelY, and bool flapByRel
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
        std::cout << etaDesignUpper << std::endl;
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
    arma::mat upperBaseCoordsRevCut = upperBaseCoords.submat(1,0,upperBaseCoords.n_rows-1,1);
    upperBaseCoordsRev = coordsFromX(upperBaseCoordsRev,upperFlapPt(0)-0.01,true,true);
    if(fk){upperBaseCoordsRevCut = coordsFromX(upperBaseCoordsRevCut,1.0,true,true);}
    arma::mat tempInverse = upperBaseCoordsRev;
    arma::mat tempInverseCut = upperBaseCoordsRevCut;

    for (int i = 0; i < tempInverse.n_rows; ++i) {
        upperBaseCoordsRev.row(tempInverse.n_rows - 1 - i) = tempInverse.row(i);
    }
    for (int i = 0; i < tempInverseCut.n_rows; ++i) {
        upperBaseCoordsRevCut.row(tempInverseCut.n_rows - 1 - i) = tempInverseCut.row(i);
    }

    flosse = arma::join_cols(upperBaseCoordsRev, coordsFromX(lowerBaseCoords,lowerFlapPt(0)-0.01,true,true));

    //Cut at 1 for correct thickness calc in Xfoil (just thickness calc)
    flosseCut = arma::join_cols(upperBaseCoordsRevCut, coordsFromX(lowerBaseCoords,1.0,true,true));

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

    std::cout << "flapPivot_fk" << fkExtracted << flapPivotFinal << std::endl;

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
