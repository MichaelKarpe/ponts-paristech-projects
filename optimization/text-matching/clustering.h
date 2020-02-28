#pragma once

#include "distance.h"

/**
 * Hierachical clustering of the often used words in txt, using JW distance
 * @param txt text to work on
 * @param threshold threshold at which the algorithm stops merging clusters
 */
void hierarchicClustering(Text &txt, const double threshold = HC_threshold);

