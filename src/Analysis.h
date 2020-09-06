
#pragma once

#include <QTreeWidgetItem>
#include "XfoilSession.h"
#include "FoilMode.h"
#include "HierarchyElement.h"

class Analysis: public HierarchyElement, public XfoilSession{

Q_OBJECT

    QMetaObject::Connection modeConnection;

protected:
    FoilMode* mode;

    double turbTop;
    double turbBot;
    enum calcTypes{alphaCalc, clCalc};
    calcTypes calcMode;
    double re, nCrit;
    bool reCa1;

    void virtual calc() = 0;

public:
    Analysis(FoilMode* mode);
    ~Analysis();

    FoilMode* getMode(){return mode;}
    void connectToMode(FoilMode* mode);
};
