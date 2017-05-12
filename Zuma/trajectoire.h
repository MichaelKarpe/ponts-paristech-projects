#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "grenouille.h"
#include "outils.h"

const int courbure=carre;

class Trajectoire
{
    std::vector<Point> t;
public:    

    // Constructeur
    Trajectoire();

    // Assesseurs
    int size();
    vector<Point> getTraj();
    Point getPoint(int i);

    Point absplan(int abs) const;
    int abscurv(Point p) const;

    void trajectoire1();
    void trajectoire2();
    void traceTrajectoire();

    void billesRandom();
};

