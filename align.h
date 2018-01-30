#pragma once

#include "compare.h"

/**
 * @brief print an alignment by length of the 2 texts without considering the DTW distance
 * @param txt1 first text to compare
 * @param txt2 second text to compare
 */
void alignByLength(const Text &txt1, const Text &txt2);
void alignByLength2(const Text &txt1, const Text &txt2);
/**
 * @brief print an alignment of the 2 texts considering the DTW distance
 * @param txt1 first text to compare
 * @param txt2 second text to compare
 * @param compare dtw map computed with DTWCompare
 */
void alignSmart(const Text &txt1, const Text &txt2, const map< pair<string,string> , double > &compare);
