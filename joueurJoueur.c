#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"
int nbrspions1=8,nbrspions2=8;
void joueurVsjoueur(){
    char sj1,sj2;
    choixSymboles(&sj1,&sj2,2);
    

        //Phase de Placement 
            int iplace,itake;
            for(int i=0;(i<8) && !is_win(sj1,sj2,nbrspions1,nbrspions2);i++){

             //tour de premier joueur
            printf("la tour de premier joueur \n");
            printf("Choisir un coin pour placer un pion (un nombre de 0 a 23) :\n");
            scanf("%d",&iplace);
            while(!isValid(iplace)){
                printf("place invalide, rentrer le coin \n");
                scanf("%d",&iplace);}
            pose(iplace,sj1);
            CheckMoulin(iplace,&itake,sj2,&nbrspions2);
        
            //tour de deuxieme joueur,On peut les réduire dans un seul bloc
            printf("la tour de deuxieme joueur \n");
            printf("Choisir un coin pour placer un pion  (un nombre de 0 a 23) :\n");
            scanf("%d",&iplace);
            while(!isValid(iplace)){
                printf("place invalid,rentrer le coin \n");
                scanf("%d",&iplace);}
            pose(iplace,sj2);
            CheckMoulin(iplace,&itake,sj1,&nbrspions1);
        }
    //Phase de mouvement       
    int ideplace,iaplace;
    int valides[4] ={-1,-1,-1,-1};
    printf("Maintnant, c'est la phase de mouvement \n");
    while(!is_win(sj1,sj2,nbrspions1,nbrspions2)){
        //tour de premier joueur
            printf("la tour de premier joueur \n");
            printf("Choisir un poin pour le deplacer :\n");
            scanf("%d",&ideplace);
            while(board[ideplace]!=sj1){
                printf("place invalide, rentrer le nombre \n");
                scanf("%d",&ideplace);}
            while(isValidToMove(ideplace,valides)){
                printf("impossible de le deplacer,essayer par un autre pion \n");
                scanf("%d",&ideplace);}
            printf("Les places disponibles pour le mouvement sont : ");
            for(int i=0;i<4;i++){
                if (valides[i]!=-1)
                    printf("%d ",valides[i]);
            }
            printf("choisis un de eux :");
            scanf("%d",&iaplace);
            while (isInArray(iaplace,valides,4) ){
                printf("choix invalid ,refaire le choix :");
                scanf("%d",&iaplace);
            }
            move(ideplace,iaplace,sj1);
            CheckMoulin(iplace,&itake,sj2,&nbrspions2);

            if(is_win(sj1,sj2,nbrspions1,nbrspions2))
                break;

        //tour de deuxieme joueur
            int valides[4] ={-1,-1,-1,-1};
            printf("la tour de deuxieme joueur \n");
            printf("Choisir un poin pour le deplacer :\n");
            scanf("%d",&ideplace);
            while(board[ideplace]!=sj2){
                printf("place invalide, rentrer le nombre \n");
                scanf("%d",&ideplace);}
            while(isValidToMove(ideplace,valides)){
                printf("impossible de le deplacer,essayer par un autre pion \n");
                scanf("%d",&ideplace);}
            printf("Les places disponibles pour le mouvement sont : ");
            for(int i=0;i<4;i++){
                if (valides[i]!=-1)
                    printf("%d ",valides[i]);
            }
            printf("choisis un de eux :");
            scanf("%d",&iaplace);
            while (isInArray(iaplace,valides,4) ){
                printf("choix invalid ,refaire le choix :");
                scanf("%d",&iaplace);
            }
            move(ideplace,iaplace,sj2);
            CheckMoulin(iplace,&itake,sj1,&nbrspions1);
    }
    
}
int main(){
    startgame1();
    return 0;
}
