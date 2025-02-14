#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"
#include <limits.h> // For INT_MAX
#include <stdbool.h> // For bool type

extern int b;

void joueurVsMachine2() {
    choixSymboles1(&sj1);  // Choix des symboles et détermination de l'ordre
    afficherCouleursJoueurs();
    Sleep(5000);
    int turn = b;  // 0: Human starts, 1: AI starts

    // **Phase de placement**
    for (int i = 0; i < Pions / 2; i++) {
        if (turn == 1) {
            TourDePlacementMACHINE(sj1, &nbrspions1); // nbrspions1 est celui du joueur
            TourDePlacement(sj1, 'm', 1, &nbrspions2);
        } else {
            TourDePlacement(sj1, 'm', 1, &nbrspions2);
            TourDePlacementMACHINE(sj1, &nbrspions1);
        }
    }

    // **Phase de Mouvement**
    while (!is_win()){
        if (b == 0) {  // Le joueur commence
            TourDeMvt(sj1, 'm', 1, nbrspions1, &nbrspions2);
            if (nbrspions2 <= 2 || (isBlocked('m') && nbrspions2 != 3)) break;
            TourDeMvtMACHINE(sj1, &nbrspions1);
        } else {  // L'IA commence
                TourDeMvtMACHINE(sj1, &nbrspions1);
                if (nbrspions1 <= 2 || (isBlocked(sj1) && nbrspions1 != 3)) break;
                TourDeMvt(sj1, 'm', 1, nbrspions1, &nbrspions2);
        }
    }
    
}
