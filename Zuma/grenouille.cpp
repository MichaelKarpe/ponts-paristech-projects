#include "grenouille.h"

//Constructeurs

Grenouille::Grenouille()
{
    B1=Bille(Point(w/2,h/2),-1,1.0);
    B2=Bille(Point(w/2,h/2),-1,1.0);
}


void Grenouille::traceGrenouille() {
    fillCircle(pos.getX()*zoom,pos.getY()*zoom,carre*zoom,B2.getCol());
    fillCircle(pos.getX()*zoom,pos.getY()*zoom,R,B1.getCol());
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


// Fonctions

void Grenouille::tir(bool &finTir, double &vx, double &vy, Bille &Btir) {

    Event ev;
    getEvent(0,ev);
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
                creationBille();
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

    if ((Btir.getCoor().getX()<-R || Btir.getCoor().getX()>W+R) || (Btir.getCoor().getY()<-R || Btir.getCoor().getY()>H+R)) {
        finTir = true;
        Btir.setCoor(Point(0,0));
    }
}




void Grenouille::changeBille() {
    //Si clic droit, échange de bille
    Bille B;
    B = B1;
    B1 = B2;
    B2 = B;

}

void Grenouille::creationBille() {
    //Pour remplacer la 2e bille lorsque la 1e est tirée
    B1 = B2;
    B2 = Bille(pos, 0, 0);

}

void Grenouille::verifieCouleurs() {
    //Empêcher le tir de couleurs qui ne sont plus présentes
}
