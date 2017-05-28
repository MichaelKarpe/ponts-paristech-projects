#include "grenouille.h"
#include "serpent.h"

#include <iostream>
using namespace std;
#include <numeric>

//Constructeurs

Grenouille::Grenouille(Trajectoire traj, Niveau Niv)
{
    pos = traj.pos;
    B1=Bille(pos,-1,1.0,Niv);
    B2=Bille(pos,-1,1.0,Niv);
}


// Assesseurs

Point Grenouille::getPos() const {
    return pos;
}

Bille Grenouille::getB1() const {
    return B1;
}

Bille Grenouille::getB2() const {
    return B2;
}

void Grenouille::setB1(Bille iB) {
    B1=iB;
}

void Grenouille::setB2(Bille iB) {
    B2=iB;
}


// Fonctions traitant les données

void Grenouille::tir(bool &finTir, double &vx, double &vy, Bille &Btir, vector<Serpent> &listSerp, Niveau Niv) {

    Event ev;
    getEvent(0,ev); //-1 pour clic plusieurs fois
    if (ev.type == EVT_BUT_ON) {
        if (finTir) {
            if (ev.button == 1) {
                // click gauche : Tir
                Point P;
                P.setX(ev.pix.x() - pos.getX()*zoom);
                P.setY(ev.pix.y() - pos.getY()*zoom);

                double costheta = P.getX()/sqrt(P.getX()*P.getX()+P.getY()*P.getY());
                double sintheta = P.getY()/sqrt(P.getX()*P.getX()+P.getY()*P.getY());

                Btir = B1;
                vx = costheta * Vtir;
                vy = sintheta * Vtir;

                finTir = false;
                creationBille(listSerp,Niv);
            }

            if (ev.button == 3) {
                // click droit : Changer la bille
                changeBille();
            }
        }

    }

    if (!finTir) {
        Btir.avanceTirBille(vx,vy);
    }

    // Si la bille sort de l'écran alors on peut tirer à nouveau

    if ((Btir.getCoor().getX()<-r || Btir.getCoor().getX()>w+r) || (Btir.getCoor().getY()<-r || Btir.getCoor().getY()>h+r)) {
        finTir = true;
        Btir.setCoor(Point(0,0));
    }
}

//Vérifier si cela fonctionne
Color verifieCouleurs(vector<Serpent> &listSerp, Niveau Niv) {
    //Empêcher le tir de couleurs qui ne sont plus présentes
    vector<int> colenjeu;
    for (int i=0;i<Niv.getNbCol();i++)
        colenjeu.push_back(0);
    bool finParcours = false;
    int Serp=0, bille=0;

    for (int i=0;i<listSerp.size();i++) {
        for (int j=0;j<listSerp[i].size();j++) {
            Color c = listSerp[i].getBille(j).getCol();
            for (int i=0;i<Niv.getNbCol();i++) {
                if (c==colors[i]) {
                    colenjeu[i]=1;
                    break;
                }
            }
            if (accumulate(colenjeu.begin(),colenjeu.end(),0)==Niv.getNbCol())
                return colors[rand()%Niv.getNbCol()];
        }
    }
    if (accumulate(colenjeu.begin(),colenjeu.end(),0)<Niv.getNbCol()) {
        while (true) {
            int aleat = rand()%Niv.getNbCol();
            if (colenjeu[aleat]==1)
                return colors[aleat];
        }
    }

    /*
    while (accumulate(colenjeu.begin(),colenjeu.end(),0)<nbCouleurs || finParcours) {

        Color c = listSerp[Serp].getBille(bille).getCol();
        for (int i=0;i<nbCouleurs;i++) {
            if (c==colors[i]) {
                colenjeu[i]=1;
                break;
            }
        }
        if (bille<listSerp[Serp].size()-1)
            bille++;
        else {
            if (Serp==listSerp.size()-1)
                finParcours = true;
            else {
                bille=0;
                Serp+1;
            }
        }
    }

    if (accumulate(colenjeu.begin(),colenjeu.end(),0)==nbCouleurs)
        return colors[rand()%nbCouleurs];
    else {
        while (true) {
            int aleat = rand()%nbCouleurs;
            if (colenjeu[aleat]==1)
                return colors[aleat];
        }
    }*/
}

void Grenouille::creationBille(vector<Serpent> &listSerp, Niveau Niv) {
    //Pour remplacer la 2e bille lorsque la 1e est tirée
    B1 = B2;
    B2 = Bille(pos, 0, 0,Niv);
    B2.setCol(verifieCouleurs(listSerp, Niv));
}

void Grenouille::changeBille() {
    //Si clic droit, échange de bille
    Bille B;
    B = B1;
    B1 = B2;
    B2 = B;
}

// Fonctions de tracé

void Grenouille::traceGrenouille() {
    fillCircle(pos.getX()*zoom,pos.getY()*zoom,carre*zoom,B2.getCol());
    fillCircle(pos.getX()*zoom,pos.getY()*zoom,R,B1.getCol()); //inverser B1 et B2?
    drawCircle(pos.getX()*zoom,pos.getY()*zoom,R,WHITE);
}
