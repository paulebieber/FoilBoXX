//
// Created by paul on 3/20/20.
//

#include "SplineFunctions.h"
#include "armadillo"
#include "iostream"

bool testDist(){

    arma::vec vec1({0.0,0.0});
    arma::vec vec2({0.0,0.1});

    if (distanceBetweenPoints(vec1,vec2) == 1.0){
        return true;
    }else{
        return false;
    }
}

bool testRotate(){

    arma::mat mat({{0.0,0.0},{0.0,1.0}});
    arma::vec vec({0.0,1.0});

    arma::mat rotated = rotate(mat,vec,M_PI/2);
    arma::mat shouldBe({{1.0,1.0},{0.0,1.0}});

    std::cout << rotated << "rotated by 90°, should be:\n" << shouldBe << std::endl;

    double diff = arma::accu(abs(rotated-shouldBe));

    if (diff == 0){
        return true;
    }else{
        return false;
    }
}

int main(){

    arma::mat coords = {{0.0,1.0},{1.0,0.0}};
    arma::vec pt = {0.5,0.0};

    arma::vec ptOnCoords = closestPointToPoint(coords,pt);

    std::cout << ptOnCoords << std::endl;

    testDist();
    testRotate();
}
