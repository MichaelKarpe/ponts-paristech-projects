#include "word.h"

Word::Word()
{

}

//Assessors

Word::Word(string ncontent, int nindice) {
    content=ncontent;
    indice=nindice;
}

string Word::getContent() {
    return content;
}

int Word::getIndice() {
    return indice;
}

int Word::getSize() {
    return content.length();
}

void Word::setContent(string ncontent) {
    content=ncontent;
}

void Word::setIndice(int nindice) {
    indice=nindice;
}
