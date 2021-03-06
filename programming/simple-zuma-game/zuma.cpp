// Imagine++ project
// Project:  Zuma
// Author:   Michaël Karpe & Bastien Déchamps
// Date:     02/06/2017

// ATTENTION ! remplacer \ par / dans les srcpth (imagine\...) et faire attention au maj min dans les noms de fichier (Cmakelists...)

#include "grenouille.h"

int main()
{
    Window Fenetre = openWindow(W, H, "Test Event");
    while (true) {
        // Menu
        menu();

         for (int i_col = 4; i_col <= nbCouleurs; i_col++) {
            for (int i_traj = 1 ; i_traj <= nbTraj; i_traj++) {

                // Initialisation
                srand((unsigned int)time(0));
                Niveau Niv(i_traj, i_col);
                Trajectoire traj = Niv.getTraj();
                Grenouille G(traj, Niv);
                vector<Serpent> listSerp;
                listSerp.push_back(Serpent(traj, nbBilles, Niv));
                int serpEnvoyes = 1;
                bool finNiveau = false;

                // Tracés initiaux
                traj.traceTrajectoire();
                G.traceGrenouille();
                for (int i = 0;i < listSerp.size(); i++)
                    listSerp[i].traceSerpent(traj);

                // Initialisation des paramètres de tir
                bool finTir = true;
                int ind_combo = -1;
                double vx, vy;
                Bille Btir(G.getPos(), 0, 0, Niv);

                // Tant que la tête du 1er serpent n'atteint pas la fin de la trajectoire
                while (!(listSerp.front().back().getAbs() >= traj.size()) && !finNiveau) {
                    noRefreshBegin();

                    // On retrace la trajectoire à chaque fois
                    traj.traceTrajectoire();

                    // Diminution de la vitesse des serpents
                    for (int i = 0;i < listSerp.size(); i++)
                        listSerp[i].vitesseDiminue(traj);

                    // Déplacement des serpents
                    deplacementSerpents(traj, listSerp);

                    // Fusion des serpents s'ils se touchent
                    fusionSerpents(traj, ind_combo, listSerp);

                    // Tir et tracé de la grenouille
                    G.tir(finTir, vx, vy, Btir, listSerp, Niv);

                    // Insertion du tir en indice I (s'il existe)
                    for (int i = 0; i < listSerp.size(); i++) {
                        int I = listSerp[i].insererTir(traj, Btir, finTir);
                        listSerp[i].destructionBilles(ind_combo, I, i, listSerp);
                    }

                    if (serpEnvoyes < nbSerpents) {
                        if (listSerp.size() > 0) {
                            if (listSerp.back().serpentLoin(traj) && listSerp.back().front().getAbs() > 2 * r * (nbBilles + 5)) {
                                listSerp.push_back(Serpent(traj, nbBilles, Niv));
                                serpEnvoyes += 1;
                            }
                        }
                        if (listSerp.size() == 0) {
                            listSerp.push_back(Serpent(traj, nbBilles, Niv));
                            serpEnvoyes += 1;
                        }
                    }

                    if (serpEnvoyes == nbSerpents && listSerp.size() == 0)
                        finNiveau = true;

                    noRefreshEnd();

                    // Pause pour affichage
                    milliSleep(20); // Le + petit possible, 10ms minimum sinon bug
                }

                // Le niveau est terminé, on nettoie la fenêtre
                clearWindow();

                // Si le niveau a été réussi, message de félicitations
                if (finNiveau == true) {
                    pageGagne();
                }
                // Sinon, terminaison de la double boucle et message de défaite
                else {
                    i_traj = nbTraj + 1;
                    i_col = nbCouleurs + 1;
                    pagePerdu();
                }

                // Passage au niveau suivant si victoire ou fermeture de la fenêtre si défaite
                clearWindow();

            }
        }
    }
    endGraphics();
    return 0;
}
