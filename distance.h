#ifndef DISTANCE_H
#define DISTANCE_H

#include "text.h"

class Distance
{

public:
    Distance();
};

double jaro_distance(const string str1, const string str2);

double jaro_winkler_distance(const string str1, const string str2, const double coeff_winkler = 0.1);

double DTW(const vector<double> v1, const vector<double> v2);

double levenshtein_distance(const string str1, const string str2);

#endif // DISTANCE_H
