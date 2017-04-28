#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;
#include <iostream>
using namespace std;

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
    Serpent(const Trajectoire &traj, int nbBilles);
    ~Serpent();

    Serpent fusionSerpents(Serpent serp2);
    void vitesseEntree();
    void vitesseDiminue(const Trajectoire &traj);
    void vitesseDestruction();
    void vitesseCombo();
    void vitesseNulle();

    void traceSerpent(const Trajectoire &traj);
    void effaceSerpent(const Trajectoire &traj);

    void deplacementSerpent(const Trajectoire &traj);

    bool serpentFin(const Trajectoire &traj);

    bool serpentLoin(const Trajectoire &traj);
};

