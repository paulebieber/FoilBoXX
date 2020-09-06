//
// Created by paul on 11.06.19.
//

#pragma once

#include "armadillo"

arma::mat rotate(const arma::mat& toRotate, const arma::vec& pt, const double& angle);

double interpolate(const arma::mat& array, const double x, const bool der=false, const bool linear = false);

arma::vec closestPointToPoint(const arma::mat& arrayCurve, const arma::vec& pt);

double searchEtaDesign(const arma::mat& coordsToFit, const arma::vec& aim, const double aimDer, const arma::vec& flapPivot, const arma::vec& neutralPt);

double distanceBetweenPoints(const arma::vec& p1,const arma::vec& p2);

arma::vec intersect(const arma::mat& coords1,const arma::vec& pt, const double dist);

arma::mat bezier(int n, arma::mat controlPoints);

arma::mat coordsFromX(const arma::mat& coords, const double x, const bool upTo = false,
        const bool includesX = false ,const bool reversed=false, double border = 0.006);
