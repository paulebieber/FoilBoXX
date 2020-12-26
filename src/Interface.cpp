// Created by paul on 3/11/20.

#include "Interface.h"
#include <dlib/optimization.h>
#include <dlib/matrix.h>
#include <qnamespace.h>
#include <QFileDialog>
#include <QInputDialog>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>
#include <vector>

Interface::Interface(QApplication& app, QString version):app(app), version(version){

    setupUi(this);

    //polarPlotWidget->setMinimumWidth(250);
    foilPlotWidget->setMinimumHeight(200);

    polarPlotWidget = new PolarPlotWidget();
    pressurePlotWidget = new PressurePlotWidget();
    stackedWidget_2->addWidget(polarPlotWidget);
    stackedWidget_2->addWidget(pressurePlotWidget);

    foilPlotWidget->connectToAxis(pressurePlotWidget);

    connectBarGeneral();
    if(!loadAirfoil()){newFoil();};
    activeAirfoil = airfoils.back();

    splitter->setSizes(QList<int>() << 250 << 450);
    treeView->expandAll();
    treeView->header()->resizeSection(0,200);
    treeView->resizeColumnToContents(1);
    treeView->resizeColumnToContents(2);

    show();

    //setAxisScale(QwtPlot::xBottom,x1,x2);
}

void Interface::saveAirfoil(AirfoilInterface* airfoil){

    if(airfoil->getHasFile()){
        writeAirfoil(airfoil);
    }else{
        saveAirfoilAs(airfoil);
    }
}

void Interface::saveAirfoilAs(AirfoilInterface* airfoil){
    
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Airfoil"),airfoil->getFile().fileName(),tr("Airfoil (*.af)"));
    if(!fileName.isEmpty()){
        airfoil->getFile().setFileName(fileName);
        writeAirfoil(airfoil);
    }
}

void Interface::saveCoords(FoilMode* mode){

    QString name = mode->getCoordsName() + QString(".dat");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Coordinates"),name,tr("Coords (*.dat, *.coor, *.coords)"));
    if(!fileName.isEmpty()){
        QFile file(fileName);
        file.open(QFile::WriteOnly);
        QTextStream out(&file);
        mode->saveCoords(out);
        file.close();
    }
}

void Interface::saveFlap(FoilMode* mode){

    QString name = QString("flapCoords_") + mode->getCoordsName() + QString(".dat");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save flapCoordinates"),name,tr("Coords (*.dat, *.coor, *.coords)"));
    if(!fileName.isEmpty()){
        QFile file(fileName);
        file.open(QFile::WriteOnly);
        QTextStream out(&file);
        mode->saveFlap(out);
        file.close();
    }
}

void Interface::writeAirfoil(AirfoilInterface* airfoil){

    QFile& file = airfoil->getFile();

    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setFloatingPointPrecision(QDataStream::DoublePrecision);

    out << (quint32)0xA0C0C0B0;
    out << QString(version);

    out.setVersion(QDataStream::Qt_5_0);

    out << *airfoil;
    
    for(FoilMode* mode : modes){
        if(mode->getAirfoil()==airfoil){

            out << (*mode);
        
            for(AnalysisPoint* pt : analysisPts){
                if(pt->getMode()==mode){
                    out << (*pt);
                }
            }
            for(Polar* polar : polars){
                if(polar->getMode()==mode){
                    out << (*polar);
                    for(PolarGoal* goal : polarGoals){
                        if(goal->getPolar() == polar){
                            out << (*goal);
                        }
                    }
                }
            }
        }
    }

    for(BernsteinShapeInterface* shape : bernsteinShapes){
        if(shape->getParent()==airfoil){
            out << (*shape);
        }
    }

    file.close();
}

bool Interface::loadAirfoil(){

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Airfoil"),tr("Airfoil (*.af)"));
    
    if(!fileName.isEmpty()){

        QFile file; file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);

        QDataStream in(&file);

        quint32 magic;
        in.setVersion(QDataStream::Qt_5_0);

        in >> magic;
        in >> fileVersion;
        
        if((magic != (quint32)0xA0C0C0B0)){return false;}

        newFoil(true);
        in >> *airfoils.back();

        //Read Modes, Polars and AnalysisPts
        while(true){

            QString string;
            in >> string;

            if(string == QString("FoilMode")){
                newFoilMode(airfoils.back(),true);
                modes.back()->blockSignals(true);
                in >> *modes.back();
            }
            //For Analysispts
            else if(string == QString("AnalysisPoint")){
                newAnalysisPoint(modes.back());
                in >> *analysisPts.back();
            } 
            //and Polars
            else if(string == QString("Polar")){
                newPolar(modes.back());
                in >> *polars.back();
            }
            //and Goals
            else if(string == QString("PolarGoal")){ //version 0.6.0
                newPolarGoal(polars.back(),PolarGoal::cD);
                in >> *polarGoals.back();
            }
            else if(string == QString("PolarGoalCLAlpha")){
                newPolarGoal(polars.back(),PolarGoal::cLAlpha);
                in >> *polarGoals.back();
            }
            else if(string == QString("PolarGoalCD")){
                newPolarGoal(polars.back(),PolarGoal::cD);
                in >> *polarGoals.back();
            }
            else if(string == QString("PolarGoalXTrTop")){
                newPolarGoal(polars.back(),PolarGoal::XTrTop);
                in >> *polarGoals.back();
            }
            //and Bernsteins 
            else if(string == QString("BernsteinShape")){
                BernsteinShapeInterface* shape = newBernsteinShape(airfoils.back());
                in >> *shape;
            }
            else{break;}
        }

        //Blocking, so that polars dont get calced with wrong coordinates while setting up,
        //and iterate long (missing Camber for high cl)
        for(FoilMode* mode: modes){mode->blockSignals(false);}
        airfoils.back()->baseCoords();
        file.close();
        return true;
    }else{
        return false;
    }
}

void Interface::loadCoords(){

    //If Current foil is Full one (not from Coords) create new one
    for(FoilMode* mode: modes){
        if(mode->getAirfoil() == activeAirfoil && mode->getModeType() == FoilMode::full){
            newFoil(true);
        }
    }

    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Load AirfoilCoordinates"),tr("AirfoilCoords (*.txt,*.dat,*.coo,*.coor)"));

    for(QString fileName: fileNames){

        if(!fileName.isEmpty()){
            QFile file(fileName);
            file.open(QIODevice::ReadOnly);
            QTextStream in(&file);

            newFoilMode(activeAirfoil,false,&in);
            file.close();
        }
    }
}

void Interface::deleteAirfoil(AirfoilInterface* airfoil){

    if(airfoils.size() > 1){
        //for(AirfoilInterface* airfoil2: airfoils){
        //    if(airfoil2 != airfoil){
        //        treeView->setCurrentItem(airfoil2->getTreeItem());
        //    }
        //}

        std::vector<FoilMode*> modesToDelete = modes;
        for(FoilMode* mode : modesToDelete){
            if(mode->getAirfoil() == airfoil){deleteMode(mode);}
        }

        for(FoilPlot* foilPlot : foilPlots){
            if(foilPlot->getAirfoil() == airfoil){
                auto it = std::find(foilPlots.begin(),foilPlots.end(),foilPlot);
                foilPlots.erase(it);
                delete foilPlot;
                break; //Only one foilPlot per Foil, easier
            }
        }

        //ShapeDeletion done in AirfoilDeconstructor, because tightly connected
        delete airfoil;
        auto it = std::find(airfoils.begin(),airfoils.end(),airfoil);
        airfoils.erase(it);
        airfoils[0]->simulateClicked();
    }
}

void Interface::deleteAnalysisPt(AnalysisPoint* pt){

    if(analysisPts.size() == 0){return;}
    auto it = std::find(analysisPts.begin(),analysisPts.end(),pt);
    analysisPts.erase(it);
    delete pt;
    if(analysisPts.size() > 0){activeAnalysisPt = analysisPts[0];}
}

void Interface::deletePolar(Polar* polar){

    if(polars.size() == 0){return;}
    auto it = std::find(polars.begin(),polars.end(),polar);
    polars.erase(it);
    for(PolarGoal* polarGoal : polarGoals){
        if(polarGoal->getPolar() == polar){
            deletePolarGoal(polarGoal);
        }
    }
    delete polar;
    if(polars.size() > 0){activePolar = polars[0];}
}

void Interface::deleteBernsteinShape(BernsteinShapeInterface* shape){

    if(bernsteinShapes.size() > 1){
        auto it = std::find(bernsteinShapes.begin(),bernsteinShapes.end(),shape);
        bernsteinShapes.erase(it);
        delete shape;
        activeShape = bernsteinShapes[0];
    }
}

void Interface::deleteMode(FoilMode* mode){

    //if(modes.size() > 1){

        mode->getAirfoil()->simulateClicked();

        for(AnalysisPoint* pt : analysisPts){
            if(pt->getMode()==mode){deleteAnalysisPt(pt);}
        }

        for(Polar* polar : polars){
            if(polar->getMode()==mode){deletePolar(polar);}
        }

        auto it = std::find(modes.begin(),modes.end(),mode);
        modes.erase(it);
        delete mode;
        modes[0]->simulateClicked();
    //}
}

void Interface::newFoil(bool fromStart){

    AirfoilInterface* newAirfoil = new AirfoilInterface(treeView,"Base");
    airfoils.push_back(newAirfoil);

    //Add Plot
    FoilPlot* foilPlot = new FoilPlot(foilPlotWidget,newAirfoil);
    foilPlots.push_back(foilPlot);

    if (!fromStart){newFoilMode(newAirfoil);}

    layout_foil->addWidget(newAirfoil->getWidget());

    connect(newAirfoil,&AirfoilInterface::activated,[this,newAirfoil](bool recursively){activeAirfoil = newAirfoil;});
            //if(!recursively){QTimer::singleShot(0,[this,newAirfoil](){scrollArea->ensureWidgetVisible(newAirfoil->getWidget());});}});

    connect(newAirfoil,&AirfoilInterface::calcAllPolars,[this,newAirfoil](){
            for(Polar* polar: polars){
                if(polar->getMode()->getAirfoil() == newAirfoil){
                    polar->calcOnDemand();
                    //polar->simulateClicked();
                }
            }});

    connect(newAirfoil,&AirfoilInterface::optimizePolars,[this,newAirfoil](){
                    optimizePolars(newAirfoil);});
    
    newAirfoil->changed();
    newAirfoil->simulateClicked();
    if(!fromStart){
        newBernsteinShape(newAirfoil);
        bernsteinShapes.back()->setModifying(true,true);
        newBernsteinShape(newAirfoil);
        bernsteinShapes.back()->setSide(BernsteinShape::bottom);
        //bernsteinShapes[bernsteinShapes.size()-2]->simulateClicked();
        modes.back()->simulateClicked();
    }
}

void Interface::optimizePolars(AirfoilInterface* airfoil){

    //optimizationThread = new OptimizationThread();
    if(!optimizationThread.runOptimization){
        std::vector<BernsteinShapeInterface*> shapes;
        std::vector<PolarGoal*> optimizationPolarGoals;

        for(BernsteinShapeInterface* shape : bernsteinShapes){
            if(shape->getParent()==airfoil){
                shapes.push_back(shape);
            }
        }
        for(PolarGoal* polarGoal : polarGoals){
            if(polarGoal->getPolar()->getMode()->getParent()==airfoil){
                optimizationPolarGoals.push_back(polarGoal);
            }
        }
        optimizationThread.setUp(activeAirfoil,shapes,optimizationPolarGoals);
        optimizationThread.start();
    }else{
        optimizationThread.runOptimization = false;
        optimizationThread.wait();
        //delete optimizationThread;
    }
}

void Interface::newFoilMode(AirfoilInterface* airfoil, bool fromStart, QTextStream* in){

    if(!(airfoil->getFoilType() == AirfoilInterface::coords && in == nullptr)){

        ModePlot* modePlot = new ModePlot(foilPlotWidget);
        FoilMode* mode = (in == nullptr) ? new FoilMode(airfoil,modePlot) : new FoilMode(airfoil,*in,modePlot);
        modes.push_back(mode);

        layout_mode->addWidget(mode->getWidget());

        connect(mode,&FoilMode::activated,[this,mode](bool recursively){activeMode = mode;
            if(!recursively){QTimer::singleShot(0,[this,mode](){scrollArea->ensureWidgetVisible(mode->getWidget());});}});
        //activeMode = mode;

        if(!fromStart){
            newPolar(mode);
            newAnalysisPoint(mode);
        }
        mode->simulateClicked();
    }
}

void Interface::newAnalysisPoint(FoilMode* mode){

    AnalysisPoint* pt = new AnalysisPoint(mode,pressurePlotWidget);
    analysisPts.push_back(pt);

    layout_analysis->addWidget(pt->getWidget());
    connect(pt,&AnalysisPoint::activated,[this,pt](bool recursively){activeAnalysisPt=pt;stackedWidget_2->setCurrentWidget(pressurePlotWidget);
            if(!recursively){QTimer::singleShot(0,[this,pt](){scrollArea->ensureWidgetVisible(pt->getWidget());});}});
    mode->getAirfoil()->baseCoords();
    pt->simulateClicked();
}

void Interface::newPolar(FoilMode* mode){

    Polar* polar = new Polar(polarPlotWidget->getPlots(),mode,fileVersion);
    polars.push_back(polar);

    layout_analysis->addWidget(polar->getWidget());

    connect(polar,&Polar::activated,[this,polar](bool recursively){activePolar = polar;stackedWidget_2->setCurrentWidget(polarPlotWidget);
            if(!recursively){QTimer::singleShot(0,[this,polar](){scrollArea->ensureWidgetVisible(polar->getWidget());});}});

    polar->simulateClicked();
}

void Interface::newPolarGoal(Polar* polar, PolarGoal::Modes mode){

    PolarGoal* polarGoal = new PolarGoal(polarPlotWidget->getPlots()[(int)mode],mode,polar,fileVersion);
    polarGoals.push_back(polarGoal);

    layout_analysis->addWidget(polarGoal->getWidget());

    connect(polarGoal,&PolarGoal::activated,[this,polarGoal](bool recursively){activePolarGoal = polarGoal;
            stackedWidget_2->setCurrentWidget(polarPlotWidget);
            if(!recursively){QTimer::singleShot(0,[this,polarGoal](){scrollArea->ensureWidgetVisible(polarGoal->getWidget());});}});

    polarGoal->simulateClicked();
}

void Interface::deletePolarGoal(PolarGoal* polarGoal){

    if(polarGoals.size() == 0){return;}
    auto it = std::find(polarGoals.begin(),polarGoals.end(),polarGoal);
    polarGoals.erase(it);
    delete polarGoal;
    if(polarGoals.size() > 0){activePolarGoal = polarGoals[0];}
}

BernsteinShapeInterface* Interface::newBernsteinShape(AirfoilInterface* airfoil){

    BernsteinShapeInterface* shape = new BernsteinShapeInterface(airfoil, foilPlotWidget,pressurePlotWidget,fileVersion);
    bernsteinShapes.push_back(shape);
    airfoil->addShapeFunction(shape);
    //shape->onActivation(false,false);

    layout_mode->addWidget(shape->getWidget());

    connect(shape,&BernsteinShapeInterface::changed,this,[=](bool needsNewShape){if(needsNewShape){activeAirfoil->setClassShapes();};
            activeAirfoil->baseCoords();},Qt::DirectConnection);
    connect(shape,&BernsteinShapeInterface::activated,[this,shape](bool recursively){activeShape = shape;
            if(!recursively){QTimer::singleShot(0,[this,shape](){scrollArea->ensureWidgetVisible(shape->getWidget());});}});

    shape->simulateClicked();

    return shape;
}

void Interface::connectBarGeneral(){

    connect(actionAirfoilfile,&QAction::triggered,[this](){loadAirfoil();});
    connect(actionsave,&QAction::triggered,[this](){saveAirfoil(activeAirfoil);});
    connect(actionsave_As,&QAction::triggered,[this](){saveAirfoilAs(activeAirfoil);});
    connect(actionadd_AnalysisPoint,&QAction::triggered,[this](){newAnalysisPoint(activeMode);});
    connect(actionadd_Polar,&QAction::triggered,[this](){newPolar(activeMode);});
    connect(actionadd_PolarGoal,&QAction::triggered,[this](){newPolarGoal(activePolar);});
    connect(actionadd_PolarGoalForCLAlpha,&QAction::triggered,[this](){newPolarGoal(activePolar,PolarGoal::XTrTop);});
    connect(actionadd_FoilMode,&QAction::triggered,[this](){newFoilMode(activeAirfoil);});
    connect(actionadd_ShapeFunction,&QAction::triggered,[this](){newBernsteinShape(activeAirfoil);});
    connect(actionset_Name,&QAction::triggered,this,&Interface::setAirfoilName);
    connect(actionquit,&QAction::triggered,[this]{app.quit();});
    connect(actiondelete_Airfoil,&QAction::triggered,[this]{deleteAirfoil(activeAirfoil);});
    connect(actiondelete_AnalysisPoint,&QAction::triggered,[this]{deleteAnalysisPt(activeAnalysisPt);});
    connect(actiondelete_Polar,&QAction::triggered,[this]{deletePolar(activePolar);});
    connect(actiondelete_PolarGoal,&QAction::triggered,[this]{deletePolarGoal(activePolarGoal);});
    connect(actiondelete_FoilMode,&QAction::triggered,[this]{deleteMode(activeMode);});
    connect(actionCoords,&QAction::triggered,[this]{loadCoords();});
    connect(actiondelete_ShapeFunction,&QAction::triggered,[this]{deleteBernsteinShape(activeShape);});
    connect(actionsave_Coords,&QAction::triggered,[this]{saveCoords(activeMode);});
    connect(actionsave_flapCoords,&QAction::triggered,[this]{saveFlap(activeMode);});
}

void Interface::setAirfoilName(){

    bool ok;
    QString text = QInputDialog::getText(this, tr("Foilname"),
            tr("Enter a name for the Airfoil:"), QLineEdit::Normal, QString(""), &ok);
    if (ok && !text.isEmpty())
        activeAirfoil->setName(text);
}
