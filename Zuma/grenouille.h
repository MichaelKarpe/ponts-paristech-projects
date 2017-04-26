#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "bille.h"

class Grenouille
{
public:
    std::vector<Bille> g; // g.size()=2

    Point pos=Point(W/2,H/2);
    Grenouille();

    void traceGrenouille();

    void tir();
    void changeBille();
    void creationBille();
    void verifieCouleurs();
};

