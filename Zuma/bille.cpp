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


void Bille::dessineBille(Point p) {
    fillCircle(p.x,p.y,r,col);
}

void Bille::setVitesse(double iv) {
    //Modifie la vitesse de la bille
}


void Bille::destructionBille() {

}
