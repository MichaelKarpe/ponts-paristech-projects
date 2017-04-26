#include "grenouille.h"

//Constructeurs

Grenouille::Grenouille()
{
    Bille b1, b2;
    g.push_back(b1);
    g.push_back(b2);

}


void Grenouille::traceGrenouille() {
    fillCircle(pos.x,pos.y,R,g[0].col);
    fillCircle(pos.x,pos.y,R/3,g[1].col);
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
