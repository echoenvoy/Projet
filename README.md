#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"

void joueurVsMachine1(){
    char sj1,sj2;
    choixSymboles(&sj1,&sj2,1); /*choix symbole+détermination de l'ordre aléatoirement*/
    /*Phase de placement*/
    for(int i=0;i<Pions/2;i++)
    { if (sj1=='m'){
        MachinePlacement(sj1,sj2);
        TourDePlacement(sj2,sj1,2,&nbrspions2);
        }
        else {
        TourDePlacement(sj1,sj2,1,&nbrspions1);
        MachinePlacement(sj2,sj1);
    /*Le joueur et la machine pose leurs pions à tour de rôle selon l'ordre attribuée en vérifiant à chaque fois si la position est valide*/
        }


        }

    /*phase de déplacement */
     while(!is_win(sj1,sj2,nbrspions1,nbrspions2))
    for(int i=0; i<Pions;i++)
    printf("Maintnant, c'est la phase de mouvement \n");
    while(!is_win(sj1,sj2,nbrspions1,nbrspions2))
    {
        if sj1='m';
    {
    placementAleatoireMachine(sj1,sj2);
     while(!is_win())
    break;
    TourDeMvt(sj2,sj1,2);}
    else;
    TourDeMvt(sj1,sj2,1);
     if(is_win())
    break;
    placementAleatoireMachine(sj2,sj1);
}


int main(){
    startgame1();
    system("PAUSE");
    return 0;
}





void Machine_placement(char machineSymbol, char adversarySymbol, int *adversaryPawns) {
    clear();
    printf(RED"C'est la phase de Placement (Machine) :\n"RESET);
    displayBoard();
    int iplace, itake;

    printf("Tour de la machine (%c)\n", machineSymbol);

    do {
        iplace = rand() % 24;
    } while (!isValid(iplace) || iplace < 0 || iplace > 23);

    // Placer le pion sur le plateau
    pose(iplace, machineSymbol);
    printf("La machine a placé un pion à la position %d\n", iplace);

    // Verifier si un moulin a ete forme et gerer la capture
    if (checkAndHandleMoulin(iplace, &itake, adversarySymbol, adversaryPawns)) {
        printf("La machine a capturé un pion adverse !\n");
    }
}




}

void placementAleatoireMachine(char smachine, char shumain) {
    int ideplace, iaplace, itake;
    int valides[SIZE] = {-1};

    if (Machine_Pawns == 3) {
        do {
            ideplace = rand() % SIZE;
            iaplace = rand() % SIZE;
        } while (board[ideplace] != smachine || board[iaplace] != 'O');
    } else {
        do {
            ideplace = rand() % SIZE;
        } while (board[ideplace] != smachine);

        isValidToMove(ideplace, valides, Machine_Pawns);
        if (valides[0] != -1) {
            do {
                iaplace = valides[rand() % SIZE];
            } while (iaplace == -1);

            move(ideplace, iaplace, smachine);
            printf("Tour de la machine (%c). Deplacer de la position %d à la position %d\n", smachine, ideplace, iaplace);

            if (checkAndHandleMoulin(iaplace, &itake, shumain, &nbrspions2)) {
                printf("La machine a capturé un pion adverse !\n");
            }
        } else {
            printf("Pas de changement(%c)\n", smachine);
        }
    }
}
