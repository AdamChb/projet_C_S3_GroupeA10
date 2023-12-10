/*----------------------------------//

            PROJET_C_3
             Partie 2
              list.h

//----------------------------------*/

#ifndef _LIST_H_
#define _LIST_H_

//----------------------------------//
// Fichiers internes

#include "cell.h"

//----------------------------------//
// Corps du fichier

// Structure d'une liste
typedef struct s_d_list{
    p_d_cell * heads;  // Tableau des premières cellules de la liste
    int nbLevel;  // Nombre de niveaux de la liste
} t_d_list, * p_d_list;

/**
 * @brief Crée une liste
 * @param nbLevels Nombre de niveaux de la liste
 * @return Liste vide
 */
t_d_list createList(int);

/**
 * @brief Affiche une ligne de la liste
 * @param list Liste à afficher
 * @param level Niveau de la liste à afficher
 * @return none
 */
void displayListLevel(t_d_list, int);

/**
 * @brief Affiche une liste complète
 * @param list Liste à afficher
 * @return none
 */
void displayList(t_d_list);

/**
 * @brief Affiche une liste complète en alignant les cellules
 * @param list Liste à afficher
 * @return none
 */
void displayAlignedList(t_d_list);

/**
 * @brief Insert une cellule en tête d'une liste
 * @param list Liste dans laquelle sera insérée la cellule
 * @param newCell Cellule à insérer
 * @return none
 */
void insertHeadList(p_d_list, p_d_cell);

/**
 * @brief Insert une cellule dans une liste
 * @param list Liste dans laquelle sera insérée la cellule
 * @param val Valeur de la nouvelle cellule
 * @param nbLevels Nombre de niveaux de la nouvelle cellule
 * @return none
 */
void insertList(p_d_list, int, int);

#endif