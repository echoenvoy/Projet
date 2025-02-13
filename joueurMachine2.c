#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_de_jeu.h"
extern int b; //variable globale pour choisir le joueur qui commence


void joueurVSordinateurEVOLUE() {
    choixSymboles(&sj1, &sj2, 1);  // Choix des symboles et détermination de l'ordre
    afficherCouleursJoueurs();
    Sleep(5000);
    int turn = b;  // 0: Human starts, 1: AI starts

    // **Phase de placement**
    for (int i = 0; i < Pions / 2; i++) {
        if (turn == 1) {
            TourDePlacementMACHINE(sj1, &nbrspions1);
            TourDePlacement(sj1, 'm', 1, &nbrspions2);
        } else {
            TourDePlacement(sj1, 'm', 1, &nbrspions2);
            TourDePlacementMACHINE(sj1, &nbrspions1);
        }
    }

    // **Phase de Mouvement**
        while (!is_win()) {
            if (b == 0) {  // Le joueur commence
                TourDeMvt(sj1, 'm', 1, nbrspions1, &nbrspions2);
                if (is_win()) break;
                TourDeMvtMACHINE(sj1, nbrspions2, &nbrspions1);
            } else {  // L'IA commence
                TourDeMvtMACHINE(sj1, nbrspions2, &nbrspions1);
                if (is_win()) break;
                TourDeMvt(sj1, 'm', 1, nbrspions1, &nbrspions2);
            }
        }
    
}
