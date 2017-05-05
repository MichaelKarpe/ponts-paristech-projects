#include "serpent.h"
#include "trajectoire.h"
#include "bille.h"

//Constructeurs

Serpent::Serpent()
{

}

Serpent::Serpent(const Trajectoire &traj, int nbBilles)
{
    for (int i=0;i<nbBilles;i++) {
        Bille b(Point(traj.t[2*r*i].getX(),traj.t[2*r*i].getY()),2*r*i,vDepart);
        s.push_back(b);
    }
}

//Destructeur

Serpent::~Serpent()
{

}

// Assesseurs

vector<Bille> Serpent::getSerp() {
    return s;
}

// Fonctions pour tracer et effacer le serpent

void Serpent::traceSerpent(const Trajectoire &traj) {
    for (int i=0;i<s.size();i++) {
        if (s[i].getAbs()<traj.t.size()-1)
            s[i].traceBille();
    }
}

void Serpent::effaceSerpent(const Trajectoire &traj) {
    for (int i=0;i<s.size();i++) {
        if (s[i].getAbs()<traj.t.size()-1)
            s[i].effaceBille();
    }
}

// Insérer une bille dans un serpent en position j

void Serpent::insererBille(const Trajectoire &traj, Bille &B, int j) {
    s.insert(s.begin()+j,B);
    s[j].setVit(s[j+1].getVit());
    s[j].setAbs(s[j+1].getAbs());
    for (int i=j;i<s.size();i++) {
        s[i].setCoor(traj.absplan(traj.abscurv(s[i].getCoor())+2*R));
        s[i].traceBille();
    }
}

// insérer la bille tirée dans le serpent (ne prend pas en cmopte les tris sur les ezxtrémités pour l'intant)
int Serpent::insererTir(const Trajectoire &traj , Bille &B, bool &finTir) {

    if (finTir) {
        return -1;
    }

    else {

        for (int i=1;i<s.size();i++) {
            if (dist(s[i-1],B) < 2*R) {

                if (dist(s[i],B) < 2*R) {
                    insererBille(traj,B,i);
                    return i;
                }

                else {
                    insererBille(traj,B,i-1);
                    return i-1;
                }

                finTir = true;

            }
        }
    }

}

//Fonctions du jeu

// Vitesse du serpent : pour l'instant abandonné, on considère que tout est à la même vitesse
void Serpent::vitesseEntree() {
    //Le serpent entre avec une vitesse très élevée (1/4 du parcours en 2s?)
    //puis prend ensuite une vitesse normale

}


void Serpent::vitesseDiminue(const Trajectoire &traj) {
    //Diminue la vitesse lorsque le serpent s'approche de la fin
    double nv = vDepart*(1.0-double(s.back().getAbs())/double(traj.t.size()))+1.0; //pour pas que vitesse nulle avant la fin
    for (int i=0;i<s.size();i++)
        if (s[i].getVit()!=0)
            s[i].setVit(nv);
}



void deplacementSerpents(const Trajectoire &traj, vector<Serpent> &listSerp) {
    for (int j=0;j<listSerp.size();j++) {
        noRefreshBegin();
        listSerp[j].effaceSerpent(traj);
        //double ds=listSerp[j].s[listSerp[j].s.size()-1].v*dt; //ou 0 si serpents à la même vitesse
        //cout << ds << endl;
        for (int k=0;k<listSerp[j].s.size();k++) {
            double ds=2*listSerp[j].s[k].getVit()*dt; //à modifier
            cout << ds << endl;
            if (ds>1) //problème lorsque ds < 1
                listSerp[j].s[k].setAbs(listSerp[j].s[k].getAbs()+ds);
            //else
                //listSerp[j].s[k].abs+=1;
            listSerp[j].s[k].setCoor(traj.absplan(listSerp[j].s[k].getAbs()));
        }
        listSerp[j].traceSerpent(traj);
        noRefreshEnd();
    }
}




//Fonction qui arrête le jeu si le serpent arrive à la fin
bool Serpent::serpentFin(const Trajectoire &traj) {
    return (s[s.size()-1].getAbs() >= traj.t.size());
}

//Fonction qui envoie un serpent si le dernier serpent envoyé a bien avancé
bool Serpent::serpentLoin(const Trajectoire &traj) {
    return (s[s.size()-1].getAbs() >= 1.0/6.0*traj.t.size());
}



//Fusion de serpents : pour l'instant inutile car tous à la même vitesse
void fusionSerpents(vector<Serpent> &listSerp) {
    for (int i=0;i<listSerp.size()-1;i++) {
        if (std::abs(listSerp[i].s[0].getAbs()-listSerp[i+1].s[listSerp[i+1].s.size()-1].getAbs())<=2*R) {
            for (int j=0;j<listSerp[i+1].s.size();j++) {
                listSerp[i+1].s[j].setVit(listSerp[i].s[0].getVit());
            }

            for (int j=0;j<listSerp[i].s.size();j++) {
                listSerp[i+1].s.push_back(listSerp[i].s[j]);
            }
            //listSerp[i].effaceSerpent();
            //listSerp[i+1].effaceSerpent();
            listSerp.erase(listSerp.begin()+i+1); // ?
            //listSerp[i].traceSerpent();
        }

    }
}
//Remplacer par front et back

void Serpent::destructionBilles(int &i) {
    Color colbille = s[i].getCol();
    int ig=0, id=0;
    while (s[i-1-ig].getCol()==colbille)
        ig+=1;
    while (s[i+1+id].getCol()==colbille)
        id+=1;
    if (id+ig+1 >= 3) {
        for (int j=i-id;j<i+id+1;j++)
            s[j].effaceBille();
        for (int j=i+id+1;j<s.size();j++)
            s[j].setVit(0.0);
        s.erase(s.begin()+i-ig,s.begin()+i+id+1); //Pk +1 ?
    }
}

void Serpent::vitesseNulle() {
    //Vitesse nulle pour la partie avant du serpent
}


//Fonctions qui interviennent lors d'un tir de bille

void Serpent::vitesseDestruction() {
    //Modifie la vitesse lorsqu'il y a destruction de billes
    //Détecte si combo ou non.
    //Si combo : appelle vitesseCombo
    //Sinon : appelle vitesseNulle

}

void Serpent::vitesseCombo() {
    //Vitesse négative pour la partie avant du serpent
}




