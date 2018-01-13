#pragma once
//#ifndef WORD_H
//#define WORD_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <set>
#include <cctype> //tolower
#include <algorithm> //find
#include <cmath> //abs
using namespace std;

#include <map>

#include "constants.h"


class Word {
    string content;
    int indice;

public:
    /**
     * Empty constructor
     */
    Word();
    /**
     * Constructor
     * @param ncontent word content
     * @param nindice word index
     */
    Word(string ncontent, int nindice);
    /**
     * @return the word as a string
     */
    string getContent() const;
    /**
     * @return the associated index in the text
     */
    int getIndice() const;
    /**
     * @return word length
     */
    int getSize() const;
    /**
     * Replace the string content with ncontent
     * @param ncontent new string to set
     */
    void setContent(string ncontent);
    /**
     * Set the index of the word
     * @param nindice index to set
     */
    void setIndice(int nindice);
};

//#endif // WORD_H
