#ifndef COMPARE_H
#define COMPARE_H

#include "clustering.h"

class Compare
{
public:
    Compare();
};

vector<pair<string, string> > compareOftenUsedWords(Text txt1, Text txt2);

map< pair<string,string>,double > DTWCompare(Text txt1, Text txt2, vector< pair<string,string> > compare);


#endif // COMPARE_H
