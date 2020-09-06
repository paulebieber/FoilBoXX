// Created by paul on 3/11/20.

#include "Interface.h"
#include <qnamespace.h>
#include <QFileDialog>
#include <QInputDialog>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>

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
    newFoil(false);
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

void Interface::loadAirfoil(){

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Airfoil"),tr("Airfoil (*.af)"));
    
    if(!fileName.isEmpty()){

        QFile file; file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);

        QDataStream in(&file);

        quint32 magic;
        QString fileVersion;
        in.setVersion(QDataStream::Qt_5_0);

        in >> magic;
        in >> fileVersion;

        if(magic != (quint32)0xA0C0C0B0){return;}

        newFoil(true);
        in >> *airfoils.back();

        //Read Modes, Polars and AnalysisPts
        while(true){

            QString string;
            in >> string;

            if(string == QString("FoilMode")){
                newFoilMode(airfoils.back(),true);
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
            //and Bernsteins 
            else if(string == QString("BernsteinShape")){
                BernsteinShapeInterface* shape = newBernsteinShape(airfoils.back());
                in >> *shape;
            }
            else{break;}
        }

        airfoils.back()->baseCoords();
        file.close();
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

        //ShapeDeletion done in AirfoilDeconstructor, because tightly connected
        delete airfoil;
        auto it = std::find(airfoils.begin(),airfoils.end(),airfoil);
        airfoils.erase(it);
        airfoils[0]->simulateClicked();
    }
}

void Interface::deleteAnalysisPt(AnalysisPoint* pt){

    if(analysisPts.size() > 1){
        auto it = std::find(analysisPts.begin(),analysisPts.end(),pt);
        analysisPts.erase(it);
        delete pt;
        activeAnalysisPt = analysisPts[0];
    }
}

void Interface::deletePolar(Polar* polar){

    if(polars.size() != 1){
        auto it = std::find(polars.begin(),polars.end(),polar);
        polars.erase(it);
        delete polar;
        activePolar = polars[0];
    }
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

    FoilPlot* foilPlot = new FoilPlot(foilPlotWidget);

    AirfoilInterface* newAirfoil = new AirfoilInterface(treeView,"Base",foilPlot);
    airfoils.push_back(newAirfoil);

    if (!fromStart){newFoilMode(newAirfoil);}

    layout_foil->addWidget(newAirfoil->getWidget());

    connect(newAirfoil,&AirfoilInterface::activated,[this,newAirfoil](bool recursively){activeAirfoil = newAirfoil;
            if(!recursively){QTimer::singleShot(0,[this,newAirfoil](){scrollArea->ensureWidgetVisible(newAirfoil->getWidget());});}});

    connect(newAirfoil,&AirfoilInterface::calcAllPolars,[this,newAirfoil](){
            for(Polar* polar: polars){
                if(polar->getMode()->getAirfoil() == newAirfoil){
                    polar->simulateClicked();
                    polar->calcOnDemand();
                }
            }});
    
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
    connect(pt,&AnalysisPoint::thickness,pt->getMode()->getAirfoil(),&AirfoilInterface::setThickness);
    mode->getAirfoil()->baseCoords();
    pt->simulateClicked();
}

void Interface::newPolar(FoilMode* mode){

    Polar* polar = new Polar(polarPlotWidget->getPlots(),mode);
    polars.push_back(polar);

    layout_analysis->addWidget(polar->getWidget());
    connect(polar,&Polar::activated,[this,polar](bool recursively){activePolar = polar;stackedWidget_2->setCurrentWidget(polarPlotWidget);
            if(!recursively){QTimer::singleShot(0,[this,polar](){scrollArea->ensureWidgetVisible(polar->getWidget());});}});


    polar->simulateClicked();
    //activePolar = polar;
}

BernsteinShapeInterface* Interface::newBernsteinShape(AirfoilInterface* airfoil){

    BernsteinShapeInterface* shape = new BernsteinShapeInterface(airfoil, foilPlotWidget,pressurePlotWidget);
    bernsteinShapes.push_back(shape);
    airfoil->addShapeFunction(shape);
    //shape->onActivation(false,false);

    layout_mode->addWidget(shape->getWidget());

    connect(shape,&BernsteinShapeInterface::changed,[this](bool needsNewShape){if(needsNewShape){activeAirfoil->setClassShapes();};activeAirfoil->baseCoords();});
    connect(shape,&BernsteinShapeInterface::activated,[this,shape](bool recursively){activeShape = shape;
            if(!recursively){QTimer::singleShot(0,[this,shape](){scrollArea->ensureWidgetVisible(shape->getWidget());});}});

    connect(foilPlotWidget,&QwtCustomPlot::dragged,[this,shape](QPointF pt, QPointF delta){shape->modify(pt,delta,false);});
    connect(pressurePlotWidget,&QwtCustomPlot::dragged,[this,shape](QPointF pt, QPointF delta){shape->modify(pt,delta,true);});

    shape->simulateClicked();

    return shape;
}

void Interface::connectBarGeneral(){

    connect(actionAirfoilfile,&QAction::triggered,[this](){loadAirfoil();});
    connect(actionsave,&QAction::triggered,[this](){saveAirfoil(activeAirfoil);});
    connect(actionsave_As,&QAction::triggered,[this](){saveAirfoilAs(activeAirfoil);});
    connect(actionadd_AnalysisPoint,&QAction::triggered,[this](){newAnalysisPoint(activeMode);});
    connect(actionadd_Polar,&QAction::triggered,[this](){newPolar(activeMode);});
    connect(actionadd_FoilMode,&QAction::triggered,[this](){newFoilMode(activeAirfoil);});
    connect(actionadd_ShapeFunction,&QAction::triggered,[this](){newBernsteinShape(activeAirfoil);});
    connect(actionset_Name,&QAction::triggered,this,&Interface::setAirfoilName);
    connect(actionquit,&QAction::triggered,[this]{app.quit();});
    connect(actiondelete_Airfoil,&QAction::triggered,[this]{deleteAirfoil(activeAirfoil);});
    connect(actiondelete_AnalysisPoint,&QAction::triggered,[this]{deleteAnalysisPt(activeAnalysisPt);});
    connect(actiondelete_Polar,&QAction::triggered,[this]{deletePolar(activePolar);});
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
