/*----------------------------------//

            PROJET_C_3
             Partie 1
              cell.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdlib.h>

//----------------------------------//
// Fichiers internes

#include "cell.h"

//----------------------------------//
// Corps du fichier

p_d_cell createCell(int val, int nbLevels){
    
    /*
    Crée une cellule
    */

    p_d_cell cell = NULL;
    cell = (p_d_cell) malloc (1 * sizeof(p_d_cell));
    if (cell != NULL)
    {
        cell->value = val;
        cell->nbLevels = nbLevels;
        cell->nexts = (p_d_cell *) malloc(nbLevels * sizeof(p_d_cell));
        for (int i = 0 ; i < cell->nbLevels ; i++)
        {
            *(cell->nexts+i) = NULL;
        }
    }
    return cell;
}