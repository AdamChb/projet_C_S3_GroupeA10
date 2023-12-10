/*----------------------------------//

            PROJET_C_3
             Partie 2
              list.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdlib.h>
#include <stdio.h>

//----------------------------------//
// Fichiers internes

#include "list.h"

//----------------------------------//
// Corps du fichier

t_d_list createList(int nbLevels){
    
    /*
    Crée une liste
    */

    t_d_list list; 
    list.nbLevel = nbLevels;
    list.heads = (p_d_cell *) malloc(nbLevels * sizeof(p_d_cell));
    for (int i = 0 ; i < list.nbLevel ; i++)
    {
        *(list.heads+i) = NULL;
    }
    return list;
}

void displayListLevel(t_d_list list, int level){
    
    /*
    Affiche une ligne de la liste
    */

    printf ("[list head_%d @-]-->", level);
    p_d_cell temp = list.heads[level];
    while (temp != NULL)
    {
        printf ("[ %d|@-]-->", temp->value);
        temp = temp->nexts[level];
    }
    printf ("NULL\n");
}

void displayList(t_d_list list){
    
    /*
    Affiche une liste complète
    */

    for (int i = 0; i < list.nbLevel; i++)
    {
        displayListLevel(list, i);
    }
}

void displayAlignedList(t_d_list list){
    
    /*
    Affiche une liste complète en alignant les cellules
    */

    for (int i = 0; i < list.nbLevel; i++)
    {
        printf ("[list head_%d @-]", i);  // Affiche la tête de la liste
        p_d_cell temp = list.heads[0];
        while (temp != NULL)
        {
            if (temp->nbLevels > i) {
                printf ("-->[ %d|@-]", temp->value);  // Affiche une cellule
            } else {
                printf ("----------");  // S'affiche si une cellule n'atteint pas ce nombre de lignes
                int val = temp->value;
                if (val < 0)
                    printf ("-");
                while (val > 9 || val < -9) {  // Ajout de '-' si le nombre est supérieur à 9 ou inférieur à -9
                    val = val/10;
                    printf("-");
                }
            }
            temp = temp->nexts[0];
        }
        printf ("-->NULL\n");
    }
}

void insertHeadList(p_d_list list, p_d_cell newCell){
    
    /*
    Insert une cellule en tête d'une liste
    */

    for (int i = 0; i < newCell->nbLevels; i++) {
       if (list->heads[i] == NULL)
        {
            list->heads[i] = newCell;  // Insertion si le niveau de la liste est vide
        }
        else
        {
            newCell->nexts[i] = list->heads[i];  // Insertion si le niveau de la liste n'est pas vide
            list->heads[i] = newCell;
        }
    }
}

void insertList(p_d_list list, int val, int nbLevels){
    
    /*
    Insert une cellule dans une liste
    */

    // Création de la nouvelle cellule
    p_d_cell newCell = createCell(val, nbLevels);
    
    // Insertion si la liste est vide
    if (list->heads[0] == NULL) {  
        for (int i = 0; i < nbLevels; i++) {
            list->heads[i] = newCell;
        }
    } else {
        // Recherche du niveau à partir duquel faire la recherche 
        // de l'emplacement de la nouvelle cellule
        int indiceMax = list->nbLevel - 1;
        while (list->heads[indiceMax] == NULL) {
            indiceMax--;
        }
        while (indiceMax >= 0 && list->heads[indiceMax]->value > val) {
            indiceMax--;
        }
        // Création des variables utiles à l'insertion
        p_d_cell temp = list->heads[indiceMax];
        p_d_cell prec = temp;
        p_d_cell precs[list->nbLevel];
        for (int i = 0; i < list->nbLevel; i++) precs[i] = NULL;
        // Recherche de l'emplacement où ajouter la cellule
        for (int i = 0; i <= indiceMax; i++) {
            while (temp != NULL && val > temp->value) {
                prec = temp;
                temp = temp->nexts[indiceMax - i];
            }
            precs[indiceMax - i] = prec;
        }
        // Ajout de la cellule en tête de liste
        if (temp == list->heads[0]) {
            for (int i = 0; i < nbLevels; i++) {
                newCell->nexts[i] = list->heads[i];
                list->heads[i] = newCell;
            }
        } else {
            // Ajout de la cellule ailleurs
            for (int i = 0; i < nbLevels; i++) {
                if (i <= indiceMax) {
                    newCell->nexts[i] = precs[i]->nexts[i];
                    precs[i]->nexts[i] = newCell;
                } else if (precs[i]) {
                    newCell->nexts[i] = precs[i]->nexts[i];
                    list->heads[i] = newCell;
                } else if (list->heads[i]) {
                    newCell->nexts[i] = list->heads[i];
                    list->heads[i] = newCell;
                } else {
                    newCell->nexts[i] = NULL;
                    list->heads[i] = newCell;
                }
                
            }
        }
    }
    
    return; 
}