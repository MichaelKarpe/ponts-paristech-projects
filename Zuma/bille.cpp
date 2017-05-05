#include "bille.h"

//Constructeurs

Bille::Bille() {

}

Bille::Bille(Point ip, int iabs, double iv)
{
    col=colors[rand()%nbCouleurs];
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

void Bille::setCol(Color icol) {
    col = icol;
}

void Bille::setVit(double iv) {
    v = iv;
}

void Bille::setCoor(Point ip) {
    p = ip;
}

void Bille::setAbs(double iabs) {
    abs = iabs;
}


// Fonctions

void Bille::avanceTirBille(double vx, double vy) {
    fillCircle(p.getX()*zoom,p.getY()*zoom,R,WHITE);
    p.setX(p.getX() + dt*vx);
    p.setY(p.getY() + dt*vy);
    fillCircle(p.getX()*zoom,p.getY()*zoom,R,col);

}

void Bille::traceBille() {
    fillCircle(p.getX()*zoom,p.getY()*zoom,R,col);
}

void Bille::effaceBille() {
    fillCircle(p.getX()*zoom,p.getY()*zoom,R,WHITE);
}

double dist(Bille b1, Bille b2) {
    return sqrt((b1.getCoor().getX()-b2.getCoor().getX())*(b1.getCoor().getX()-b2.getCoor().getX()) + (b1.getCoor().getY()-b2.getCoor().getY())*(b1.getCoor().getY()-b2.getCoor().getY()));
}
