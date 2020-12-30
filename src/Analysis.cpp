
#include "Analysis.h"
#include <qnamespace.h>

Analysis::Analysis(FoilMode* mode):HierarchyElement(mode),XfoilSession(mode->getCoords(),mode->getTurbTop(),mode->getTurbBot()),
            calcMode(alphaCalc), re(1e6), nCrit(8), reCa1(false){

    connectToMode(mode);
}

Analysis::~Analysis(){
}

void Analysis::connectToMode(FoilMode* mode){

    this->mode = mode;
    //modeConnection = connect(mode,&FoilMode::changed,this,&Analysis::calc);
    modeConnection = connect(mode,&FoilMode::changed,this,&Analysis::calc,Qt::DirectConnection);
}
