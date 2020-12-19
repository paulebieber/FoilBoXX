
#pragma once

#include "ShapeFunction.h"

class BernsteinShape: public ShapeFunction{
    /* Internally supersamples the UnitDistributions (for a Bernstein-Binom) once for a certain Amount of Coefficients
     * When Coefficients are set, the ShapeSum corresponding to the CoefficientsValues is created from the UnitDists.
     * If Shape for a specific x-Distribution is requested (getShape), they get Interpolated from the high resolution
     * ones calced on setCoefficients.
     */

    void setUnitDistribution();
    void calcShape();
    
protected:
    arma::vec spacing; //Resulting X-Positions for coefficients, so that spacing of these is linear from 0 to 1.
    arma::vec coefficients;
    std::vector<arma::vec> unitDistributions; //Unit Distributions (before weighting). Sum would be constant 1.
    std::vector<arma::vec> distributions; //Weighted Distributions after call to calcShape
    arma::vec shape;
    arma::vec xs; //Resulting X-Positions for coefficients, so that spacing of these is linear from 0 to 1.
    virtual void onChangeFromAirfoil() = 0;
    void setSide(sideType side){this->side = side;}

public:
    BernsteinShape(arma::vec coefficients = arma::vec({1,1,1,1,1,1,1,1,1,1,1,1}));
    virtual ~BernsteinShape(){};

    void setCoefficients(arma::vec& newCoefficients);
    arma::vec& getCoefficients();
    void setSpacing(arma::vec spacing);
    int getN(){return coefficients.n_rows;}
    int getSpacingLen(){return spacing.size();}

    arma::vec getInfluence(arma::vec& spacing, arma::vec& influenceCoefficients);
    arma::vec getShape();
    arma::vec getXs();
};
