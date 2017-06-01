#include "niveau.h"

Niveau::Niveau(const int &ind_traj, const int &nbCoul) {
    assert(ind_traj<=nbTraj && ind_traj>0 && nbCoul>=4 && nbCoul<=nbCouleurs);
    nbCol = nbCoul;
    if (ind_traj == 1)
        Traj.trajectoire1();
    else if (ind_traj == 2)
        Traj.trajectoire2();
}

int Niveau::getNbCol() const {
    return nbCol;
}

Trajectoire Niveau::getTraj() const {
    return Traj;
}

void Niveau::setNbCol(const int &i) {
    nbCol = i;
}

void Niveau::setTraj(const Trajectoire &traj) {
    Traj = traj;
}
