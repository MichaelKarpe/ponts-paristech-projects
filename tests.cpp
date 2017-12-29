#include "tests.h"

Tests::Tests(Text txt)
{
    //cout << "Content: " << content << endl;
    //cout << "Cleaned Content: " << cleanedContent << endl;
    cout << "Number of sections: " << txt.getNbSections() << endl;
    cout << "Number of spaces: " << txt.getNbSpaces() << endl;
    cout << "Number of words: " << txt.getNbWords() << endl;
    cout << "Size of text: " << txt.getSizeText() << endl;
    cout << "Size of cleaned text: " << txt.getSizeCleanedText() << endl;
    cout << "Is lingua continua: " << txt.getIsLinguaContinua() << endl;

//    cout << "Size of sections: ";
//    for (map<int, int>::iterator it = txt.getSizeSections().begin(); it!=txt.getSizeSections().end(); ++it)
//        cout << it->second << " ; " ;
//    cout << endl;

//    cout << "Words: ";
//    for (int i=0;i<txt.getWords().size();i++)
//        cout << txt.getWords()[i] << " ; ";
//    cout << endl;

//    cout << "Often used words: ";
//    for (int i=0;i<txt.getOftenUsedWords().size();i++)
//        cout << txt.getOftenUsedWords()[i] << " ; ";
//    cout << endl;

//    cout << "Word Indices: ";
//    for (map<string, vector<int> >::iterator it = txt.getWordIndices().begin(); it!=txt.getWordIndices().end(); ++it)
//        cout << it->first << " : " << it->second[0] << " ; ";
//    cout << endl;

//    cout << "Word Section Indices: ";
//    for (map<string, vector<int> >::iterator it = txt.getWordSectionIndices().begin(); it!=txt.getWordSectionIndices().end(); ++it)
//        cout << it->first << " : " << it->second[0] << " ; ";
//    cout << endl;

//    cout << "Section contents: ";
//    for (map<int, string>::iterator it = txt.getSectionContent().begin(); it!=txt.getSectionContent().end(); ++it)
//        cout << "Section " << it->first << " : " << it->second << endl;

//    cout << "Word Positions: ";
//    for (map<string, vector<double> >::iterator it = txt.getWordPosition().begin(); it!=txt.getWordPosition().end(); ++it) {
//        cout << it->first << " : " << it->second[0] << " ; ";
//        for (int i=1;i<it->second.size();i++)
//            cout << it->second[i] << " ; ";
//        cout << endl;
//    }
//    cout << endl;

//    cout << "Word Recency: ";
//    for (map<string, vector<double> >::iterator it = txt.getWordRecency().begin(); it!=txt.getWordRecency().end(); ++it) {
//        cout << it->first << " : " << it->second[0] << " ; ";
//        for (int i=1;i<it->second.size();i++)
//            cout << it->second[i] << " ; ";
//        cout << endl;
//    }
//    cout << endl;
}

