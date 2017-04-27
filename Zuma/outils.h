#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

const int zoom = 1;
const int w = 240*5;
const int W = w*zoom;
const int h = 120*5;
const int H = h*zoom;
const int carre = 12*5;
const int r = 4*5;
const int R = r*zoom;
const int CARRE = carre*zoom;

const double vd = 20.0;

const Color colors[8] = {RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN, BLACK, Color(128,128,128)};

const double dt = 1.0;

class Point
{
public:
    int x,y;
    Point();
    Point(int ix, int iy);
};

void quadrillage();
