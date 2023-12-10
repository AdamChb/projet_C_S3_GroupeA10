/*----------------------------------//

            PROJET_C_3
             Partie 3
              cell.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdlib.h>

#include <stdio.h>

//----------------------------------//
// Fichiers internes

#include "cell.h"
#include "meeting.h"
#include "contact.h"
#include "diary.h"

//----------------------------------//
// Corps du fichier

p_cell createHTCell(void * data) {

    /*
    Crée une cellule d'une liste doublement chaînée
    */

    p_cell cell = (p_cell) malloc(sizeof(t_cell));
    cell->meeting = data;
    cell->next = NULL;
    cell->prec = NULL;

    return cell;
}

void deleteHTCell(p_cell cell) {
    
    /*
    Supprime une cellule d'une liste doublement chaînée
    */

    deleteMeeting(cell->meeting);
    free(cell);
    cell = NULL;
    
    return;
}

p_skipcell createSkipCell(void * data, int nbLevel) {

    /*
    Crée une cellule d'une skipliste
    */
    
    p_skipcell skipcell = (p_skipcell) malloc(sizeof(t_skipcell));
    skipcell->diary = data;
    skipcell->nbLevel = nbLevel;
    skipcell->nexts = (p_skipcell *) malloc(nbLevel * sizeof(p_skipcell));
    for (int i = 0; i < nbLevel; i++) {
        skipcell->nexts[i] = NULL;
    }

    return skipcell;
}

void deleteSkipCell(p_skipcell cell) {
    
    /*
    Supprime une cellule d'une skipliste
    */

    deleteDiary(cell->diary);
    free(cell);

    return;
}
