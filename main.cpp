// Project:  Projet MOPSI
// Author:   Michaël Karpe & Bastien Déchamps
// Date:     30/12/2017

#include <iostream>
using namespace std;

//#include "text.h"
//#include "distance.h"

#include "compare.h"
#include "tests.h"

int main()
{
    //Attention : le cas "Lingua Continua" n'est pas traité !
    //warning à cause types char / string

    Text udhr_fr("udhr_fr.txt",3./89);  //Seuil pour oftenUsedWords (mots présents dans 3 sections minimum)
    Tests tests_fr(udhr_fr);            //Comparer avec bcp présents dans un texte (mais par ex que dans 1 section) ?

    Text udhr_en("udhr_en.txt",3./88);
    Tests tests_en(udhr_en);

//    Text udhr_es("udhr_es.txt");
//    Tests tests_es(udhr_es);

//    Text udhr_de("udhr_de.txt");
//    Tests tests_de(udhr_de);

//    Text udhr_ru("udhr_ru.txt");
//    Tests tests_ru(udhr_ru);

//    Text udhr_ar("udhr_ar.txt");
//    Tests tests_ar(udhr_ar);

//    Ne fonctionne pas du tout !
//    Text udhr_ch("udhr_ch.txt");
//    Tests tests_ch(udhr_ch);

    //vector< pair<string,string> > compare = compareOftenUsedWords(udhr_fr,udhr_en);
    //map< pair<string,string>,double > dtwcompare = DTWCompare(udhr_fr,udhr_en,compare, 0.1);

    hierarchicClustering(udhr_fr,0.8);
    hierarchicClustering(udhr_en,0.8);

    map< pair< vector<string>,vector<string> >,double > jrcompareclusters = JRCompareClusters(udhr_fr,udhr_en, 0.9); //JW distance




    return 0;
}
