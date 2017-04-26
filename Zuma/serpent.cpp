#include "serpent.h"

//Constructeurs

Serpent::Serpent()
{

}

void Serpent::SerpentAleatoire()
{ //Créer un serpent sous conditions en fonction des niveaux

}

//Destructeur

Serpent::~Serpent()
{

}


//Fusion de serpents

Serpent Serpent::fusionSerpents(Serpent serp2) {

}



//Fonctions du jeu

// Vitesse du serpent
void Serpent::vitesseEntree() {
    //Le serpent entre avec une vitesse très élevée (1/4 du parcours en 2s?)
    //puis prend ensuite une vitesse normale

}


void Serpent::vitesseDiminue() {
    //Diminue la vitesse lorsque le serpent s'approche de la fin
}


void Serpent::vitesseDestruction() {
    //Modifie la vitesse lorsqu'il y a destruction de billes
    //Détecte si combo ou non.
    //Si combo : appelle vitesseCombo
    //Sinon : appelle vitesseNulle
}

void Serpent::vitesseCombo() {
    //Vitesse négative pour la partie avant du serpent
}

void Serpent::vitesseNulle() {
    //Vitesse nulle pour la partie avant du serpent
}




