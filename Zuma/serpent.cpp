#include "serpent.h"
#include "trajectoire.h"
#include "bille.h"

//Constructeurs

Serpent::Serpent()
{

}

Serpent::Serpent(Trajectoire &traj, int nbBilles)
{
    for (int i=0;i<nbBilles;i++) {
        Bille b(Point(traj.getPoint(2*r*i).getX(),traj.getPoint(2*r*i).getY()),2*r*i,vDepart);
        s.push_back(b);
    }
}

//Destructeur

Serpent::~Serpent()
{

}


// Assesseurs

int Serpent::size() {
    return s.size();
}

Bille &Serpent::getBille(int i) {
    return s[i];
}

void Serpent::push(Bille b) {
    s.push_back(b);
}

// Fonctions traitant les données

// Vitesse du serpent : pour l'instant abandonné, on considère que tout est à la même vitesse
void Serpent::vitesseEntree() {
    //Le serpent entre avec une vitesse très élevée (1/4 du parcours en 2s?)
    //puis prend ensuite une vitesse normale

}

void Serpent::vitesseDiminue(Trajectoire &traj) {
    //Diminue la vitesse lorsque le serpent s'approche de la fin
    double nv = vDepart*(1.0-double(s.back().getAbs())/double(traj.size()))+1/dt; //pour pas que vitesse nulle avant la fin car ds > 1
    for (int i=0;i<s.size();i++) {
        if (s[i].getVit()!=0)
            s[i].setVit(nv);
    }
}


void deplacementSerpents(Trajectoire &traj, vector<Serpent> &listSerp) {
    for (int j=0;j<listSerp.size();j++) {
        noRefreshBegin();
        listSerp[j].effaceSerpent(traj);
        for (int k=0;k<listSerp[j].size();k++) {
            double ds=listSerp[j].getBille(k).getVit()*dt; //à modifier ds = v*dt > 1
            //cout << ds << endl;
            if (ds>1) //problème lorsque ds < 1
                listSerp[j].getBille(k).setAbs(listSerp[j].getBille(k).getAbs()+ds);
            //else
                //listSerp[j].s[k].abs+=1;
            listSerp[j].getBille(k).setCoor(traj.absplan(listSerp[j].getBille(k).getAbs()));
        }
        listSerp[j].traceSerpent(traj);
        noRefreshEnd();
    }
}

//Fonctionne si la tête du serpent entrant ne dépasse pas la queue du dernier serpent
//Fusion de serpents : pour l'instant inutile car tous à la même vitesse
void fusionSerpents(vector<Serpent> &listSerp, Trajectoire &traj) {
    for (int i=0;i<listSerp.size()-1;i++) {
        if (std::abs(listSerp[i].getBille(0).getAbs()-listSerp[i+1].getBille(listSerp[i+1].size()-1).getAbs())<=2*r) {
            for (int j=0;j<listSerp[i+1].size();j++) {
                listSerp[i+1].getBille(j).setVit(listSerp[i].getBille(0).getVit());
            }

            for (int j=0;j<listSerp[i].size();j++) {
                listSerp[i+1].push(listSerp[i].getBille(j));
            }
            listSerp[i+1].effaceSerpent(traj);
            listSerp.erase(listSerp.begin()+i); //Vérifier les indices, normalement OK
            listSerp[i].traceSerpent(traj);
        }

    }
}


//Fonction qui arrête le jeu si le serpent arrive à la fin
bool Serpent::serpentFin(Trajectoire &traj) {
    return (s[s.size()-1].getAbs() >= traj.size());
}

//Fonction qui envoie un serpent si le dernier serpent envoyé a bien avancé
bool Serpent::serpentLoin(Trajectoire &traj) {
    return (s[s.size()-1].getAbs() >= 1.0/6.0*traj.size());
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
    if (finTir)
        return -1;
    else {
        for (int i=1;i<s.size();i++) {
            if (dist(s[i-1],B) < 2*r) {
                if (dist(s[i],B) < 2*r) {
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



// Fonctions de tracé

void Serpent::traceSerpent(Trajectoire &traj) {
    for (int i=0;i<s.size();i++) {
        if (s[i].getAbs()<traj.size()-1)
            s[i].traceBille();
    }
}

void Serpent::effaceSerpent(Trajectoire &traj) {
    for (int i=0;i<s.size();i++) {
        if (s[i].getAbs()<traj.size()-1)
            s[i].effaceBille();
    }
}



