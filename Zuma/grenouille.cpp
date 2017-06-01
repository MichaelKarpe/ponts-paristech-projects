#include "grenouille.h"
#include "serpent.h"

#include <iostream>
using namespace std;
#include <numeric>

//Constructeurs

Grenouille::Grenouille(const Trajectoire &traj, const Niveau &Niv)
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

void Grenouille::setB1(const Bille &iB) {
    B1=iB;
}

void Grenouille::setB2(const Bille &iB) {
    B2=iB;
}


// Méthodes modifiant la classe

//changeBille : si clic droit, la bille de tir et la bille en réserve sont échangées
void Grenouille::changeBille() {
    Bille B;
    B = B1;
    B1 = B2;
    B2 = B;
}

//creationBille: : crée une nouvelle bille de réserve lorsqu'une bille est tirée
void Grenouille::creationBille(const vector<Serpent> &listSerp, const Niveau &Niv) {
    B1 = B2;
    B2 = Bille(pos, 0, 0, Niv);
    //On ajoute une couleur en vérifiant qu'elle soit encore présente dans les serpents
    B2.setCol(verifieCouleurs(listSerp, Niv));
}

//tir : tire dans la direction du clic gauche
void Grenouille::tir(bool &finTir, double &vx, double &vy, Bille &Btir, vector<Serpent> &listSerp, const Niveau &Niv) {
    Event ev;
    getEvent(0,ev); //-1 pour clic plusieurs fois
    if (ev.type == EVT_BUT_ON) {
        if (finTir) {
            //Si clic gauche : tir
            if (ev.button == 1) {
                //Calcul de la direction de tir
                Point P;
                P.setX(ev.pix.x() - pos.getX()*zoom);
                P.setY(ev.pix.y() - pos.getY()*zoom);

                double costheta = P.getX()/sqrt(P.getX()*P.getX()+P.getY()*P.getY());
                double sintheta = P.getY()/sqrt(P.getX()*P.getX()+P.getY()*P.getY());

                Btir = B1;
                vx = costheta * Vtir;
                vy = sintheta * Vtir;

                finTir = false;

                //On crée une nouvelle bille pour la grenouille
                creationBille(listSerp,Niv);
            }

            if (ev.button == 3) {
                // Si clic droit : changement de bille de tir
                changeBille();
            }
        }
    }

    //Si tir, on envoie la bille de tir
    if (!finTir) {
        Btir.avanceTirBille(vx,vy);
    }

    // Si la bille sort de l'écran alors on peut tirer à nouveau
    if ((Btir.getCoor().getX()<-r || Btir.getCoor().getX()>w+r) || (Btir.getCoor().getY()<-r || Btir.getCoor().getY()>h+r)) {
        finTir = true;
        Btir.setCoor(Point(0,0));
    }

    //On trace la grenouille avec les 2 billes
    traceGrenouille();
}

//verifieCouleurs : pour éviter que les billes fournies à la grenouille soient
//des billes dont la couleur n'est plus présente dans les serpents en jeu
Color verifieCouleurs(const vector<Serpent> &listSerp, const Niveau &Niv) {
    //Vecteur comprenant les couleurs présentes parmi les serpents en jeu
    vector<int> colenjeu;
    //On initiale avec une valeur 0 : les couleurs ne sont pas présentes
    for (int i=0;i<Niv.getNbCol();i++)
        colenjeu.push_back(0);
    bool finParcours = false;
    int Serp=0, bille=0;

    //Pour tous les serpents et pour toutes les billes de chaque serpent
    for (int i=0;i<listSerp.size();i++) {
        for (int j=0;j<listSerp[i].size();j++) {
            //On regarde la couleur de la bille et on marque la couleur comme présente
            Color c = listSerp[i].getBille(j).getCol();
            for (int i=0;i<Niv.getNbCol();i++) {
                if (c==colors[i]) {
                    colenjeu[i]=1;
                    break;
                }
            }
            //Si toutes les couleurs sont présentes, on renvoie une couleur aléatoire
            if (accumulate(colenjeu.begin(),colenjeu.end(),0)==Niv.getNbCol())
                return colors[rand()%Niv.getNbCol()];
        }
    }
    //Si on a tout parcouru et qu'une couleur n'est pas présente
    if (accumulate(colenjeu.begin(),colenjeu.end(),0)<Niv.getNbCol()) {
        //On renvoie une couleur parmi celles qui sont encore en jeu
        while (true) {
            int aleat = rand()%Niv.getNbCol();
            if (colenjeu[aleat]==1)
                return colors[aleat];
        }
    }
}


// Fonctions de tracé

//traceGrenouille : trace la grenouille qui tire les billes
void Grenouille::traceGrenouille() const {
    //Tracé de la bille de tir B1
    fillCircle(pos.getX()*zoom,pos.getY()*zoom,CARRE,B1.getCol());
    //Tracé de la bille de rechange B2
    fillCircle(pos.getX()*zoom,pos.getY()*zoom,R/2,B2.getCol());
    drawCircle(pos.getX()*zoom,pos.getY()*zoom,R/2,WHITE);
}
