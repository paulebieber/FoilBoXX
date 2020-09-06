//
// Created by paul on 3/20/20.
//

#include "Airfoil.h"
#include "AirfoilPlot.h"
#include <QApplication>
#include <QGridLayout>
#include "qwt_plot.h"

int main(int argc, char **argv){

    QApplication app(argc,argv);

    QWidget* window = new QWidget;
    QwtCustomPlot* plot = new QwtCustomPlot(window);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(plot);
    window->setLayout(layout);

    Airfoil* naca = new Airfoil();
    AirfoilPlot* airfoilPlot = new AirfoilPlot(naca,plot);

    window->show();

    return app.exec();
}
