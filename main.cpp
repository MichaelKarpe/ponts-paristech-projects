// Project:  Projet MOPSI
// Author:   Michaël Karpe & Bastien Déchamps
// Date:     26/12/2017

#include <iostream>
using namespace std;

#include "text.h"

int main()
{
    Text textfrancais("dudh_fr.txt"); //warning à cause types char / string
    textfrancais.Tests();

    return 0;
}
