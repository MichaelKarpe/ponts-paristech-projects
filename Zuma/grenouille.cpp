#include "grenouille.h"

//Constructeurs

Grenouille::Grenouille()
{
    Bille b1(Point(w/2,h/2),-1,1.0), b2(Point(w/2,h/2),-1,1.0);
    g.push_back(b1);
    g.push_back(b2);
}


void Grenouille::traceGrenouille() {
    fillCircle(pos.x*zoom,pos.y*zoom,carre*zoom,g[0].col);
    fillCircle(pos.x*zoom,pos.y*zoom,carre*zoom/3,g[1].col);
}


//Fonction de tir
void Grenouille::tir(Bille b) {

    Event ev;
    getEvent(1,ev);

    if (ev == EVT_BUT_ON) {
        if (ev.button() == 3) {
            // Changer la bille
            changeBille();
        }
        if (ev.button() == 1) {
            // Tir
            IntPoint2 P = ev.pix - pos;
            double costheta = P.x()/sqrt(P.x()**P.x()+P.y()*P.y());
            double sintheta = P.y()/sqrt(P.x()**P.x()+P.y()*P.y());

            b.col = g[0].col;
            b.p.x = int(costheta*(carre + r/3.));
            b.p.y = int(sintheta*(carre + r/3.));




            creationBille();
        }
    }

    //Si clic gauche, beaucoup de choses à faire!
}


void Grenouille::changeBille() {
    //Si clic droit, échange de bille
}

void Grenouille::creationBille() {
    //Pour remplacer la 2e bille lorsque la 1e est tirée
}

void Grenouille::verifieCouleurs() {
    //Empêcher le tir de couleurs qui ne sont plus présentes
}
