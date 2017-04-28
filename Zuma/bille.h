#pragma once

#include <vector>

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "outils.h"

class Bille
{
public:
    Color col;
    double v; //pas d'accélération pour l'instant
    Point p;
    int abs;

    Bille();
    Bille(Point ip, int iabs, double iv);
    ~Bille();

    void setVitesse(double iv);
    void destructionBille();
    void dessineBille();
};
