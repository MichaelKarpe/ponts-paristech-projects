#include "bille.h"

//Constructeurs

Bille::Bille()
{
    col=colors[rand()%8];
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
