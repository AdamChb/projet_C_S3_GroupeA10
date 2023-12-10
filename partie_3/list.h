/*----------------------------------//

            PROJET_C_3
             Partie 3
              list.h

//----------------------------------*/

#ifndef PROJET_C_S3_LIST_H
#define PROJET_C_S3_LIST_H

//----------------------------------//
// Fichiers internes

#include "cell.h"

//----------------------------------//
// Corps du fichier

//Structure d'une liste doublement chaînée
typedef struct s_ht_list {
    p_cell head, tail;
} t_ht_list, * p_ht_list;

/**
 * @brief Crée une liste de rendez-vous doublement chaînée vide
 * @return Une liste doublement chaînée vide
 */
t_ht_list createHTList();

/**
 * @brief Insert un rendez-vous dans une liste
 * @param list Liste dans laquelle insérer la nouvelle cellule
 * @param cell Cellule à insérer dans la liste
 */
void insertHTList(p_ht_list, p_cell);

/**
 * @brief Supprime une cellule de la liste
 * @param list Liste dans laquelle supprimer une cellule
 * @param cell Cellule à supprimer
 */
void deleteCellInHTList(p_ht_list, p_cell);

/**
 * @brief Supprime une liste doublement chaînée
 * @param list Liste à supprimer
*/
void deleteHTList(p_ht_list);

//Structure d'une skiplist
typedef struct s_skiplist {
    int nbLevel;
    p_skipcell * heads;
} t_skiplist, * p_skiplist;

/**
 * @brief Crée une skipliste vide de contacts
 * @return Une liste doublement chaînée vide
 */
t_skiplist createSkipList(int);

/**
 * @brief Modifie le nombre de niveaux de la cellule suivante
 * @param list Liste des entrées d'agenda
 * @param precs Tableau des cellules précédent la nouvelle
 * @param cell Cellule suivante
 */
void modifyNbLevelsNext(p_skiplist, p_skipcell *, p_skipcell, p_skipcell);

/**
 * @brief Modifie le nombre de niveaux de la cellule suivante si la cellule est insérée en tête
 * @param list Liste des entrées d'agenda
 * @param cell Cellule suivante
 */
void modifyNbLevelsNextHead(p_skiplist,  p_skipcell);

/**
 * @brief Modifie le nombre de niveaux de la nouvelle cellule
 * @param list Liste des entrées d'agenda
 * @param oldDiary Nom du contact précédant
 * @param newDiary Nom du nouveau contact
 * @param cell Nouvelle cellule
 */
void modifyNbLevelPrec(p_skiplist, p_skipcell, p_skipcell);

/**
 * @brief Insert un contact dans une skipliste
 * @param list Liste dans laquelle insérer la nouvelle cellule
 * @param cell Cellule à insérer dans la liste
 * @return 1 si le contact a bien été ajouté, 0 si le contact existe déjà
 */
int insertSkipList(p_skiplist, p_skipcell);

/**
 * @brief Supprime une cellule de la skipliste
 * @param list Liste dans laquelle supprimer une cellule
 * @param cell Cellule à supprimer
 */
void deleteCellInSkipList(p_skiplist, p_skipcell);

#endif //PROJET_C_S3_LIST_H
