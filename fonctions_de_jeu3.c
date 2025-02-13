#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"
#include <ctype.h> 


int checkAndHandleMoulinMACHINE(int iplace, char adversarySymbol, int *adversaryPawns) {
    if (moulin(iplace)) {
        clear();
        printf(RED "L'IA a formé un moulin !\n" RESET);
        displayBoard();

        int hasNonMoulinPawns = 0;

        // Vérifier s'il existe des pions adverses qui ne font pas partie d'un moulin
        for (int i = 0; i < SIZE; i++) {
            if (board[i] == adversarySymbol && !moulin(i)) {
                hasNonMoulinPawns = 1;
                break;
            }
        }

        int choice;
        // Si des pions adverses sont hors moulin, l'IA enlève un pion libre
        if (hasNonMoulinPawns) {
            do {
                choice = rand() % SIZE;
            } while (!(board[choice] == adversarySymbol && !moulin(choice)));
        } 
        // Sinon, l'IA enlève n'importe quel pion adverse
        else {
            do {
                choice = rand() % SIZE;
            } while (board[choice] != adversarySymbol);
        }

        // Retirer le pion sélectionné
        printf("L'IA a capturé le pion en position %d\n", choice);
        board[choice] = 'O';
        (*adversaryPawns)--;
        return 1;
    }
    return 0;
}


void TourDePlacementMACHINE( char adversarySymbol, int *adversaryPawns) {
    clear();
    displayBoard();
    int bestmove = getBestMove(board, adversarySymbol);
    // Placer le pion sur le plateau
    pose(bestmove, 'm');

    // Verifier si un moulin a ete forme et gerer la capture
    if (checkAndHandleMoulinMACHINE(bestmove, adversarySymbol, adversaryPawns)) {
        printf("La machine a capture un pion adverse !\n");
    };
}

void displayArray(char arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c ", arr[i]);
    }
    printf("\n");
}

void TourDeMvtMACHINE(char adversarySymbol, int AiPawns, int *adversaryPawns) {
    clear();
    printf(RED "Tour de l'IA (Phase de Mouvement) :\n" RESET);
    displayBoard();

    int bestScore = -10000;
    int bestSource = -1;
    int bestDestination = -1;

    // Parcourir toutes les cases du plateau
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == 'm') {  // Trouver un pion IA
            int valides[4];
            int count = isValidToMove(i, valides, AiPawns);

            // Vérifier tous les déplacements possibles pour ce pion
            for (int j = 0; j < count; j++) {
                int destination = valides[j];

                // Simuler le déplacement
                board[i] = 'O';  // Vider la case de départ
                board[destination] = 'm';  // Placer le pion IA à la destination
                int moveScore = getBestMove(board, adversarySymbol);
                board[destination] = 'O';  // Annuler la simulation
                board[i] = 'm';  // Restaurer la position initiale

                // Comparer avec le meilleur score trouvé
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestSource = i;
                    bestDestination = destination;
                }
            }
        }
    }

    // Effectuer le meilleur mouvement trouvé
    if (bestSource != -1 && bestDestination != -1) {
        move(bestSource, bestDestination, 'm');

        // Vérifier si un moulin est formé et capturer un pion
        if (moulin(bestDestination)) {
            checkAndHandleMoulinMACHINE(bestDestination, adversarySymbol, adversaryPawns);
        }
    }
}


int getBestMove(char *board, char adversarySymbol) { 

    for (int i = 0; i < SIZE; i++) { 
        if (isValid(i)) {  // Vérifier chaque case vide
            int threatLevel = isThreatened(board, adversarySymbol);
            board[i] = 'O';  // Annuler le test

            if (threatLevel == 2) {
                return i;  // Priorité absolue au blocage d'un moulin
            } 

            else if (threatLevel == 1 ) {
                return i;  // Sauvegarde si aucun autre bon coup n'est trouvé
            }
            } 
        } 
}
void captureOpponentPieceAI(char adversarySymbol, int *adversaryPawns) {
    
    int hasNonMoulinPawns = 0;
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == adversarySymbol && !moulin(i)) {
            hasNonMoulinPawns = 1;
            break;
        }
    }

    // AI selects a valid piece to remove
    int choice;
    do {
        choice = rand() % SIZE;  // AI picks a random position
    } while (!(board[choice] == adversarySymbol && (hasNonMoulinPawns ? !moulin(choice) : 1)));

    printf("L'IA a enlevé le pion en position %d\n", choice);
    board[choice] = 'O';
    (*adversaryPawns)--;
}

int isThreatened(char *board, char adversarySymbol) { 
    for (int i = 0; i < SIZE; i++) { 
        if (board[i] == 'O') {  // Vérifier chaque case vide 
            board[i] = adversarySymbol;  // Simuler que l'adversaire place un pion ici
            
            // Vérifier si ce placement complète un moulin
            if (moulin(i)) {   
                board[i] = 'O';  // Annuler la simulation 
                return 2;  // Menace de moulin immédiat (doit être bloqué immédiatement)
            } 

            // Vérifier si l’adversaire se met en position pour faire un moulin au prochain tour
            for (int j = 0; j < 4 && adjacences[i][j] != -1; j++) {
                int voisin = adjacences[i][j];  
                if (board[voisin] == 'O') {  
                    board[voisin] = adversarySymbol;  
                    if (moulin(voisin)) {  
                        board[voisin] = 'O';  
                        board[i] = 'O';  
                        return 1;  // Menace de moulin au prochain tour
                    }  
                    board[voisin] = 'O';  
                }  
            }
            board[i] = 'O';  // Annuler la simulation
        } 
    } 
    return 0;  // Aucune menace détectée 
}
