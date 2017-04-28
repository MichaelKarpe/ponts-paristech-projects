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

    std::vector<Serpent> listSerp;
    listSerp.push_back(Serpent(traj,20));

    for (int i=0;i<listSerp.size();i++)
        listSerp[i].traceSerpent(traj);

    bool serpentMort=false;

    //Le premier serpent est celui qui est le plus proche de la fin
    while (!(listSerp[0].s[listSerp[0].s.size()-1].abs >= traj.t.size())) {
        for (int i=0;i<listSerp.size();i++) {
            listSerp[i].vitesseDiminue(traj);
            listSerp[i].deplacementSerpent(traj);
            if (listSerp[listSerp.size()-1].serpentLoin(traj) || serpentMort) {
                listSerp.push_back(Serpent(traj,20));
            }
        }
    }

    //Hypothèse simplificatrice : tous la vitesse du plus lent

    endGraphics();
    return 0;
}
