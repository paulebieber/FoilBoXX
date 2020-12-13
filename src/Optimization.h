#pragma once 

#include <QThread>
#include <dlib/optimization.h>
#include <dlib/matrix.h>
#include <vector>
#include "BernsteinShapeInterface.h"
#include "Polar.h"
#include "PolarGoal.h"
#include "AirfoilInterface.h"

class OptimizationThread: public QThread {
    Q_OBJECT
 
    std::vector<BernsteinShapeInterface*> shapes;
    std::vector<PolarGoal*> polarGoals;
    AirfoilInterface* airfoil;
    const double fitness(const dlib::matrix<double>& coefs);

public:
    OptimizationThread();
    void setUp(AirfoilInterface* airfoil, std::vector<BernsteinShapeInterface*> shapes, 
            std::vector<PolarGoal*> polarGoals){
        this->shapes = shapes;
        this->polarGoals = polarGoals;
        this->airfoil = airfoil;
    }
 
public slots:
    void run() override;
 
signals:
    //void readyForShapePlot(BernsteinShape* shape);
    //void readyForPolarPlot(Polar*);
};
