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


// Fonctions pour tracer et effacer le serpent

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



//Fonctions du jeu

// Vitesse du serpent : pour l'instant abandonné, on considère que tout est à la même vitesse
void Serpent::vitesseEntree() {
    //Le serpent entre avec une vitesse très élevée (1/4 du parcours en 2s?)
    //puis prend ensuite une vitesse normale

}


void Serpent::vitesseDiminue(const Trajectoire &traj) {
    //Diminue la vitesse lorsque le serpent s'approche de la fin
    double nv = vDepart*(1.0-double(s.back().abs)/double(traj.t.size()))+1.0; //pour pas que vitesse nulle avant la fin
    for (int i=0;i<s.size();i++)
        s[i].v=nv;
}



void deplacementSerpents(const Trajectoire &traj, vector<Serpent> &listSerp) {

    /*int indtete=0, dstete=0;
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
    }*/

    double ds=listSerp[0].s[listSerp[0].s.size()-1].v*dt;

    for (int i=0;i<ds;i++) {
        noRefreshBegin();

        for (int j=0;j<listSerp.size();j++)
            listSerp[j].effaceSerpent(traj);

        for (int j=0;j<listSerp.size();j++) {
            for (int k=0;k<listSerp[j].s.size();k++) {
                listSerp[j].s[k].abs+=1;
                listSerp[j].s[k].p=traj.absplan(listSerp[j].s[k].abs);
            }
        }

        for (int j=0;j<listSerp.size();j++)
            listSerp[j].traceSerpent(traj);

        noRefreshEnd();

        milliSleep(50.0/ds); //milliSleep(50/dstete);
    }
}


//Fonction qui arrête le jeu si le serpent arrive à la fin
bool Serpent::serpentFin(const Trajectoire &traj) {
    return (s[s.size()-1].abs >= traj.t.size());
}

//Fonction qui envoie un serpent si le dernier serpent envoyé a bien avancé
bool Serpent::serpentLoin(const Trajectoire &traj) {
    return (s[s.size()-1].abs >= 1.0/6.0*traj.t.size());
}



//Fusion de serpents : pour l'instant inutile car tous à la même vitesse
Serpent Serpent::fusionSerpents(Serpent serp2) {

}


//Fonctions qui interviennent lors d'un tir de bille

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
