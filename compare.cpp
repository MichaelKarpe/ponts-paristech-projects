#include "compare.h"

// Return couples of often used words in both texts
vector< pair<string, string> > compareOftenUsedWords(const Text txt1, const Text txt2) {
    vector< pair<string, string> > couples;
    for (int i = 0; i < txt1.getOftenUsedWords().size(); i++)
        for (int j = 0; j < txt2.getOftenUsedWords().size(); j++)
            if (
                    txt1.getWordIndices()[txt1.getOftenUsedWords()[i]].size() < 2 * txt2.getWordIndices()[txt2.getOftenUsedWords()[j]].size() &&
                    txt2.getWordIndices()[txt2.getOftenUsedWords()[j]].size() < 2 * txt1.getWordIndices()[txt1.getOftenUsedWords()[i]].size()
               )
                couples.push_back(make_pair(txt1.getOftenUsedWords()[i], txt2.getOftenUsedWords()[j]));
    return couples;
}

// Compute DTW for couples of often used words with threshold btw 0 and 1
map< pair<string, string>,double > DTWCompare(const Text txt1, const Text txt2, const vector< pair<string, string> > compare, const double threshold) {
    map< pair<string, string>,double > dtwCompare;
    map<string, string> dict1to2;
    map<string, string> dict2to1;
    for (int i = 0; i < compare.size(); i++) {
        vector<double> rec1 = txt1.getWordRecency()[compare[i].first];
        vector<double> rec2 = txt2.getWordRecency()[compare[i].second];
        double dtw = DTW(rec1, rec2);
        // dtwCompare[compare[i]] = DTW(rec1, rec2);
        if (dtw < threshold) {
            dict1to2[compare[i].first] = compare[i].second;
            dict2to1[compare[i].second] = compare[i].first;
            dtwCompare[compare[i]] = dtw;
            cout << compare[i].first << " ; " << compare[i].second << " : " << dtwCompare[compare[i]] << endl;
//          // Not a good approach: a word may be translated in many ways, and as the for loop deletes, not efficient
//            // If both words not in dictionnaries
//            if (dict1to2.find(compare[i].first) == dict1to2.end() && dict2to1.find(compare[i].second) == dict2to1.end()) {
//                dict1to2[compare[i].first] = compare[i].second;
//                dict2to1[compare[i].second] = compare[i].first;
//                dtwCompare[compare[i]] = dtw;
//                cout << compare[i].first << " ; " << compare[i].second << " : " << dtwCompare[compare[i]] << endl;
//            }
//            //If word of 2nd language already in dictionnary
//            else if (dict1to2.find(compare[i].first) == dict1to2.end()) {
//                if (dtw < dtwCompare[make_pair(dict2to1[compare[i].second], compare[i].second)]) {
//                    dict2to1[compare[i].second] = compare[i].first;
//                    dtwCompare[compare[i]] = dtw;
//                    cout << compare[i].first << " ; " << compare[i].second << " : " << dtwCompare[compare[i]] << " is better" << endl;
//                }
//            }
//            //If word of 1st language already in dictionnary
//            else if (dict2to1.find(compare[i].second) == dict2to1.end()) {
//                if (dtw < dtwCompare[make_pair(compare[i].first, dict1to2[compare[i].first])]) {
//                    dict1to2[compare[i].first] = compare[i].second;
//                    dtwCompare[compare[i]] = dtw;
//                    cout << compare[i].first << " ; " << compare[i].second << " : " << dtwCompare[compare[i]] << " is better" << endl;
//                }
//            }
        }
    }
    return dtwCompare;
}

// Compute average Jaro-Winkler distance between clusters of both texts (does not work yet)
map< pair< vector<string>, vector<string> >, double > JRCompareClusters(Text txt1, Text txt2, const double threshold) {  // TODO: set as const?
    map< pair< vector<string>, vector<string> >, double > JRCompare;
    map< vector<string>, vector<string> > dict1to2;
    map< vector<string>, vector<string> > dict2to1;
    // For all pairs of clusters
    for (int i = 0; i < txt1.getWordsClusters().size(); i++)
        for (int j = 0; j < txt2.getWordsClusters().size(); j++) {
            // Compute average DTW
            double averageJR = 0;
            for (int k = 0; k < txt1.getWordsClusters()[i].size(); k++)
                for (int l = 0; l < txt2.getWordsClusters()[j].size(); l++) {
                    // Warning: Error, not DTW but Jaro Winkler!
                    // DTWmean += DTW(txt1.getWordRecency()[txt1.getWordsClusters()[i][k]], txt2.getWordRecency()[txt2.getWordsClusters()[j][l]]);
                    averageJR+=jaro_winkler_distance(txt1.getWordsClusters()[i][k], txt2.getWordsClusters()[j][l]);
                }
            averageJR /= txt1.getWordsClusters()[i].size() * txt2.getWordsClusters()[j].size();
            // If averageJR over threshold, associate clusters
            if (averageJR >= threshold) {
                JRCompare[make_pair(txt1.getWordsClusters()[i], txt2.getWordsClusters()[j])] = averageJR;
                for (int k = 0; k < txt1.getWordsClusters()[i].size(); k++)
                    cout << txt1.getWordsClusters()[i][k] << " ; ";
                cout << endl;
                for (int l = 0; l < txt2.getWordsClusters()[j].size(); l++)
                    cout << txt2.getWordsClusters()[j][l] << " ; ";
                cout << endl;
                cout << "JR Mean : " << averageJR << endl;
            }
        }

    return JRCompare;

}

map<pair<string, string>, double> DTWGroups(Text txt1, Text txt2, const map<pair<string, string>, double> &DTWcomp) {
    map<pair<string, string>, double> CompareGroups;
    // On parcourt les paires de mots calculées à l'aide de DTWCompare
    for (map<pair<string,string>, double>::const_iterator it = DTWcomp.begin(); it != DTWcomp.end(); ++it) {
        string w1 = (it->first).first;
        string w2 = (it->first).second;
        // On va former des groupes de mots en ajoutant les mots à gauche et/ou à droite des mots courants dans les 2 textes
        // On ne gardera que les groupes de mots significatifs (qui apparaissent un nb suffisant de fois)
        map<string, int> groupsOccur1;
        map<string, int> groupsOccur2;
        // En vue de calculer la distance DTW entre ces groupes de mots, on calcule leur position (et donc leur récence)
        map<string, vector<double> > groupsPosition1;
        map<string, vector<double> > groupsPosition2;

        // Indices de chaque mot
        vector<int> indw1 = txt1.getWordIndices()[w1];
        vector<int> indw2 = txt2.getWordIndices()[w2];

        // Calcul de groupsOccur1 et groupsPosition1
        int compt = 0;
        for(vector<int>::iterator ind1 = indw1.begin(); ind1 != indw1.end(); ++ind1) {
            if((*ind1) > 0 && (*ind1) < txt1.getNbWords()-1) {
                groupsOccur1[txt1.getWords().at(*ind1 - 1) + " " + txt1.getWords().at(*ind1)]++;
                groupsOccur1[txt1.getWords().at(*ind1) + " " + txt1.getWords().at(*ind1 + 1)]++;
                groupsOccur1[txt1.getWords().at(*ind1 - 1) + " " + txt1.getWords().at(*ind1) + " " + txt1.getWords().at(*ind1 + 1)]++;
                // Approximation ici : on considère que la position du groupe de mot est celle du mot dans le texte
                groupsPosition1[txt1.getWords().at(*ind1 - 1) + " " + txt1.getWords().at(*ind1)].push_back((txt1.getWordPosition()[w1]).at(compt));
                groupsPosition1[txt1.getWords().at(*ind1) + " " + txt1.getWords().at(*ind1 + 1)].push_back(txt1.getWordPosition()[w1].at(compt));
                groupsPosition1[txt1.getWords().at(*ind1 - 1) + " " + txt1.getWords().at(*ind1) + " " + txt1.getWords().at(*ind1 + 1)].push_back(txt1.getWordPosition()[w1].at(compt));
                compt++;
            }
        }

        // Calcul de groupsOccur2 et groupsPosition2
        compt = 0;
        for(vector<int>::iterator ind2 = indw2.begin(); ind2 != indw2.end(); ++ind2) {
            if((*ind2) > 0 && (*ind2) < txt2.getNbWords()-1) {
                groupsOccur2[txt2.getWords().at(*ind2 - 1) + " " + txt2.getWords().at(*ind2)]++;
                groupsOccur2[txt2.getWords().at(*ind2) + " " + txt2.getWords().at(*ind2 + 1)]++;
                groupsOccur2[txt2.getWords().at(*ind2 - 1) + " " + txt2.getWords().at(*ind2) + " " + txt2.getWords().at(*ind2 + 1)]++;

                groupsPosition2[txt2.getWords().at(*ind2 - 1) + " " + txt2.getWords().at(*ind2)].push_back(txt2.getWordPosition()[w2].at(compt));
                groupsPosition2[txt2.getWords().at(*ind2) + " " + txt2.getWords().at(*ind2 + 1)].push_back(txt2.getWordPosition()[w2].at(compt));
                groupsPosition2[txt2.getWords().at(*ind2 - 1) + " " + txt2.getWords().at(*ind2) + " " + txt2.getWords().at(*ind2 + 1)].push_back(txt2.getWordPosition()[w2].at(compt));
                compt++;
            }
        }

        // Post-traitement : on enlève les groupes inintéressants (si pas assez nombreux)
        for (map<string,int>::iterator gr = groupsOccur1.begin(); gr != groupsOccur1.end(); ++gr)
            if(gr->second < nb_group)
                groupsPosition1.erase(gr->first);

        for (map<string,int>::iterator gr = groupsOccur2.begin(); gr != groupsOccur2.end(); ++gr)
            if(gr->second < nb_group)
                groupsPosition2.erase(gr->first);

        // On calcule la le vecteur de récence de chaque groupe de mot gardé
        map< string, vector<double> > groupsRecency1;
        map< string, vector<double> > groupsRecency2;
        for (map< string, vector<double> >::iterator gr = groupsPosition1.begin(); gr != groupsPosition1.end(); ++gr) {
            double temp = gr->second[0];
            groupsRecency1[gr->first].push_back(temp);
            if (gr->second.size() > 1) {
                for (int i = 1; i < gr->second.size(); i++) {
                    groupsRecency1[gr->first].push_back(gr->second[i] - temp);
                    temp = gr->second[i];
                }
            }
            groupsRecency1[gr->first].push_back(1 - temp);
        }
        for (map< string, vector<double> >::iterator gr = groupsPosition2.begin(); gr!=groupsPosition2.end(); ++gr) {
            double temp = gr->second[0];
            groupsRecency2[gr->first].push_back(temp);
            if (gr->second.size() > 1) {
                for (int i = 1; i < gr->second.size(); i++) {
                    groupsRecency2[gr->first].push_back(gr->second[i] - temp);
                    temp = gr->second[i];
                }
            }
            groupsRecency2[gr->first].push_back(1 - temp);
        }

        // On calcule pour chaque paire de groupe de mot la distance DTW
        for (map< string, vector<double> >::iterator gr1 = groupsRecency1.begin(); gr1 != groupsRecency1.end(); ++gr1) {
            for (map< string, vector<double> >::iterator gr2 = groupsRecency2.begin(); gr2 != groupsRecency2.end(); ++gr2) {
                double dtw = DTW(gr1->second, gr2->second);
                if (dtw < it->second) {
                    CompareGroups[make_pair(gr1->first, gr2->first)] = dtw;
                    cout << gr1->first << " ; " << gr2->first << " : " << dtw << endl;
                }
            }
        }
    }
    return CompareGroups;
}


