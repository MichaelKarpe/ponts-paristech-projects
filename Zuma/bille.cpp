#include "bille.h"


//Constructeurs

Bille::Bille() {

}

Bille::Bille(const Point &ip, const int &iabs, const double &iv, const Niveau &Niv)
{
    col=colors[rand()%Niv.getNbCol()];
    abs=iabs;
    v=iv;
    p=ip;
}


// Destructeur

Bille::~Bille()
{

}


// Assesseurs

Color Bille::getCol() const {
    return col;
}

double Bille::getVit() const {
    return v;
}

Point Bille::getCoor() const {
    return p;
}

int Bille::getAbs() const {
    return abs;
}

void Bille::setCol(const Color &icol) {
    col = icol;
}

void Bille::setVit(const double &iv) {
    v = iv;
}

void Bille::setCoor(const Point &ip) {
    p = ip;
}

void Bille::setAbs(const int &iabs) {
    abs = iabs;
}


// Fonctions traitant les données

void Bille::avanceTirBille(const double &vx, const double &vy) {
    fillCircle(p.getX()*zoom,p.getY()*zoom,R,WHITE);
    p.setX(p.getX() + dt*vx);
    p.setY(p.getY() + dt*vy);
    fillCircle(p.getX()*zoom,p.getY()*zoom,R,col);
}


// Fonctions de tracé

void Bille::traceBille() const {
    fillCircle(p.getX()*zoom,p.getY()*zoom,R,col);
}

void Bille::effaceBille() const {
    fillCircle(p.getX()*zoom,p.getY()*zoom,R,WHITE);
}


// Autres fonctions
double dist(Bille b1, Bille b2) {
    return sqrt((b1.getCoor().getX()-b2.getCoor().getX())*(b1.getCoor().getX()-b2.getCoor().getX()) + (b1.getCoor().getY()-b2.getCoor().getY())*(b1.getCoor().getY()-b2.getCoor().getY()));
}
