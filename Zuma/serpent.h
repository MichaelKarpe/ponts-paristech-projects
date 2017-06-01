#pragma once

#include "bille.h"
//#include "trajectoire.h"

class Serpent
{
    std::vector<Bille> s; //Vecteur de billes

public:

    // Constructeurs et destructeur
    Serpent();
    Serpent(const Trajectoire &traj, const int &nbBilles, const Niveau &Niv);
    ~Serpent();

    //Assesseurs

    //Get
    int size() const;
    Bille getBille(const int &i) const;

    //Get et Set
    Bille &front();
    Bille &back();

    //Set
    void push(const Bille &b);
    void setVitSerp(const double &iv);
    void setAbsBille(const int &ibille, const int &iabs);
    void setCoorBille(const int &ibille, const Point &icoor);
    void setVitBille(const int &ibille, const double &ivit);


    // Méthodes modifiant la classe

    bool serpentFin(const Trajectoire &traj);
    bool serpentLoin(const Trajectoire &traj);

    void vitesseDiminue(const Trajectoire &traj);

    void insererBille(const Trajectoire &traj, const Bille &B, const int &j);
    int insererTir(const Trajectoire &traj, const Bille &B, bool &finTir);
    void destructionBilles(int &ind_combo, const int &i, const int &ind_list_serp, vector<Serpent> &listSerp);

    // Fonctions de tracé
    void traceSerpent(const Trajectoire &traj) const;
    void effaceSerpent(const Trajectoire &traj) const;
};

// Autres fonctions
void deplacementSerpents(const Trajectoire &traj, vector<Serpent> &listSerp);
void fusionSerpents(const Trajectoire &traj, int &ind_combo, vector<Serpent> &listSerp);
