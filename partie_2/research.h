/*----------------------------------//

            PROJET_C_3
             Partie 2
            research.h

//----------------------------------*/

#ifndef _RESEARCH_H_
#define _RESEARCH_H_

//----------------------------------//
// Fichiers internes

#include "list.h"

//----------------------------------//
// Corps du fichier

/**
 * @brief Recherche dans une liste une valeur à partir 
    de la première ligne uniquement 
 * @param list Liste dans laquelle sera effectué la recherche
 * @param val Valeur recherchée
 * @return La cellule recherché si elle existe, sinon NULL
 */
p_d_cell researchClassic(t_d_list, int);

/**
 * @brief Recherche dans une liste une valeur à partir 
    du plus haut niveau et en descendant de niveau 
 * @param list Liste dans laquelle sera effectué la recherche
 * @param val Valeur recherchée
 * @return La cellule recherché si elle existe, sinon NULL
 */
p_d_cell researchAdvanced(t_d_list, int);

/**
 * @brief Teste les fonctions de recherche
 */
void graphics();

#endif