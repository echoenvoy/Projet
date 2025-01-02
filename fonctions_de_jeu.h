#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "start.h"
//Start game
void startgame1(){
   if (startgame0()==11)
      joueurVsjoueur();
   if (startgame0()==2)
      rules();
   if (startgame0()==3)
      quitter();
}
//Définir un joueur aléatoire
int aleajoueur(){
    srand(time(NULL));
    int a=rand();
    return (a%2==0);
}

//poser un pion dans la position i
void pose(int i,char x){
   board[i]=x;
}
//déplcer un pion d'une position i1 à une  position i2
void move(int i1,int i2,char x){
   board[i1] = 'o';
   board[i2]=x;
}
int isValid(int i){
   return (board[i]=='o');
}
int isValidToTake(){}

//après une move ou un pose cette fonction verifier si on a obtenu une moulin
int moulin(int i){
 int i1=i - i%3;
 if (board[i1] == board[i1+1] && board[i1] == board[i1+2]);{//pour les moulins horizontales
    return 1;}
 switch (i) {//pour les moulins verticales 
 case 0:case 9 :case 21:
    return (board[0] == board[9] && board[9] == board[21]);
 case 1:case 4 :case 7:
    return (board[4] == board[1] && board[4] == board[7]);
 case 2:case 14 :case 23:
    return (board[2] == board[14] && board[14] == board[23]);
 case 3:case 10 :case 18:
    return (board[3] == board[10] && board[23] == board[18]);
 case 5:case 13 :case 20:
    return (board[5] == board[13] && board[13] == board[20]);
 case 6:case 11 :case 15:
    return (board[6] == board[11] && board[11] == board[15]);
 case 8:case 12 :case 17:
    return (board[8] == board[12] && board[12] == board[17]);
 case 16:case 19 :case 22:
    return (board[16] == board[19] && board[19] == board[22]);
}
}
//Si un joueur peut apprendre un moulin dans une position i
void take(int i){
   board[i] = ' ';
}

int is_win(char x,char y,int joueur1,int joueur2){
   //vérifie si l'un des joueurs n’a que deux pions 
   if (joueur1<=2)
      return 11;
   if (joueur2<=2)
      return 12;
   //vérifie si un joueur ne peut plus en bouger
}
