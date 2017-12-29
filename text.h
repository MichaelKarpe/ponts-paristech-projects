#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cctype> //tolower
#include <algorithm> //find
#include <cmath> //abs
using namespace std;

#include <map>
#include "word.h"

//#ifndef TEXT_H
//#define TEXT_H

class Text
{
    vector<char> punctuation;

    string content;
    string cleanedContent; // Texte nettoyé

    int nbSections; // OK, vérifié
    int nbSpaces; // OK, vérifié
    int nbWords; // Pas bon, à revoir
    int sizeText;
    int sizeCleanedText; // OK, vérifié
    bool isLinguaContinua;

    vector<string> words;
    vector< vector<string> > wordsClusters;
    vector<string> oftenUsedWords;

    map<int, int> sizeSections; // Dictionnaire : {indice section : taille de la section}
    map<int, string> sectionContent; // Dictionnaire : {indice section : texte de la section}

    map<string, vector<int> > wordIndices; // Dictionnaire {mot : [indice1, ..., indicen]}
    map<string, vector<double> > wordPosition; // Dictionnaire {mot : [position1, ..., positionn]} (les positions sont normalisées)
    map<string, vector<double> > wordRecency; // Dictionnaire de récence normalisée
    map<string, vector<int> > wordSectionIndices; // Dictionnaire {mot : [indicesection1, ..., indicesectionn]}
    map<string, double> wordFrequency;

    //Methods for constructor
    void addWordToTables(Word &currentWord, int &currentSection);
    void addCharToCleanedText(char character, int &currentSection);
    void addSpaceToCleanedText(string line, int indChar, int &currentSection);
    void changeSection(int &currentSection);

public:
    //Constructor
    Text(char *filename);

    //Assessors
    //Get
    string getContent();

    int getNbSections();
    int getNbSpaces();
    int getNbWords();
    int getSizeText();
    int getSizeCleanedText();
    bool getIsLinguaContinua();

    map<int, int> getSizeSections();
    map <int, string> getSectionContent();

    vector<string> getWords();
    vector< vector<string> > getWordsClusters();
    vector<string> getOftenUsedWords();

    map<string, vector<int> > getWordIndices();
    map<string, vector<double> > getWordPosition();
    map<string, vector<double> > getWordRecency();
    map<string, vector<int> > getWordSectionIndices();

    //Set
//    void setWordIndices();
//    void setWordPosition();
//    void setWordRecency();
//    void setWordSectionIndices();
//    void setSectionContent();

    void hierarchicClustering(double threshold);
};

double jaro_winkler_distance(string str1, string str2, double coeff_winkler);

//#endif // TEXT_H
