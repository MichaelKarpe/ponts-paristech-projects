#include "niveau.h"


int Niveau::getNbCol() {
    return nbCol;
}

Trajectoire Niveau::getTraj() {
    return Traj;
}

void Niveau::setNbCol(int i) {
    nbCol = i;
}

void Niveau::setTraj(Trajectoire traj) {
    Traj = traj;
}
