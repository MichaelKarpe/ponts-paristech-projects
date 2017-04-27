#include "serpent.h"
#include "trajectoire.h"

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


void Serpent::traceSerpent(Trajectoire traj) {
    for (int i=0;i<s.size()-1;i++) {
        if (s[i].abs<traj.t.size()-1)
            fillCircle(s[i].p.x*zoom,s[i].p.y*zoom,R,s[i].col);
    }
}

void Serpent::effaceSerpent(Trajectoire traj) {
    for (int i=0;i<s.size()-1;i++) {
        if (s[i].abs<traj.t.size()-1)
            fillCircle(s[i].p.x*zoom,s[i].p.y*zoom,R,WHITE);
    }
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


void Serpent::vitesseDiminue(Trajectoire traj) {
    double nv = vd*(1-s.back().abs/traj.t.size())+1.0; //pour pas que vitesse nulle avant la fin
    for (int i=0;i<s.size()-1;i++)
        s[i].v=nv;
    //Diminue la vitesse lorsque le serpent s'approche de la fin
}

void Serpent::deplacementSerpent(Trajectoire traj) {
    int indtete=0, dstete=0;
    //effaceSerpent();

    for (int i=0;i<s.size()-1;i++) {
        int ds=s[i].v*dt;
        if (ds>0) {
            //s[i].abs+=ds;
            //s[i].p=traj.absplan(s[i].abs);
            indtete = i; //Affectations inutiles
            dstete = ds;
        }
        else //Sortie de boucle
            i=s.size();
    }

    for (int j=0;j<dstete;j++) {
        effaceSerpent(traj);
        //Il faudrait ajouter une fonction qui retrace la trajectoire
        //Mais ça lague trop
        for (int i=0;i<indtete+1;i++) {
            s[i].abs+=1;
            s[i].p=traj.absplan(s[i].abs);
        }
        traceSerpent(traj);
        milliSleep(5); //milliSleep(50/dstete);
    }

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




