// Created by paul on 15.06.19.

#include "XfoilSession.h"

XfoilSession::XfoilSession(arma::mat& coords, double turbTop, double turbBot):
    coords(coords), turbBot(turbBot), turbTop(turbTop){

    }

bool XfoilSession::setAnalysis(double re, double nCrit, bool reCa1) {

    nPoints = coords.n_rows;
    x = coords.colptr(0);
    xs = arma::vec(x,nPoints);
    y = coords.colptr(1);

    //foil->npan = nPoints;
    //foil->pangen();

    foil->initXFoilGeometry(nPoints, x, y, nx, ny);

    double* posPress = foil->cpi; posPress++;
    double* posVisc = foil->cpv; posVisc++;
    double* velo = foil->qgamm; //posVisc++;

    pressure = arma::vec(posPress,nPoints,false); 
    pressureVisc = arma::vec(posVisc,nPoints,false); 
    velocity = arma::vec(velo,nPoints,false);

    //if(velocity){
    //    pressure(i,1) = sqrt(1-pressure(i,1));
    //}
    
    auto ss = new std::stringstream();

    if (!foil->initXFoilAnalysis(re, 0, 0.0, nCrit, turbTop, turbBot, reCa1 ? 2 : 1, 1, true,*ss)) {
        return false;
    }
    return true;
}

double XfoilSession::calcJustThickness(){

    nPoints = coords.n_rows;
    x = coords.colptr(0);
    xs = arma::vec(x,nPoints);
    y = coords.colptr(1);

    //foil->npan = nPoints;
    //foil->pangen();

    foil->initXFoilGeometry(nPoints, x, y, nx, ny);
    return foil->thickb;
}

std::tuple<arma::mat,arma::mat> XfoilSession::getHFac(){

    double ws[302][3];
    double xs[302][3];
    foil->createXBL(xs);
    foil->fillHk(ws);
    hFacTop = arma::mat(foil->m_nSide1,2);
    hFacBot = arma::mat(foil->m_nSide2,2);
    for (int i = 4; i < hFacTop.n_rows; ++i) {
        hFacTop(i,0) = xs[i][1];
        hFacTop(i,1) = ws[i][1];
    }
    for (int i = 4; i < hFacBot.n_rows; ++i) {
        hFacBot(i,0) = xs[i][2];
        hFacBot(i,1) = ws[i][2];
    }
    return std::tuple<arma::mat,arma::mat>{hFacTop,hFacBot};
}

void XfoilSession::calcSingle(bool cl, double value, bool visc) {

    if (visc){
        calcPolar(cl,value,value,1);
        return;
    }

    if (!cl) {
        //foil->lalfa = true;
        foil->setAlpha(value * 3.14159 / 180);
        foil->specal();
    } else{
        //foil->lalfa = false;
        foil->setClSpec(value);
        foil->speccl();
    }
}

bool XfoilSession::calcPolar(bool cl, double min, double max, double delta){

    n_errors = 0;
    m_bErrors = false;
    //s_bAutoInitBL = true;
    s_IterLim = 75;

    foil->setBLInitialized(false);
    foil->lipan = false;

    arma::vec cls = arma::linspace(min,max,floor(1+(max-min)/delta));
    arma::mat polarNew = arma::mat(cls.n_rows,6);

    int n_converged = 0;
    for (int i = 0; i < cls.n_rows; ++i) {

        m_Iterations = 0;

        if (!cl) {
            ///std::cout << "alpha : " << cls(i) << std::endl;
            foil->setAlpha(cls(i) * 3.14159 / 180);
            foil->lalfa = true;
            if (!foil->specal()) {
                std::cout << "Invalid ModeCase SettingsInterface" << std::endl;
                return false;
            }
        } else {
            foil->setClSpec(cls(i));
            foil->lalfa = false;
            if (!foil->speccl()) {
                std::cout << "Invalid ModeCase SettingsInterface" << std::endl;
                return false;
            }
        }

        foil->setQInf(1.0);

        foil->lwake = false;
        foil->lvconv = false;

        while (!iterate());

        //std::cout << FoilMode->m_pOutStream->str() << std::endl;

        if (foil->lvconv) {
            ///std::cout << "  converged after " << m_Iterations << " iterations"
            ///          << std::endl;
            ///std::cout << "  cl : " << foil->cl << ", cd : " << foil->cd
            ///          << ", cm : " << foil->cm << ", xcp : " << foil->xcp
            ///         << std::endl;

            polarNew(n_converged,0) = foil->cl;
            polarNew(n_converged,1) = foil->cd;
            polarNew(n_converged,2) = foil->alpha()*360/(2*M_PI);
            polarNew(n_converged,3) = foil->xoctr[1];
            polarNew(n_converged,4) = foil->xoctr[2];
            polarNew(n_converged,5) = foil->cm;

            n_converged++;

        } else {
            n_errors++;
        }
    }
    polarNew = polarNew.head_rows(n_converged);
    polar = polarNew;
    return (polar.n_rows > 0);
}

bool XfoilSession::iterate() {
    if (!foil->viscal()) {
        foil->lvconv = false;
        std::cout
                << "CpCalc: local speed too large\nCompressibility corrections invalid"
                << std::endl;
        return false;
    }

    while (m_Iterations < s_IterLim && !foil->lvconv /*&& !s_bCancel*/) {
        if (foil->ViscousIter()) {
            // if (m_x0 && m_y0) {
            //  m_x0->append((double)m_Iterations);
            //  m_y0->append(FoilMode->rmsbl);
            //}
            // if (m_x1 && m_y1) {
            //  m_x1->append((double)m_Iterations);
            //  m_y1->append(FoilMode->rmxbl);
            //}
            m_Iterations++;
        } else {m_Iterations = s_IterLim;}
    }

    if (!foil->ViscalEnd()) {
        foil->lvconv = false;  // point is unconverged

        foil->setBLInitialized(false);
        foil->lipan = false;
        m_bErrors = true;
        return true;  // to exit loop
    }

    if (m_Iterations >= s_IterLim && !foil->lvconv) {
        if (s_bAutoInitBL) {
            foil->setBLInitialized(false);
            foil->lipan = false;
        }
        foil->fcpmin();  // Is it of any use ?
        return true;
    }
    if (!foil->lvconv) {
        m_bErrors = true;
        foil->fcpmin();  // Is it of any use ?
        return false;
    } else {
        // converged at last
        foil->fcpmin();  // Is it of any use ?
        return true;
    }
    return false;
}
