#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"
#include <ctype.h> 

void MachinePlacement(char sj1,char sj2){
    srand(time(NULL));
    int iplace, itake;
    printf("   la tour de la machine :\n");
    do
    {
    iplace=rand()%24;
    } while (!isValid(iplace));
    pose(iplace,sj1);
    checkAndHandleMoulin(iplace,&itake,sj2,&nbrspions2);// on donne le symbole de l'adversaire
}
