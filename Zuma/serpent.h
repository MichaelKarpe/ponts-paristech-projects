#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "bille.h"

class Serpent
{
    std::vector<Bille> s;
public:
    //Variables utiles ?
    int nbBilles; // = s.size()
    Bille front, back; // = s.front(), = s.back()

    Serpent();
    void SerpentAleatoire();
    ~Serpent();

    Serpent fusionSerpents(Serpent serp2);
    void vitesseEntree();
    void vitesseDiminue();
    void vitesseDestruction();
    void vitesseCombo();
    void vitesseNulle();
};

