#include "serpent.h"
#include "trajectoire.h"

//Constructeurs

Serpent::Serpent()
{

}

Serpent::Serpent(const Trajectoire &traj, int nbBilles)
{
    for (int i=0;i<nbBilles;i++) {
        Bille b(Point(traj.t[2*r*i].x,traj.t[2*r*i].y),2*r*i,vDepart);
        s.push_back(b);
    }
}

//Destructeur

Serpent::~Serpent()
{

}


void Serpent::traceSerpent(const Trajectoire &traj) {
    for (int i=0;i<s.size()-1;i++) {
        if (s[i].abs<traj.t.size()-1)
            fillCircle(s[i].p.x*zoom,s[i].p.y*zoom,R,s[i].col);
    }
}

void Serpent::effaceSerpent(const Trajectoire &traj) {
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


void Serpent::vitesseDiminue(const Trajectoire &traj) {
    double nv = vDepart*(1.0-double(s.back().abs)/double(traj.t.size()))+1.0; //pour pas que vitesse nulle avant la fin
    //cout << nv << endl;
    for (int i=0;i<s.size();i++)
        s[i].v=nv;
    //Diminue la vitesse lorsque le serpent s'approche de la fin
}

void Serpent::deplacementSerpent(const Trajectoire &traj) {
    int indtete=0, dstete=0;
    //effaceSerpent();
    double ds=s[s.size()-1].v*dt;
    /*for (int i=0;i<s.size()-1;i++) {
        int ds=s[i].v*dt;
        if (ds>0) {
            //s[i].abs+=ds;
            //s[i].p=traj.absplan(s[i].abs);
            indtete = i; //Affectations inutiles
            dstete = ds;
        }
        else //Sortie de boucle
            i=s.size();
    }*/

    for (int j=0;j<ds;j++) {
        noRefreshBegin();
        effaceSerpent(traj);
        //traj.traceTrajectoire();
        //Il faudrait ajouter une fonction qui retrace la trajectoire
        //Mais ça lague trop
        //cout << indtete << endl;
        for (int i=0;i<s.size();i++) {
            s[i].abs+=1;
            s[i].p=traj.absplan(s[i].abs);
        }
        traceSerpent(traj);
        noRefreshEnd();
        //cout << dstete << endl;
        milliSleep(50.0/ds); //milliSleep(50/dstete);
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

bool Serpent::serpentFin(const Trajectoire &traj) {
    return (s[s.size()-1].abs >= traj.t.size());
}

bool Serpent::serpentLoin(const Trajectoire &traj) {
    return (s[s.size()-1].abs >= 1.0/6.0*traj.t.size());
}

