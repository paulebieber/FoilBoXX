//
// Created by paul on 11.10.19.
//

#include "NoseBezier.h"

NoseBezier::NoseBezier(arma::vec noseTension, arma::mat noseControlPts):
   noseTension(noseTension), noseControlPts(noseControlPts){}

arma::mat NoseBezier::calc(arma::vec upperPoint,arma::vec lowerPoint,double upperGradient, double lowerGradient, int nNose){

    //Append tensionCtrlPoints and first Points of upper/lowerCoords to CtrlPts
    finalNoseControlPoints = arma::mat(noseControlPts.n_rows+4,2);
    finalNoseControlPoints.row(0) = upperPoint.t();
    finalNoseControlPoints.row(1) = arma::vec({upperPoint(0)+cos(upperGradient)*noseTension(0),
                                               upperPoint(1)+sin(upperGradient)*noseTension(0)}).t();
    finalNoseControlPoints.submat(2,0,size(noseControlPts)) = noseControlPts;
    finalNoseControlPoints.row(finalNoseControlPoints.n_rows-2) = arma::vec({lowerPoint(0)+cos(lowerGradient)*noseTension(1),
                                                                             lowerPoint(1)+sin(lowerGradient)*noseTension(1)}).t();
    finalNoseControlPoints.row(finalNoseControlPoints.n_rows-1) = lowerPoint.t();

    //Create Curve
    arma::mat nosePts = bezier(nNose,finalNoseControlPoints);

    //Delete first and last point of NoseCurve (is managed by coordsFromX)
    return nosePts.rows(1,nosePts.n_rows-2);
}

/*void NoseBezier::plot(){

    QVector<QCPCurveData> graphData(finalNoseControlPoints.rows());

    for (int i = 0; i < finalNoseControlPoints.rows(); ++i) {
        graphData[i] = QCPCurveData(i, finalNoseControlPoints(i, 0), finalNoseControlPoints(i, 1));
    }

    graph->data()->set(graphData, true);
}*/