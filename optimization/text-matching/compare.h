#pragma once

#include "clustering.h"

/**
 * Make pairs of words that could possibly match (heuristically)
 * @param txt1 first text
 * @param txt2 second text
 * @return a vector of pairs of words
 */
vector<pair<string, string> > compareOftenUsedWords(const Text txt1, const Text txt2);

/**
 * Compute the DTW distances between the often used words of txt1 and
 * txt2 and save them into a map if they are under a threshold
 * @param txt1 first text
 * @param txt2 second text
 * @param compare pairs of words to compare
 * @param threshold threshold under which DTW distance is saved
 * @return the map which associate a pair of words with its DTW distance
 */
map< pair<string, string>, double > DTWCompare(const Text txt1, const Text txt2, const vector< pair<string, string> > compare, const double threshold);

/**
 * Compute average Jaro-Winkler distance between clusters of both texts
 * @param txt1 first text
 * @param txt2 second text
 * @param threshold threshold under which JW distance is saved
 * @return the map which associate a pair of clusters with its JR distance
 */
map<pair< vector<string>, vector<string> >, double> JRCompareClusters(const Text txt1, const Text txt2, const double threshold);

/**
 * @brief Adding groups of words in the dictionary
 * @param txt1 first text
 * @param txt2 second text
 * @param DTWcomp
 * @return
 */
map<pair<string, string>, double> DTWGroups(Text txt1, Text txt2, const map<pair<string, string>, double> &DTWcomp);
