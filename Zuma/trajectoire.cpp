#include "trajectoire.h"

//Constructeur

Trajectoire::Trajectoire()
{

}

void Trajectoire::traceTrajectoire() {
    for (int i=0;i<t.size()-2;i++) {
        drawLine(t[i].x*zoom,t[i].y*zoom,t[i+1].x*zoom,t[i+1].y*zoom,RED,zoom);
        //milliSleep(1);
    }

}

void pointsCercle(std::vector<Point> &p, Point c, int r, int cote) {
    double l=M_PI*r; //longueur de l'arc de cercle
    for (int i=0;i<l;i++) {
        if (cote==0) //droite
            p.push_back(Point(c.x+r*sin(M_PI*i/l),c.y-r*cos(M_PI*i/l)));
        else //gauche
            p.push_back(Point(c.x-r*sin(M_PI*i/l),c.y-r*cos(M_PI*i/l)));
    }
}

void Trajectoire::trajectoire1() {
    int nbCentres=4;
    Point centres[nbCentres]={{w-3*carre/2,3*carre/2},{3*carre/2,7*carre/2},{w-3*carre/2,11*carre/2},{3*carre/2,15*carre/2}};
    for (int j=0;j<nbCentres+1;j++) {
        if (j%2==0) {
            for (int i=0;i<w-3*carre;i++)
                t.push_back(Point(i+3*carre/2,carre/2+2*j*carre));
        }
        else {
            for (int i=0;i<w-3*carre;i++)
                t.push_back(Point(w-(i+3*carre/2),carre/2+2*j*carre));
        }
        if (j<nbCentres)
            pointsCercle(t,centres[j],carre,j%2);
    }
}

void Trajectoire::billesRandom() {
    for (int i=0;i<t.size()/(2*r);i++)
        //dessineBille(t[40*i]);
        fillCircle(t[2*r*i].x*zoom,t[2*r*i].y*zoom,R,colors[rand()%8]);
}
