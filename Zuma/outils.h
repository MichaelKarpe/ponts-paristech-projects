#pragma once

#include <vector>
#include <ctime>
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <iostream>
using namespace std;
#include <numeric>

// Variables de traitement des données
const int w = 240;
const int h = 120;
const int r = 4;
const int carre = 12;

// Variables de tracé
const int zoom = 5;
const int W = w*zoom;
const int H = h*zoom;
const int R = r*zoom;
const int CARRE = carre*zoom;

// Paramètres
const int nbBilles = 15;
const int nbCouleurs = 4;
const Color colors[8] = {RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN, BLACK, Color(128,128,128)};

const double dt = 0.1;      //Modifier tous ces pas de temps!
const double vDepart = 0.5;    //Level hardcore : vDepart = 20, dt = 1 !
const double Vtir = 50.0;


class Point
{
    int x,y;
public:

    // Constructeurs
    Point();
    Point(int ix, int iy);

    // Assesseurs
    int getX() const ;
    int getY() const ;
    void setX(int ix);
    void setY(int iy);
};

// Fonctions de tracé
void quadrillage();
