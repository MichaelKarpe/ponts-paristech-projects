#pragma once
//#ifndef WORD_H
//#define WORD_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cctype> //tolower
#include <algorithm> //find
#include <cmath> //abs
using namespace std;

#include <map>


class Word {
    string content;
    int indice;

public:
    Word();
    Word(string ncontent, int nindice);

    string getContent() const;
    int getIndice() const;
    int getSize() const;

    void setContent(string ncontent);
    void setIndice(int nindice);
};

//#endif // WORD_H
