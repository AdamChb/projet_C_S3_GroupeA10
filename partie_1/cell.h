/*----------------------------------//

            PROJET_C_3
             Partie 1
              cell.h

//----------------------------------*/

#ifndef _CELL_H_
#define _CELL_H_

// Structure d'une cellule
typedef struct s_d_cell{
    int value;  // Valeur de la cellule
    struct s_d_cell ** nexts;  // Tableau de pointeurs vers la cellue suivante
    int nbLevels;  // Nombre de niveaux dans la cellule
} t_d_cell, * p_d_cell;

/**
 * @brief Crée une cellule
 * @param val Valeur de la cellule
 * @param nbLevels Nombre de niveaux de la cellule
 * @return Cellule vide
 */
p_d_cell createCell(int, int);

#endif