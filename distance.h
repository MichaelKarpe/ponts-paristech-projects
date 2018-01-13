#ifndef DISTANCE_H
#define DISTANCE_H

#include "text.h"


class Distance
{

public:
    Distance();
};
/**
 * @param str1 first string to compare
 * @param str2 second string to compare
 * @return the Jaro distance between str1 and str2
 */
double jaro_distance(const string str1, const string str2);
/**
 * @param str1 first string to compare
 * @param str2 seconde string to compare
 * @return the Jaro-Winkler distance between str1 and str2
 */
double jaro_winkler_distance(const string str1, const string str2);
/**
 * @brief Dynamic Time Warping distance computation
 * @param v1 recency vector of the first word
 * @param v2 recency vector of the second word
 * @return the timewarp distance between 2 words whose rencency vectors are v1 and v2
 */
double DTW(const vector<double> v1, const vector<double> v2);
/**
 * @param str1 first string to compare
 * @param str2 second string to compare
 * @return the Levenshtein distance between str1 and str2
 */
double levenshtein_distance(const string str1, const string str2);

#endif // DISTANCE_H
