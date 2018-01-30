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

vector<int> makeCrossTable(const Text &txt1, const Text &txt2) {
    vector< int > crossTable;
    crossTable.push_back(0);
    double s1=txt2.getSectionPosition()[0], s2=txt2.getSectionPosition()[1];
    int n=2;
    int i=0;

    while (i<txt1.getSectionPosition().size() && n-1<txt2.getSectionPosition().size()) {
        if (abs(txt1.getSectionPosition()[i]-s1)<abs(txt1.getSectionPosition()[i]-s2)) { //plus près de s1 que de s2
            crossTable.push_back(n-1);
            i++;
        }
        else {
            n++;
            if (n-1!=txt2.getSectionPosition().size()) {
                s1=txt2.getSectionPosition()[n-2];
                s2=txt2.getSectionPosition()[n-1];
            }
        }
    }

    //BRICOLAGE, pb de gestion des indices à la fin
    while (i<txt1.getSectionPosition().size()) {
        crossTable.push_back(n-1);
        i++;
    }

//    for (int i=0; i< crossTable.size(); i++)
//        cout << i << " : " << crossTable[i] << endl;

    return crossTable;
}

void alignByLength2(const Text &txt1, const Text &txt2) {
    vector< int > crossTable1to2 = makeCrossTable(txt1,txt2);
    vector< int > crossTable2to1 = makeCrossTable(txt2,txt1);
    vector< pair<int, int> > perfectMatches;
    for (int i=1;i<crossTable2to1.size();i++)
        if (i==crossTable1to2[crossTable2to1[i]])
            perfectMatches.push_back(make_pair(i,crossTable2to1[i]));

    int ind1=perfectMatches[0].first, ind2=perfectMatches[0].second;
    for (int i=1;i<perfectMatches.size();i++) {
        for (int j=ind1;j<perfectMatches[i].first;j++)
            cout << j << " ";
        cout << " : ";
        for (int j=ind2;j<perfectMatches[i].second;j++)
            cout << j << " ";
        cout << endl;
        ind1=perfectMatches[i].first;
        ind2=perfectMatches[i].second;
    }
}



void alignSmart(const Text &txt1, const Text &txt2, const map< pair<string,string> , double > &compare) {
    vector<double> crossTable;
    for (int i=0;i<txt1.getSectionPosition().size();i++) {
        for (int j=0;j<txt2.getSectionPosition().size();j++) {
            crossTable.push_back(abs(txt1.getSectionPosition()[i] - txt2.getSectionPosition()[j]));
        }
    }

    // DTW distance computed before is taken into account
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
