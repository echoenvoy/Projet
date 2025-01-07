#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "start.h"
//Start game
void startgame1(){
   int a = startgame0();
   if (a==11)
      joueurVsjoueur();
   if (a==2)
      rules();
   if (a==3)
      printf(" Bye Bye !!");
}
//Définir un joueur aléatoire
int aleajoueur(){
    srand(time(NULL));
    int a=rand();
    return (a%2==0);
}

//choisir les symboles des joueurs 
void choixSymboles(char *sj1,char *sj2,int a){
    char sjd, sjg, sj;
    if (a==2){
    printf("le joueur droite ,choisir un symbole (un seul caractere):  ");
    scanf(" %c",&sjd);
    printf("le joueur gauche ,choisir un symbole (un seul caractere):  ");
    scanf(" %c",&sjg);
    if (aleajoueur()==0){
        printf("le joueur droite commence;  \n");
        *sj1=sjd;*sj2=sjg;}
    else {
        printf("le joueur gauche commence;  \n");
        *sj1=sjg;*sj2=sjd;
        }
   }
   if (a==1){
    printf("le joueur  ,choisir un symbole (un seul caractere):  ");
    scanf("%c",&sj);
    printf("Pour la machine on choisit le symbole : 'm' \n");;
    if (aleajoueur()==0){
        printf("le joueur va commencer;  \n");
        *sj1=sj;*sj2='m';}
    else {
        printf("la machine va commencer ;  \n");
        *sj1='m';*sj2=sj;
        }
   }
}
//poser un pion dans la position i
void pose(int i,char x){
   board[i]=x;
   displayBoard();
}
//déplcer un pion d'une position i1 à une  position i2
void move(int i1,int i2,char x){
   board[i1] = 'O';
   board[i2]=x;
}

//verifie si le pion  est vide
int isValid(int i){
   return (board[i]=='O');
}


//Taking :

//verifie si le pion  est valide a le prendre
int isValidToTake(int iplace,int* itake,char sj){
      printf("tu es fait un moulin, alors choisir un pion d'adversaire a apprendre :");
      scanf("%d",itake);
      while (!((board[*itake]==sj) && !(moulin(*itake)))){//il faut ajouter le cas si il n y'a aucun pion a prendre 
         printf("tu es choisir un invalid place, rechoisir :");
         scanf("%d",itake);}   
}
//Si un joueur peut apprendre un moulin dans une position i
void take(int i){
   board[i] = 'O';
}
//Si un joueur peut a fait un moulin ,alors il prends un pion 
int CheckMoulin(int iplace,int* itake,char sj,int *nbrspions){
   if (moulin(iplace)){
      isValidToTake(iplace,&itake,sj);
      take(itake);
      *nbrspions--;
      }
}


//verifie si le pion peut bouger 
int isValidToMove(int ideplace,int* L){
   int a = 0;
   for (int j = 0; j < 4 && adjacences[ideplace][j] != -1; j++) {
         int voisin = adjacences[ideplace][j];
         if (board[voisin] == 'O') {
            L[j] = voisin;
            a=1; 
            }
         }
   return a;
}

//après une move ou un pose cette fonction verifier si on a obtenu une moulin
int moulin(int i){
 int i1=i - i%3;
 //pour les moulins horizontales
 if ((board[i1] == board[i1+1]) && (board[i1] == board[i1+2])){
    return 1;}

//pour les moulins verticales 
 switch (i) {
 case 0:case 9 :case 21:
    return ((board[0] == board[9]) && (board[9] == board[21]));
 case 1:case 4 :case 7:
    return ((board[4] == board[1]) && (board[4] == board[7]));
 case 2:case 14 :case 23:
    return ((board[2] == board[14]) && (board[14] == board[23]));
 case 3:case 10 :case 18:
    return ((board[3] == board[10]) && (board[10] == board[18]));
 case 5:case 13 :case 20:
    return ((board[5] == board[13]) && (board[13] == board[20]));
 case 6:case 11 :case 15:
    return ((board[6] == board[11]) && (board[11] == board[15]));
 case 8:case 12 :case 17:
    return ((board[8] == board[12]) && (board[12] == board[17]));
 case 16:case 19 :case 22:
    return ((board[16] == board[19]) && (board[19] == board[22]));
 default :
   return 0;
}
}


int is_win(char sj1,int nbrpions1,char sj2,int nbrpions2){
   //vérifie si l'un des joueurs n’a que deux pions 
   if (joueur1<=2)
      return 11;
   if (joueur2<=2)
      return 12;
   //vérifie si un joueur ne peut plus bouger
   if (isBlocked(sj1)) {
     return 12;
   }
   if (isBlocked(sj2)) {
     return 11;
   }

   else
      return 0;

}

int isBlocked(char sj){
   // Parcourir le plateau pour trouver les pions du joueur
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == sj) {
            // Vérifier toutes les positions adjacentes
            for (int j = 0; j < 4 && adjacences[i][j] != -1; j++) {
                int voisin = adjacences[i][j];
                if (board[voisin] == 'O') {
                    return 0; // Une case adjacente est libre, le joueur peut bouger
                }
            }
        }
    }
    return 1; // Aucun mouvement possible pour ce joueur

}

int isInArray(int a, int* L, int size) {
    for (int i = 0; i < size; i++) {
        if (L[i] == a) {
            return 1; // `a` is found in the array
        }
    }
    return 0; // `a` is not in the array
}
