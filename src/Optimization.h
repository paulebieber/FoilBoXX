#pragma once 

#include <QThread>
#include <dlib/optimization.h>
#include <dlib/matrix.h>
#include <vector>
#include "BernsteinShapeInterface.h"
#include "Polar.h"
#include "PolarGoal.h"
#include "AirfoilInterface.h"
#include "dlib/optimization/optimization.h"
#include "dlib/optimization/optimization_bobyqa.h"

class OptimizationThread: public QThread {
    Q_OBJECT
 
    std::vector<BernsteinShapeInterface*> shapes;
    std::vector<PolarGoal*> polarGoals;
    std::vector<Polar*> polars;
    AirfoilInterface* airfoil;
    const double fitness(const dlib::matrix<double>& coefs);

public:
    OptimizationThread();
    void setUp(AirfoilInterface* airfoil, std::vector<BernsteinShapeInterface*> shapes, 
            std::vector<PolarGoal*> polarGoals){
        this->shapes = shapes;
        this->polarGoals = polarGoals;
        this->airfoil = airfoil;
        //Enables stopping the Opt
        runOptimization = true;
    void changeFlapText();
    }
    bool runOptimization;
 
public slots:
    void run() override;
 
signals:
    void finished();
};
