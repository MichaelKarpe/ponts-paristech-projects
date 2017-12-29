// Project:  Projet MOPSI
// Author:   Michaël Karpe & Bastien Déchamps
// Date:     29/12/2017

#include <iostream>
using namespace std;

//#include "text.h"
//#include "distance.h"

#include "compare.h"
#include "tests.h"

int main()
{
    Text dudh_fr("dudh_fr.txt"); //warning à cause types char / string
    Tests testsfr(dudh_fr);

    Text dudh_en("dudh_en.txt"); //warning à cause types char / string
    Tests testsen(dudh_en);

    vector< pair<string,string> > compare = compareOftenUsedWords(dudh_fr,dudh_en);
    map< pair<string,string>,double > dtwcompare = DTWCompare(dudh_fr,dudh_en,compare);

    //dudh_fr.hierarchicClustering(0.8);


    return 0;
}
