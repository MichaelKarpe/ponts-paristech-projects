// Project:  Projet MOPSI
// Author:   Michaël Karpe & Bastien Déchamps
// Date:     30/12/2017

#include <iostream>
using namespace std;

//#include "text.h"
//#include "distance.h"

#include "align.h"
#include "tests.h"



int main()
{
    //Attention : le cas "Lingua Continua" n'est pas traité !
    //warning à cause types char / string
    char* filename[7] = {"udhr_fr.txt", "udhr_en.txt", "udhr_es.txt", "udhr_de.txt", "udhr_ru.txt", "udhr_ar.txt", "udhr_ch.txt"};
    //Marche pas encore en chinois

    Text udhr1(filename[0],3./89);  //Seuil pour oftenUsedWords (mots présents dans 3 sections minimum)
    Tests tests1(udhr1);            //Comparer avec bcp présents dans un texte (mais par ex que dans 1 section) ?

    Text udhr2(filename[1],3./88);
    Tests tests2(udhr2);

    //Compare often used words: display couple of words with smallest DTW distance
    cout << "Couples of matching words :" << endl;
    vector< pair<string,string> > compare = compareOftenUsedWords(udhr1,udhr2);
    map< pair<string,string>,double > dtwcompare = DTWCompare(udhr1,udhr2,compare, 0.1);

    //map< pair<string,string>,double > dtwgroups = DTWGroups(udhr1,udhr2,dtwcompare);
    // Paragraph alignment taking into account DTWDistance
    cout << endl << "Alignement : " << endl;
    alignByLength2(udhr1, udhr2);
    //alignSmart(udhr1, udhr2,dtwcompare);

    //hierarchicClustering(udhr_fr);
    //hierarchicClustering(udhr_en);

    //map< pair< vector<string>,vector<string> >,double > jrcompareclusters = JRCompareClusters(udhr1,udhr2, 0.9); //JW distance

    return 0;
}
