#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"
#include <ctype.h> 

//Start game
void startgame1(){
   int a = startgame0();
   if (a==11)
      joueurVsjoueur();
   if (a==12)
      printf("Partie a ajouter ");//joueurVsMachine1()
   else if (a==2){
      rules();
      startgame1();}
   else if (a==3){
      printf(" Bye Bye !!");}
}
//Definir un joueur aleatoire
int aleajoueur(){
    srand(time(NULL));
    int a=rand();
    return (a%2==0);
}

//choisir les symboles des joueurs 
void isValidCharch(char* sj){
   while(!isalpha(*sj)) {
        printf("Vous devez choisir une lettre : ");
        scanf(" %c",sj);
    }
}
void choixSymboles(char *sj1,char *sj2,int a){
    char sjd, sjg, sj;
    if (a==2){//Pour deux joueures
    printf("le joueur droite ,choisir un symbole (un seul caractere):  ");
    scanf(" %c",&sjd);
    isValidCharch(&sjd);

    printf("le joueur gauche ,choisir un symbole (un seul caractere):  ");
    scanf(" %c",&sjg);
    isValidCharch(&sjg);

    if (aleajoueur()==0){
        printf("le joueur droite commence : \n");
        *sj1=sjd;*sj2=sjg;}
    else {
        printf("le joueur gauche commence :  \n");
        *sj1=sjg;*sj2=sjd;
        }
   }
   if (a==1){//Pour un joueur avec la machine
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
//deplcer un pion d'une position i1 a une  position i2
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
/*int isValidToTake(int iplace,int* itake,char sj){
      printf("tu es fait un moulin, alors choisir un pion d'adversaire a apprendre :");
      scanf("%d",itake);
      while (!((board[*itake]==sj) && !(moulin(*itake)))){
         printf("tu es choisir un invalid place, rechoisir :");
         scanf("%d",itake);}  
}*/
//Si un joueur peut apprendre un moulin dans une position i
/*void take(int i){
   board[i] = 'O';
}*/
//Si un joueur peut a fait un moulin ,alors il prends un pion 
int checkAndHandleMoulin(int iplace, int *itake, char adversarySymbol, int *adversaryPawns) {
    if (moulin(iplace)) {
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
            printf("Vous avez forme un moulin ! Choisissez un pion adverse a capturer (ne faisant pas partie d'un moulin) : ");
            scanf("%d", itake);

            // Verifier que le pion choisi est valide et ne fait pas partie d'un moulin
            while (!(board[*itake] == adversarySymbol && !moulin(*itake))) {
                printf("Position invalide. Veuillez choisir un pion adverse qui ne fait pas partie d'un moulin : ");
                scanf("%d", itake);
            }
        } else {
            printf("Tous les pions adverses font partie de moulins. Vous pouvez capturer n'importe lequel d'entre eux. Choisissez : ");
            scanf("%d", itake);

            // Verifier que le pion choisi appartient a l'adversaire
            while (!(board[*itake] == adversarySymbol)) {
                printf("Position invalide. Veuillez choisir un pion appartenant a l'adversaire : ");
                scanf("%d", itake);
            }
        }

        // Capturer le pion et mettre a jour les pions restants
        board[*itake] = 'O';
        (*adversaryPawns)--;
        return 1; // Moulin valide et pion capture
    }

    return 0; // Pas de moulin
}


void TourDePlacement(char joueurSymbol, char adversarySymbol, int joueurNum, int *adversaryPawns) {
    int iplace, itake;
    printf("Tour du joueur %d (%c). Choisissez une position pour placer votre pion (0 a 23) :\n", joueurNum, joueurSymbol);
    scanf("%d", &iplace);

    // Verifier que la position est valide
    while (!isValid(iplace)) {
        printf("Position invalide. Veuillez choisir une position libre (0 a 23) :\n");
        scanf("%d", &iplace);
    }

    // Placer le pion sur le plateau
    pose(iplace, joueurSymbol);

    // Verifier si un moulin a ete forme et gerer la capture
    if (checkAndHandleMoulin(iplace, &itake, adversarySymbol, adversaryPawns)) {
        printf("Le joueur %d a capture un pion adverse !\n", joueurNum);
    }
}

void ChercheMonPion(char sj,int* ideplace){
   while(board[*ideplace]!=sj){
      printf("place invalide, rentrer le nombre \n");
      scanf("%d",ideplace);}
}

void TourDeMvt(char sj1,char sj2,int i){
   int ideplace,iaplace,itake;
   int valides[4] ={-1,-1,-1,-1};
   printf("la tour de %d joueur \n",i);
   printf("Choisir un poin pour le deplacer :\n");
   scanf("%d",&ideplace);
   ChercheMonPion(sj1,&ideplace);
   while(isValidToMove(ideplace,valides)){
      printf("impossible de le deplacer,essayer par un autre pion \n");
      scanf("%d",&ideplace);
      ChercheMonPion(sj1,&ideplace);}
   printf("Les places disponibles pour le mouvement sont : ");
   for(int i=0;i<4;i++){
   if (valides[i]!=-1)
      printf("%d ",valides[i]);
      }
   printf("\n");
   printf("choisis un de eux :");
   scanf("%d",&iaplace);
   while (isInArray(iaplace,valides,4) ){
      printf("choix invalid ,refaire le choix :");
      scanf("%d",&iaplace);
      }
      move(ideplace,iaplace,sj1);
      checkAndHandleMoulin(iaplace,&itake,sj2,&nbrspions2);
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

//apres une move ou un pose cette fonction verifier si on a obtenu une moulin
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


int is_win(char sj1, char sj2, int nbrspions1, int nbrspions2) {
    if (nbrspions1 <= 2 || isBlocked(sj1)) {//verifie si un joueur ne peut plus bouger ou si si l'un des joueurs n’a que deux pions
        return 12; // Joueur 1 perd
    }
    if (nbrspions2 <= 2 || isBlocked(sj2)) {
        return 11; // Joueur 2 perd
    }
    return 0; // Pas de victoire
}

int isBlocked(char sj){
   // Parcourir le plateau pour trouver les pions du joueur
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == sj) {
            // Verifier toutes les positions adjacentes
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
