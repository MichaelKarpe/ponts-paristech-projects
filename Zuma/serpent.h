#pragma once

#include "bille.h"
#include "trajectoire.h"

class Serpent
{
    std::vector<Bille> s;

public:

    //Assesseurs
    int size();
    Bille &getBille(int i);
    void push(Bille b);
    Bille &front();
    Bille &back();

    // Constructeurs et destructeur
    Serpent();
    Serpent(Trajectoire &traj, int nbBilles);
    ~Serpent();


    // Fonctions traitant les données

    //void fusionSerpents(vector<Serpent> &listSerp);
    void vitesseEntree();
    void vitesseDiminue(Trajectoire &traj);

    bool serpentFin(Trajectoire &traj);
    bool serpentLoin(Trajectoire &traj);

    void insererBille(const Trajectoire &traj, Bille &B, int j);
    int insererTir(const Trajectoire &traj , Bille &B, bool &finTir);
    void destructionBilles(int &i);

    void vitesseNulle();
    void vitesseDestruction();
    void vitesseCombo();

    // Fonctions de tracé
    void traceSerpent(Trajectoire traj);
    void effaceSerpent(Trajectoire traj);
};

// Autres fonctions
void deplacementSerpents(Trajectoire &traj, vector<Serpent> &listSerp);
void fusionSerpents(vector<Serpent> &listSerp, Trajectoire &traj);
