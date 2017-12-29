#include "text.h"

//Methods for constructor

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

Text::Text(char* filename)
{
    //Initialization
    nbSections = 0;
    nbSpaces = 0;
    nbWords = 0;
    sizeText = 0;
    sizeCleanedText = 0;

    char punctuationtable[6] = {'.' , ',' , ';' , '\'' , '(' , ')'};
    punctuation.insert(punctuation.end(), punctuationtable, punctuationtable+6);

    //Ne fonctionne pas si on met filename...
    ifstream filefirst(filename, ios::in);  // on ouvre en lecture // ATTENTION : fichier doit être dans dossier build !
    if(filefirst) {
        char character;
        while(filefirst.get(character))
            content+=character;
    }

    filefirst.close();

    ifstream file(filename, ios::in);

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
        if (it->second.size()>=3)//nbSections/20) //>3 et dtwCompare < 0.1
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

}


///Assesseurs

//Get

string Text::getContent() {
    return content;
}

int Text::getNbSections() {
    return nbSections;
}

int Text::getNbSpaces() {
    return nbSpaces;
}

int Text::getNbWords() {
    return nbWords;
}

int Text::getSizeText() {
    return sizeText;
}

int Text::getSizeCleanedText() {
    return sizeCleanedText;
}

bool Text::getIsLinguaContinua() {
    return isLinguaContinua;
}

vector<string> Text::getWords() {
    return words;
}

vector< vector<string> > Text::getWordsClusters() {
    return wordsClusters;
}

vector<string> Text::getOftenUsedWords() {
    return oftenUsedWords;
}

map<int, int> Text::getSizeSections() {
    return sizeSections;
}

map<string, vector<int> > Text::getWordIndices() {
    return wordIndices;
}

map<string, vector<double> > Text::getWordPosition() {
    return wordPosition;
}

map<string, vector<double> > Text::getWordRecency() {
    return wordRecency;
}

map<string, vector<int> > Text::getWordSectionIndices() {
    return wordSectionIndices;
}

map <int, string> Text::getSectionContent() {
    return sectionContent;
}



///Clustering methods

void Text::hierarchicClustering(double threshold = 0.8) {
    int size = wordsClusters.size();
    //double* distances = new double[size*size];
    double maxsim = 0;
    int i = 0, j = 0;
    for (int k=0;k<size;k++)
        for (int l=k+1;l<size;l++) {
            double dist = 0;
            for (int m=0;m<wordsClusters[k].size();m++)
                for (int n=0;n<wordsClusters[l].size();n++)
                    dist+=jaro_winkler_distance(wordsClusters[k][m], wordsClusters[l][n], 0.1);
            dist=dist/(wordsClusters[k].size()*wordsClusters[l].size());
            if (dist>maxsim) {
                maxsim = dist; i = k; j = l;
            }
            //distances[i*size+j]=jaro_winkler_distance(wordsClusters[i][0], wordsClusters[j][0], 0.1);
            //cout << distances[i*size+j] << endl;
        }

    if (maxsim>=threshold) {
        //Affichage du nb de clusters
        cout << size << endl;
        swap(wordsClusters[j], wordsClusters[size-1]);
        for (int k=0; k<wordsClusters[size-1].size();k++)
            wordsClusters.at(i).push_back(wordsClusters[size-1].at(k));
        wordsClusters.pop_back();
        this->hierarchicClustering(threshold);
    }
    else {
        for (int k=0; k<size;k++) {
            if (wordsClusters[k].size()>=2) {
                for (int l=0; l<wordsClusters[k].size();l++)
                    cout << wordsClusters[k][l] << " ; ";
                cout << endl;
                cout << endl;
            }
        }
        cout << "Fini" << endl;
    }
}
