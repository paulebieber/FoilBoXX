//
// Created by paul on 11.10.19.
//

#ifndef FOILBOXX_NOSEBEZIER_H
#define FOILBOXX_NOSEBEZIER_H

#include "SplineFunctions.h"

class NoseBezier{

    arma::mat coefficients;
    arma::vec noseTension;
    arma::mat noseControlPts;
    arma::mat finalNoseControlPoints;

public:
    NoseBezier(arma::vec noseTension, arma::mat noseControlPts);
    arma::mat calc(arma::vec upperPoint,arma::vec lowerPoint,double upperGradient, double lowerGradient, int nNose);
    void setPts(arma::mat pts){noseControlPts = pts;};
    void setTensions(arma::vec tensions){noseTension = tensions;};
    arma::mat getPts(){return noseControlPts;}
    arma::vec getTensions(){return noseTension;}

};


#endif //FOILBOXX_NOSEBEZIER_H
