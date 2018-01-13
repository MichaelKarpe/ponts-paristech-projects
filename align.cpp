#include "align.h"
void alignByLength(const Text &txt1, const Text &txt2) {
    vector<double> crossTable;
    for (int i=0;i<txt1.getSectionPosition().size();i++) {
        for (int j=0;j<txt2.getSectionPosition().size();j++) {
            crossTable.push_back(abs(txt1.getSectionPosition()[i] - txt2.getSectionPosition()[j]));
        }
    }


    // Optimal path computation on the crosstable
    int n1 = txt1.getNbSections();
    int n2 = txt2.getNbSections();

    int I = 0, J = 0;
    string str1 = "", str2 = "";

    while (I<n1 || J<n2) {
        if (I == n1) {
            J++;
            str2 += (" " + to_string(J));
        }
        else if (J == n2) {
            I++;
            str1 += (" " + to_string(I));
        }
        else {
            double MIN = crossTable[(I+1)*n2+J];
            if (MIN > crossTable[I*n2+J+1]) {
                J++;
                str2 += (" " + to_string(J));
            }
            else if (MIN >= crossTable[(I+1)*n2+J+1]) {
                I++; J++;
                cout << str1 << " : " << str2 << endl;
                str1 = to_string(I);str2 = to_string(J);
            }
            else {
                I++;
                str1 += (" " + to_string(I));
            }
        }
    }
    cout << str1 << " : " << str2 << endl;
}

void alignSmart(const Text &txt1, const Text &txt2, const map< pair<string,string> , double > &compare) {
    vector<double> crossTable;
    for (int i=0;i<txt1.getSectionPosition().size();i++) {
        for (int j=0;j<txt2.getSectionPosition().size();j++) {
            crossTable.push_back(abs(txt1.getSectionPosition()[i] - txt2.getSectionPosition()[j]));
        }
    }

    for (map< pair<string,string>, double>::const_iterator it=compare.begin();it!=compare.end();++it) {
        vector<int> word1Sections = txt1.getWordSectionIndices()[(it->first).first];
        vector<int> word2Sections = txt1.getWordSectionIndices()[(it->first).second];

        for (int i=0; i<word1Sections.size(); i++) {
            for (int j=0; j<word2Sections.size(); j++) {
                double dist = crossTable[word1Sections[i]*txt1.getSectionPosition().size() + word2Sections[j]];
                crossTable[word1Sections[i]*txt1.getSectionPosition().size() + word2Sections[j]] += (it->second * dist);
            }
        }
    }
    // Optimal path computation on the crosstable
    int n1 = txt1.getNbSections();
    int n2 = txt2.getNbSections();

    int I = 0, J = 0;
    string str1 = "", str2 = "";

    while (I<n1 || J<n2) {
        if (I == n1) {
            J++;
            str2 += (" " + to_string(J));
        }
        else if (J == n2) {
            I++;
            str1 += (" " + to_string(I));
        }
        else {
            double MIN = crossTable[(I+1)*n2+J];
            if (MIN > crossTable[I*n2+J+1]) {
                J++;
                str2 += (" " + to_string(J));
            }
            else if (MIN >= crossTable[(I+1)*n2+J+1]) {
                I++; J++;
                cout << str1 << " : " << str2 << endl;
                str1 = to_string(I);str2 = to_string(J);
            }
            else {
                I++;
                str1 += (" " + to_string(I));
            }
        }
    }
    cout << str1 << " : " << str2 << endl;
}
