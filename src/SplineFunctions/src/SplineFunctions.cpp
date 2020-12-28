//
// Created by paul on 17.06.19.
//

#include "SplineFunctions.h"
#include "dlib/optimization.h"
#include <tuple>

// For Optimization of PointToSpline

struct optimizationData{
    const arma::mat& coords;
    const arma::vec& pt;
    bool debug = false;
    optimizationData(const arma::mat& coords,const arma::vec& pt, bool debug = false):
    coords(coords), pt(pt), debug(debug){}
};

struct calcDistanceFromPointToSpline{

    const optimizationData& data;
    explicit calcDistanceFromPointToSpline(const optimizationData& data):data(data){};
    const double operator()(const dlib::matrix<double,0,1>& x) const;
};

struct calcDistanceFromPointToSplineDer{

    const optimizationData& data;
    explicit calcDistanceFromPointToSplineDer(const optimizationData& data):data(data){};
    const dlib::matrix<double,0,1> operator()(const dlib::matrix<double,0,1>& x) const;
};

const double calcDistanceFromPointToSpline::operator()(const dlib::matrix<double, 0, 1>& x) const {

    arma::vec ptInter = {x,interpolate(data.coords,x)};
    if(data.debug){
        std::cout << "At: " << ptInter << std::endl;
    }
    return distanceBetweenPoints(data.pt,ptInter);
}

const dlib::matrix<double,0,1> calcDistanceFromPointToSplineDer::operator()(const dlib::matrix<double, 0, 1>& x) const {

    double delta = 0.02;
    arma::vec pt = {x-delta,interpolate(data.coords,x-delta)};
    arma::vec pt2 = {x+delta,interpolate(data.coords,x+delta)};
    dlib::matrix<double,0,1> result = {(distanceBetweenPoints(pt2,data.pt)-distanceBetweenPoints(pt,data.pt))/(delta*2)};
    if(data.debug){
        std::cout << "grad:" << result << std::endl;
    }
    return result;
}

struct optimizationDataIntersect{
    const arma::mat& coords1;
    const arma::vec& pt;
    const double dist;
    bool debug = false;
    optimizationDataIntersect(const arma::mat& coords1,const arma::vec& pt, const double dist, bool debug = false):
    coords1(coords1), pt(pt), dist(dist), debug(debug){}
};

struct calcIntersect{

    const optimizationDataIntersect& data;
    explicit calcIntersect(const optimizationDataIntersect& data):data(data){};
    const double operator()(const dlib::matrix<double,0,1>& x) const;
};

struct calcIntersectDer{

    const optimizationDataIntersect& data;
    const calcIntersect& funcIntersect;
    explicit calcIntersectDer(const optimizationDataIntersect& data, const calcIntersect& funcIntersect):funcIntersect(funcIntersect),data(data){};
    const dlib::matrix<double,0,1> operator()(const dlib::matrix<double,0,1>& x) const;
};

const double calcIntersect::operator()(const dlib::matrix<double, 0, 1>& x) const {

    arma::vec ptOnCurve{x,interpolate(data.coords1,x)};

    return std::abs(distanceBetweenPoints(ptOnCurve,data.pt)-data.dist);
}

const dlib::matrix<double,0,1> calcIntersectDer::operator()(const dlib::matrix<double, 0, 1>& x) const {

    double delta = 0.005;
    double dist1 = funcIntersect(x-delta);
    double dist2 = funcIntersect(x+delta);
    dlib::matrix<double,0,1> result = {(dist2-dist1)/(delta*2)};
    if(data.debug){
        std::cout << "grad:" << result << std::endl;
    }
    return result;
}

struct optimizationDataEta{
    const arma::mat& coordsToFit;
    const arma::vec& aim;
    const arma::vec& flapPivot;
    const arma::vec& neutralPt;
    const double aimDer;
    bool debug = false;

    optimizationDataEta(const arma::mat& coordsToFit, const arma::vec& aim, const double aimDer,
            const arma::vec& flapPivot, const arma::vec& neutralPt, bool debug = false):
        coordsToFit(coordsToFit), aim(aim), aimDer(aimDer), flapPivot(flapPivot), neutralPt(neutralPt), debug(debug){}
};

struct calcEtaDesign{

    const optimizationDataEta& data;
    explicit calcEtaDesign(const optimizationDataEta& data):data(data){};
    const double operator()(const dlib::matrix<double,0,1>& x) const;
};

struct calcEtaDesignDer{

    const optimizationDataEta& data;
    const calcEtaDesign& funcEta;
    explicit calcEtaDesignDer(const optimizationDataEta& data, const calcEtaDesign& funcEta):data(data),funcEta(funcEta){};
    const dlib::matrix<double,0,1> operator()(const dlib::matrix<double,0,1>& x) const;
};

const double calcEtaDesign::operator()(const dlib::matrix<double, 0, 1>& eta) const {

    arma::vec etaPt = rotate(data.neutralPt,data.flapPivot,-eta);
    arma::mat movedCoordsToFit = data.coordsToFit;
    arma::vec add = etaPt - data.coordsToFit.row(data.coordsToFit.n_rows-1).t();
    for(int i=0; i<movedCoordsToFit.n_rows;i++){
        movedCoordsToFit.row(i) += add.t();
    }

    arma::vec radiusOnCoordsToTilt = intersect(movedCoordsToFit,etaPt,distanceBetweenPoints(etaPt,data.aim));
    double toTilt = -(atan2(data.aim(1)-etaPt(1), etaPt(0)-data.aim(0)) - atan2(radiusOnCoordsToTilt(1)-etaPt(1), etaPt(0)-radiusOnCoordsToTilt(0)));

    movedCoordsToFit = rotate(movedCoordsToFit,etaPt,toTilt);
    double der1 = interpolate(movedCoordsToFit,data.aim(0),true);
    double stayingEta = std::abs(der1-data.aimDer);

    //std::cout << stayingEta << " for: " << eta << der1 << data.aimDer << std::endl;

    return stayingEta;
}

const dlib::matrix<double,0,1> calcEtaDesignDer::operator()(const dlib::matrix<double, 0, 1>& eta) const {

    double delta = M_PI/200;
    double stayingeta1 = funcEta(eta-delta);
    double stayingeta2 = funcEta(eta+delta);
    dlib::matrix<double,0,1> result = {(stayingeta2-stayingeta1)/(delta*2)};
    if(data.debug){
        std::cout << "grad:" << result << std::endl;
    }
    return result;
}

arma::mat bezier(int n, arma::mat controlPoints){

    arma::mat bezier(n,2);
    arma::vec spacing = arma::linspace(0,1,n);
    arma::mat vec;

    for (int i = 0; i < spacing.n_rows; ++i) {
        vec = controlPoints;
        for (int j = controlPoints.n_rows-1; j > 0; --j) {
            for (int k = 0; k < j; ++k) {
                vec.row(k) = vec.row(k)+spacing(i)*(vec.row((k+1))-vec.row(k));
            }
        }
        bezier.row(i) = vec.row(0);
    }
    return bezier;
}

arma::mat rotate(const arma::mat& toRotate, const arma::vec& pt, const double& angle){
    // Rotates Array by angle rad in mathematically positive direction

    arma::mat rMatrix = {{cos(angle), -sin(angle)},
                         {sin(angle), cos(angle)}};

    arma::mat rotated = toRotate;
    if (toRotate.n_cols > 1){ //(Multiple Pts) first col: x, second y
        rotated.each_row() -= pt.t(); // Rotate relative to Pt
        rotated = (rMatrix * rotated.t()).t();
        rotated.each_row() += pt.t();
    }else{ //first row: x, second y
        rotated -= pt;
        rotated = (rMatrix * rotated);
        rotated += pt;
    }
    return rotated;
}

double interpolate(const arma::mat& array, const double x, const bool der, const bool linear){

    int n = array.n_rows;
    if(array(array.n_rows-1,0) <= x){return array(n-1,1)+((x-array(n-1,0))/(array(n-1,0)-array(n-2,0)))*(array(n-1,1)-array(n-2,1));}
    if(array(0,0) >= x){return array(0,1)+((x-array(0,0))/(array(1,0)-array(0,0)))*(array(1,1)-array(0,1));}

    for (int i = 1; i < array.n_rows; ++i) {
        if ((array(i,0) > x) && (i>0)){

            double x0;
            double y0;
            if(i < 2){x0 = array(i-1,0)-(array(i,0)-array(i-1,0));y0=array(i-1,0);}
            else{x0 = array(i-2,0);y0 = array(i-2,1);}
            double x1 = array(i-1,0);
            double x2 = array(i,0);
            double y1 = array(i-1,1);
            double y2 = array(i,1);

            if(!der){
                if(linear){return array(i-1,1)+((x-array(i-1,0))/(array(i,0)-array(i-1,0)))*(array(i,1)-array(i-1,1));}
                else{return y0*(x-x1)*(x-x2)/((x0-x1)*(x0-x2))+y1*(x-x0)*(x-x2)/((x1-x0)*(x1-x2))+y2*(x-x0)*(x-x1)/((x2-x0)*(x2-x1));} 
            }else{
                if(linear){return (array(i,1)-array(i-1,1))/std::abs(array(i,0)-array(i-1,0));
                }else{return y0*(2*x0-x1-x2)/((x0-x1)*(x0-x2))+y1*(x0-x2)/((x1-x0)*(x1-x2))+y2*(x0-x1)/((x2-x0)*(x2-x1));}
            }
        }
    }
    return -1;
}

arma::mat coordsFromX(const arma::mat& coords,const double x,const bool upTo,const bool includesX,const bool reversed, double border){

    arma::mat array;
    if(x > coords(coords.n_rows-1,0)){
       array = coords;
    }else{

        int index;
        for (index = 0; index < coords.n_rows-1; ++index) {
            if (coords(index+1,0)>=x){break;}
        }

        if (upTo){array = coords.head_rows(index+1);}
        else {array =  coords.tail_rows(coords.n_rows - (index+1));}

        // Find interpolated Value at x
        if (includesX){
            //SplineFunction spline(coords.col(0),coords.col(1));
            arma::mat inter{x,interpolate(coords,x)};

            arma::mat array2;
            if (upTo){
                // Check if interpolated Point is to close to next regular one.
                if (x-array(array.n_rows-1,0) > border){
                    array2 = arma::mat(array.n_rows+1,2);
                } else{
                    array2 = array;
                }
                array2.head_rows(array.n_rows)=array;
                array2.row(array2.n_rows-1) = inter;
            }
            else {
                if (array(0,0) - x > border){
                    array2 = arma::mat(array.n_rows+1,2);
                } else{
                    array2 = array;
                }
                array2.tail_rows(array.n_rows) = array;
                array2.row(0) = inter;
            }
            array = array2;
        }
    }

    if (reversed){
        arma::mat array_temp = array;
        for (int i = 0; i < array.n_rows; ++i) {
            array.row(i) = array_temp.row(array_temp.n_rows-1-i);
        }
    }
    return array;
}

double distanceBetweenPoints(const arma::vec& p1, const arma::vec& p2){
    return sqrt(pow(p1(0)-p2(0),2)+pow(p1(1)-p2(1),2));
}

arma::vec closestPointToPoint(const arma::mat& arrayCurve, const arma::vec& pt,
        const double lowerBound, const double upperBound){

    dlib::matrix<double,0,1> start = {pt(0)};
    dlib::matrix<double,0,1> lb = {lowerBound};
    dlib::matrix<double,0,1> ub = {upperBound};

    optimizationData data(arrayCurve,pt,false);
    calcDistanceFromPointToSpline ptp(data);
    calcDistanceFromPointToSplineDer ptpDer(data);

    dlib::find_min_box_constrained(dlib::bfgs_search_strategy(),
            dlib::objective_delta_stop_strategy(1e-5),
            ptp,ptpDer,start,lb,ub);

    arma::vec result = {start,interpolate(arrayCurve,start)};
    return result;
}

arma::vec intersect(const arma::mat& coords1, const arma::vec& pt, const double dist){

    dlib::matrix<double,0,1> start = {coords1(floor(coords1.n_rows/2),0)};
    arma::vec bounds{coords1(0,0),coords1(coords1.n_rows-1,0)};

    dlib::matrix<double,0,1> lb = {min(bounds)};
    dlib::matrix<double,0,1> ub = {max(bounds)};

    optimizationDataIntersect data(coords1,pt,dist,false);
    calcIntersect inter(data);
    calcIntersectDer interDer(data, inter);

    dlib::find_min_box_constrained(dlib::bfgs_search_strategy(),
            dlib::objective_delta_stop_strategy(1e-5),
            inter,interDer,start,lb,ub);

    arma::vec result = {start,interpolate(coords1,start)};
    return result;
}

double searchEtaDesign(const arma::mat& coordsToFit, const arma::vec& aim, const double aimDer, const arma::vec& flapPivot, const arma::vec& neutralPt){

    dlib::matrix<double,0,1> start = {0.0};
    dlib::matrix<double,0,1> lb = {-M_PI/2};
    dlib::matrix<double,0,1> ub = {M_PI/2};

    optimizationDataEta data(coordsToFit,aim,aimDer,flapPivot,neutralPt,false);
    calcEtaDesign eta(data);
    calcEtaDesignDer etaDesign(data,eta);

    dlib::find_min_box_constrained(dlib::bfgs_search_strategy(),
            dlib::objective_delta_stop_strategy(1e-8),
            eta,etaDesign,start,lb,ub);

    return start;
}
