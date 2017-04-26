// Imagine++ project
// Project:  Vide
// Author:   Michaël Karpe & Bastien Déchamps
// Date:     26/04/2017

#include <Imagine/Graphics.h>
#include <iostream>
#include <ctime>
using namespace std;
using namespace Imagine;

#include "trajectoire.h"

int main()
{
    //srand((unsigned int)time(0));

    Window Fenetre=openWindow(W,H);

    Grenouille G;
    G.traceGrenouille();
    quadrillage();

    Trajectoire traj;
    traj.trajectoire1();
    traj.traceTrajectoire();
    traj.billesRandom();
    std::cout << traj.t.size() << std::endl;

    //Serpent snake;
    //for (int i=)
    //snake.s.

    endGraphics();
    return 0;
}
