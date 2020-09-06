
#include "BernsteinShape.h"
#include "SplineFunctions.h"

long double binom(long double n,long double k) {
    if(k >  n)
        throw "Error";
    if(k == 0)
        return 1;
    if(k > n/2)
        return binom(n,n-k);
    return n * binom(n-1,k-1) / k;
}

BernsteinShape::BernsteinShape(arma::vec coefficients):coefficients(coefficients){
}

void BernsteinShape::calcShape() {

    shape = arma::ones(spacing.n_elem);
    shape = distributions[0];

    for (int i = 1; i < unitDistributions.size(); ++i) {
       shape += distributions[i];
    }
}

arma::vec BernsteinShape::getShape(){
    return shape;
}

arma::vec BernsteinShape::getXs(){
    return xs;
}

void BernsteinShape::setCoefficients(arma::vec& newCoefficients){

    int len = coefficients.size();
    coefficients = newCoefficients;
    if (len != coefficients.size()){setUnitDistribution();} //Recalc unitDists then

    distributions = unitDistributions; 
    for (int i = 0; i < unitDistributions.size(); ++i) {
       distributions[i] *= coefficients[i];
    }
    calcShape();
}

void BernsteinShape::setSpacing(arma::vec spacing){

    this->spacing = spacing;
    setUnitDistribution();
    setCoefficients(coefficients);
    onChangeFromAirfoil();
    calcShape();
}

void BernsteinShape::setUnitDistribution(){

    long double k_i;
    unitDistributions.resize(coefficients.n_elem);
    xs = arma::zeros(coefficients.n_elem);

    arma::vec spacingNormed = spacing/spacing.back();

    for (int i = 0; i < coefficients.n_elem; ++i) {
        k_i = binom(coefficients.n_elem-1, i);
        xs[i] = ((double)i)/(coefficients.n_elem-1)*spacing.back();
        unitDistributions[i] = k_i * pow(spacingNormed, i) % pow(1 - spacingNormed, coefficients.n_elem-1 - i);
    }
}

//arma::vec BernsteinShape::getInfluence(arma::vec& spacing, arma::vec& influenceCoefficients){
//
//    arma::vec tempCoefs = coefficients;
//    setCoefficients(influenceCoefficients);
//    arma::vec influence = getShape(spacing);
//    setCoefficients(tempCoefs);
//    
//    return influence;
//}


