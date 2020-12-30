// Created by paul on 3/12/20.

#include "AirfoilInterface.h"
#include <QDebug>

AirfoilInterface::AirfoilInterface(QTreeWidget* tree, QString name): thicknessXfoil(getFlosseCut()),HierarchyElement(tree),
    name(name), hasFile(false), flapRelChanged(true){

    connect(this,&AirfoilInterface::changed,this,[=](){
                ui.thickness->setText(QString::number(thickness*100.0,'f',2) + " %");},Qt::QueuedConnection);
    connect(this,&AirfoilInterface::changed,this,&AirfoilInterface::changeFlapText,Qt::QueuedConnection);
    
    setName(name);
    setBold(true);  
    setupInterface(); 
}

AirfoilInterface::~AirfoilInterface(){
}

QDataStream& operator<<(QDataStream& out, AirfoilInterface& airfoil){

    out << airfoil.name;
    out << airfoil.file.fileName();
    //out << airfoil.topShape << airfoil.botShape << airfoil.fkShape;
    out << airfoil.yPlus << airfoil.yMinus << airfoil.flapByRel << airfoil.flapRelY << airfoil.flapPivot(0) << airfoil.flapPivot(1);
    out << airfoil.turbOn << airfoil.getTurb()[0] << airfoil.getTurb()[1];
    out << airfoil.fk << airfoil.fkChordfactor;
    airfoil.hasFile = true;
    return out;
}

QDataStream& operator>>(QDataStream& in, AirfoilInterface& airfoil){

    //in.setFloatingPointPrecision(QDataStream::DoublePrecision);

    QString name; in >> name;
    airfoil.setName(name);
    in >> name;
    airfoil.file.setFileName(name);
    in >> airfoil.yPlus >> airfoil.yMinus >> airfoil.flapByRel >> airfoil.flapRelY >> airfoil.flapPivot(0) >> airfoil.flapPivot(1);
    double turbTop,turbBot;
    bool turbOn;
    in >> turbOn >> turbTop >> turbBot;
    airfoil.setAttribute(Airfoil::setTurbTop,turbTop,false);
    airfoil.setTurbOn(turbOn,false);
    bool fk;
    in >> fk >> airfoil.fkChordfactor;
    airfoil.setFkOn(fk,false);
    airfoil.setClassShapes();
    airfoil.setAttribute(Airfoil::setTurbBot,turbBot,true); //Also recalcs
    airfoil.setInterfaceValues();
    airfoil.hasFile = true;

    return in;
}

void AirfoilInterface::setFkOn(bool on, bool recalc){
    setAttribute(setFk,on,recalc);
    ui.doubleSpinBox_fkChordFactor->setEnabled(on);
}

void AirfoilInterface::setTurbOn(bool on, bool recalc){
    setAttribute(Airfoil::setTurbOn,on,recalc);
    ui.doubleSpinBox_turbBot->setEnabled(on);
    ui.doubleSpinBox_turbTop->setEnabled(on);
}

void AirfoilInterface::changedBaseCoords(bool nChanged){

    thickness = thicknessXfoil.calcJustThickness();
    emit changed();
    if(nChanged){emit replot();}
}

void AirfoilInterface::changeFlapText(){

    if(flapByRel){
        ui.doubleSpinBox_flapY->blockSignals(true);
        ui.doubleSpinBox_flapY->setValue(getFlapYAbsolute());
        ui.doubleSpinBox_flapY->blockSignals(false);
    }
    if(!flapByRel){
        ui.doubleSpinBox_flapY_rel->blockSignals(true);
        ui.doubleSpinBox_flapY_rel->setValue(getFlapYRelative());
        ui.doubleSpinBox_flapY_rel->blockSignals(false);
    }
    if(flapRelChanged){
        QString inactive = "background-color: white;";
        QString active = "background-color: lightGray;";
        ui.doubleSpinBox_flapY->setStyleSheet(flapByRel?inactive:active);
        ui.doubleSpinBox_flapY_rel->setStyleSheet(flapByRel?active:inactive);
        flapRelChanged = false;
    }

}

void AirfoilInterface::onActivation(bool active, bool recursively){

    emit activeChanged(active && !recursively);
    if(active){emit activated(recursively);}
    if(type == coords){widget.hide();}
}

void AirfoilInterface::onVisible(bool visible){

    emit visibleChanged(visible);
}

void AirfoilInterface::setName(QString string){

    name = string;
    if(!hasFile){file.setFileName(name+QString(".af"));}
    treeItem->setText(0,name);
}

void AirfoilInterface::setupInterface(){

    //UIWidget
    ui.setupUi(&widget);
    setInterfaceValues(); 

    connect(this,&AirfoilInterface::reInterface,this,&AirfoilInterface::setInterfaceValues);

    connect(ui.doubleSpinBox_yPlus,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double yPlus){setAttribute(setYPlus,yPlus,true);});
    connect(ui.doubleSpinBox_yMinus,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double yMinus){setAttribute(setYMinus,yMinus,true);});
    connect(ui.doubleSpinBox_yNose,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double yNose){setAttribute(setNoseY,yNose,true);});
    connect(ui.doubleSpinBox_flapX,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double x){setAttribute(setFlapX,x,true);});
    connect(ui.doubleSpinBox_flapY,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double y){if(flapByRel){flapRelChanged = true;};setAttribute(setFlapYAbsolute,y,true);});
    connect(ui.doubleSpinBox_flapY_rel,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double y){if(!flapByRel){flapRelChanged = true;};setAttribute(setFlapYRelative,y,true);});
    connect(ui.doubleSpinBox_fkChordFactor,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double x){setAttribute(setFkChordFactor,x,true);});
    connect(ui.doubleSpinBox_fkChordFactor,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double x){setAttribute(setFkChordFactor,x,true);});
    connect(ui.doubleSpinBox_turbTop,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double x){setAttribute(setTurbTop,x,true);});
    connect(ui.doubleSpinBox_turbBot,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double x){setAttribute(setTurbBot,x,true);});
    connect(ui.groupBox_fk,&QGroupBox::toggled,[this](bool state){setFkOn(state,true);});
    connect(ui.groupBox_Turb,&QGroupBox::toggled,[this](bool state){setTurbOn(state,true);});
    connect(ui.pushButton_calcPolarAll,&QPushButton::clicked,[this](){emit calcAllPolars();});
    connect(ui.pushButton_optimizePolars,&QPushButton::clicked,[this](){emit optimizePolars();});

    ui.doubleSpinBox_yPlus->setRange(0.0,0.3);
    ui.doubleSpinBox_yMinus->setRange(0.0,0.3);
    ui.doubleSpinBox_yPlus->setSingleStep(0.001);
    ui.doubleSpinBox_yMinus->setSingleStep(0.001);

    ui.doubleSpinBox_yNose->setRange(-0.012,0.012);
    ui.doubleSpinBox_yNose->setSingleStep(0.0005);

    ui.doubleSpinBox_flapX->setRange(0.3,0.95);
    ui.doubleSpinBox_flapX->setSingleStep(0.001);

    ui.doubleSpinBox_flapY_rel->setRange(0.0,1.0);
    ui.doubleSpinBox_flapY_rel->setSingleStep(0.01);
    ui.doubleSpinBox_flapY->setRange(-0.05,0.05);
    ui.doubleSpinBox_flapY->setSingleStep(0.0005);

    ui.doubleSpinBox_turbTop->setRange(0,1);
    ui.doubleSpinBox_turbBot->setRange(0,1);
    ui.doubleSpinBox_turbBot->setSingleStep(0.005);
    ui.doubleSpinBox_turbTop->setSingleStep(0.005);

    ui.doubleSpinBox_fkChordFactor->setRange(1.02,1.3);
    ui.doubleSpinBox_fkChordFactor->setSingleStep(0.005);

    for(QDoubleSpinBox* spin : std::list<QDoubleSpinBox*>{ui.doubleSpinBox_yPlus,ui.doubleSpinBox_yMinus,ui.doubleSpinBox_yNose,ui.doubleSpinBox_flapY,ui.doubleSpinBox_flapX,
            ui.doubleSpinBox_flapY_rel,ui.doubleSpinBox_fkChordFactor,ui.doubleSpinBox_turbBot,ui.doubleSpinBox_turbBot}){

            spin->setDecimals(4);
            if(spin == ui.doubleSpinBox_flapY_rel){spin->setDecimals(3);}
    }
}

void AirfoilInterface::setInterfaceValues(){

    std::list<QObject*> toChange({ui.doubleSpinBox_flapX,ui.doubleSpinBox_flapY,ui.doubleSpinBox_yNose,
                            ui.doubleSpinBox_yPlus,ui.doubleSpinBox_yMinus,ui.doubleSpinBox_turbBot,ui.doubleSpinBox_turbTop,
                            ui.doubleSpinBox_flapY_rel,ui.groupBox_fk,ui.groupBox_Turb});
    for(QObject* obj : toChange){obj->blockSignals(true);}

    ui.doubleSpinBox_yPlus->setValue(getYPlus());
    ui.doubleSpinBox_yMinus->setValue(getYMinus());
    ui.doubleSpinBox_yNose->setValue(getNoseY());
    ui.doubleSpinBox_flapX->setValue(getFlapX());
    ui.doubleSpinBox_fkChordFactor->setValue(getFkChordfactor());
    if(flapByRel){
        ui.doubleSpinBox_flapY_rel->setValue(getFlapYRelative());
    }else{
        ui.doubleSpinBox_flapY->setValue(getFlapYAbsolute());
    }
    ui.doubleSpinBox_turbTop->setValue(getTurb()[0]);
    ui.doubleSpinBox_turbBot->setValue(getTurb()[1]);

    auto turb = getTurb();
    ui.doubleSpinBox_turbTop->setValue(turb[0]);
    ui.doubleSpinBox_turbBot->setValue(turb[1]);
    ui.groupBox_Turb->setChecked(turbOn);
    ui.groupBox_fk->setChecked(fk);

    for(QObject* obj : toChange){obj->blockSignals(false);}
}
