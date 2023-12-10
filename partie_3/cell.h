/*----------------------------------//

            PROJET_C_3
             Partie 3
              cell.h

//----------------------------------*/

#ifndef PROJET_C_S3_CELL_H
#define PROJET_C_S3_CELL_H

//----------------------------------//
// Fichiers internes

// #include "cell.h"
// #include "diary.h"
// #include "meeting.h"
// #include "contact.h"

//----------------------------------//
// Corps du fichier

// Structure d'une cellule de liste doublement chaînée
typedef struct s_cell {
    void * meeting;
    struct s_cell * next, * prec;
} t_cell, * p_cell;

/**
 * @brief Crée une cellule d'une liste doublement chaînée
 * @param data Information à stocker dans la cellule
 * @return Une cellule stockant l'information et pointant vers NULL
 */
p_cell createHTCell(void *);

/**
 * @brief Supprime une cellule d'une liste doublement chaînée
 * @param cell Cellule à supprimer
 */
void deleteHTCell(p_cell);

// Structure d'une cellule de skiplist
typedef struct s_skipcell {
    int nbLevel;
    void * diary;
    struct s_skipcell ** nexts;
} t_skipcell, * p_skipcell;

/**
 * @brief Crée une cellule d'une skipliste
 * @param data Information à stocker dans la cellule
 * @return Une cellule stockant l'information et pointant vers NULL
 */
p_skipcell createSkipCell(void *, int);

/**
 * @brief Supprime une cellule d'une skipliste
 * @param cell Cellule à supprimer
 */
void deleteSkipCell(p_skipcell);

#endif //PROJET_C_S3_CELL_H
