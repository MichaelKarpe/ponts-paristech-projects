// Imagine++ project
// Project:  Vide
// Author:   Michaël Karpe
// Date:     22/05/2017

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <ctime>
using namespace std;
using namespace Imagine;

const int delta = 50; //50
const int sigma2 = 5; //5
const int beta = 5; //5

//Potentiel pour k-means
float pot(int fi, int fj) {
    float pote;
    pote = 1.0 + fabs((float)(fi-fj))/delta;
    return(1.0/pote);
}


//Potentiel phi
float phi(float x) {
    float y;
    y = x*x;
    y = (y/(1.0+y));
    return(y);
}


//Potentiel de clique
float Uclique (float a, float b) {
    float Uo;
    //Modèle de Potts
    Uo = 1.0;
    if (a==b)
        Uo = -1.0;

    //Uo = phi(a-b);
    return(Uo);
}


// Potentiel clique 4-connexe
float U14(float x00,float x10,float x01,float x20,float x02) {
    float Uo;
    Uo = Uclique(x00,x10)+Uclique(x00,x01)+Uclique(x00,x20)+Uclique(x00,x02);
    return(Uo);
}

// Potentiel clique 8-connexe
float U18(float x00,float x10,float x01,float x20,float x02,float x11,float x21,float x12,float x22) {
    float Uo;
    Uo = Uclique(x00,x10)+Uclique(x00,x01)+Uclique(x00,x20)+Uclique(x00,x02);
    Uo += Uclique(x00,x11)+Uclique(x00,x12)+Uclique(x00,x21)+Uclique(x00,x22);
    return(Uo);
}


// Potentiel lié à la source
float U0(float a, float b) {
    float Uo;
    //Uo = phi(a-b);*/
    Uo = ((float) (a-b)*(a-b));
    //Uo=0;
    //if (a!=b)
    //    Uo++;
    return(Uo);
}


//Traitement par k-means
void kmeans(Image<byte> &J, Image<byte> &K) {
    int w=J.width(), h=J.height();
    int pixel[w][h], x, xmin;
    float min, proba;

    for(int i=0; i<w; i++)
        for(int j=0; j<h; j++)
            pixel[i][j] = (int) J(i,j);

    //cliques d'ordre 2 horizontales  et verticales
    for(int passages=0; passages<20; passages++) {
        for(int i=1; i<w-1; i++) {
            for(int j=1; j<h-1; j++) {
                int xmin = 0;
                min = (float)(pixel[i][j]*pixel[i][j])/(2.0*sigma2) - beta*(pot(pixel[i][j-1],0)+pot(pixel[i][j+1],0)+pot(pixel[i-1][j], 0)+pot(pixel[i+1][j], 0)+ pot(pixel[i-1][j-1], x) + pot(pixel[i-1][j+1], x)+pot(pixel[i+1][j-1], x) + pot(pixel[i+1][j+1], x));
                for(int x=1; x<256; x++) {
                    proba = (float)((pixel[i][j]-x)*(pixel[i][j]-x))/(2.0*sigma2) - beta*(pot(pixel[i][j-1],x)+pot(pixel[i][j+1],x)+pot(pixel[i-1][j], x)+pot(pixel[i+1][j], x));
                    if(min>proba) {
                        min = proba;
                        xmin = x;
                    }
                }
                pixel[i][j] = xmin;
            }
        }
    }

    for(int i=0; i<w-1; i++) {
        for(int j=0; j<h-1; j++) {
            K(i,j) = byte(pixel[i][j]);
        }
    }

}

//Traitement par recuit
void recuit(Image<byte> &E, Image<byte> &S) {
    int c = 8; //pour 8 connexité ou 4 connexité
    float s = 1.0; //sigma
    float t = 1.0; //température
    int m = 10; //nb de boucles metropolis
    int n = 10; //nb de boucles recuit

    int numRows = E.height();
    int numCols = E.width();

    int k,i,j,r;
    int lambda;
    int a00,a10,a01,a02,a20,a11,a21,a12,a22;
    float dU;
    float pixmax = 0.0;
    float pixmin = 255.0;

    for (i=0;i<numRows;i++) {
        for (j=0;j<numCols;j++) {
            lambda = (int)E(i,j);
            S(i,j) = (byte)lambda;
            if (lambda>pixmax) pixmax=lambda;
            if (lambda<pixmin) pixmin=lambda;
        }
    }

    //Boucle du recuit simulé
    for (r=0;r<n;r++) {
        //Boucle de l'algorithme de Metropolis
        for (k=0;k<m;k++) {
            for (i=0;i<(numRows);i++) {
                for (j=0;j<(numCols);j++) {
                    a00 = (float)S((i)           %numRows,(j)           %numCols);
                    a10 = (float)S((i+1)         %numRows,(j)           %numCols);
                    a20 = (float)S((i-1+numRows) %numRows,(j)           %numCols);
                    a01 = (float)S((i  )         %numRows,(j+1)         %numCols);
                    a02 = (float)S((i  )         %numRows,(j-1+numCols) %numCols);
                    if (c==8) {
                        a11 = (float)S((i+1)         %numRows,(j+1)         %numCols);
                        a21 = (float)S((i-1+numRows) %numRows,(j+1)         %numCols);
                        a12 = (float)S((i+1        ) %numRows,(j-1+numCols) %numCols);
                        a22 = (float)S((i-1+numRows) %numRows,(j-1+numCols) %numCols);
                    }
                    lambda = (int) floor(((pixmax-pixmin)*((float)rand()/RAND_MAX))+pixmin);
                    //Régularisation
                    if (c==8) {
                        dU  = U18(lambda,a10,a01,a20,a02,a11,a21,a12,a22);
                        dU -= U18(a00   ,a10,a01,a20,a02,a11,a21,a12,a22);
                    }
                    else {
                        dU  = U14(lambda,a10,a01,a20,a02);
                        dU -= U14(a00   ,a10,a01,a20,a02);
                    }

                    if (dU<0)
                        S(i%numRows,j%numCols)=(byte)lambda;
                    else
                    {
                        dU *= (log(2.0 + r)/t);
                        //dU *= (1+r)/t;
                        if ( ((double)rand()/RAND_MAX)< exp(-dU))
                            S(i%numRows,j%numCols)=(byte)lambda;
                    }

                }
            }
        }
    }

}

//Traitement par ICM
void ICM(Image<byte> &E, Image<byte> &S) {
    int c = 8; //pour 8 connexité ou 4 connexité
    float s = 1.0; //sigma
    int n = 10; //nb de boucles ICM

    int numRows = E.height();
    int numCols = E.width();

    int k,i,j,r;
    int lambda;
    int a00,a10,a01,a02,a20,a11,a21,a12,a22;
    float dU;
    float pixmax = 0.0;
    float pixmin = 255.0;
    Image<byte> A(numRows,numCols), B(numRows,numCols), C(numRows,numCols); //A = Cout1, B=Cout0, C=Cout00

    for (i=0;i<numRows;i++) {
        for (j=0;j<numCols;j++) {
            lambda = (int)E(i,j);
            S(i,j) = (byte)lambda;
            A(i,j) = (byte)lambda;
            if (lambda>pixmax) pixmax=lambda;
            if (lambda<pixmin) pixmin=lambda;
        }
    }

    //Boucle de l'ICM
    for (r=0;r<n;r++) {
        if ((r%2)==1) {
            B=A.clone();
            C=S.clone();
        }
        else {
            C=A.clone();
            B=S.clone();
        }

        for (i=0;i<(numRows);i++) {
            for (j=0;j<(numCols);j++) {
                //a00 = (float)S((i)           %numRows,(j)           %numCols);
                a10 = (float)B((i+1)         %numRows,(j)           %numCols);
                a20 = (float)B((i-1+numRows) %numRows,(j)           %numCols);
                a01 = (float)B((i  )         %numRows,(j+1)         %numCols);
                a02 = (float)B((i  )         %numRows,(j-1+numCols) %numCols);
                if (c==8) {
                    a11 = (float)B((i+1)         %numRows,(j+1)         %numCols);
                    a21 = (float)B((i-1+numRows) %numRows,(j+1)         %numCols);
                    a12 = (float)B((i+1        ) %numRows,(j-1+numCols) %numCols);
                    a22 = (float)B((i-1+numRows) %numRows,(j-1+numCols) %numCols);
                }
                lambda=((int) pixmax);
                for (k=((int) pixmin);k<((int) pixmax);k++) {/* regularization */
                    if (c==8) {
                        dU  = U18(lambda,a10,a01,a20,a02,a11,a21,a12,a22);
                        dU -= U18(k     ,a10,a01,a20,a02,a11,a21,a12,a22);
                    }
                    else {
                        dU  = U14(lambda,a10,a01,a20,a02);
                        dU -= U14(k     ,a10,a01,a20,a02);
                    }
                    lambda=((dU>0.0)?(k):(lambda));
                }
                C((i)%numRows,(j)%numCols)=(byte)lambda;
            }
        }
        if ((r%2)==1) {
            A=B.clone();
            S=C.clone();
        }
        else {
            A=C.clone();
            S=B.clone();
        }
    }

}



int main(int argc, char* argv[]) {

    Image<byte> I; //image nette
    if(! load(I, argc>1? argv[1]: srcPath("A200.png"))) {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 1;
    }

    Image<byte> J=I.clone(); //future image bruitée

    //Générateur aléatoire de variable suivant une loi gaussienne
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::normal_distribution<double> distribution (0.0,1.0); //moyenne 0.0, écart-type 1.0

    int w=I.width(), h=I.height();

    for(int i=0; i<w; i++) {
        for(int j=0; j<h; j++) {
            double aleat = 127*distribution(generator);
            if ((double)I(i,j)+aleat<=255 && 0<=(double)I(i,j)+aleat)
                J(i,j)=byte((double)I(i,j)+aleat);
            else
                J(i,j)=I(i,j);
        }
    }

    openWindow(w, h);
    display(I);
    setActiveWindow(openWindow(J.width(), J.height()));
    display(J);

    Image<byte> K = J.clone();
    //Ne décommenter qu'une seule ligne
    //kmeans(J,K);
    //recuit(J,K);
    ICM(J,K);

    setActiveWindow(openWindow(K.width(), K.height()));
    display(K);
    endGraphics();
    return 0;
}
