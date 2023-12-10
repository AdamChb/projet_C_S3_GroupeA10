/*----------------------------------//

            PROJET_C_3
             Partie 3
              data.h

//----------------------------------*/

#ifndef PROJET_C_S3_DATA_H
#define PROJET_C_S3_DATA_H

//----------------------------------//
// Fichiers internes

#include "cell.h"
#include "list.h"

//----------------------------------//
// Corps du fichier

/**
 * @brief Vide le fichier de sauvegarde
 */
void emptyFile();

/**
 * @brief Vérifie si le fichier de sauvegarde est vide
 * @return 1 si le fichier est vide, 0 sinon
 */
int isEmptyFile();

/**
 * @brief Sauvegarde les données de la skipliste 
 * dans un fichier txt
 * @param list Skipliste à sauvegarder
 */
void saveData(p_skiplist);

/**
 * @brief Charge les données de la sauvegarde dans une skipliste
 * @param list Skipliste à charger
 */
void loadData(p_skiplist);

#endif //PROJET_C_S3_DATA_H
