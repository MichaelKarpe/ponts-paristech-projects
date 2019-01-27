#include "trajectoire.h"

//Constructeur

Trajectoire::Trajectoire()
{

}



// Assesseurs

int Trajectoire::size() const {
    return t.size();
}

Point Trajectoire::getPoint(const int &i) const {
    return t[i];
}


// Bijection coordonnées du plan  -  abscisse curviligne pour la trajectoire

Point Trajectoire::absplan(const int &abs) const {
    return t[abs];
}

int Trajectoire::abscurv(const Point &p) const {
    for (int i = 0; i < t.size(); i++) {
        if (t[i].getX()  ==  p.getX() && t[i].getY()  ==  p.getY())
            return i;
    }
}



// Fonctions de création de la trajectoire 1

// pointsCercle1 : ajoute les morceaux de trajectoire courbe de la trajectoire 1
void pointsCercle1(std::vector<Point> &p, const Point &c, const int &r, const int &cote) {
    double l = M_PI * r / 2;  // longueur de l'arc de cercle
    for (int i = 0; i < l; i++) {
        // Selon le paramètre cote,  on choisit le 1/4 de cercle qu'on ajoute à la trajectoire 1
        if (cote == 0)
            p.push_back(Point(c.getX() + r * sin(M_PI * i / (2 * l)), c.getY() - r * cos(M_PI * i / (2 * l))));
        else if (cote == 1)
            p.push_back(Point(c.getX() + r * cos(M_PI * i / (2 * l)), c.getY() + r * sin(M_PI * i / (2 * l))));
        else if (cote == 2)
            p.push_back(Point(c.getX() - r * sin(M_PI * i / (2 * l)), c.getY() + r * cos(M_PI * i / (2 * l))));
        else
            p.push_back(Point(c.getX() - r * cos(M_PI * i / (2 * l)), c.getY() - r * sin(M_PI * i / (2 * l))));
    }
}

// trajectoire1 : crée la trajectoire 1 en ajoutant la liste des points,  du départ à l'arrivée
void Trajectoire::trajectoire1() {
    pos=Point(w / 2, h / 2);  // Position de la grenouille
    // Définition des centres des morceaux courbes de la trajectoire
    int nbCentres = 16;
    Point centres[nbCentres]={{w - 3 * carre / 2, 3 * carre / 2}, {w - 3 * carre / 2, h - 3 * carre / 2}, {3 * carre / 2, h - 3 * carre / 2}, {3 * carre / 2, 5 * carre / 2},
                             {w - 5 * carre / 2, 5 * carre / 2}, {w - 5 * carre / 2, h - 5 * carre / 2}, {5 * carre / 2, h - 5 * carre / 2}, {5 * carre / 2, 7 * carre / 2},
                             {w - 7 * carre / 2, 7 * carre / 2}, {w - 7 * carre / 2, h - 7 * carre / 2}, {7 * carre / 2, h - 7 * carre / 2}, {7 * carre / 2, 9 * carre / 2},
                             {w - 9 * carre / 2, 9 * carre / 2}, {w - 9 * carre / 2, h - 9 * carre / 2}, {9 * carre / 2, h - 9 * carre / 2}, {9 * carre / 2, 11 * carre / 2}};
    // Ajout des morceaux droits de la trajectoire
    for (int j = 0; j < nbCentres; j++) {
        if (j % 4 == 0) {
            for (int i = 0; i < w - (2 + 2 * (j/4)) * carre; i++)
                t.push_back(Point(i + (1 + 2 * (j/4)) * carre / 2, (1 + 2 * (j/4)) * carre / 2));
        }
        else if (j % 4 == 1) {
            for (int i = 0; i < h - (3 + 2 * (j/4)) * carre; i++)
                t.push_back(Point(w - (1 + 2 * (j/4)) * carre / 2, (3 + 2 * (j/4)) * carre / 2 + i));
        }
        else if (j % 4 == 2) {
            for (int i = 0; i < w - (3 + 2 * (j/4)) * carre; i++)
                t.push_back(Point(w - (i + (3 + 2 * (j/4)) * carre / 2), h - (1 + 2 * (j/4)) * carre / 2));
        }
        else {
            for (int i = 0; i < h - (4 + 2 * (j/4)) * carre; i++)
                t.push_back(Point((1 + 2 * (j/4)) * carre / 2, h - (i + (3 + 2 * (j/4)) * carre / 2)));
        }
        // Si on n'est pas à la fin de la trajectoire et qu'on a ajouté un morceau droit,
        // on ajoute un morceau courbe
        if (j < nbCentres)
            pointsCercle1(t, centres[j], carre, j % 4);
    }
}

// Fonctions de création de la trajectoire 2

// pointsCercle2 : ajoute les morceaux de trajectoire courbe de la trajectoire 2
void pointsCercle2(std::vector<Point> &p, const Point &c, const int &r, const int &sens) {
    double l1 = M_PI * r;
    double l2 = M_PI * r / 2;
    // Selon le paramètre cote,  on choisit le 1/4 ou la moitié de cercle qu'on ajoute à la trajectoire 2
    if (sens == 0 || sens == 1 || sens == 3 || sens == 4) {
        for (int i = 0; i < l2; i++) {
            if (sens == 0)
                p.push_back(Point(c.getX() - r * cos(M_PI * i / (2 * l2)), c.getY() - r * sin(M_PI * i / (2 * l2))));
            else if (sens == 1)
                p.push_back(Point(c.getX() + r * sin(M_PI * i / (2 * l2)), c.getY() - r * cos(M_PI * i / (2 * l2))));
            else if (sens == 3)
                p.push_back(Point(c.getX() + r * cos(M_PI * i / (2 * l2)), c.getY() - r * sin(M_PI * i / (2 * l2))));
            else
                p.push_back(Point(c.getX() - r * sin(M_PI * i / (2 * l2)), c.getY() - r * cos(M_PI * i / (2 * l2))));
        }
    }
    else {
        for (int i = 0; i < l1; i++) {
            if (sens == 2)
                p.push_back(Point(c.getX() + r * cos(M_PI * i / l1), c.getY() + r * sin(M_PI * i / l1)));
            else
                p.push_back(Point(c.getX() - r * cos(M_PI * i / l1), c.getY() + r * sin(M_PI * i / l1)));
        }
    }

}

// trajectoire2 : crée la trajectoire 2 en ajoutant la liste des points,  du départ à l'arrivée
void Trajectoire::trajectoire2() {
    pos=Point(w / 2, h / 2 + carre); //Position de la grenouille
    // Définition des centres des morceaux courbes de la trajectoire
    int nbCentres = 11;
    Point centres[nbCentres]={{3 * carre / 2, 3 * carre / 2}, {w - 3 * carre / 2, 3 * carre / 2}, {w - 3 * carre / 2, h - 3 * carre / 2}, {w - 7 * carre / 2, 5 * carre / 2},
                             {7 * carre / 2, 5 * carre / 2}, {7 * carre / 2, h - 3 * carre / 2}, {11 * carre / 2, 7 * carre / 2}, {w - 11 * carre / 2, 7 * carre / 2},
                             {w - 11 * carre / 2, h - 3 * carre / 2}, {w - 15 * carre / 2, 9 * carre / 2}, {15 * carre / 2, 9 * carre / 2}};
   // Ajout des morceaux droits de la trajectoire
    for (int j = 0; j < nbCentres + 1; j++) {
        if (j == 0) {
            for (int i = 0; i < h - 2 * carre; i++)
                t.push_back(Point(carre / 2, h - carre / 2 - i));
        }
        else if (j == 1) {
            for (int i = 0; i < w - 3 * carre; i++)
                t.push_back(Point(3 * carre / 2 + i, carre / 2));
        }
        else if (j == 2) {
            for (int i = 0; i < h - 3 * carre; i++)
                t.push_back(Point(w - carre / 2, 3 * carre / 2 + i));
        }
        else if (j == 3) {
            for (int i = 0; i < h - 4 * carre; i++)
                t.push_back(Point(w - 5 * carre / 2, h - 3 * carre / 2 - i));
        }
        else if (j == 4) {
            for (int i = 0; i < w - 7 * carre; i++)
                t.push_back(Point(w - 7 * carre / 2 - i, 3 * carre / 2));
        }
        else if (j == 5) {
            for (int i = 0; i < h - 4 * carre; i++)
                t.push_back(Point(5 * carre / 2, 5 * carre / 2 + i));
        }
        else if (j == 6) {
            for (int i = 0; i < h - 5 * carre; i++)
                t.push_back(Point(9 * carre / 2, h - 3 * carre / 2 - i));
        }
        else if (j == 7) {
            for (int i = 0; i < w - 11 * carre; i++)
                t.push_back(Point(11 * carre / 2 + i, 5 * carre / 2));
        }
        else if (j == 8) {
            for (int i = 0; i < h - 5 * carre; i++)
                t.push_back(Point(w - 9 * carre / 2, 7 * carre / 2 + i));
        }
        else if (j == 9) {
            for (int i = 0; i < h - 6 * carre; i++)
                t.push_back(Point(w - 13 * carre / 2, h - 3 * carre / 2 - i));
        }
        else if (j == 10) {
            for (int i = 0; i < w - 15 * carre; i++)
                t.push_back(Point(w - 15 * carre / 2 - i, 7 * carre / 2));
        }
        else {
            for (int i = 0; i < h - 6 * carre; i++)
                t.push_back(Point(13 * carre / 2, 9 * carre / 2 + i));
        }

        if (j < nbCentres)
            pointsCercle2(t, centres[j], carre, j % 6);
    }
}


// Fonctions de tracé

// traceTrajectoire : trace la trajectoire
void Trajectoire::traceTrajectoire() const {
    for (int i = 0; i < t.size() - 2; i++)
        drawLine(t[i].getX() * zoom, t[i].getY() * zoom, t[i + 1].getX() * zoom, t[i + 1].getY() * zoom, RED);
}
