#pragma once

#include "trajectoire.h"
#include "serpent.h"

class Grenouille
{
    Bille B1,B2; //On tire B1, B2 en attente
    Point pos;//=Point(w/2,h/2);

public:

    // Constructeur
    Grenouille(Trajectoire traj,Niveau Niv);

    //Assesseurs inutiles (sauf getPos) ?
    Point getPos() const;
    Bille getB1() const;
    Bille getB2() const;
    void setB1(Bille iB);
    void setB2(Bille iB);

    // Fonctions traitant les données
    void tir(bool &finTir, double &vx, double &vy, Bille &Btir, vector<Serpent> &listSerp, Niveau Niv);
    void changeBille();
    void creationBille(vector<Serpent> &listSerp,Niveau Niv);

    // Fonctions de tracé
    void traceGrenouille();
};


Color verifieCouleurs(vector<Serpent> &listSerp);
