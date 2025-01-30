#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"
#include <ctype.h> 

void MachinePlacement(char machineSymbol, char adversarySymbol){
    srand(time(NULL));
    int iplace, itake;
    printf("   la tour de la machine :\n");
    do
    {
    iplace=rand()%24;
    } while (!isValid(iplace));
    pose(iplace,machineSymbol);
    checkAndHandleMoulin(iplace,&itake,adversarySymbol,&nbrspions2);// on donne le symbole de l'adversaire
}
