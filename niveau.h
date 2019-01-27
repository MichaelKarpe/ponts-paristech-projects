#pragma once

#include "trajectoire.h"

class Niveau {
    int nbCol;          //Nombre de couleurs
    Trajectoire Traj;   //Trajectoire

public:

    // Constructeur
    Niveau(const int &ind_traj, const int &nbCoul);

    // Assesseurs

    // Get
    int getNbCol() const;
    Trajectoire getTraj() const;

    // Set
    void setNbCol(const int &i);
    void setTraj(const Trajectoire &traj);
};

