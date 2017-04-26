#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "bille.h"

class Grenouille
{
    std::vector<Bille> g; // g.size()=2
public:
    Grenouille();

    void tir();
    void changeBille();
    void creationBille();
    void verifieCouleurs();
};

