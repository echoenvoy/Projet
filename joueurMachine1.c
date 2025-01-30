#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"

void joueurVsMachine1(){
    choixSymboles(&sj1,&sj2,1);
    for(int i=0;i<Pions/2;i++){
        
        if (sj1=='m'){
            MachinePlacement(sj1,sj2); //tour de premier joueur :
            TourDePlacement(sj2,sj1,2,&nbrspions2);//tour de deuxieme joueur :
        }
        else {
        TourDePlacement(sj1,sj2,1,&nbrspions1);//tour de premier joueur :
         MachinePlacement(sj2,sj1);//tour de deuxieme joueur :
        }
            
            
        }
        

}