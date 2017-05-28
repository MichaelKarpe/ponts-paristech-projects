#include "niveau.h"

Niveau::Niveau(int ind_traj, int nbCoul) {
    assert(ind_traj<4 && ind_traj>0 && nbCoul>3 && nbCoul<9);
    nbCol = nbCoul;
    if (ind_traj == 1)
        Traj.trajectoire1();
    else if (ind_traj == 2)
        Traj.trajectoire2();
    else
        Traj.trajectoire3();
}

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
