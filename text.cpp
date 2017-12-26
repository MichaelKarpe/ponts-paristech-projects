#include "text.h"


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


//Methods for constructor
void Text::addWordToTables(Word &currentWord, int &currentSection) {
    wordIndices[currentWord.getContent()].push_back(currentWord.getIndice());
    wordPosition[currentWord.getContent()].push_back(sizeCleanedText-currentWord.getSize());
    if (wordSectionIndices[currentWord.getContent()].empty() || wordSectionIndices[currentWord.getContent()].back()!=currentSection)
        wordSectionIndices[currentWord.getContent()].push_back(currentSection);

    currentWord.setContent("");
    currentWord.setIndice(sizeCleanedText+1);
    nbWords+=1;
}

void Text::addCharToCleanedText(char character, int &currentSection) {
    cleanedContent+=character;
    if (character!='\n') {
        sizeCleanedText+=1;
        sizeSections[currentSection]+=1;
        sectionContent[currentSection]+=character;
    }
    if(int(character)<0 && int(character)!=-61) { //si accent : double caractère avec premier tq int = -61
        sizeCleanedText-=1;
        sizeSections[currentSection]-=1;
    }
}

void Text::addSpaceToCleanedText(string line, int indChar, int &currentSection) {
    if (line[indChar+1]!='\n') {
        addCharToCleanedText(' ', currentSection);
        nbSpaces+=1;
    }
}

void Text::changeSection(int &currentSection) {
    currentSection+=1;
    nbSections+=1;
}


//Constructor

Text::Text(string filename)
{
    //Initialization
    nbSections = 0; // Normalement OK
    nbSpaces = 0; // OK, vérifié
    nbWords = 0; // Pas bon, à revoir
    sizeText = 0; // = 0; // Argument non self ?
    sizeCleanedText = 0; // = 0; // OK, vérifié

    char punctuationtable[6] = {'.' , ',' , ';' , '\'' , '(' , ')'};
    punctuation.insert(punctuation.end(), punctuationtable, punctuationtable+6);
    //Ne fonctionne pas si on met filename...
    ifstream filefirst("dudh_fr.txt", ios::in);  // on ouvre en lecture // ATTENTION : fichier doit être dans dossier build !
    if(filefirst) {
        char character;
        while(filefirst.get(character))
            content+=character;
    }

    filefirst.close();

    ifstream file("dudh_fr.txt", ios::in);

    int currentSection = 0;
    if(file) {
        string line;
        while(getline(file, line)) {

            line+="\n";
            Word currentWord("", sizeCleanedText);

            for (int indChar=0;indChar<line.size();indChar++) {
                char character = line[indChar];

                if (character==' ') {
                    if (*cleanedContent.rbegin()!=' ' && *cleanedContent.rbegin()!='\n') { //cleanedContent.back() seulement pour C++11
                        addWordToTables(currentWord, currentSection);
                        addSpaceToCleanedText(line, indChar, currentSection);
                    }
                }

                else if (character=='\n') {
                    if (*cleanedContent.rbegin()!='\n') {
                        addCharToCleanedText(character, currentSection);
                        changeSection(currentSection);
                        if (line[indChar-1]!=' ' && indChar!=0)
                            addWordToTables(currentWord, currentSection);
                    }
                }

                else {
                    if (find(punctuation.begin(), punctuation.end(), character) != punctuation.end()) { //character in punctuation
                        if (*cleanedContent.rbegin()!=' ' && *cleanedContent.rbegin()!='\n')
                            addSpaceToCleanedText(line, indChar, currentSection);
                        if (line[indChar-1]!=' ' && indChar!=0)
                            addWordToTables(currentWord, currentSection);
                    }
                    else {
                        currentWord.setContent(currentWord.getContent()+char(tolower(character)));
                        addCharToCleanedText(char(tolower(character)), currentSection);
                    }
                }
                sizeText+=1;

            }
        }
    }
    cout << cleanedContent << endl;

    isLinguaContinua = double(nbSpaces)/double(sizeCleanedText)<0.1;

    for (map<string, vector<int> >::iterator it = wordIndices.begin(); it!=wordIndices.end(); ++it)
        wordFrequency[it->first]=it->second.size()/nbWords;

    for (map<string, vector<int> >::iterator it = wordPosition.begin(); it!=wordPosition.end(); ++it)
        for (int i=0;i<it->second.size();i++)
            it->second[i]/=sizeCleanedText;

    for (map<string, vector<int> >::iterator it = wordPosition.begin(); it!=wordPosition.end(); ++it) {
        int temp = it->second[0];
        wordRecency[it->first].push_back(temp);
        if (it->second.size()>1) {
            for (int i=1;i<it->second.size();i++) {
                wordRecency[it->first].push_back(it->second[i]-temp);
                temp=it->second[i];
            }
        }
        wordRecency[it->first].push_back(1-temp);
    }

}

void Text::Tests() {

    //cout << "Content: " << content << endl;
    //cout << "Cleaned Content: " << cleanedContent << endl;
    cout << "Number of sections: " << nbSections << endl;
    cout << "Number of spaces: " << nbSpaces << endl;
    cout << "Number of words: " << nbWords << endl;
    cout << "Size of text: " << sizeText << endl;
    cout << "Size of cleaned text: " << sizeCleanedText << endl;
    cout << "Is lingua continua: " << isLinguaContinua << endl;

    cout << "Size of sections: ";
    for (map<int, int>::iterator it = sizeSections.begin(); it!=sizeSections.end(); ++it)
        cout << it->second << " ; " ;
    cout << endl;

//    cout << "Word Indices: ";
//    for (map<string, vector<int> >::iterator it = wordIndices.begin(); it!=wordIndices.end(); ++it)
//        cout << it->first << " : " << it->second[0] << " ; ";
//    cout << endl;

//    cout << "Word Section Indices: ";
//    for (map<string, vector<int> >::iterator it = wordSectionIndices.begin(); it!=wordSectionIndices.end(); ++it)
//        cout << it->first << " : " << it->second[0] << " ; ";
//    cout << endl;

    cout << "Section contents: ";
    for (map<int, string>::iterator it = sectionContent.begin(); it!=sectionContent.end(); ++it)
        cout << "Section " << it->first << " : " << it->second << endl;

}

//Assesseurs

//Get

string Text::getContent() {
    return content;
}

int Text::getNbSections() { // = 0; // Normalement OK
    return nbSections;
}

int Text::getNbSpaces() { // = 0; // OK, vérifié
    return nbSpaces;
}

int Text::getNbWords() { // = 0 // Pas bon, à revoir
    return nbWords;
}

int Text::getSizeText() { // = 0; // Argument non self ?
    return sizeText;
}

int Text::getSizeCleanedText() { // = 0; // OK, vérifié
    return sizeCleanedText;
}

map<int, int> Text::getSizeSections() { // = [0]
    return sizeSections;
}

map<string, vector<int> > Text::getWordIndices() { // = {} // Dictionnaire {mot : [indice1, ..., indicen]}
    return wordIndices;
}

map<string, vector<int> > Text::getWordPosition() { // = {} // Dictionnaire {mot : [position1, ..., positionn]} (les positions sont normalisées)
    return wordPosition;
}

map<string, vector<int> > Text::getWordRecency() { // = {} // Dictionnaire de récence normalisée
    return wordRecency;
}

map<string, vector<int> > Text::getWordSectionIndices() { // = {} // Dictionnaire {mot : [indicesection1, ..., indicesectionn]}
    return wordSectionIndices;
}

map <int, string> Text::getSectionContent() {
    return sectionContent;
}
