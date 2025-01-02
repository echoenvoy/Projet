#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define SIZE 24
#define Pions 16 //8 pour chaque joueur 

int joueur1,joueur2;

// Représentation du plateau de jeu
char board[SIZE] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// Fonction pour initialiser le plateau de jeu
void initializeBoard() {
    for(int i = 0; i < SIZE; i++) {
        board[i] = 'o';}
}
void nbrPions(char x,char y,int *A, int *B){
 *A=0,*B=0;
   for(int i = 0; i < SIZE; i++){
      if(board[i]==x)
         *A++;
      if(board[i]==y)
         *B++;
   }}
void rules(){
    
}
void quitter(){}
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
    printf("Choisir une option (1 ou 2) \n");
    scanf("%d",&choix);
    if (choix==1){
        printf("      1- joueur vs joueur \n");
        printf("      2- joueur vs machine \n");
        printf("Choisir une option (1 ou 2) \n");
        scanf("%d",&choix2);
        initializeBoard();
        displayBoard();
        if  (choix2==1)
            return 11 ;
        if  (choix2==2)
            return 12 ;
        }
    else 
        return choix;

}

