#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonctions_de_jeu.h"

int nbrspions1=8,nbrspions2=8;

// Representation du plateau de jeu
char board[SIZE] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

int adjacences[SIZE][4] = {
        {1, -1, 9, -1},  // Connexions pour la case 0
        {0, 2, 4, -1},  // Connexions pour la case 1
        {1, -1, 14, -1}, // Connexions pour la case 2
        {-1, 4, -1, 10},  // Connexions pour la case 3
        {1, 3, 5, 7},   // Connexions pour la case 4
        {-1, 4, -1, 13},  // Connexions pour la case 5
        {-1, 7, 11, -1}, // Connexions pour la case 6
        {4, 6, 8, -1},  // Connexions pour la case 7
        {-1, 7, 12, -1}, // Connexions pour la case 8
        {0, 10, 21, -1},// Connexions pour la case 9
        {3, 9, 11, 18}, // Connexions pour la case 10
        {6, 10, 15, -1},// Connexions pour la case 11
        {8, 13, 17, -1},// Connexions pour la case 12
        {5, 12, 14, 20},// Connexions pour la case 13
        {2, 13, 23, -1},// Connexions pour la case 14
        {11, 16, -1, -1},// Connexions pour la case 15
        {15, 17, 19, -1},// Connexions pour la case 16
        {12, 16, -1, -1},// Connexions pour la case 17
        {10, 19, -1, -1},// Connexions pour la case 18
        {16, 18, 20, 22},// Connexions pour la case 19
        {13, 19, -1, -1},// Connexions pour la case 20
        {9, -1, 22, -1}, // Connexions pour la case 21
        {19, 21, 23, -1},// Connexions pour la case 22
        {14, 22, -1, -1} // Connexions pour la case 23
    };

// Fonction pour initialiser le plateau de jeu
void initializeBoard() {
    for(int i = 0; i < SIZE; i++) {
        board[i] = 'O';}
}
/*void nbrPions(char x,char y,int *A, int *B){
 *A=0,*B=0;
   for(int i = 0; i < SIZE; i++){
      if(board[i]==x)
         (*A)++;
      if(board[i]==y)
         (*B)++;
   }}*/
char rules(){
    printf("Regles du Jeu : (Voir la documentation en annexe) \n"
           "1. Le jeu se deroule en deux temps : la pose puis le mouvement.\n"
           "2. Dans un premier temps, les joueurs posent a tour de rôle chacun de leurs\n"
           "   pions sur un point vide (intersection) du plateau.\n"
           "   - Le premier joueur est defini aleatoirement par la machine.\n"
           "   - Lorsqu’il n’y a plus de pion a poser, les joueurs deplacent leurs pions vers\n"
           "     une intersection voisine libre en suivant un chemin prevu. L’objectif est de\n"
           "     former des « moulins » ou files de trois pions alignes.\n"
           "   - Lorsque l'un des joueurs forme un moulin, il peut capturer un pion adverse, \n"
           "     il choisit librement le pion qu´il capturera entre tous les pions de l´adversaire\n"
           "     qui n´appartiennent a aucun moulin. Au cas où tous les pions de l´adversaire forment des moulins,\n" 
           "     celui qui fait la prise choisira librement un quelconque d´entre eux.\n"
           "3. Une fois sorti du jeu, un pion ne peut plus y rentrer.\n"
           "4. Le jeu s’acheve quand un joueur n’a plus que deux pions ou ne peut plus jouer,\n"
           "   il est alors le perdant.\n");
    return 0;
}


// Fonction pour afficher le plateau de jeu
void displayBoard() {
    int ligne =1;
    for(int i = 0; i < SIZE; i+=3) {
        if (i==12){
            continue;
        }
        if ((ligne==1)||(ligne==7)){
            printf("%c--------%c--------%c\n", board[i],board[i+1],board[i+2]);
            if (ligne==1)
               printf("|        |        |\n");
            }
        if ((ligne==2)||(ligne==6)){
            printf("|  %c-----%c-----%c  |\n", board[i],board[i+1],board[i+2]);
            if (ligne==2)
                printf("|  |     |     |  |\n");
            else
                printf("|        |        |\n");
            }
        if ((ligne==3)||(ligne==5)){
            printf("|  |  %c--%c--%c  |  |\n", board[i],board[i+1],board[i+2]);
            if (ligne==3)
                printf("|  |  |     |  |  |\n");
            else
                printf("|  |     |     |  |\n");
            }
        if (ligne==4){
            printf("%c--%c--%c     %c--%c--%c\n", board[i],board[i+1],board[i+2],board[i+3],board[i+4],board[i+5]);
            printf("|  |  |     |  |  |\n");
            }
        ligne++;
    }
}

int startgame0(){
    int choix;int choix2;
    printf("*****  JEU MOULIN  *****\n");
    printf("  ***     Menu     ***  \n");
    printf("      1- JOUER \n");
    printf("      2- Regles \n");
    printf("      3- Quitter \n");
    printf("Choisir une option (1 ou 2 ou 3 ) \n");
    scanf("%d",&choix);
    while((choix!=1) && (choix!=2) && (choix!=3)){
        printf("Choix invalid,refaire le choix  (1 ou 2 ou 3 ) \n");
        scanf("%d",&choix);
        }
    if (choix==1){
        printf("      1- joueur vs joueur \n");
        printf("      2- joueur vs machine \n");
        printf("Choisir une option (1 ou 2) \n");
        scanf("%d",&choix2);
        while((choix2!=1) && (choix2!=2)){
            printf("Choix invalid,refaire le choix  (1 ou 2 ) \n");
            scanf("%d",&choix2);
            }
        initializeBoard();
        displayBoard();
        if  (choix2==1){
            return 11 ;}
        else if  (choix2==2){
            printf("      1- Niveau debutant \n");
            printf("      2- Niveau advancee  \n");
            scanf("%d",&choix2);
            while((choix2!=1) && (choix2!=2)){
                printf("Choix invalid,refaire le choix  (1 ou 2 ) \n");
                scanf("%d",&choix2);
            }
            if  (choix2==1){
                return 121 ;}
            else if  (choix2==2){
                return 122 ;}
            }
        }
    else {
        return choix;}
    return -1;

}

 