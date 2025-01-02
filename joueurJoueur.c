#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"

void joueurVsjoueur(){
    char sj1,sj2,sjd,sjg;
    printf("le joueur droite ,choisir un symbole (un seul caractere):  ");
    scanf("%c",&sjd);
    printf("le joueur gauche ,choisir un symbole (un seul caractere):  ");
    scanf(" %c",&sjd);
    printf("sjd= %c\n",sjd);
    if (aleajoueur()==0){
        printf("le joueur droite commence;  \n");
        sj1=sjd;sj2=sjg;}
    else {
        printf("le joueur gauche commence;  \n");
        sj1=sjg;sj2=sjd;
        }
    int iplace,itake;
    int nbrspions1=8,nbrspions2=8;

    while(is_win(sj1,sj2,nbrspions1,nbrspions2)){
        //Phase de Placement 

        for(int i=0;i<Pions/2;i++){
        //tour de premier joueur
        printf("la tour de premier joueur \n");
        printf("Choisir un coin pour placer un pion (un nombre de 0 a 23) \n");
        scanf("%d",&iplace);
        while(!isValid(iplace))
            printf("place invalide, rentrer le coin \n");
            scanf("%d",&iplace);
        pose(iplace,sj1);
        if (moulin(iplace)){
            printf("tu es fait un moulin, alors choisir un pion d'adversaire à apprendre ");
            scanf("%d",&itake);
            while (!isValidToTake())//il faut ajouter le cas si il n y'a aucun pion a prendre 
                printf("tu es choisir un invalid place  ");
            take(itake);
        }
            
        
        //tour de deuxieme joueur,On peut les réduire dans un seul bloc
        printf("la tour de deuxieme joueur \n");
        printf("Choisir un coin pour placer un pion  (un nombre de 0 a 23) \n");
        scanf("%d",&iplace);
        while(!isValid(iplace))
            printf("place invalid,rentrer le coin \n");
            scanf("%d",&iplace);
        pose(iplace,sj1);
        if (moulin(iplace)){
            printf("tu es fait un moulin, alors choisir un pion d'adversaire à apprendre ");
            scanf("%d",&itake);
            while (!isValidToTake())//il faut ajouter le cas si il n y'a aucun pion a prendre 
                printf("tu es choisir un invalid place  ");
            take(itake);
        }
        nbrPions(sj1,sj2,&nbrspions1,&nbrspions2);
        }
    //Phase de mouvement       

    }
}
int main(){
    startgame1();
    return 0;
}
