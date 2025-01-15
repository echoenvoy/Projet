#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 24
#define Pions 16 //8 pour chaque joueur 
extern int nbrspions1;
extern int nbrspions2;
extern char board[SIZE];
extern int adjacences[SIZE][4];


// Fonction pour initialiser le plateau de jeu
void initializeBoard();
char rules();
// Fonction pour afficher le plateau de jeu
void displayBoard(); 
int startgame0();

//Start 
void startgame1();
//Définir un joueur aléatoire
int aleajoueur();
//choisir les symboles des joueurs 
void choixSymboles(char *sj1,char *sj2,int a);
//poser un pion dans la position i
void pose(int i,char x);
//déplcer un pion d'une position i1 à une  position i2
void move(int i1,int i2,char x);
//verifie si le pion  est vide
int isValid(int i);

//Taking :
//verifie si le pion  est valide a le prendre
int isValidToTake(int iplace,int* itake,char sj);
//Si un joueur peut apprendre un moulin dans une position i
void take(int i);
//Si un joueur peut a fait un moulin ,alors il prends un pion 
int CheckMoulin(int iplace,int* itake,char sj,int *nbrspions);

void TourDePlacement(char sj1,char sj2,int i);

//verifie si le pion peut bouger 
int isValidToMove(int ideplace,int* L);

//après une move ou un pose cette fonction verifier si on a obtenu une moulin
int moulin(int i);


int is_win(char sj1, char sj2, int nbrspions1, int nbrspions2);
int isBlocked(char sj);

int isInArray(int a, int* L, int size);
