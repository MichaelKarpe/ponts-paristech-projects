#include "compare.h"

Compare::Compare()
{

}

vector< pair<string,string> > compareOftenUsedWords(Text txt1, Text txt2) {
    vector< pair<string,string> > couples;
    for (int i=0;i<txt1.getOftenUsedWords().size();i++)
        for (int j=0;j<txt2.getOftenUsedWords().size();j++)
            if (txt1.getWordIndices()[txt1.getOftenUsedWords()[i]].size()<2*txt2.getWordIndices()[txt2.getOftenUsedWords()[j]].size() && txt2.getWordIndices()[txt2.getOftenUsedWords()[j]].size()<2*txt1.getWordIndices()[txt1.getOftenUsedWords()[i]].size()) {
                couples.push_back(make_pair(txt1.getOftenUsedWords()[i],txt2.getOftenUsedWords()[j]));
                //cout << txt1.getOftenUsedWords()[i] << " ; " << txt2.getOftenUsedWords()[j] << endl;
            }

    return couples;
}

map< pair<string,string>,double > DTWCompare(Text txt1, Text txt2, vector< pair<string,string> > compare) {
    map< pair<string,string>,double > dtwCompare;
    for (int i=0;i<compare.size();i++) {
        vector<double> rec1 = txt1.getWordRecency()[compare[i].first];
        vector<double> rec2 = txt2.getWordRecency()[compare[i].second];
        dtwCompare[compare[i]]=DTW(rec1,rec2);
        cout << compare[i].first << " ; " << compare[i].second << " : " << dtwCompare[compare[i]] << endl;
    }

    return dtwCompare;

}
