#pragma once

//#include "trajectoire.h"
#include "serpent.h"

class Grenouille
{
    Bille B1, B2;   // B1 bille de tir, B2 bille de rechange
    Point pos;      // Position de la grenouille

public:

    // Constructeur
    Grenouille(const Trajectoire &traj, const Niveau &Niv);

    // Assesseurs

    // Get
    Point getPos() const;
    Bille getB1() const;
    Bille getB2() const;

    // Set
    void setB1(const Bille &iB);
    void setB2(const Bille &iB);

    // Méthodes modifiant la classe
    void changeBille();
    void creationBille(const vector<Serpent> &listSerp, const Niveau &Niv);
    void tir(bool &finTir, double &vx, double &vy, Bille &Btir, vector<Serpent> &listSerp, const Niveau &Niv);

    // Fonctions de tracé
    void traceGrenouille() const;
};

// Autres fonctions
Color verifieCouleurs(const vector<Serpent> &listSerp, const Niveau &Niv);
