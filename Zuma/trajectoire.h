#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

#include "serpent.h"
#include "grenouille.h"
#include "outils.h"

const int courbure=carre;

class Trajectoire
{
public:
    std::vector<Point> t;
    Trajectoire();
    void traceTrajectoire();
    void trajectoire1();
    void billesRandom();
};

