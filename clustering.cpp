#include "clustering.h"

Clustering::Clustering()
{

}

///Clustering methods

void hierarchicClustering(Text &txt, const double threshold = 0.8) {
    int size = txt.getWordsClusters().size();
    //double* distances = new double[size*size];
    double maxsim = 0;
    int i = 0, j = 0;

    //Find two clusters with the biggest similarity
    for (int k=0;k<size;k++)
        for (int l=k+1;l<size;l++) {
            double dist = 0;
            for (int m=0;m<txt.getWordsClusters()[k].size();m++)
                for (int n=0;n<txt.getWordsClusters()[l].size();n++)
                    dist+=jaro_winkler_distance(txt.getWordsClusters()[k][m], txt.getWordsClusters()[l][n], 0.1);
            dist=dist/(txt.getWordsClusters()[k].size()*txt.getWordsClusters()[l].size());
            if (dist>maxsim) {
                maxsim = dist; i = k; j = l;
            }
            //distances[i*size+j]=jaro_winkler_distance(txt.getWordsClusters()[i][0], txt.getWordsClusters()[j][0], 0.1);
            //cout << distances[i*size+j] << endl;
        }

    //If the biggest similarity is over threshold, merge the two clusters and use hierarchicClustering
    if (maxsim>=threshold) {
        //Affichage du nb de clusters
        cout << size << endl;
        swap(txt.getWordsClusters()[j], txt.getWordsClusters()[size-1]);
        for (int k=0; k<txt.getWordsClusters()[size-1].size();k++)
            txt.getWordsClusters().at(i).push_back(txt.getWordsClusters()[size-1].at(k));
        txt.getWordsClusters().pop_back();
        hierarchicClustering(txt, threshold);
    }

    //Else, end of the process, display clusters
    else {
        for (int k=0; k<size;k++) {
            if (txt.getWordsClusters()[k].size()>=2) {
                for (int l=0; l<txt.getWordsClusters()[k].size();l++)
                    cout << txt.getWordsClusters()[k][l] << " ; ";
                cout << endl;
                cout << endl;
            }
        }
        cout << "Fini" << endl;
    }
}
