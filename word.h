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
    string getContent();
    int getIndice();
    int getSection();
    int getSize();

    void setContent(string ncontent);
    void setIndice(int nindice);
    void setSection(int nsection);

    Word(string ncontent, int nindice);
};
//#endif // WORD_H
