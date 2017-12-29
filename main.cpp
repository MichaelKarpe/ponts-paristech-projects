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
    Text udhr_fr("udhr_fr.txt"); //warning à cause types char / string
    //Tests tests_fr(udhr_fr);

    Text udhr_en("udhr_en.txt"); //warning à cause types char / string
    //Tests tests_en(udhr_en);

//    Text udhr_es("udhr_es.txt"); //warning à cause types char / string
//    Tests tests_es(udhr_es);

//    Text udhr_de("udhr_de.txt"); //warning à cause types char / string
//    Tests tests_de(udhr_de);

//    Text udhr_ru("udhr_ru.txt"); //warning à cause types char / string
//    Tests tests_ru(udhr_ru);

//    Text udhr_ar("udhr_ar.txt"); //warning à cause types char / string
//    Tests tests_ar(udhr_ar);

//    Ne fonctionne pas du tout !
//    Text udhr_ch("udhr_ch.txt"); //warning à cause types char / string
//    Tests tests_ch(udhr_ch);

    vector< pair<string,string> > compare = compareOftenUsedWords(udhr_fr,udhr_en);
    map< pair<string,string>,double > dtwcompare = DTWCompare(udhr_fr,udhr_en,compare);

//    udhr_fr.hierarchicClustering(0.8);


    return 0;
}
