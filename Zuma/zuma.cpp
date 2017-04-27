// Imagine++ project
// Project:  Vide
// Author:   Michaël Karpe & Bastien Déchamps
// Date:     26/04/2017

#include <Imagine/Graphics.h>
#include <iostream>
#include <ctime>
using namespace std;
using namespace Imagine;

#include "serpent.h"

int main()
{

    //srand((unsigned int)time(0));

    Window Fenetre=openWindow(W,H);

    Grenouille G;
    G.traceGrenouille();
    quadrillage();

    Trajectoire traj;
    traj.trajectoire2();
    traj.traceTrajectoire();
    //traj.billesRandom();
    std::cout << traj.t.size() << std::endl;

    Serpent snake;
    for (int i=0;i<50;i++) {
        Bille b(Point(traj.t[2*r*i].x,traj.t[2*r*i].y),2*r*i,vd);
        snake.s.push_back(b);
    }
    snake.traceSerpent(traj);

    for (int i=0;i<380;i++) { //380 fait arriver juste avant la fin de traj2
        snake.vitesseDiminue(traj);
        snake.deplacementSerpent(traj);
    }


    endGraphics();
    return 0;
}
