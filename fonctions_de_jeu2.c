#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"
#include <ctype.h> 
//Si la machine  a fait un moulin ,alors il prends un pion aléatoirement
int checkAndHandleMoulin2(int iplace, int *itake, char adversarySymbol, int *adversaryPawns) {
    if (moulin(iplace) ) {
        clear();
        printf(RED"La machine a forme un moulin !"RESET);
        displayBoard();
        int hasNonMoulinPawns = 0;
        // Verifier s'il existe des pions adverses qui ne font pas partie d'un moulin
        for (int i = 0; i < SIZE; i++) {
            if (board[i] == adversarySymbol && !moulin(i)) {
                hasNonMoulinPawns = 1;
                break;
            }
        }

        // Demander au joueur de capturer un pion
        if (hasNonMoulinPawns) {
            *itake = rand() % 24;
            // Verifier que le pion choisi est valide et ne fait pas partie d'un moulin
            while (!(board[*itake] == adversarySymbol && !moulin(*itake))) {
                *itake = rand() % 24;
            }
        } else {
            *itake = rand() % 24;
            // Verifier que le pion choisi appartient a l'adversaire
            while (!(board[*itake] == adversarySymbol)) {
                *itake = rand() % 24;
            }
        }

        // Capturer le pion et mettre a jour les pions restants
        board[*itake] = 'O';
        (*adversaryPawns)--;
        return 1; // Moulin valide et pion capture
    }

    return 0; // Pas de moulin
}


void Machine_placement(char smachine,char shumain, int *humanPawns) {
    clear();
    printf(RED"C'est la phase de Placement (Machine) :\n"RESET);
    displayBoard();
    int iplace, itake;

    printf("Tour de la machine (%c)\n", smachine);

    do {
        iplace = rand() % 24;  // Choisir une position aléatoire
    } while (!isValid(iplace) || iplace < 0 || iplace > 23);  // Vérifier si la position est valide

    // Placer le pion sur le plateau
    pose(iplace, smachine);
    printf("La machine a placé un pion à la position %d\n", iplace);

    // Vérifier si un moulin a été formé et gérer la capture
    checkAndHandleMoulin2(iplace, &itake, shumain, humanPawns);
}


void placementAleatoireMachine(char smachine,char shumain,int Machine_Pawns, int *adversaryPawns) {
    clear();
    printf(RED"C'est la phase de Mouvement :\n"RESET);
    displayBoard();

    int ideplace, iaplace, itake, count;
    int valides[SIZE] = {-1}; 

    printf("Tour de la machine (%c)\n", smachine);

    if (Machine_Pawns == 3) {
        printf(YELLOW " La machine a 3 pions,il peut sauter n'importe ou ! \n" RESET);
    }
    // Selection d'un pion a deplacer
    do {
        ideplace = rand() % SIZE;
        
        count=isValidToMove(ideplace, valides,Machine_Pawns);

    }  while (board[ideplace] != smachine || !count );// Vérifier que le pion appartient au joueur et peut bouger


    // Selection de la nouvelle position
    do {
        iaplace =valides[ rand() % count];

    } while (!isInArray(iaplace, valides, count));

    // Effectuer le mouvement
    move(ideplace, iaplace, smachine);

    // Verifier et gerer un eventuel moulin
    checkAndHandleMoulin(iaplace, &itake, shumain, adversaryPawns);
}