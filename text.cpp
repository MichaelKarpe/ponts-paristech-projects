#include "text.h"

//Methods for constructor

/**



/**
 * Method used in constructor
 * Called when cursor at the end of the word,
 */
void Text::addWordToTables(Word &currentWord, int &currentSection) {
    wordIndices[currentWord.getContent()].push_back(currentWord.getIndice());
    if (wordIndices[currentWord.getContent()].size()==1) {
        words.push_back(currentWord.getContent());
        vector<string> cluster;
        cluster.push_back(currentWord.getContent());
        wordsClusters.push_back(cluster);
    }
    wordPosition[currentWord.getContent()].push_back(sizeCleanedText-currentWord.getSize());
    //cout << sizeCleanedText-currentWord.getSize() << endl;
    if (wordSectionIndices[currentWord.getContent()].empty() || wordSectionIndices[currentWord.getContent()].back()!=currentSection)
        wordSectionIndices[currentWord.getContent()].push_back(currentSection);

    currentWord.setContent("");
    currentWord.setIndice(sizeCleanedText+1);
    nbWords+=1;
}

void Text::addCharToCleanedText(const char character, int &currentSection) {
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

void Text::addSpaceToCleanedText(const string line, const int indChar, int &currentSection) {
    if (line[indChar+1]!='\n') {
        addCharToCleanedText(' ', currentSection);
        nbSpaces+=1;
    }
}

void Text::changeSection(int &currentSection) {
    currentSection+=1;
    nbSections+=1;
    //cout << currentSection << endl;
}


//Constructor

Text::Text(char* filename, double thresholdOftenUsedWords)
{
    //Initialization
    nbSections = 0;
    nbSpaces = 0;
    nbWords = 0;
    sizeText = 0;
    sizeCleanedText = 0;

    char punctuationtable[7] = {'.' , ',' , ';' , '\'' , '(' , ')', '-'};
    punctuation.insert(punctuation.end(), punctuationtable, punctuationtable+7);

    //Open file
    ifstream filefirst(filename, ios::in);  // on ouvre en lecture // ATTENTION : fichier doit être dans dossier build !
    if(filefirst) {
        char character;
        while(filefirst.get(character))
            content+=character;
    }

    filefirst.close();

    ifstream file(filename, ios::in); //A améliorer

    //Main loop for cleaning text + construct some tables
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

    isLinguaContinua = double(nbSpaces)/double(sizeCleanedText)<0.1;

    //Construct oftenUsedWords
    for (map<string, vector<int> >::iterator it = wordSectionIndices.begin(); it!=wordSectionIndices.end(); ++it)
        if (it->second.size()>=thresholdOftenUsedWords*nbSections)//nbSections/20) //>3 et dtwCompare < 0.1
            oftenUsedWords.push_back(it->first);

    //Construct wordFrequency
    for (map<string, vector<int> >::iterator it = wordIndices.begin(); it!=wordIndices.end(); ++it)
        wordFrequency[it->first]=double(it->second.size())/double(nbWords);

    //Normalize wordPosition
    for (map<string, vector<double> >::iterator it = wordPosition.begin(); it!=wordPosition.end(); ++it)
        for (int i=0;i<it->second.size();i++)
            it->second[i]=double(it->second[i])/double(sizeCleanedText);

    //Construct wordRecency
    for (map<string, vector<double> >::iterator it = wordPosition.begin(); it!=wordPosition.end(); ++it) {
        double temp = it->second[0];
        wordRecency[it->first].push_back(temp);
        if (it->second.size()>1) {
            for (int i=1;i<it->second.size();i++) {
                wordRecency[it->first].push_back(it->second[i]-temp);
                temp=it->second[i];
            }
        }
        wordRecency[it->first].push_back(1-temp);
    }

    //Normalization of sectionPosition
    double somme = 0;
    //for (map<int,int>::iterator it = sizeSections.begin(); it!=sizeSections.end(); ++it) {
    for (int i=0; i<sizeSections.size();i++) {
        sectionPosition[i] = somme/sizeCleanedText;
        somme += sizeSections[i];
    }
}


///Assesseurs

//Get

string Text::getContent() const {
    return content;
}

int Text::getNbSections() const {
    return nbSections;
}

int Text::getNbSpaces() const {
    return nbSpaces;
}

int Text::getNbWords() const {
    return nbWords;
}

int Text::getSizeText() const {
    return sizeText;
}

int Text::getSizeCleanedText() const {
    return sizeCleanedText;
}

bool Text::getIsLinguaContinua() const {
    return isLinguaContinua;
}

vector<string> Text::getWords() const {
    return words;
}

vector<vector<string> > &Text::getWordsClusters() {
    return wordsClusters;
}

vector<string> Text::getOftenUsedWords() const {
    return oftenUsedWords;
}

map<int, int> Text::getSizeSections() const {
    return sizeSections;
}

map<int, double> Text::getSectionPosition() const {
    return sectionPosition;
}

map<string, vector<int> > Text::getWordIndices() const {
    return wordIndices;
}

map<string, vector<double> > Text::getWordPosition() const {
    return wordPosition;
}

map<string, vector<double> > Text::getWordRecency() const {
    return wordRecency;
}

map<string, vector<int> > Text::getWordSectionIndices() const {
    return wordSectionIndices;
}

map <int, string> Text::getSectionContent() const {
    return sectionContent;
}
