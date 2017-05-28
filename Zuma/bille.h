#pragma once

#include <vector>

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "Niveau.h"

class Bille
{
    Color col;
    double v; //pas d'accélération pour l'instant
    Point p;
    int abs;

public:

    // Constructeurs et destructeur
    Bille();
    Bille(Point ip, int iabs, double iv, Niveau Niv);
    ~Bille();

    // Assesseurs
    Color getCol() const ;
    double getVit() const ;
    Point &getCoor();
    int getAbs() const ;

    void setCol(Color icol);
    void setVit(double iv);
    void setCoor(Point ip);
    void setAbs(double iabs);

    // Fonctions traitant les données
    void avanceTirBille(double vx, double vy);

    // Fonctions de tracé
    void traceBille();
    void effaceBille();
};

// Autres fonctions
double dist(Bille b1, Bille b2);
