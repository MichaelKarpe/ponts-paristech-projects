#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

const int zoom = 5;
const int w = 240;
const int W = w*zoom;
const int h = 120;
const int H = h*zoom;
const int carre = 12;
const int r = 4;
const int R = r*zoom;
const int CARRE = carre*zoom;


class Point
{
public:
    int x,y;
    Point();
    Point(int ix, int iy);
};

void quadrillage();
