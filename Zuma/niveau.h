#pragma once

#include "trajectoire.h"

class Niveau {
    int nbCol;
    Trajectoire Traj;

public:

    Niveau(int ind_traj, int nbCoul);
    int getNbCol();
    Trajectoire getTraj();
    void setNbCol(int i);
    void setTraj(Trajectoire traj);
};

