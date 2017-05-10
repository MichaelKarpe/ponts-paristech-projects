// Imagine++ project
// Project:  Vide
// Author:   Michaël Karpe & Bastien Déchamps
// Date:     10/05/2017

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
    //quadrillage();

    Trajectoire traj;
    traj.trajectoire2();
    traj.traceTrajectoire();
    //traj.billesRandom();
    cout << traj.size() << endl;

    vector<Serpent> listSerp;
    listSerp.push_back(Serpent(traj,nbBilles));

    for (int i=0;i<listSerp.size();i++)
        listSerp[i].traceSerpent(traj);

    bool serpentMort=false;

    // Paramètres servant pour le tir
    bool finTir = true;
    double vx;
    double vy;
    Bille Btir(G.getPos(),0,0);

    //Le premier serpent est celui qui est le plus proche de la fin
    while (!(listSerp[0].getSerp()[listSerp[0].getSerp().size()-1].getAbs() >= traj.size())) {

        //Diminution de la vitesse
        for (int i=0;i<listSerp.size();i++)
            listSerp[i].vitesseDiminue(traj);

        //Déplacement des serpents
        deplacementSerpents(traj,listSerp);

        //Fusion des serpents
        fusionSerpents(listSerp, traj);

        //Tir de la grenouille
        G.tir(finTir,vx,vy,Btir);
        G.traceGrenouille();

        //Insertion du tir
        for (int i=0;i<listSerp.size();i++)
            int I = listSerp[i].insererTir(traj,Btir,finTir);

        //Arrivée d'un nouveau serpent
        if (listSerp[listSerp.size()-1].serpentLoin(traj) && listSerp[listSerp.size()-1].getSerp()[0].getAbs()>2*r*(nbBilles+5) || serpentMort) //rajouter nbSerpents à envoyer
            listSerp.push_back(Serpent(traj,nbBilles));

        //Pause pour affichage
        milliSleep(10); //Aussi à régler, le + petit possible, 10ms minimum sinon bug

    }

    //Hypothèse simplificatrice : tous la vitesse du plus lent, mais pas utilisée pour le moment
    endGraphics();
    return 0;
}
