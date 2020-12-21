
#include "Optimization.h"
#include "dlib/optimization/optimization.h"
#include "dlib/optimization/optimization_bobyqa.h"
#include <iostream>
#include <qnamespace.h>

OptimizationThread::OptimizationThread():runOptimization(false){
}

const double OptimizationThread::fitness(const dlib::matrix<double>& coefs){

    double fitness = 0;

    if(!runOptimization){
        //terminate();
        return 0;
    }

    try{
        //std::cout << "I try using"<< coefs << std::endl;
        //assign new coefs
        int n = 0;
        for(BernsteinShapeInterface* shape : shapes){
            arma::vec shapeCoefs(shape->getN());
            for(int i=0; i< shape->getN(); i++){
                shapeCoefs(i) = coefs(i+n);
            }
            n+=shape->getN();
            shape->setCoefficients(shapeCoefs);
            shape->update();
            //std::cout << shapeCoefs << std::endl;
        }

        //std::vector<QThread*> threads;
        std::vector<Polar*> polars;
        for(PolarGoal* polarGoal : polarGoals){
            polars.push_back(polarGoal->getPolar());
        }

        //for(Polar* polar: polars){
        //    threads.push_back(polar->calcOnDemand());
        //}

        for(int i = 0; i< polars.size();i++){
            //threads[i]->wait(20*1000);
            polars[i]->thread->wait(20*1000);
            if(polars[i]->getSuccess() & polars[i]->getBorderTight()){
                double add = polarGoals[i]->getArea();
                if(polarGoals[i]->getMode() == PolarGoal::cD){add*=200;} //Cd very small
                fitness += add;
                std::cout << "mode: " << polarGoals[i]->getMode() << std::endl;
                std::cout << "adding: " << add << std::endl;
            }else{
                std::cout << "fitness += 1" << std::endl;
                fitness += 1.0;
            }
        }

        //Add Thickness panelty
        //fitness += (airfoil->getThickness()-0.1375) * 10;
        
        std::cout << "overall: " << fitness << std::endl;
  }
  catch (exception& e){
    cout << e.what() << '\n';
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

    //resize start
    start.set_size(n_coefs);

    int n = 0;
    for(BernsteinShape* shape : shapes){
        arma::vec& coefs = shape->getCoefficients();
        for(int i = 0; i<coefs.n_rows; i++){
            start(n) = coefs.at(i);
            n++;
        }
    }

    arma::vec bounds{-2.0,2.0};

    dlib::matrix<double,0,1> lb = start;
    dlib::matrix<double,0,1> ub = start;
    lb+=min(bounds);
    ub+=max(bounds);

    dlib::find_min_bobyqa([this](const dlib::matrix<double>& coefs) {return this->fitness(coefs);},
           start,n_coefs*2,lb,ub,0.2,1e-4,1000);

    //dlib::find_min_using_approximate_derivatives(dlib::bfgs_search_strategy(),
    //                                       dlib::objective_delta_stop_strategy(1e-10),
    //                                       [this](const dlib::matrix<double>& coefs) {return this->fitness(coefs);},
    //                                       start, -1, 0.1);
}
