/*----------------------------------//

            PROJET_C_3
             Partie 3
            research.h

//----------------------------------*/

#ifndef PROJET_C_S3_RESEARCH_H
#define PROJET_C_S3_RESEARCH_H

//----------------------------------//
// Fichiers internes

#include "cell.h"
#include "list.h"

//----------------------------------//
// Corps du fichier

/**
 * @brief Vérifie si une chaîne de caractère commence
 * par une autre
 * @param researched Début de chaîne recherchée
 * @param verified Chaîne pour laquelle on vérifie le début
 * @return 1 si la condition est vérifiée, 0 sinon
*/
int isStarting(char *, char *);

/**
 * @brief Cherche dans la liste de contacts le nom
   correpondant à la recherche
 * @param list Skiplist contenant la liste des contact dans 
   laquelle sera effectuée la recherche
 * @return Cellule recherchée si elle est trouvée, sinon NULL
 */
p_skipcell autoCompletion(t_skiplist);

#endif //PROJET_C_S3_RESEARCH_H
