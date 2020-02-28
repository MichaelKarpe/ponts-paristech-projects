#include "align.h"

/// Methods as described in Kim Gerdes paper
/// Applicable with DTW

vector<int> makeCrossTable(const Text &txt1, const Text &txt2, const vector<double> &bigCrossTable) {
    vector<int> crossTable;
    crossTable.push_back(0);

    for (int i = 0; i < txt1.getSectionPosition().size(); i++) {
        double distmin = 1;
        int indmin = 0;
        for (int j = 0; j < txt2.getSectionPosition().size(); j++) {
            if (bigCrossTable[i * txt2.getSectionPosition().size() + j] < distmin) {
                distmin = bigCrossTable[i * txt2.getSectionPosition().size() + j];
                indmin = j + 1;
            }
        }
        crossTable.push_back(indmin);
    }

    return crossTable;
}

vector<double> makeExhaustiveCrossTable(const Text &txt1, const Text &txt2) {
    vector<double> crossTable;
    for (int i = 0; i < txt1.getSectionPosition().size(); i++)
        for (int j = 0; j<txt2.getSectionPosition().size(); j++)
            crossTable.push_back(abs(txt1.getSectionPosition()[i] - txt2.getSectionPosition()[j]));
    return crossTable;
}

void makeAnddisplayAlignment(const Text &txt1, const Text &txt2, const vector<int> &crossTable1to2, const vector<int> &crossTable2to1) {
    // Make alignment
    vector< pair<int, int> > perfectMatches;
    for (int i = 1; i<crossTable1to2.size(); i++)
        if (i == crossTable2to1[crossTable1to2[i]])
            perfectMatches.push_back(make_pair(i, crossTable1to2[i])); //Attention au sens !

    // Display alignment
    int ind1 = perfectMatches[0].first, ind2=perfectMatches[0].second;
    for (int i = 1; i < perfectMatches.size(); i++) {
        for (int j = ind1; j<perfectMatches[i].first; j++)
            cout << j << " ";
        cout << " : ";
        for (int j = ind2; j < perfectMatches[i].second; j++)
            cout << j << " ";
        cout << endl;
        ind1 = perfectMatches[i].first;
        ind2 = perfectMatches[i].second;
    }

    for (int j = ind1; j < txt1.getSectionPosition().size() + 1; j++)
        cout << j << " ";
    cout << " : ";
    for (int j = ind2; j < txt2.getSectionPosition().size() + 1; j++)
        cout << j << " ";
    cout << endl;
}

void alignByLength(const Text &txt1, const Text &txt2) {
    vector<double> crossTable1 = makeExhaustiveCrossTable(txt1, txt2);
    vector<double> crossTable2 = makeExhaustiveCrossTable(txt2, txt1);

    vector<int> crossTable1to2 = makeCrossTable(txt1, txt2, crossTable1);
    vector<int> crossTable2to1 = makeCrossTable(txt2, txt1, crossTable2);

    makeAnddisplayAlignment(txt1, txt2, crossTable1to2, crossTable2to1);
}

vector<double> makeExhaustiveDTWCrossTable(const Text &txt1, const Text &txt2, const map<pair<string,string> , double> &compare) {
    vector<double> crossTable = makeExhaustiveCrossTable(txt1, txt2);
    // DTW distance computed before is taken into account
    for (map<pair<string,string>, double>::const_iterator it = compare.begin(); it != compare.end(); ++it) {
        vector<int> word1Sections = txt1.getWordSectionIndices()[(it->first).first];
        vector<int> word2Sections = txt2.getWordSectionIndices()[(it->first).second];
        for (int i = 0; i < word1Sections.size(); i++) {
            for (int j = 0; j < word2Sections.size(); j++) {
                double dist = crossTable[word1Sections[i] * txt1.getSectionPosition().size() + word2Sections[j]];
                crossTable[word1Sections[i] * txt1.getSectionPosition().size() + word2Sections[j]] += (it->second * dist);
            }
        }
    }
    return crossTable;
}

void alignWithDTW(const Text &txt1, const Text &txt2, const double &threshold) {
    // cout << "Couples of matching words :" << endl;
    vector< pair<string,string> > compare1 = compareOftenUsedWords(txt1, txt2);
    vector< pair<string,string> > compare2 = compareOftenUsedWords(txt2, txt1);

    map<pair<string,string>, double> dtwcompare1 = DTWCompare(txt1, txt2, compare1, threshold);
    map<pair<string,string>, double> dtwcompare2 = DTWCompare(txt2, txt1, compare2, threshold);

    vector<double> crossTable1 = makeExhaustiveDTWCrossTable(txt1, txt2, dtwcompare1);
    vector<double> crossTable2 = makeExhaustiveDTWCrossTable(txt2, txt1, dtwcompare2);

    vector<int> crossTable1to2 = makeCrossTable(txt1, txt2, crossTable1);
    vector<int> crossTable2to1 = makeCrossTable(txt2, txt1, crossTable2);

    makeAnddisplayAlignment(txt1, txt2, crossTable1to2, crossTable2to1);

}



/// Simple methods, not as described in Kim Gerdes paper
/// Only applicable to align by length, do not work with DTW
/// A more efficient way to do alignment by length

vector<int> makeCrossTableSimple(const Text &txt1, const Text &txt2) {
    vector<int> crossTable;
    crossTable.push_back(0);
    double s1 = txt2.getSectionPosition()[0], s2 = txt2.getSectionPosition()[1];
    int n = 2;  // number of paragraph in txt2
    int i = 0;  // indice in txt1

    while (i < txt1.getSectionPosition().size()) {
        if (abs(txt1.getSectionPosition()[i] - s1) < abs(txt1.getSectionPosition()[i] - s2)) {  // If closer from s1 than s2
            crossTable.push_back(n - 1);
            i++;
        }
        else {
            n++;
            if (n - 1 < txt2.getSectionPosition().size()) {
                s1 = txt2.getSectionPosition()[n - 2];
                s2 = txt2.getSectionPosition()[n - 1];
            }
            else if(n - 1 == txt2.getSectionPosition().size()) {
                s1 = txt2.getSectionPosition()[n - 2];
                s2 = INFINITY;
            }
        }
    }

    return crossTable;
}



void alignByLengthSimple(const Text &txt1, const Text &txt2) {
    vector<int> crossTable1to2 = makeCrossTableSimple(txt1, txt2);
    vector<int> crossTable2to1 = makeCrossTableSimple(txt2, txt1);
    makeAnddisplayAlignment(txt1, txt2, crossTable1to2, crossTable2to1);
}
