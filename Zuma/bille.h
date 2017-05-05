#pragma once

#include <vector>

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "outils.h"

class Bille
{
    Color col;
    double v; //pas d'accélération pour l'instant
    Point p;
    int abs;
public:
    // Assesseurs

    Color getCol() const ;
    double getVit() const ;
    Point getCoor() const ;
    int getAbs() const ;

    void setCol(Color icol);
    void setVit(double iv);
    void setCoor(Point ip);
    void setAbs(double iabs);


    Bille();
    Bille(Point ip, int iabs, double iv);
    ~Bille();

    void setVitesse(double iv);
    void effaceBille();
    void traceBille();
    void avanceTirBille(double vx, double vy);
};

double dist(Bille b1, Bille b2);
