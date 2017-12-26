#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cctype> //tolower
#include <algorithm> //find
using namespace std;

#include <map>

//#ifndef TEXT_H
//#define TEXT_H


class Word {
    string content;
    int indice;

public:
    string getContent();
    int getIndice();
    int getSection();
    int getSize();

    void setContent(string ncontent);
    void setIndice(int nindice);
    void setSection(int nsection);

    Word(string ncontent, int nindice);
};


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

    map<int, int> sizeSections; // Dictionnaire : {indice section : taille de la section}
    map<int, string> sectionContent; // Dictionnaire : {indice section : texte de la section}

    map<string, vector<int> > wordIndices; // Dictionnaire {mot : [indice1, ..., indicen]}
    map<string, vector<int> > wordPosition; // Dictionnaire {mot : [position1, ..., positionn]} (les positions sont normalisées)
    map<string, vector<int> > wordRecency; // Dictionnaire de récence normalisée
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

    map<int, int> getSizeSections();
    map <int, string> getSectionContent();

    map<string, vector<int> > getWordIndices();
    map<string, vector<int> > getWordPosition();
    map<string, vector<int> > getWordRecency();
    map<string, vector<int> > getWordSectionIndices();

    //Set
//    void setWordIndices();
//    void setWordPosition();
//    void setWordRecency();
//    void setWordSectionIndices();
//    void setSectionContent();

    //Tests
    void Tests();
};

//#endif // TEXT_H
