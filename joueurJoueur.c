#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"

void joueurVsjoueur(){
    char sj1,sj2;
    choixSymboles(&sj1,&sj2,2);
    

        //Phase de Placement (!is_win(sj1,sj2,nbrspions1,nbrspions2))
        int iplace,itake;
        for(int i=0;i<Pions/2;i++){

             //tour de premier joueur :
            TourDePlacement(sj1,sj2,1,&nbrspions2);

            //tour de deuxieme joueur :
            TourDePlacement(sj2,sj1,2,&nbrspions1);
        }
    //Phase de mouvement       
    /*int ideplace,iaplace;
    int valides[4] ={-1,-1,-1,-1};*/
    printf("Maintnant, c'est la phase de mouvement \n");
    while(!is_win(sj1,sj2,nbrspions1,nbrspions2)){
        //tour de premier joueur
            TourDeMvt(sj1,sj2,1);

            if(is_win(sj1,sj2,nbrspions1,nbrspions2))
                break;

        //tour de deuxieme joueur
            TourDeMvt(sj2,sj1,2);
            /*
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
            checkAndHandleMoulin(iaplace,&itake,sj1,&nbrspions1);*/
    }
    
}
int main(){
    startgame1();
    system("PAUSE");
    return 0;
}
