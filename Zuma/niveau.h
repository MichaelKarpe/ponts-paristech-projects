#pragma once

#include "trajectoire.h"



class Niveau {
    int nbCol;
    Trajectoire Traj;
public:
    int getNbCol();
    Trajectoire getTraj();
    void setNbCol(int i);
    void setTraj(Trajectoire traj);
};

