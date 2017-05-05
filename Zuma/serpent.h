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
    vector<Bille> getSerp();

    //Variables utiles ?
    int nbBilles; // = s.size()
    Bille front, back; // = s.front(), = s.back()

    Serpent();
    Serpent(const Trajectoire &traj, int nbBilles);
    ~Serpent();

    //void fusionSerpents(vector<Serpent> &listSerp);
    void vitesseEntree();
    void vitesseDiminue(const Trajectoire &traj);
    void vitesseDestruction();
    void vitesseCombo();
    void vitesseNulle();

    void insererBille(const Trajectoire &traj, Bille &B, int j);
    int insererTir(const Trajectoire &traj , Bille &B, bool &finTir);

    void traceSerpent(const Trajectoire &traj);
    void effaceSerpent(const Trajectoire &traj);

    bool serpentFin(const Trajectoire &traj);

    bool serpentLoin(const Trajectoire &traj);

    void destructionBilles(int &i);
};

void deplacementSerpents(const Trajectoire &traj, vector<Serpent> &listSerp);
void fusionSerpents(vector<Serpent> &listSerp);
