#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cctype>       // tolower
#include <algorithm>    // find
#include <cmath>        // abs
#include <map>
using namespace std;

#include "word.h"

class Text
{
    vector<char> punctuation;

    string content;
    string cleanedContent;  // Cleaned text

    int nbSections;         // OK, checked
    int nbSpaces;           // OK, checked
    int nbWords;            // KO, to be checked
    int sizeText;
    int sizeCleanedText;    // OK, checked
    bool isLinguaContinua;

    vector<string> words;
    vector< vector<string> > wordsClusters;
    vector<string> oftenUsedWords;

    map<int, int> sizeSections;                     // Dictionary : {section indice : section size}
    map<int, string> sectionContent;                // Dictionary : {section indice : section text}
    map<int, double> sectionPosition;               // normalized positions of the sections

    map<string, vector<int> > wordIndices;          // Dictionary {mot : [indice1, ..., indicen]}
    map<string, vector<double> > wordPosition;      // Dictionary {mot : [position1, ..., positionn]} (positions are normalized)
    map<string, vector<double> > wordRecency;       // Dictionary of normalized recency
    map<string, vector<int> > wordSectionIndices;   // Dictionary {mot : [indicesection1, ..., indicesectionn]}
    map<string, double> wordFrequency;

    // Methods for constructor
    void addWordToTables(Word &currentWord, int &currentSection);
    void addCharToCleanedText(const char character, int &currentSection);
    void addSpaceToCleanedText(const string line, const int indChar, int &currentSection);
    void changeSection(int &currentSection);

public:
    /**
     * @brief Constructor: reads the text, cleans it and creates hash tables
     * @param filename name of the file
     * @param thresholdOftenUsedWords threshold between 0 and 1, word considered as often used if over it
     */
    Text(char *filename, double thresholdOftenUsedWords);

    ///--------------------Assessors--------------------///

    ///-----------------------Get-----------------------///

    /**
     * @return the content of the text as a string
     */
    string getContent() const;
    /**
     * @return the number of sections in the text
     */
    int getNbSections() const;
    /**
     * @return the number of spaces in the text
     */
    int getNbSpaces() const;
    /**
     * @return the number of words in the text
     */
    int getNbWords() const;
    /**
     * @return the size of the text
     */
    int getSizeText() const;
    /**
     * @return the size of the cleaned text
     */
    int getSizeCleanedText() const;
    /**
     * @return false if there's spaces in the language else true
     */
    bool getIsLinguaContinua() const;
    /**
     * @return the map of the section indexes with their size
     */
    map<int, int> getSizeSections() const;
    /**
     * @return the map of the normalized positions of the sections
     */
    map<int, double> getSectionPosition() const;
    /**
     * @return the content of each section in a map
     */
    map <int, string> getSectionContent() const;
    /**
     * @return the words of the text in a vector
     */
    vector<string> getWords() const;
    /**
     * @return the cluster
     */
    vector< vector<string> > &getWordsClusters();
    /**
     * @return often used words
     */
    vector<string> getOftenUsedWords() const;
    /**
     * @return the vector of indexes of each word in a map
     */
    map<string, vector<int> > getWordIndices() const;
    /**
     * @return the positions of each word in a map
     */
    map<string, vector<double> > getWordPosition() const;
    /**
     * @return the recency of each word in a map
     */
    map<string, vector<double> > getWordRecency() const;
    /**
     * @return the indexes of the sections in which a word is, in a map
     */
    map<string, vector<int> > getWordSectionIndices() const;
};
