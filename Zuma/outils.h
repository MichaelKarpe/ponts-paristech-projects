#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

const int w = 240;
const int h = 120;
const int r = 4;
const int carre = 12;

const int zoom = 5;
const int W = w*zoom;
const int H = h*zoom;
const int R = r*zoom;
const int CARRE = carre*zoom;

const int nbCouleurs = 4;
const Color colors[8] = {RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN, BLACK, Color(128,128,128)};

const double dt = 1.0;
const double vDepart = 4.0;

class Point
{
public:
    int x,y;
    Point();
    Point(int ix, int iy);
};

void quadrillage();
