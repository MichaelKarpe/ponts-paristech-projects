#ifndef COMPARE_H
#define COMPARE_H

#include "clustering.h"

class Compare
{
public:
    Compare();
};

vector<pair<string, string> > compareOftenUsedWords(const Text txt1, const Text txt2);

map< pair<string,string>,double > DTWCompare(const Text txt1, const Text txt2, const vector< pair<string,string> > compare, const double threshold);

map< pair< vector<string>,vector<string> >,double > JRCompareClusters(const Text txt1, const Text txt2, const double threshold);

#endif // COMPARE_H
