#pragma once

#include <vector>

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "outils.h"

const int r = 50;
const Color colors[8] = {RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN, BLACK, Color(128,128,128)};

const double dt = 0.01;

class Bille
{
public:
    Color col;
    double v; //pas d'accélération pour l'instant
    Point p;

    Bille();
    ~Bille();

    void setVitesse(double iv);
    void destructionBille();
};
