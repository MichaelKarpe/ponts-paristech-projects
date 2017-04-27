#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "bille.h"
#include "trajectoire.h"

class Serpent
{
public:
    std::vector<Bille> s;

    //Variables utiles ?
    int nbBilles; // = s.size()
    Bille front, back; // = s.front(), = s.back()

    Serpent();
    void SerpentAleatoire();
    ~Serpent();

    Serpent fusionSerpents(Serpent serp2);
    void vitesseEntree();
    void vitesseDiminue(Trajectoire traj);
    void vitesseDestruction();
    void vitesseCombo();
    void vitesseNulle();

    void traceSerpent(Trajectoire traj);
    void effaceSerpent(Trajectoire traj);

    void deplacementSerpent(Trajectoire traj);
};

