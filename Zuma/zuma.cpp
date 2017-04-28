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
    cout << traj.t.size() << endl;

    vector<Serpent> listSerp;
    listSerp.push_back(Serpent(traj,20));

    for (int i=0;i<listSerp.size();i++)
        listSerp[i].traceSerpent(traj);

    bool serpentMort=false;

    //Le premier serpent est celui qui est le plus proche de la fin
    while (!(listSerp[0].s[listSerp[0].s.size()-1].abs >= traj.t.size())) {
        for (int i=0;i<listSerp.size();i++) {
            listSerp[i].vitesseDiminue(traj);
            deplacementSerpents(traj,listSerp);
            if (listSerp[listSerp.size()-1].serpentLoin(traj) || serpentMort) { //rajouter nbSerpents à envoyer
                listSerp.push_back(Serpent(traj,20));
            }
        }
    }

    //Hypothèse simplificatrice : tous la vitesse du plus lent

    endGraphics();
    return 0;
}
