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
    void addCharToCleanedText(const char character, int &currentSection);
    void addSpaceToCleanedText(const string line, const int indChar, int &currentSection);
    void changeSection(int &currentSection);

public:
    //Constructor
    Text(char *filename, double thresholdOftenUsedWords);

    //Assessors
    //Get
    string getContent() const;

    int getNbSections() const;
    int getNbSpaces() const;
    int getNbWords() const;
    int getSizeText() const;
    int getSizeCleanedText() const;
    bool getIsLinguaContinua() const;

    map<int, int> getSizeSections() const;
    map <int, string> getSectionContent() const;

    vector<string> getWords() const;
    vector< vector<string> > &getWordsClusters();
    vector<string> getOftenUsedWords() const;

    map<string, vector<int> > getWordIndices() const;
    map<string, vector<double> > getWordPosition() const;
    map<string, vector<double> > getWordRecency() const;
    map<string, vector<int> > getWordSectionIndices() const;

    //Set
//    void setWordIndices();
//    void setWordPosition();
//    void setWordRecency();
//    void setWordSectionIndices();
//    void setSectionContent();

};

double jaro_winkler_distance(const string str1, const string str2, const double coeff_winkler);

//#endif // TEXT_H
