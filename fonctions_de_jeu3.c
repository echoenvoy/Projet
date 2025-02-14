#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"
#include <ctype.h> 
#include <limits.h> // For INT_MAX
#include <stdbool.h> // For bool type
int b; //variable globale pour choisir le joueur qui commence
int c; // pour savoir si il y a possibilite d'un moulin assure pour l'adversaire
int MoulinAssureTableau[2] = {-1}; //champs pour stocker les positions des pions qui peuvent former un moulin dans un moulin assure






void choixSymboles1(char *sj1){ // pour joueur vs machine
    char sj;
    printf("le joueur  ,choisir un symbole (un seul caractere):  ");
    scanf(" %c",&sj);
    isValidCharch(&sj);
    *sj1 = sj;
    printf("Pour la machine, on choisit le symbole : 'm' \n");
    if (aleajoueur()==0){
        printf("le joueur va commencer;  \n");
        b=0;
    }
    else {
        printf("la machine va commencer ;  \n");
        b=1;
    }
}

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
            choice = machineCapturePion1( adversarySymbol,  adversaryPawns);
        } 
        // Sinon, l'IA enlève n'importe quel pion adverse
        else {
            choice = machineCapturePion0( adversarySymbol,  adversaryPawns);
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
    int bestmove = getBestMovePlacement(board, adversarySymbol);
    // Placer le pion sur le plateau
    pose(bestmove, 'm');
    // Verifier si un moulin a ete forme et gerer la capture
    if (checkAndHandleMoulinMACHINE(bestmove, adversarySymbol, adversaryPawns)) {
        printf("La machine a capture un pion adverse !\n");
    };
}


void TourDeMvtMACHINE(char adversarySymbol,  int *adversaryPawns) {
    clear();
    displayBoard();

    int bestSource = getBestMoveMvt(board, 'm').from;
    int bestDestination = getBestMoveMvt(board, 'm').to;
    
    move(bestSource, bestDestination, 'm');

    // Vérifier si un moulin est formé et capturer un pion
    if (moulin(bestDestination)) {
        checkAndHandleMoulinMACHINE(bestDestination, adversarySymbol, adversaryPawns);
    }
}


int getBestMovePlacement(char *board, char adversarySymbol) { 
    int bestMove = -1;
    int biggest_threat = -1;
    for (int i = 0; i < SIZE; i++) { 
        if (board[i] == 'O') {  // Vérifier chaque case vide
            int threatlevel = threatPlacement(board, adversarySymbol, i);
            if (threatlevel > biggest_threat) {
                biggest_threat = threatlevel;
                bestMove = i;
            }
            } 
        } 
    return bestMove;
}

Move getBestMoveMvt(char *board, char adversarySymbol) {
    Move bestMove = {-1, -1};
    int bestScore = -1; 

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            if (board[i]== 'm' && board[j] == 'O' ) {
                if (j == adjacences[i][0] || j == adjacences[i][1] || j == adjacences[i][2] || j == adjacences[i][3]){
                    int score = threatMouvement(board, adversarySymbol, i, j);
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove.from = i;
                        bestMove.to = j;
                    }
               }
            }
        }
    }

    return bestMove;
}

int machineCapturePion1(char adversarySymbol, int *adversaryPawns) {
    
    int hasNonMoulinPawns = 0;
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == adversarySymbol && !moulin(i)) {
            hasNonMoulinPawns = 1;
            break;
        }
    }

    // AI selects a valid piece to remove
    int choice;

    // Si des pions adverses sont hors moulin, l'IA enlève un pion libre
    if (hasNonMoulinPawns) {
        choice = bestcapture1(board, adversarySymbol);
    }

    board[choice] = 'O'; // AI retire le pion
    (*adversaryPawns)--;
    return choice;
}

int machineCapturePion0(char adversarySymbol, int *adversaryPawns) {

    int hasNonMoulinPawns = 0;
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == adversarySymbol && !moulin(i)) {
            hasNonMoulinPawns = 1;
            break;
        }
    }

    // AI selects a valid piece to remove
    int choice;
    if (!hasNonMoulinPawns) {
        choice = bestcapture0(board, adversarySymbol);
        }

    board[choice] = 'O';
    (*adversaryPawns)--;
    return choice;
}


int bestcapture1(char *board, char adversarySymbol) {
    int best = -1;
    int max = -100;

    for (int k = 0; k < SIZE; k++) {
        if (board[k] == adversarySymbol && !moulin(k)) {
            int score = 20;
            if (PionBloque(k, adversarySymbol, nbrspions1)) { // ne jamais prendre un pion bloque
                score -= 5;
            }

            board[k] = 'O'; // On simule le retrait du pion
            
            // Simule le Mvt de l'adversaire
            for (int i = 0; i < SIZE; i++) {
                if (board[i] == adversarySymbol) {
                    board[i] = 'O'; // On simule le retrait du pion
                    if (doubleMoulinPossible2(board, adversarySymbol, i)) {
                        score = -6;
                    }
                    board[i] = adversarySymbol; // Annuler le test
                    for (int j = 0; j < SIZE; j++){
                        if (board[i] == adversarySymbol && board[j] == 'O' ) {
                            if (j == adjacences[i][0] || j == adjacences[i][1] || j == adjacences[i][2] || j == adjacences[i][3]){
                                
                                board[i] = 'O'; 
                                board[j] = adversarySymbol; // Simuler un déplacement du symbole ici

                                if (PionSemi_bloque(board, i, adversarySymbol, nbrspions1) && !moulindouble(adversarySymbol, nbrspions1)) { // ne jamais prendre un pion semi-bloque et ne faisant pas partie d'un double moulin
                                    score -= 3;
                                }

                                if (moulindouble(adversarySymbol, nbrspions1)) { // prendre un pion faisant partie d'un double moulin
                                    if (moulin(j)) {
                                        score += 30;
                                    }
                                }

                                if (MoulinAssure(board, adversarySymbol)) { // prendre un pion faisant partie d'un moulin assure
                                    if (moulin(j)) {
                                        score += 20;
                                    }
                                }

                                board[i] = adversarySymbol; // Annuler le test
                                board[j] = 'O'; // Annuler le test
                            }           
                        }
                    }
                }
            }   
            
            if (score > max) {
                max = score;
                best = k;
            }
            board[k] = adversarySymbol; // Annuler le test
        }
    }
    return best;
}

int bestcapture0(char *board, char adversarySymbol) {
    int best = -1;
    int max = -1;
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == adversarySymbol) {
            int score = 0;
            for (int j = 0; j < 4 && adjacences[i][j] != -1; j++) {
                int voisin = adjacences[i][j];
                if (board[voisin] == 'O') {
                    score++;
                }
            }
            if (score > max) {
                max = score;
                best = i;
            }
        }
    }
    return best;
}


int threatPlacement(char *board, char adversarySymbol, int i) { 
    int score = 0;  // Initialiser le score à 0

        //prevenir un moulin assure pour l'adversaire
        if (board[i] == 'O') {  // Vérifier si la case est vide 
            if (c==1){
                if (MoulinAssureTableau[0] == i || MoulinAssureTableau[1] == i) {
                    score += 11;  // Prioriser les cases qui forment un moulin assure pour l'adversaire
                }
            }

            // Vérifier si l’adversaire se met en position pour faire un moulin assure au prochain tour
            board[i] = adversarySymbol; // Simuler un placement du symbole ici
            if (MoulinAssure(board, adversarySymbol)) {
                c=1;
            }
            board[i] = 'O'; // Annuler le test

            // Vérifier si la machine peut se mettre en position pour faire un moulin assure au prochain tour
            board[i] = 'm'; // Simuler un placement du symbole ici
            if (MoulinAssure(board, 'm')) {
                score += 13;  
            }
            board[i] = 'O'; // Annuler le test


            // Vérifier si ce placement complète un moulin pour l'adversaire
            if (MoulinPossible(board, adversarySymbol, i)) {   
                score += 20;  
            } 

            // Vérifier si ce placement complète un moulin pour la machine
            if (MoulinPossible(board, 'm', i)) {   
                score += 21;  
            }

            // Verifier si la machine peut bloquer un pion de l'adversaire
            board[i] = 'm'; // Simuler un placement du symbole ici
            for (int j = 0; j < 4 && adjacences[i][j] != -1; j++) { // Vérifier les cases adjacentes
                int voisin = adjacences[i][j];  
                if (PionBloque(i, adversarySymbol, 9)) { // On met un nombre different de 3 (9) car on est dans la phase de placement
                    score += 3;
                }  
            }
            board[i] = 'O'; // Annuler le test

            // Verifier si la machine peut semi-bloquer un pion de l'adversaire
            board[i] = 'm'; // Simuler un placement du symbole ici
            for (int j = 0; j < 4 && adjacences[i][j] != -1; j++) { // Vérifier les cases adjacentes
                int voisin = adjacences[i][j];  
                if (PionSemi_bloque(board, voisin, adversarySymbol, nbrspions1)) { 
                    score += 3;
                }  
            }
            board[i] = 'O'; // Annuler le test

            // Verifier si le joueur peut semi-bloquer un pion de la machine
            board[i] = adversarySymbol; // Simuler un placement du symbole ici
            for (int j = 0; j < 4 && adjacences[i][j] != -1; j++) { // Vérifier les cases adjacentes
                int voisin = adjacences[i][j];  
                if (PionSemi_bloque(board, voisin, 'm', nbrspions2)) { 
                    score += 3;
                }  
            }
            board[i] = 'O'; // Annuler le test

            // Vérifier si l’adversaire peut se mettre en position pour faire un moulin au tour suivant
            board[i] = adversarySymbol; // Simuler un placement du symbole ici
            for (int j = 0; j < 4 && adjacences[i][j] != -1; j++) { // Vérifier les cases adjacentes
                int voisin = adjacences[i][j];  
                if (MoulinPossible(board, adversarySymbol, voisin)) {
                    score += 1;
                }
            }
            board[i] = 'O'; // Annuler le test
            
            // Vérifier si la machine peut se mettre en position pour faire un moulin au tour suivant
            board[i] = 'm'; // Simuler un placement du symbole ici
            for (int j = 0; j < 4 && adjacences[i][j] != -1; j++) {
                int voisin = adjacences[i][j];  
                if (MoulinPossible(board, 'm', voisin)) {
                    score += 1;
                }  
            }
            board[i] = 'O'; // Annuler le test

            // prioriser les cases centrales
            if (i == 4 || i == 10 || i == 13 || i == 19) {
                score += 4;
            }
        }
        // prioriser l'asphyxion des cases centrales

        if (board[4] == adversarySymbol){
            if (i==1){
                score += 4;
            }
        }

        if (board[10] == adversarySymbol){
            if (i==9){
                score += 4;
            }
        }

        if (board[13] == adversarySymbol){
            if (i==14){
                score += 4;
            }
        }

        if (board[19] == adversarySymbol){
            if (i==22){
                score += 4;
            }
        }

        if (nbrspions1 > 7) {
            board[i] = 'm'; // Simuler un placement du symbole ici
            if (moulindouble(adversarySymbol, nbrspions1)) {
                score += 10;
            }
            board[i] = 'O'; // Annuler le test

            board[i] = adversarySymbol; // Simuler un placement du symbole ici
            if (moulindouble('m', nbrspions2)) {
                score -= 10;
            }
            board[i] = 'O'; // Annuler le test
        }

    return score;  // Aucune menace détectée 
}

int threatMouvement(char *board, char adversarySymbol, int source, int destination) {
    int score = 0;  // Initialiser le score à 0

        board[source] = 'O';
        board[destination] = 'm'; // Simuler un déplacement du symbole ici

        if (nbrspions1 <= 2 || (isBlocked(sj1) && nbrspions1 != 3)) { // Possibilite de perdre pour le joueur
            return 50000; 
        }

        // Simule le Mvt de l'adversaire
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                if (board[i]== adversarySymbol && board[j] == 'O' ) {
                    if (j == adjacences[i][0] || j == adjacences[i][1] || j == adjacences[i][2] || j == adjacences[i][3]){
                        
                        board[i] = 'O';
                        board[j] = adversarySymbol; // Simuler un déplacement du symbole ici
                        if (nbrspions2 <= 2 || (isBlocked(sj2) && nbrspions2 != 3)) { // Possibilte de perdre pour la machine
                            board[i]== adversarySymbol;
                            board[j] == 'O';
                            return -50000;
                        }

                        if (moulindouble( adversarySymbol, nbrspions1)) {   // Verifier si le mouvement complète un moulin double pour le joueur
                            score -= 20;
                            if (moulin(destination)){ // verifier la machine peut faire un moulin et par consequent detruire le potentiel double moulin
                                score += 80;
                            }
                        }

                        if (MoulinAssure(board, adversarySymbol)) {   // Verifier si le mouvement complète un moulin assure pour le joueur
                            score -= 12; 
                            if (moulin(destination)){ // verifier la machine peut faire un moulin et par consequent detruire le potentiel double moulin
                                score += 60;
                            } 
                        }
                        for (int j = 0; j < 4 && adjacences[destination][j] != -1; j++) { // Vérifier les cases adjacentes
                            int voisin = adjacences[destination][j];

                            if (moulin(voisin)) {  // Verifier s'il forme un moulin et bloque un pion de l'adversaire

                                if (PionBloque(voisin, adversarySymbol, nbrspions1)) { 
                                    score -= 10;
                                }
                            }
                            if (board[voisin] == 'm'){
                                if (PionBloque(voisin, 'm', nbrspions2)) {  // Verifier si le joueur peut bloquer un pion de l'adversaire
                                    score -= 4;
                                }

                                if (PionSemi_bloque(board, voisin, 'm', nbrspions2)) { // Verifier si le joueur peut semi-bloquer un pion de la machine
                                    score -= 3;
                                }
                            }
                        }
                        
                        board[i] = adversarySymbol; // Annuler le test
                        board[j] = 'O'; // Annuler le test
                    }
                }
            }
        }
        // Vérifier si le mouvement complète un moulin double pour le joueur  
        if (moulindouble( 'm', nbrspions2)) {   
            score += 40;  
        }
        
        // Vérifier si le mouvement complète un moulin pour l'adversaire
        if (moulindouble(adversarySymbol , nbrspions1)) {   
            score -= 60;  
        }
        
        for (int j = 0; j < 4 && adjacences[destination][j] != -1; j++) { // Vérifier les cases adjacentes
            int voisin = adjacences[destination][j];  

            if (board[voisin] == adversarySymbol){  // Verifier si la machine peut bloquer un pion faisant partie d'un moulin de l'adversaire
                if (moulin(voisin)) { 
                    if (PionBloque(voisin, adversarySymbol, nbrspions1)) { 
                        score += 14;
                    }
                }
            }
            if (board[voisin] == 'm'){  // Verifier si la machine peut bloquer un pion faisant partie d'un moulin de la machine
                if (moulin(voisin)) { 
                    if (PionBloque(voisin, adversarySymbol, nbrspions1)) { 
                        score -= 6;
                    }
                }
            }
            if (board[voisin] == adversarySymbol){  // Verifier si la machine peut bloquer un pion de l'adversaire
                if (PionBloque(voisin, adversarySymbol, nbrspions1)) { 
                    score += 5;
                }
            } 
            if (board[voisin] == 'm'){    
                if (PionBloque(voisin, 'm', nbrspions2)) { // Verifier si la machine peut bloquer un pion de la machine
                    score -= 4;
                }
                if (PionSemi_bloque(board, voisin, 'm', nbrspions2)) { // Verifier si la machine peut Semi-bloquer un pion de la machine
                    score -= 3;
                }
            }
            if (board[voisin] == adversarySymbol){  
                if (PionSemi_bloque(board, voisin, adversarySymbol, nbrspions1)) { // Verifier si la machine peut semi-bloquer un pion de l'adversaire
                    score += 3;
                }
            }
        } 
        score += 1;  // Pour eviter qu'aucun mouvement ne soit fait


        board[destination] = 'O'; // Annuler le test
        board[source] = 'm'; // Annuler le test




        // prioriser les cases centrales
        if (destination == 4 || destination == 10 || destination == 13 || destination == 19) {
            score += 4;
        }

        return score;  // Aucune menace détectée
}



// Verifie si un joueur peut faire un moulin en placant un pion dans la position i dans la phase de placement ou lorsque 3 pions lui restent
int MoulinPossible(char *board, char symbol, int i) {
        if (board[i] == 'O') {
            board[i] = symbol; // Simuler un placement du symbole ici
            if (moulin(i)) {
                board[i] = 'O'; // Annuler le test
                return 1;
            }
            board[i] = 'O'; // Annuler le test
        }
    return 0;
}

// Verifie si on peut faire un double moulin quelque soit le move de l'adversaire
int doubleMoulinPossible2(char *board, char symbol, int k) {
        if (board[k] == 'O') {
            // Simule le Mvt 
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){
                    for (int m = 0; m < 4 && adjacences[i][m] != -1; m++) {
                        int voisin = adjacences[i][j]; // Pour savoi si le moulin peut etre prevenu
                        char charvoisin = board[voisin];
                        if (charvoisin != symbol){
                            if (board[i]== 'm' && board[j] == 'O' ) { // pour s'assurer que le move est possible
                                if (j == adjacences[i][0] || j == adjacences[i][1] || j == adjacences[i][2] || j == adjacences[i][3]){
                                    board[i] = 'O';
                                    board[j] = symbol; // Simuler un déplacement du symbole ici
                                    if (moulin(j)) {
                                        board[j] = 'O'; // Annuler le test
                                        board[i] = symbol; // Annuler le test
                                        return 1;
                                    }
                                    board[j] = 'O'; // Annuler le test
                                    board[i] = symbol; // Annuler le test
                                }
                            } 
                        } 
                    }     
                }
            }
            board[k] = 'O'; // Annuler le test
        }
    return 0;
}

int PionBloque(int pos, char adversarySymbol, int playerPawns){
    // If the player has only 3 pawns, free movement (jumping) is allowed.
    if (playerPawns == 3) {
        return 0; // No restrictions on movement
    } else {
        // Otherwise, only adjacent moves are allowed.
        for (int i = 0; i < 4; i++) {
            int adjacent = adjacences[pos][i];
            if (adjacent == -1) break;  // End of the list.
            if (board[adjacent] == 'O') {
                return 0;  // Found an adjacent empty cell.
            }
        }
        // No adjacent empty cell found.
        return 1;
    }
}

int PionSemi_bloque(char *board, int pos, char adversarySymbol, int adversaryPawns){
    if (adversaryPawns == 3) {
        return 0;
    }
    
    // Récupérer les cases accessibles depuis pos
    int moves[4];
    for (int i = 0; i < 4; i++) {
        moves[i] = -1; // Initialiser
    }
    int count = 0;
    for (int i = 0; i < 4 && adjacences[pos][i] != -1; i++) {
        int adjacent = adjacences[pos][i];
        if (board[adjacent] == 'O') {
            moves[count] = adjacent;
            count++;
        }
    }
    
    if (count == 0)
        return 0; // Aucun déplacement disponible.
    
    int next = moves[0];
    
    // Sauvegarder les valeurs originales depuis le plateau
    char originalPos = board[pos];   
    char originalNext = board[next];    
    
    // Simulation du déplacement
    board[pos] = 'O';
    board[next] = adversarySymbol;
    
    // Récupérer les mouvements disponibles depuis la nouvelle position
    int movesFromNext[4];
    for (int i = 0; i < 4; i++) {
        movesFromNext[i] = -1;
    }
    int countNext = 0;
    for (int i = 0; i < 4 && adjacences[next][i] != -1; i++) {
        int adjacent = adjacences[next][i];
        if (board[adjacent] == 'O') {
            movesFromNext[countNext] = adjacent;
            countNext++;
        }
    }
    
    // Restaurer l'état initial du plateau
    board[pos] = originalPos;
    board[next] = originalNext;
    
    // Le pion est semi-bloqué si le seul déplacement depuis 'next' est de revenir à 'pos'
    if (countNext == 1 && movesFromNext[0] == pos) {
        return 1;
    } else {
        return 0;
    }
}


int moulindouble(char playerSymbol, int playerPawns){
    // Loop over all board positions to find the player's pieces
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == playerSymbol && moulin(i)) {
            // This piece is currently in a mill. Let's see if moving it somewhere else can form a new mill.

            board[i] = 'O'; // Remove the piece from its current position

            int possibleMoves[4];
            int count = 0;

            if (playerPawns < 5) {
                board[i] = playerSymbol; // Restore the piece
                return 0;  // Only possible with 5 pawns or more.
            } else {
                // Move to adjacent empty cells
                for (int adj = 0; adj < 4 && adjacences[i][adj] != -1; adj++) {
                    int voisin = adjacences[i][adj];
                    if (board[voisin] == 'O') {
                        possibleMoves[count++] = voisin;
                    }
                }
            }

            // 3) Test each possible move
            for (int k = 0; k < count; k++) {
                int newPos = possibleMoves[k];

                // Simulate placing the piece at newPos
                board[newPos] = playerSymbol;

                // Check if a mill is formed
                if (moulin(newPos)) {
                    // Restore and return success
                    board[newPos] = 'O';
                    board[i] = playerSymbol;
                    return 1; 
                }
                // Restore that spot
                board[newPos] = 'O';
            }

            // Restore the piece to original position before continuing
            board[i] = playerSymbol;
        }
    }
    // If we never found a double‐mill opportunity
    return 0;
}

// Function to find the nearest desired pawn to a given spot
int nearestdesiredPawn(char *board, char Symbol, int targetPos) {
    int minDistance = 500;
    int nearestPawn = -1;

    // Loop through the board to find all desired pawns
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == Symbol) {
            // Perform BFS from this pawn to the target position
            int distance = bfsFindDistance(board, i, targetPos);
            if (distance < minDistance) {
                minDistance = distance;
                nearestPawn = i;
            }
        }
    }

    return nearestPawn; // Returns the nearest adversary pawn's position
}

// Breadth-First Search (BFS) to find the shortest path from start to target
int bfsFindDistance(char *board, int start, int target) {
    if (start == target) return 0;  // Already at the target position

    int queue[SIZE], front = 0, rear = 0;
    int distances[SIZE];
    bool visited[SIZE];

    // Initialize distances and visited array
    for (int i = 0; i < SIZE; i++) {
        distances[i] = 500;
        visited[i] = false;
    }

    // Enqueue start position
    queue[rear++] = start;
    distances[start] = 0;
    visited[start] = true;

    // BFS loop
    while (front < rear) {
        int current = queue[front++];
        int currentDistance = distances[current];

        // Explore all adjacent positions
        for (int i = 0; i < 4 && adjacences[current][i] != -1; i++) {
            int voisin = adjacences[current][i];

            // Only move to empty spots ('O')
            if (board[voisin] == 'O' && !visited[voisin]) {
                queue[rear++] = voisin;
                distances[voisin] = currentDistance + 1;
                visited[voisin] = true;

                // Stop early if we reached the target
                if (voisin == target) {
                    return distances[voisin];
                }
            }
        }
    }

    return 500; // No valid path found
}


int MoulinAssure(char *board, char adversarySymbol) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == 'O') {
            board[i] = adversarySymbol; // Simuler un placement du symbole ici
            if (moulin(i)) {
                MoulinAssureTableau[count] = i;
                count++;
            }
            board[i] = 'O'; // Annuler le test
        }
    }
    if (count>1){
        return 1;
    }
    return 0;
}









