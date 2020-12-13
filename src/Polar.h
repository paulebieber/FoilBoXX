
#pragma once

#include "Analysis.h"
#include "ui_polarWidget.h"
#include "QwtCustomPlot.h"
#include "armadillo"
#include "QThread"
#include <vector>

class WorkerThread;

class Polar: public Analysis{

Q_OBJECT
friend class WorkerThread;
friend class PolarGoal;

friend QDataStream& operator<<(QDataStream& out, const Polar& polar); //For Serrialization, (saving the Airfoil)
friend QDataStream& operator>>(QDataStream& in, Polar& polar); //For Serrialization, (loading the Airfoil)

    double alpha1, alpha2, alphaDiscretization;
    double cl1, cl2, clDiscretization;

    double re=1e6, nCrit=8;
    bool success;
    bool borderTight;

    QString& fileVersion;

    //Plotting
    arma::vec multipliedCd;
    std::vector<QwtCustomPlot*> plots;
    QwtPlotCurve* curveCLCD = new QwtPlotCurve();
    QwtPlotCurve* curveCLAlpha = new QwtPlotCurve();
    QwtPlotCurve* curveCLXTrTop = new QwtPlotCurve();
    QwtPlotCurve* curveCLXTrBot = new QwtPlotCurve();
    QwtPlotCurve* curveCM = new QwtPlotCurve();

    QPen pen;

    void calcPolarParallel();

    //UI
    void setItemText();
    void needsUpdate(bool need);
    void setupInterface();
    void setInterfaceValues();
    Ui_polarWidget ui;

    void onActivation(bool active, bool recursively = false); //Gets called if Hierarchyelement gets activated
    void onVisible(bool visible);

public:
    Polar(std::vector<QwtCustomPlot*>, FoilMode* mode, QString& fileVersion);
    ~Polar();
    void calc(){}; //Does nothing (virtual calc by Analysis class, fired if foilMode changes)
    void plot();
    void setCurveColor(QColor color);
    bool getSuccess(){return success;}
    bool getBorderTight(){return borderTight;}
    WorkerThread* thread;

signals:
    void activated(bool recursively);
    void changed();

public slots:
    QThread* calcOnDemand();
};

class WorkerThread: public QThread {
    Q_OBJECT
 
public:
        WorkerThread(Polar* polar):polar(polar){};
 
public slots:
    void run() override{
        polar->calcPolarParallel();
        emit resultReady();
    };
 
private:
    Polar* polar;
signals:
    void resultReady();
};
