
#include "Optimization.h"
#include "dlib/optimization/optimization.h"
#include "dlib/optimization/optimization_bobyqa.h"
#include <iostream>
#include <ostream>
#include <qnamespace.h>

OptimizationThread::OptimizationThread():runOptimization(false){
}

const double OptimizationThread::fitness(const dlib::matrix<double>& coefs){

    double fitness = 0;

    if(!runOptimization){
        return 0;
    }

    try{

        std::cout << "Iteration \n" << "=============" << std::endl;
        int n = 0;
        for(FoilMode* mode : modes){
            std::cout << "Setting eta " << coefs(n) << std::endl;
            mode->setEta(coefs(n)*10,false);
            n++;
        }

        //YPlus
        airfoil->setAttribute(Airfoil::setYPlus,coefs(coefs.nr()-1)/10,false);

        //YMinus
        airfoil->setAttribute(Airfoil::setYMinus,coefs(coefs.nr()-2)/10,false);

        //TurbBot
        //airfoil->setAttribute(Airfoil::setTurbBot,coefs(coefs.nr()-3),false);

        for(int j=0; j<shapes.size();j++){
            arma::vec shapeCoefs(shapes[j]->getN());
            for(int i=0; i< shapes[j]->getN(); i++){
                shapeCoefs(i) = coefs(i+n);
            }
            n+=shapes[j]->getN();
            shapes[j]->setCoefficients(shapeCoefs,shapes.size()==(j+1));
            //shapes[j]->setCoefficients(shapeCoefs,false);
        }

        //Wait for polars to calc
        for(int i = 0; i< polars.size();i++){
            polars[i]->thread->wait(7*1000); //Wait 7 secs
        }

        for(int i = 0; i< polarGoals.size();i++){
            if(polarGoals[i]->getPolar()->getSuccess() &&
                    polarGoals[i]->getPolar()->getBorderTight()){
                double add = polarGoals[i]->getArea();
                fitness += add;
                std::cout << " Goal mode: " << polarGoals[i]->getMode() << "\n--------------"<< std::endl;
                std::cout << "adding: " << add << std::endl;
            }else{
                std::cout << "fitness += 1" << std::endl;
                fitness += 1.0;
            }
        }

        //Add Thickness panelty
        double add = std::max(0.138-airfoil->getThickness(), 0.0) * 100;
        //double add = fabs(0.138-airfoil->getThickness()vB* 100;
        fitness += add;
        std::cout << "thickAdd: " << add << std::endl;

        add = std::max((0.07-airfoil->getFkThickness()) * 100,0.0);
        std::cout << "FkThickness: " << airfoil->getFkThickness() << std::endl;
        fitness += add;
        std::cout << "thickFkAdd: " << add << std::endl;
        
        std::cout << "overall: " << fitness << std::endl;
        std::cout << "\n"<< std::endl;
  }
  catch (exception& e){
      std::cout << e.what() << std::endl;
    fitness += 1;
  }
    return fitness;
}

void OptimizationThread::run(){

    if(polarGoals.size() == 0){return;}

    dlib::matrix<double,0,1> start;

    //get size for start & fill shapes
    int n_coefs = 0;
    for(BernsteinShape* shape : shapes){
            n_coefs+=shape->getCoefficients().n_rows;
    }
    int n_polars;
    polars.clear();
    modes.clear();
    for(PolarGoal* goal : polarGoals){
            Polar* polar=goal->getPolar();
            FoilMode* mode=polar->getMode();
            if(std::find(begin(polars),end(polars),polar) == end(polars)){
                polars.push_back(polar);
            }
            if(!mode->getSmoothLower() && !mode->getSmoothUpper() && std::find(begin(modes),end(modes),mode) == end(modes)){
                modes.push_back(mode);
            }
    }

    //resize start
    start.set_size(n_coefs+2+modes.size());

    arma::vec bounds{-2.0,2.0};
    arma::vec boundsEta{-20.0,25.0};

    dlib::matrix<double,0,1> lb = start;
    dlib::matrix<double,0,1> ub = start;

    int n = 0;
    for(FoilMode* mode : modes){
        start(n) = mode->getEta()/10;
        lb(n)=min(boundsEta)/10;
        ub(n)=max(boundsEta)/10;
        n++;
    }

    for(BernsteinShape* shape : shapes){
        arma::vec& coefs = shape->getCoefficients();
        for(int i = 0; i<coefs.n_rows; i++){
            start(n) = coefs.at(i);
            lb(n)=start(n)+min(bounds);
            ub(n)=start(n)+max(bounds);
            n++;
        }
    }

    //YPlus
    start(start.nr()-1) = airfoil->getYPlus()*10;
    lb(lb.nr()-1) = 0.0;
    ub(ub.nr()-1) = 0.45*10;

    //YMinus
    start(start.nr()-2) = airfoil->getYMinus()*10;
    lb(lb.nr()-2) = 0.0;
    ub(ub.nr()-2) = 0.3*10;

    //TurbBot
    //start(start.nr()-3) = airfoil->getTurb()[1];
    //lb(lb.nr()-3) = 0.5;
    //ub(ub.nr()-3) = 0.92;

    std::cout << "lower" << lb << "upper" << ub << std::endl;
    std::cout << "start" << start << std::endl;

    dlib::find_min_bobyqa([this](const dlib::matrix<double>& coefs) {return this->fitness(coefs);},
           start,n_coefs*2,lb,ub,0.2,1e-4,1000);

    std::cout << "ended" << std::endl;
    emit finished();

    //dlib::find_min_using_approximate_derivatives(dlib::bfgs_search_strategy(),
    //                                       dlib::objective_delta_stop_strategy(1e-10),
    //                                       [this](const dlib::matrix<double>& coefs) {return this->fitness(coefs);},
    //                                       start, -1, 0.1);
}
