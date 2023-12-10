/*----------------------------------//

            PROJET_C_3
             Partie 3
           complexity.c

//----------------------------------*/

#ifndef PROJET_C_S3_COMPLEXITY_H
#define PROJET_C_S3_COMPLEXITY_H

//----------------------------------//
// Fichiers internes

#include "list.h"

//----------------------------------//
// Corps du fichier

/**
 * @brief Crée une liste de 1000 contact aléatoires
 * @param val Nombre de contacts à ajouter dans la liste
 */
void listContact(int);

/**
 * @brief Insert un contact dans une skiplist via le niveau 0
 * @param list Skiplist dans laquelle insérer la cellule
 */
void insertSkipListSimple(p_skiplist, p_skipcell);

/**
 * @brief Calcule la complexité  
 */
void complexity();

/**
 * @brief Remplie une liste avec 1000 contacts
 * @param list Liste dans laquelle seront insérées les 1000 contacts
 */
void thousandContactList(p_skiplist);

#endif // PROJET_C_S3_COMPLEXITY_H
