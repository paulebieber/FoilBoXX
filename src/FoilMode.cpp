
#include "FoilMode.h"
#include "SplineFunctions.h"
#include <qnamespace.h>

FoilMode::FoilMode(AirfoilInterface* airfoil, ModePlot* modePlot):HierarchyElement(airfoil),airfoil(airfoil),modeType(full),modePlot(modePlot){

    connectToFoil(airfoil);
    modePlot->connectToMode(this);
    setupInterface();

    connect(this,&FoilMode::changed,this,[=](){setItemText();});

    calcCoords();
}

FoilMode::FoilMode(AirfoilInterface* airfoil, QTextStream& in, ModePlot* modePlot): HierarchyElement(airfoil), modePlot(modePlot), airfoil(airfoil), modeType(coords){

    //Extract coords
    double x;
    double y;
    QStringList list;
    QString string;
    coordsAero = arma::mat(0,2);

    int i = 0;
    while (!in.atEnd()) {
        string = in.readLine();
        list = string.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        bool gotName = false;
        if (i == 0){
            if(list[0].at(0).isLetter()){
                setItemText(list[0]);
                gotName = true;
            }
        }
        if(!gotName){
            x = list[0].toDouble();
            y = list[1].toDouble();
            coordsAero.resize(coordsAero.n_rows+1,2);
            coordsAero.row(coordsAero.n_rows-1) = arma::vec2{x,y}.t();
        }
        i++;
    }
    //Calc upper and lower Side from it
    arma::mat reversed = coordsAero;
    for (int i = 0; i < reversed.n_rows; ++i) {
        reversed.row(i) = coordsAero.row(reversed.n_rows-1-i);
    }

    double noseX = coordsAero.col(0).index_min();
    upperSide = reversed.tail_rows(noseX);
    lowerSide = coordsAero.tail_rows(coordsAero.n_rows-noseX);

    setTurbsFromAero();
    
    connectToFoil(airfoil);
    airfoil->setFoilType(AirfoilInterface::coords);
    modePlot->connectToMode(this);
    setupInterface();

    calcCoords();
}

FoilMode::~FoilMode(){
    delete modePlot;
}

void FoilMode::setTurbsFromAero(){

    turbTop(0) = upperSide(upperSide.n_rows-1,0);
    turbBot(0) = lowerSide(lowerSide.n_rows-1,0);
}

QDataStream& operator<<(QDataStream& out, const FoilMode& mode){

    out << QString("FoilMode");
    out << mode.eta << mode.fk;
    return out;
}

QDataStream& operator>>(QDataStream& in, FoilMode& mode){

    in >> mode.eta >> mode.fk;
    mode.setItemText();
    mode.setInterfaceValues();
    mode.calcCoords();
    return in;
}

void FoilMode::calcCoords(){
  
    if(modeType == full){

        std::tuple<std::vector<arma::mat>,arma::vec,arma::vec> all = airfoil->getModeCoords(fk,eta);
        std::vector<arma::mat> coords = std::get<0>(all);

        turbTop = std::get<1>(all);
        turbBot = std::get<2>(all);

        coordsAero = coords[0]; fkTop = coords[1], fkBot = coords[2], flapTop = coords[3], flapBot = coords[4];

    }else{
        //Calc Turbulator y
        turbTop(1) = interpolate(upperSide,turbTop(0));
        turbBot(1) = interpolate(lowerSide,turbBot(0));
    }
    
    emit changed();
}

void FoilMode::saveCoords(QTextStream& out){

    out << getCoordsName() << "\n";
    for (int i = 0; i < coordsAero.n_rows; ++i) {
       out << coordsAero(i,0) << "\t" << coordsAero(i,1) << "\n";
    }
}

void FoilMode::saveFlap(QTextStream& out){

    out << "FlapCoords for: " << getCoordsName() << "\n";
    for (int i = flapTop.n_rows-1; i >= 0; --i) {
       out << flapTop(i,0) << "\t" << flapTop(i,1) << "\n";
    }
    for (int i = 0; i < flapBot.n_rows; ++i) {
       out << flapBot(i,0) << "\t" << flapBot(i,1) << "\n";
    }
}

QString FoilMode::getCoordsName(){

    QString name(airfoil->getName() + "_" + QString("%1_deg").arg(eta));
    return name;
}

void FoilMode::connectToFoil(AirfoilInterface* foil){

    airfoil = foil; 
    disconnect(airfoilConnection);
    airfoilConnection = connect(airfoil,&AirfoilInterface::changed,this,&FoilMode::calcCoords,Qt::DirectConnection);
    color = *(foil->getColor());
    setBold(true);
    setColor(color);
}

void FoilMode::setItemText(){
    treeItem->setText(0,getCoordsName());
}

void FoilMode::setItemText(QString string){
    treeItem->setText(0,string);
}

void FoilMode::setEta(double eta, bool recalc){

    this->eta = eta;
    if(recalc){calcCoords();}
}

void FoilMode::setFK(bool on, bool recalc){

    fk = on;
    if(recalc){calcCoords();}
}

void FoilMode::onActivation(bool active, bool recursively){

    modePlot->setActive(!recursively && active);

    if(active){emit activated(recursively);}
}

void FoilMode::onVisible(bool visible){

    modePlot->setVisible(visible);
}

void FoilMode::setupInterface(){

    if(modeType == full){
        ui.setupUi(&widget);
        ui.doubleSpinBox_eta->setRange(-30,30);
        ui.doubleSpinBox_eta->setSingleStep(0.5);
        connect(ui.pushButton_designEtaLower,&QPushButton::clicked,[this](){setEta(airfoil->getEtaDesignLower(),true);setInterfaceValues();});
        connect(ui.pushButton_designEtaUpper,&QPushButton::clicked,[this](){
                if(!fk){setEta(airfoil->getEtaDesignUpper(),true);}
                else{setEta(0.0,true);}
                setInterfaceValues();});
        connect(ui.doubleSpinBox_eta,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double eta){setEta(eta,true);});
        connect(ui.checkBox_fk,&QCheckBox::stateChanged,[this](int status){setFK(status,true);});
    }
    else{
        uiCoords.setupUi(&widget);
        uiCoords.doubleSpinBox_turbTop->setRange(0.0,1.5);
        uiCoords.doubleSpinBox_turbBot->setRange(0.0,1.5);
        uiCoords.doubleSpinBox_turbBot->setSingleStep(0.005);
        uiCoords.doubleSpinBox_turbTop->setSingleStep(0.005);
        uiCoords.doubleSpinBox_turbTop->setDecimals(3);
        uiCoords.doubleSpinBox_turbBot->setDecimals(3);
        connect(uiCoords.doubleSpinBox_turbTop,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double x){turbTop(0)=x;calcCoords();});
        connect(uiCoords.doubleSpinBox_turbBot,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[this](double x){turbBot(0)=x;calcCoords();});
        connect(uiCoords.groupBox_Turb,&QGroupBox::toggled,[this](bool on){if(!on){setTurbsFromAero();setInterfaceValues();}});
    }
    setInterfaceValues();
}

void FoilMode::setInterfaceValues(){

    if(modeType == full){
        ui.doubleSpinBox_eta->setValue(eta);
        ui.checkBox_fk->setChecked(fk);
    }else{
        uiCoords.doubleSpinBox_turbTop->setValue(turbTop(0));
        uiCoords.doubleSpinBox_turbBot->setValue(turbBot(0));
    }
}
