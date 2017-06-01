#pragma once

#include <vector>

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "niveau.h"

class Bille
{
    Color col; //Couleur
    double v; //Vitesse
    Point p; //Position
    int abs; //Abscisse curviligne (sur la trajectoire)

public:

    // Constructeurs et destructeur
    Bille();
    Bille(const Point &ip, const int &iabs, const double &iv, const Niveau &Niv);
    ~Bille();

    // Assesseurs

    //Get
    Color getCol() const ;
    double getVit() const ;
    Point getCoor() const;
    int getAbs() const ;

    //Set
    void setCol(const Color &icol);
    void setVit(const double &iv);
    void setCoor(const Point &ip);
    void setAbs(const int &iabs);

    // Méthodes modifiant la classe
    void avanceTirBille(const double &vx, const double &vy);

    // Fonctions de tracé
    void traceBille() const;
    void effaceBille() const;
};

// Autres fonctions
double dist(const Bille b1, const Bille b2);
