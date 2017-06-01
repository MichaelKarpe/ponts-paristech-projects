#pragma once

#include <vector>
#include <ctime>
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <iostream>
using namespace std;
#include <numeric>


// Variables de traitement des données
const int w = 240; //Largeur fenêtre
const int h = 120; //Hauteur fenêtre
const int r = 4; //Rayon billes
const int carre = 12; //Unité de mesure pour la conception du jeu

// Variables de tracé
const int zoom = 5;
const int W = w*zoom;
const int H = h*zoom;
const int R = r*zoom;
const int CARRE = carre*zoom;

// Paramètres
const int nbBilles = 15; //Nombre de billes par serpent
const int nbCouleurs = 8;
const Color colors[nbCouleurs] = {RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN, Color(128,128,128), BLACK}; //Couleurs des billes

const int nbTraj = 2; //Nombre de trajectoires
const int nbVit = 1; //Nombre de niveaux de vitesse pour augmenter la difficulté de jeu
const int nbNiveaux = 5*nbVit*nbTraj;
const int nbSerpents = 3; //Nombre initial de serpents envoyés par niveau

//Régler les paramètres avant d'envoyer

const double dt = 0.05;      //Incrément de temps
const double vDepart = 5.0;    //Vitesse initiale des serpents
const double Vtir = 6000*dt; //Vitesse de tir (200 pour dt = 0.05)

const float newSerp = 10.0*4.0/float(nbBilles); //Paramètre pour envoyer un nouveau serpent

class Point
{
    int x,y;

public:

    // Constructeurs
    Point();
    Point(const int &ix, const int &iy);

    // Assesseurs

    //Get
    int getX() const;
    int getY() const;

    //Set
    void setX(const int &ix);
    void setY(const int &iy);
};

// Fonctions de tracé
void quadrillage();

// Affichage du menu
void menu();
