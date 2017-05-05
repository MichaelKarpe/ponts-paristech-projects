#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;
#include <iostream>
using namespace std;

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

const double dt = 0.2;
const double vDepart = 5.0;
const double Vtir = 30.0;

class Point
{
    int x,y;
public:
    Point();
    Point(int ix, int iy);

    int getX() const ;
    int getY() const ;
    void setX(int ix);
    void setY(int iy);
};

void quadrillage();
