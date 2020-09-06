
#pragma once

#include "armadillo"

class ShapeFunction{

public: enum sideType{top,bottom};
protected:
    //arma::mat shape;
    sideType side;    

public:
    ShapeFunction(sideType side = top);
    virtual ~ShapeFunction(){};
    virtual arma::vec getShape()=0;
    virtual void setSpacing(arma::vec spacing)=0;
    sideType getSide(){return side;}
};
