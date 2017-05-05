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

    // Paramètres servant pour le tir
    bool finTir = true;
    double vx;
    double vy;
    Bille Btir(G.getPos(),0,0);

    //Le premier serpent est celui qui est le plus proche de la fin
    while (!(listSerp[0].getSerp()[listSerp[0].getSerp().size()-1].getAbs() >= traj.t.size())) {

        for (int i=0;i<listSerp.size();i++) {
            listSerp[i].vitesseDiminue(traj);
            int I = listSerp[i].insererTir(traj,Btir,finTir);
        }

        for (int i=0; i<listSerp[0].getSerp().size();i++)
            cout << listSerp[0].getSerp()[i].getVit() << endl;

        deplacementSerpents(traj,listSerp);

        if (listSerp[listSerp.size()-1].serpentLoin(traj) || serpentMort) //rajouter nbSerpents à envoyer
            listSerp.push_back(Serpent(traj,20));

        milliSleep(10);

        //for (int i=0;i<listSerp.size();i++)
        //    listSerp[i].effaceSerpent(traj);

        fusionSerpents(listSerp);

        //for (int i=0;i<listSerp.size();i++)
        //    listSerp[i].traceSerpent(traj);

        //for (int i=0;i<listSerp[0].s.size();i++)
            //listSerp[0].destructionBilles(i);

        // Tir de la grenouille
        G.tir(finTir,vx,vy,Btir);
        G.traceGrenouille();


        // Fusion avec les serpent : fonction inserer bille a completer
        /*
        if (!finTir) {
            for (int i=0;i<listSerp.size()-1;i++) {
                for (int j=1;j<listSerp[i].nbBilles-1;j++) {
                    if (dist(Btir.p,listSerp[i].s[j].p) < 2*R && dist(Btir.p,listSerp[i].s[j-1].p) < 2*R) {
                        listSerp[i].insererBille(traj,Btir,j-1);
                        finTir = true;
                    }
                    else {
                        listSerp[i].insererBille(traj,Btir,j);
                        finTir = true;
                    }
                }
            }
        }
        */

    }

    //Hypothèse simplificatrice : tous la vitesse du plus lent
    endGraphics();
    return 0;
}
