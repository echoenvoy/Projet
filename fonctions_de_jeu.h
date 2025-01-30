#ifndef FONCTIONS_DE_JEU_H
#define FONCTIONS_DE_JEU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define SIZE 24
#define Pions 18 //9 pour chaque joueur 

// Déclaration des variables globales
extern int nbrspions1;
extern int nbrspions2;
extern char board[SIZE];
extern int adjacences[SIZE][4];

extern char sj1;
extern char sj2;

// Fonctions du jeu
void clear();
void joueurVsjoueur();
void joueurVsMachine1();
void initializeBoard();
char rules();
void displayBoard0();
void displayBoard();
int startgame0();
void startgame1();
int aleajoueur();
void choixSymboles(char *sj1, char *sj2, int a);
void pose(int i, char x);
void move(int i1, int i2, char x);
int isValid(int i);
int isValidToTake(int iplace,int* itake,char sj);
void take(int i);
int checkAndHandleMoulin(int iplace, int *itake, char adversarySymbol, int *adversaryPawns);
void TourDePlacement(char joueurSymbol, char adversarySymbol, int joueurNum, int *adversaryPawns) ;
void TourDeMvt(char joueurSymbol, char adversarySymbol, int joueurNum, int *adversaryPawns) ;
int isValidToMove(int ideplace,int* L);
int moulin(int i);
int is_win();
int isBlocked(char sj);
int isInArray(int a, int* L, int size);
void MachinePlacement(char machineSymbol, char adversarySymbol);

#endif
