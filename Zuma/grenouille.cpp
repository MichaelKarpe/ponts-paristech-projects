#include "grenouille.h"

//Constructeurs

Grenouille::Grenouille()
{
    Bille b1(Point(w/2,h/2),-1,1.0), b2(Point(w/2,h/2),-1,1.0);
    g.push_back(b1);
    g.push_back(b2);

}


void Grenouille::traceGrenouille() {
    fillCircle(pos.x*zoom,pos.y*zoom,carre*zoom,g[0].col);
    fillCircle(pos.x*zoom,pos.y*zoom,carre*zoom/3,g[1].col);
}


//Fonction de tir
void Grenouille::tir() {
    //Si clic gauche, beaucoup de choses à faire!
}


void Grenouille::changeBille() {
    //Si clic droit, échange de bille
}

void Grenouille::creationBille() {
    //Pour remplacer la 2e bille lorsque la 1e est tirée
}

void Grenouille::verifieCouleurs() {
    //Empêcher le tir de couleurs qui ne sont plus présentes
}
