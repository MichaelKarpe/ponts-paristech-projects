#pragma once

#include "outils.h"

const int courbure=carre;

class Trajectoire
{
    std::vector<Point> t;

public:    

    Point pos;

    // Constructeur
    Trajectoire();

    // Assesseurs
    int size();
    Point &getPoint(int i);

    Point absplan(int abs) const;
    int abscurv(Point p) const;

    void trajectoire1();
    void trajectoire2();
    void trajectoire3();
    void traceTrajectoire();

    void billesRandom();
};

