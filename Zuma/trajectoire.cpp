#include "trajectoire.h"

//Constructeur

Trajectoire::Trajectoire()
{

}

// Il faut tracer les contours de la trajectoire
void Trajectoire::traceTrajectoire() {
    for (int i=0;i<t.size()-2;i++)
        drawLine(t[i].x*zoom,t[i].y*zoom,t[i+1].x*zoom,t[i+1].y*zoom,RED);
}


// Fonctions de création de la trajectoire 1

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


// Fonctions de création de la trajectoire 2

void pointsCercle2(std::vector<Point> &p, Point c, int r, int cote) {
    double l=M_PI*r/2; //longueur de l'arc de cercle
    for (int i=0;i<l;i++) {
        if (cote==0) //droite
            p.push_back(Point(c.x+r*sin(M_PI*i/(2*l)),c.y-r*cos(M_PI*i/(2*l))));
        else if (cote==1)//gauche
            p.push_back(Point(c.x+r*cos(M_PI*i/(2*l)),c.y+r*sin(M_PI*i/(2*l))));
        else if (cote==2)//gauche
            p.push_back(Point(c.x-r*sin(M_PI*i/(2*l)),c.y+r*cos(M_PI*i/(2*l))));
        else //gauche
            p.push_back(Point(c.x-r*cos(M_PI*i/(2*l)),c.y-r*sin(M_PI*i/(2*l))));
    }
}

void Trajectoire::trajectoire2() {
    int nbCentres=16;
    Point centres[nbCentres]={{w-3*carre/2,3*carre/2},{w-3*carre/2,h-3*carre/2},{3*carre/2,h-3*carre/2},{3*carre/2,5*carre/2},
                             {w-5*carre/2,5*carre/2},{w-5*carre/2,h-5*carre/2},{5*carre/2,h-5*carre/2},{5*carre/2,7*carre/2},
                             {w-7*carre/2,7*carre/2},{w-7*carre/2,h-7*carre/2},{7*carre/2,h-7*carre/2},{7*carre/2,9*carre/2},
                             {w-9*carre/2,9*carre/2},{w-9*carre/2,h-9*carre/2},{9*carre/2,h-9*carre/2},{9*carre/2,11*carre/2}};
    for (int j=0;j<nbCentres;j++) {
        if (j%4==0) {
            for (int i=0;i<w-(2+2*(j/4))*carre;i++)
                t.push_back(Point(i+(1+2*(j/4))*carre/2,(1+2*(j/4))*carre/2));
        }
        else if (j%4==1) {
            for (int i=0;i<h-(3+2*(j/4))*carre;i++)
                t.push_back(Point(w-(1+2*(j/4))*carre/2,(3+2*(j/4))*carre/2+i));
        }
        else if (j%4==2) {
            for (int i=0;i<w-(3+2*(j/4))*carre;i++)
                t.push_back(Point(w-(i+(3+2*(j/4))*carre/2),h-(1+2*(j/4))*carre/2));
        }
        else {
            for (int i=0;i<h-(4+2*(j/4))*carre;i++)
                t.push_back(Point((1+2*(j/4))*carre/2,h-(i+(3+2*(j/4))*carre/2)));
        }
        if (j<nbCentres)
            pointsCercle2(t,centres[j],carre,j%4);
    }
}


// Bijection coordonnées du plan - abscisse curviligne

Point Trajectoire::absplan(int abs) const {
    return t[abs];
}

int Trajectoire::abscurv(Point p) const {
    for (int i=0;i<t.size();i++) {
        if (t[i].x==p.x && t[i].y==p.y)
            return i;
    }
}


// Fonctions inutiles

void Trajectoire::billesRandom() {
    for (int i=0;i<t.size()/(2*r);i++)
        //dessineBille(t[40*i]);
        fillCircle(t[2*r*i].x*zoom,t[2*r*i].y*zoom,R,colors[rand()%8]);
}
