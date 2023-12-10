/*----------------------------------//

            PROJET_C_3
             Partie 3
              list.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//----------------------------------//
// Fichiers internes

#include "list.h"
#include "meeting.h"
#include "diary.h"

//----------------------------------//
// Corps du fichier

t_ht_list createHTList() {

    /*
    Crée une liste de rendez-vous doublement chaînée vide
    */

    t_ht_list list;
    list.head = NULL;
    list.tail = NULL;

    return list;
}

void insertHTList(p_ht_list list , p_cell cell) {

    /*
    Insert un rendez-vous dans une liste
    */

    if (list->head == NULL) {
        // Si la liste est vide
        list->head = cell;
        list->tail = cell;
    } else {
        p_cell temp = list->head;
        int dateTest = 0;

        while (temp != NULL && dateTest == 0) {
            char* new = (char*) malloc(sizeof(char)*32);
            p_meeting newMeeting = cell->meeting;
            sprintf(new, "%04d %02d %02d %02d %02d", newMeeting->moment.year, newMeeting->moment.month, newMeeting->moment.day, newMeeting->start.hour, newMeeting->start.minute);
            char* old = (char*) malloc(sizeof(char)*32);
            p_meeting oldMeeting = temp->meeting;
            sprintf(old, "%04d %02d %02d %02d %02d", oldMeeting->moment.year, oldMeeting->moment.month, oldMeeting->moment.day, oldMeeting->start.hour, oldMeeting->start.minute);

            // Recherche de l'emplacement de la cellule dans la liste des rendez-vous
            // pour le mettre dans l'ordre chronologique
            if (strcmp(new, old) <= 0)
                dateTest = 1;
            else
                temp = temp->next;
        }
        if (temp == NULL) {
            // Si la cellule doit aller à la fin de la liste
            list->tail->next = cell;
            cell->prec = list->tail;
            list->tail = cell;
        } else if (temp == list->head) {
            // Si la cellule doit aller en t^te de liste
            cell->next = list->head;
            list->head->prec = cell;
            list->head = cell;
        } else {
            // Si la cellule doit aller dans le milieu de la liste
            cell->next = temp;
            cell->prec = temp->prec;
            temp->prec->next = cell;
            temp->prec = cell;
        }
    }

    return;
}

void deleteCellInHTList(p_ht_list list, p_cell cell) {

    /*
    Supprime une cellule de la liste
    */
    if (cell == list->head && cell == list->tail)
        // Si la cellule est la tête et la queue de la cellule : seul maillon de la liste
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else if (cell == list->head) {
        // Si la cellule est en tête de liste
        list->head = cell->next;
        list->head->prec = NULL;
    } else if (cell == list->tail) {
        // Si la cellule est en queue de liste
        list->tail = cell->prec;
        list->tail->next = NULL;
    } else {
        // Si la cellule est dans le milieu de la liste
        cell->next->prec = cell->prec;
        cell->prec->next = cell->next;
    }
    deleteHTCell(cell);

    return;
}

void deleteHTList(p_ht_list list) {

    /*
    Supprime une liste doublement chaînée
    */

    while (list->head != NULL) {
        deleteCellInHTList(list, list->head);
    }

    return;
}

t_skiplist createSkipList(int nbLevel) {

    /*
    Crée une skipliste vide de contacts
    */

    t_skiplist list;
    list.nbLevel = nbLevel;
    list.heads = (p_skipcell * ) malloc(nbLevel * sizeof(p_skipcell));
    for (int i = 0; i < nbLevel; i++) {
        list.heads[i] = NULL;
    }

    return list;
}

void modifyNbLevelsNext(p_skiplist list, p_skipcell * precs,  p_skipcell cell, p_skipcell temp) {

    /*
    Modifie le nombre de niveaux de la cellule suivante
    */

    p_diary newDiary = cell->diary;
    p_diary oldDiary = temp->diary;
    int sameLetter = sameLetterNumber(newDiary->person->fullName, oldDiary->person->fullName);
    if (sameLetter != 0) {
        for (int i = list->nbLevel - sameLetter; i < temp->nbLevel; i++) {
            if (precs[i]->nexts[i] != NULL)
            precs[i]->nexts[i] = precs[i]->nexts[i]->nexts[i];
        }
        temp->nbLevel = list->nbLevel - sameLetter;
        temp->nexts = (p_skipcell *) realloc(temp->nexts, temp->nbLevel * sizeof(p_skipcell));
    }

    return;
}

void modifyNbLevelsNextHead(p_skiplist list,  p_skipcell cell) {

    /*
    Modifie le nombre de niveaux de la cellule suivante si la cellule est insérée en tête
    */

    p_diary newDiary = cell->diary;
    p_diary oldDiary = list->heads[0]->diary;
    int sameLetter = sameLetterNumber(newDiary->person->fullName, oldDiary->person->fullName);
    if (sameLetter != 0) {
        for (int i = list->nbLevel - sameLetter; i < list->heads[0]->nbLevel; i++) {
            list->heads[i] = list->heads[i]->nexts[i];
        }
        list->heads[0]->nbLevel = list->nbLevel - sameLetter;
        list->heads[0]->nexts = (p_skipcell *) realloc(list->heads[0]->nexts, list->heads[0]->nbLevel * sizeof(p_skipcell));
    }

    return;
}

void modifyNbLevelPrec(p_skiplist list, p_skipcell prec, p_skipcell cell) {

    /*
    Modifie le nombre de niveaux de la nouvelle cellule
    */

    p_diary newDiary = cell->diary;
    p_diary oldDiary = prec->diary;
    int sameLetterPrec = sameLetterNumber(newDiary->person->fullName, oldDiary->person->fullName);
    if (sameLetterPrec != 0) {
        cell->nbLevel = list->nbLevel - sameLetterPrec;
        cell->nexts = (p_skipcell *) realloc(cell->nexts, cell->nbLevel * sizeof(p_skipcell));
    }

    return;
}

int insertSkipList(p_skiplist list, p_skipcell cell) {

    /*
    Insert un contact dans une skipliste
    */

    // Insertion si la liste est vide
    if (list->heads[0] == NULL) {
        for (int i = 0; i < cell->nbLevel; i++) {
            list->heads[i] = cell;
        }
    } else {
        // Création des variables utiles à l'insertion
        p_diary newDiary = cell->diary;
        p_diary oldDiary = NULL;
        int indiceMax = list->nbLevel - 1;
        p_skipcell temp = list->heads[indiceMax];
        p_skipcell prec = temp;
        p_skipcell precs[list->nbLevel];
        for (int i = 0; i < list->nbLevel; i++) precs[i] = NULL;
        // Recherche de l'emplacement où ajouter la cellule
        int i = 0;
        while (temp != NULL && i <= indiceMax) {
            oldDiary = temp->diary;
            int val = strcmp(newDiary->person->fullName, oldDiary->person->fullName);
            if (val == 0) {
                printf("Ce nom existe deja\n");
                deleteSkipCell(cell);
                return 0;
            } else if (val < 0) {
                precs[indiceMax - i] = prec;
                i++;
                if (i <= indiceMax) temp = prec->nexts[indiceMax - i];
            } else if (temp->nexts[indiceMax - i] == NULL && val > 0) {
                precs[indiceMax - i] = temp;
                i++;
                prec = temp;
            } else if (val > 0) {
                prec = temp;
                temp = temp->nexts[indiceMax - i];
            }
        }
        // Ajout de la cellule en tête de liste
        oldDiary = list->heads[0]->diary;
        if (strcmp(newDiary->person->fullName, oldDiary->person->fullName) < 0) {
            // Modifie le nombre de niveaux de la cellule suivante
            modifyNbLevelsNextHead(list, cell);
            // Insertion de la cellule
            for (int i = 0; i < list->nbLevel; i++) {
                // La première cellule doit avoir le nombre de niveaux de
                // la liste, donc il n'y a pas besoin de realloc() le tableau
                // des cellules suivantes, une cellule étant initialisée avec
                // le même nombre de niveaux que la liste
                cell->nexts[i] = list->heads[i];
                list->heads[i] = cell;
            }
        } else {
            // Ajout de la cellule à la fin de la liste
            if (precs[0]->nexts[0] == NULL) {
                // Modifie le nombre de niveaux de la nouvelle cellule
                modifyNbLevelPrec(list, precs[0], cell);
                for (int i = 0; i < cell->nbLevel; i++) {
                    precs[i]->nexts[i] = cell;
                }
            } else {  // Ajout de la cellule au milieu de la liste
                // Modifie le nombre de niveaux de la cellule suivante
                modifyNbLevelsNext(list, precs, cell, precs[0]->nexts[0]);
                // Modifie le nombre de niveaux de la nouvelle cellule
                modifyNbLevelPrec(list, precs[0], cell);
                for (int i = 0; i < cell->nbLevel; i++) {
                    cell->nexts[i] = precs[i]->nexts[i];
                    precs[i]->nexts[i] = cell;
                }
            }
        }
    }

    return 1;
}

void deleteCellInSkipList(p_skiplist list, p_skipcell cell) {

    /*
    Supprime une cellule de la skipliste
    */

    // Création des variables utiles à la suppression
    p_diary newDiary = cell->diary;
    p_diary oldDiary = NULL;
    int indiceMax = list->nbLevel - 1;
    p_skipcell temp = list->heads[indiceMax];
    p_skipcell prec = temp;
    p_skipcell precs[list->nbLevel];
    for (int i = 0; i < list->nbLevel; i++) precs[i] = NULL;
    int nbPrec = 0;

    // Recherche de l'emplacement de la cellule à supprimer
    int i = 0;
    while (temp != NULL && i <= indiceMax) {
        oldDiary = temp->diary;
        int val = strcmp(newDiary->person->fullName, oldDiary->person->fullName);
        if (val <= 0) {
            precs[indiceMax - i] = prec;
            nbPrec++;
            i++;
            temp = prec->nexts[indiceMax - i];
        } else if (temp->nexts[indiceMax - i] == NULL && val > 0) {
            precs[indiceMax - i] = temp;
            nbPrec++;
            i++;
            prec = temp;
        } else if (val > 0) {
            prec = temp;
            temp = temp->nexts[indiceMax - i];
        }
    }

    // Suppression de la cellule si elle est en tête de liste
    if (cell == list->heads[0] && cell->nexts[0] != NULL) {
        cell->nexts[0]->nbLevel = list->nbLevel;
        cell->nexts[0]->nexts = (p_skipcell *) realloc(cell->nexts[0]->nexts, cell->nexts[0]->nbLevel * sizeof(p_skipcell));
        for (int i = 0; i < list->nbLevel; i++) {
            list->heads[i] = cell->nexts[0];
        }
    } else if (cell->nexts[0] != NULL) {
        // Suppression de la cellule si elle est ailleurs
        cell->nexts[0]->nbLevel = cell->nbLevel;
        cell->nexts[0]->nexts = (p_skipcell *) realloc(cell->nexts[0]->nexts, cell->nexts[0]->nbLevel * sizeof(p_skipcell));
        for (int i = 0; i < cell->nexts[0]->nbLevel; i++) {
            precs[i]->nexts[i] = cell->nexts[0];
        }
    } else if (cell != list->heads[0]) {
        // Suppression de la cellule si elle est à la fin de la liste
        for (int i = 0; i < cell->nbLevel; i++) {
            precs[i]->nexts[i] = NULL;
        }
    } else {
        // Suppression de la cellule si elle est la seule de la liste
        for (int i = 0; i < list->nbLevel; i++) {
            list->heads[i] = NULL;
        }
    }

    free(cell->nexts);
    cell->nexts = NULL;
    deleteSkipCell(cell);

    return;
}
