#include "serpent.h"
#include "trajectoire.h"
#include "bille.h"

//Constructeurs

Serpent::Serpent()
{

}

Serpent::Serpent(const Trajectoire &traj, const int &nbBilles, const Niveau &Niv)
{
    //Ajout de billes de couleur aléatoire au serpent
    for (int i=0;i<nbBilles;i++) {
        Bille b(Point(traj.getPoint(2*r*i).getX(),traj.getPoint(2*r*i).getY()),2*r*i,vDepart,Niv);
        s.push_back(b);
    }
}

//Destructeur

Serpent::~Serpent()
{

}


// Assesseurs

int Serpent::size() const {
    return s.size();
}

Bille Serpent::getBille(const int &i) const {
    return s[i];
}

Bille &Serpent::front() {
    s.front();
}

Bille &Serpent::back() {
    s.back();
}

void Serpent::push(const Bille &b) {
    s.push_back(b);
}

//setVitSerp : attribue à toutes les billes du serpent la valeur iv.
void Serpent::setVitSerp(const double &iv) {
    for (int i=0;i<s.size();i++)
        s[i].setVit(iv);
}

void Serpent::setAbsBille(const int &ibille, const int &iabs) {
    s[ibille].setAbs(iabs);
}

void Serpent::setCoorBille(const int &ibille, const Point &icoor) {
    s[ibille].setCoor(icoor);
}

void Serpent::setVitBille(const int &ibille, const double &ivit) {
    s[ibille].setVit(ivit);
}


// Méthodes modifiant la classe

//serpentFin : arrête le niveau si le serpent
//arrive à la fin de la trajectoire
bool Serpent::serpentFin(const Trajectoire &traj) {
    return (s.back().getAbs() >= traj.size());
}

//serpentLoin : envoie un serpent si le dernier serpent envoyé a avancé assez loin
bool Serpent::serpentLoin(const Trajectoire &traj) {
    return (s.back().getAbs() >= 1.0/newSerp*traj.size());
}


//vitesseDiminue : diminue la vitesse du serpent en fonction
//de la distance entre le serpent et la fin de la trajectoire
void Serpent::vitesseDiminue(const Trajectoire &traj) {
    //Calcul de la vitesse qui diminue proportionnellement à la distance avec la fin,
    //tel que l'incrément de position dans deplacementSerpents soit toujours supérieur ou égal à 1
    double nv = vDepart*(1.0-double(s.back().getAbs())/double(traj.size()))+1/dt;
    //Si la vitesse de la bille n'est pas nulle (rupture du serpent), on diminue la vitesse
    for (int i=0;i<s.size();i++) {
        if (s[i].getVit()!=0)
            s[i].setVit(nv);
    }
}

// insererBille : insère une bille dans le serpent en position j
void Serpent::insererBille(const Trajectoire &traj, const Bille &B, const int &j) {
    effaceSerpent(traj);
    //Insertion de la bille B et mise à jour avec les paramètres des billes juxtaposées
    s.insert(s.begin()+j,B);

    s[j].setVit(s[j+1].getVit()); //problème ici ?
    s[j].setAbs(s[j+1].getAbs());
    //Décalage des billes à l'avant du serpent pour permettre l'insertion de la bille
    for (int i=j+1;i<s.size();i++) {
        s[i].setAbs(traj.abscurv(s[i].getCoor())+2*r);
        s[i].setCoor(traj.absplan(traj.abscurv(s[i].getCoor())+2*r));
        s[i].traceBille();
    }
}

// insererTir : insérer la bille tirée dans le serpent
int Serpent::insererTir(const Trajectoire &traj, const Bille &B, bool &finTir) {
    Bille Binser = B;
    if (finTir)
        return -1;
    else {
        int i=1;
        while (i<=s.size() && !finTir) {
            //On repère si on insère la bille dans le serpent à l'indice i ou i-1
            if (dist(s[i-1],B) < 2*r) {
                if (dist(s[i],B) < 2*r) {
                    insererBille(traj,Binser,i);
                    finTir = true;
                    return i;
                }
                else {
                    insererBille(traj,Binser,i-1);
                    finTir = true;
                    return i-1;
                }
            }
        i++;
        }
    return -1;
    }
}

//destructionBilles : détruit les billes de couleur lors du tir si à
//l'endroit où l'on a tiré, il y a au moins 3 billes de couleur identique
void Serpent::destructionBilles(int &ind_combo, const int &i, const int &ind_list_serp, vector<Serpent> &listSerp) {
    //i est l'indice de la bille dont on vérifie si on la supprime avec les billes voisines ou non
    //les indices ig et id parcourent le serpent vers la gauche et vers la droite tant que la couleur
    //est la même que celle de la bille d'indice i. S'il y a 3 billes ou plus de même couleur à l'endroit
    //où on a tiré, alors on supprime les billes et on annule la vitesse des billes à l'avant du serpent,
    //pour que les billes de l'arrière du serpent reviennent se coller à l'avant du serpent et que le serpent
    //ne soit pas scindé en 2 serpents.
    if (i!=-1) {
        Color colbille = s[i].getCol();
        int ig=0, id=0;
        while (i-ig>0 && s[i-1-ig].getCol()==colbille)
            ig+=1;
        while (i+1+id<s.size() && s[i+1+id].getCol()==colbille)
            id+=1;
        if (id+ig+1 >= 3) {
            for (int j=i-id;j<i+id+1;j++)
                s[j].effaceBille();
            if (ig+id+1 == s.size())
                listSerp.erase(listSerp.begin()+ind_list_serp);
            else if (i-ig == 0)
                s.erase(s.begin(),s.begin()+i+id+1);
            else if (i+id == s.size()-1)
                s.erase(s.begin()+i-ig,s.begin()+s.size());
            else {
                Serpent Sreste;
                if (s[i-ig-1].getCol()==s[i+id+1].getCol())
                    ind_combo = ind_list_serp;
                for (int j=i+id+1;j<s.size();j++) {
                    s[j].setVit(0.0);
                    Sreste.push(s[j]);
                }
                s.erase(s.begin()+i-ig,s.begin()+s.size());
                listSerp.insert(listSerp.begin()+ind_list_serp,Sreste);
            }
        }
    }
}


// Autres fonctions

//deplacementSerpents : permet le déplacement de l'ensemble des serpents
void deplacementSerpents(const Trajectoire &traj, vector<Serpent> &listSerp) {
    for (int j=0;j<listSerp.size();j++) {
        listSerp[j].effaceSerpent(traj); //On efface les serpents
        for (int k=0;k<listSerp[j].size();k++) {
            //On effectue le déplacement du serpent avec l'incrément de position ds
            double ds=listSerp[j].getBille(k).getVit()*dt;
            if (ds>1) //Sinon le serpent n'avance plus
                listSerp[j].setAbsBille(k,listSerp[j].getBille(k).getAbs()+ds);
            listSerp[j].setCoorBille(k,traj.absplan(listSerp[j].getBille(k).getAbs()));
        }
        listSerp[j].traceSerpent(traj); //On trace les serpents déplacés de leur incrément ds
    }
}


//fusionSerpents : pour l'instant inutile car tous à la même vitesse
//Permet de fusionner les serpents si un serpent rattrape un autre
void fusionSerpents(const Trajectoire &traj, int &ind_combo, vector<Serpent> &listSerp) {
    //Pour tous les serpents
    for (int i=0;i<listSerp.size()-1;i++) {
        //On calcule la distance entre la queue du i-ème serpent rentré et la tête du
        //(i+1)-ème serpent rentré
        int dist = std::abs(listSerp[i].front().getAbs()-listSerp[i+1].back().getAbs());
        //Si cette distance est inférieure à 2R, les serpents se touchent : il faut les fusionner
        if (dist<=2*r) {
            int J = listSerp[i+1].size()-1;
            //On met les deux serpents à la même vitesse
            if (listSerp[i].getBille(0).getVit()==0)
                listSerp[i].setVitSerp(listSerp[i+1].front().getVit());
            for (int j=0;j<listSerp[i+1].size();j++)
                listSerp[i+1].setVitBille(j,listSerp[i].front().getVit());
            //On corrige la position des billes pour que les billes du nouveau serpent ne se chevauchent pas
            for (int j=0;j<listSerp[i].size();j++) {
                Bille B = listSerp[i].getBille(j);
                B.setAbs(B.getAbs()+2*r-dist);
                listSerp[i+1].push(B);
            }
            //On efface et supprime le (i+1)-ème serpent qui a fusionné
            listSerp[i+1].effaceSerpent(traj);
            listSerp.erase(listSerp.begin()+i);
            //On retrace le nouveau i-ème serpent, fusion des anciens i-ème et (i+1)-ème serpent
            listSerp[i].traceSerpent(traj);
            //Si la fusion relie au moins 3 billes de même couleur, elles sont détruites
            if (ind_combo == i) {
                listSerp[i].destructionBilles(ind_combo,J,i,listSerp);
                ind_combo = -1;
            }
        }
    }
}


// Fonctions de tracé

void Serpent::traceSerpent(const Trajectoire &traj) const {
    for (int i=0;i<s.size();i++) {
        if (s[i].getAbs()<traj.size()-1)
            s[i].traceBille();
    }
}

void Serpent::effaceSerpent(const Trajectoire &traj) const {
    for (int i=0;i<s.size();i++) {
        if (s[i].getAbs()<traj.size()-1)
            s[i].effaceBille();
    }
}



