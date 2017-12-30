#pragma once
//#ifndef CLUSTERING_H
//#define CLUSTERING_H

#include "distance.h"

//A vocation à recevoir les méthodes de clustering

class Clustering
{
public:
    Clustering();
};

void hierarchicClustering(Text &txt, const double threshold);

//#endif // CLUSTERING_H
