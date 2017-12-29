#ifndef DISTANCE_H
#define DISTANCE_H

#include "text.h"

class Distance
{

public:
    Distance();
};

double jaro_distance(string str1, string str2);

double jaro_winkler_distance(string str1, string str2, double coeff_winkler);

double levenshtein_distance(string str1, string str2);

double DTW(vector<double> v1, vector<double> v2);


#endif // DISTANCE_H
