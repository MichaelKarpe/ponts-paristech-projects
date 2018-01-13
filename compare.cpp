#include "compare.h"

Compare::Compare()
{

}

//Return couples of often used words in both texts
vector< pair<string,string> > compareOftenUsedWords(const Text txt1, const Text txt2) {
    vector< pair<string,string> > couples;
    for (int i=0;i<txt1.getOftenUsedWords().size();i++)
        for (int j=0;j<txt2.getOftenUsedWords().size();j++)
            if (txt1.getWordIndices()[txt1.getOftenUsedWords()[i]].size()<2*txt2.getWordIndices()[txt2.getOftenUsedWords()[j]].size() && txt2.getWordIndices()[txt2.getOftenUsedWords()[j]].size()<2*txt1.getWordIndices()[txt1.getOftenUsedWords()[i]].size()) {
                couples.push_back(make_pair(txt1.getOftenUsedWords()[i],txt2.getOftenUsedWords()[j]));
                //cout << txt1.getOftenUsedWords()[i] << " ; " << txt2.getOftenUsedWords()[j] << endl;
            }

    return couples;
}

//Compute DTW for couples of often used words with threshold btw 0 and 1
map< pair<string,string>,double > DTWCompare(const Text txt1, const Text txt2, const vector< pair<string,string> > compare, const double threshold) {
    map< pair<string,string>,double > dtwCompare;
    map<string,string> dict1to2;
    map<string,string> dict2to1;
    for (int i=0;i<compare.size();i++) {
        vector<double> rec1 = txt1.getWordRecency()[compare[i].first];
        vector<double> rec2 = txt2.getWordRecency()[compare[i].second];
        double dtw = DTW(rec1,rec2);
        //dtwCompare[compare[i]]=DTW(rec1,rec2);
        if (dtw<threshold) {
            dict1to2[compare[i].first] = compare[i].second;
            dict2to1[compare[i].second] = compare[i].first;
            dtwCompare[compare[i]]=dtw;
            cout << compare[i].first << " ; " << compare[i].second << " : " << dtwCompare[compare[i]] << endl;
//          Pas une bonne approche : un mot peut être traduit de plusieurs façons, et comme boucle for qui supprime, pas efficace
//            //If both words not in dictionnaries
//            if (dict1to2.find(compare[i].first)==dict1to2.end() && dict2to1.find(compare[i].second)==dict2to1.end() ) {
//                dict1to2[compare[i].first] = compare[i].second;
//                dict2to1[compare[i].second] = compare[i].first;
//                dtwCompare[compare[i]]=dtw;
//                cout << compare[i].first << " ; " << compare[i].second << " : " << dtwCompare[compare[i]] << endl;
//            }
//            //If word of 2nd language already in dictionnary
//            else if (dict1to2.find(compare[i].first)==dict1to2.end()) {
//                if (dtw<dtwCompare[make_pair(dict2to1[compare[i].second],compare[i].second)]) {
//                    dict2to1[compare[i].second] = compare[i].first;
//                    dtwCompare[compare[i]]=dtw;
//                    cout << compare[i].first << " ; " << compare[i].second << " : " << dtwCompare[compare[i]] << " is better" << endl;
//                }
//            }
//            //If word of 1st language already in dictionnary
//            else if (dict2to1.find(compare[i].second)==dict2to1.end()) {
//                if (dtw<dtwCompare[make_pair(compare[i].first, dict1to2[compare[i].first])]) {
//                    dict1to2[compare[i].first] = compare[i].second;
//                    dtwCompare[compare[i]]=dtw;
//                    cout << compare[i].first << " ; " << compare[i].second << " : " << dtwCompare[compare[i]] << " is better" << endl;
//                }
//            }
        }
    }
    return dtwCompare;
}

//Compute average Jaro-Winkler distance between clusters of both texts (does not work yet)
map< pair< vector<string>,vector<string> >,double > JRCompareClusters(Text txt1, Text txt2, const double threshold) { //faire en sorte de passer const ?
    map< pair< vector<string>, vector<string> >, double > JRCompare;
    map< vector<string>, vector<string> > dict1to2;
    map< vector<string>, vector<string> > dict2to1;
    //For all pairs of clusters
    for (int i=0;i<txt1.getWordsClusters().size();i++)
        for (int j=0;j<txt2.getWordsClusters().size();j++) {
            //Compute average DTW
            double averageJR = 0;
            for (int k=0;k<txt1.getWordsClusters()[i].size();k++)
                for (int l=0;l<txt2.getWordsClusters()[j].size();l++) {
                    //Attention : erreur, pas DTW mais Jaro Winkler !
                    //DTWmean+=DTW(txt1.getWordRecency()[txt1.getWordsClusters()[i][k]], txt2.getWordRecency()[txt2.getWordsClusters()[j][l]]);
                    averageJR+=jaro_winkler_distance(txt1.getWordsClusters()[i][k], txt2.getWordsClusters()[j][l]);
                }
            averageJR/=(txt1.getWordsClusters()[i].size()*txt2.getWordsClusters()[j].size());
            //If averageJR over threshold, associate clusters
            if (averageJR>=threshold) {
                JRCompare[make_pair(txt1.getWordsClusters()[i],txt2.getWordsClusters()[j])]=averageJR;
                for (int k=0;k<txt1.getWordsClusters()[i].size();k++)
                    cout << txt1.getWordsClusters()[i][k] << " ; ";
                cout << endl;
                for (int l=0;l<txt2.getWordsClusters()[j].size();l++)
                    cout << txt2.getWordsClusters()[j][l] << " ; ";
                cout << endl;
                cout << "JR Mean : " << averageJR << endl;
            }
        }

    return JRCompare;


}


