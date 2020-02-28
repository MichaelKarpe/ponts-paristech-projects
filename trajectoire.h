#pragma once

#include "outils.h"

const int courbure=carre;

class Trajectoire
{
    std::vector<Point> t;  //Vecteur de points

public:    

    Point pos;  //à passer en private

    // Constructeur
    Trajectoire();

    // Assesseurs

    //Get
    int size() const;
    Point getPoint(const int &i) const;
    Point absplan(const int &abs) const;
    int abscurv(const Point &p) const;

    //Set
    void trajectoire1();
    void trajectoire2();

    //Fonctions de tracé
    void traceTrajectoire() const;
};

