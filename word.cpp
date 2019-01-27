#include "word.h"

Word::Word()
{

}

Word::Word(string ncontent, int nindice) {
    content=ncontent;
    indice=nindice;
}

///--------------------Assessors--------------------///

///-----------------------Get-----------------------///

string Word::getContent() const {
    return content;
}

int Word::getIndice() const {
    return indice;
}

int Word::getSize() const {
    return content.length();
}

///-----------------------Set-----------------------///

void Word::setContent(string ncontent) {
    content=ncontent;
}

void Word::setIndice(int nindice) {
    indice=nindice;
}
