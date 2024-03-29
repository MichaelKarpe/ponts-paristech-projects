/**
  * Project:  Projet MOPSI : Correspondance automatique de textes en langues différentes sans connaissances préalables
  * Author:   Michaël Karpe & Bastien Déchamps
  * Date:     05/02/2018
  */

#include <iostream>
using namespace std;

#include "align.h"
#include "tests.h"

int main()
{
    // The Lingua continua case is not processed yet, therefore algorithms do not work with Chinese language yet
    // Warning at compilation because of conflict between char and string types
    char* filename[7] = {
        "data/udhr_fr.txt", "data/udhr_en.txt", "data/udhr_es.txt", "data/udhr_de.txt", "data/udhr_ru.txt",
        "data/udhr_ar.txt", "data/udhr_ch.txt"
    };

    /// Construct texts from files
    Text udhr1(filename[0], 3. / 89);
    Tests tests1(udhr1);

    Text udhr2(filename[1], 3. / 88);
    Tests tests2(udhr2);


    /// Compute paragraph alignment by length only
    cout << "Alignment by length only:" << endl;
    alignByLength(udhr1, udhr2);

    /// Compute paragraph alignment taking into account DTW distance
    cout << endl << "Alignment with DTW:" << endl;
    alignWithDTW(udhr1, udhr2, 0.1);


    /// Compute DTW groups
//    cout << "Computing DTW groups..." << endl;
//    map<pair<string, string>, double> dtwgroups = DTWGroups(udhr1, udhr2, dtwcompare);


    /// Compute word clustering in languagues
//    cout << "Computing word clusters in both languages..." << endl;
//    hierarchicClustering(udhr_fr);
//    hierarchicClustering(udhr_en);

    /// Compute clusters comparisons with Jaro-Winkler distance over threshold 0.9
//    cout << "Computing Jaro-Winkler distances between clusters..." << endl;
//    map<pair< vector<string>, vector<string> >, double> jrcompareclusters = JRCompareClusters(udhr1, udhr2, 0.9);

    return 0;
}
