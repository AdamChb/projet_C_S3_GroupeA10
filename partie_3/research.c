/*----------------------------------//

            PROJET_C_3
             Partie 3
            research.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//----------------------------------//
// Fichiers internes

#include "research.h"
#include "diary.h"

//----------------------------------//
// Corps du fichier

int isStarting(char * researched, char * verified) {

    /*
    Vérifie si une chaîne de caractère commence par une autre
    */

    int test = 1;
    for (int i = 0 ; i < strlen(researched) && test == 1 ; i++) {
        if (researched[i] != verified[i]) {
            test = 0;
        }
    }

    return test;
}

p_skipcell autoCompletion(t_skiplist list) {

    /*
    Cherche dans la liste de contacts le nom correpondant
    à la recherche
    */

    p_skipcell cell = NULL;
    int stop = 0;
    int found = 0;

    // Vérifie si la liste contient des contacts
    if (list.heads[0] == NULL && stop == 0) {
        printf("La liste de contacts est vide.");
        found = 1;
        return NULL;
    }

    do {
        char * name;

        // Entrée du nom du contact recherché
        int nameTest = 1;
        do {
            nameTest = 1;
            printf("Entrez le nom de la personne que vous cherchez, sous le format nom_prenom, minimum 3 lettres (STOP pour annuler): \n");
            printf("--> ");
            name = scanString();
            for (int i = 0; name[i]; i++) {
                if ((name[i] < 'a' || name[i] > 'z') && name[i] != '_' && name[i] != ' ' && name[i] != '-' && name[i] != '\'') {
                    nameTest = 0;
                }
            }
            if (strlen(name) < 3) nameTest = 0;
            if (strcmp(name, "STOP") == 0) {
                nameTest = 1;
                stop = 1;
                cell = NULL;
            }
            if (!nameTest) printf("Veuillez entrer un nom sous le bon format.\n");
        } while (nameTest == 0);

        // Parcours de la liste pour trouver la ou les contacts correspondants à la recherche
        int firstName = 1;
        if (stop == 0 && found == 0) {
            p_skipcell temp = list.heads[list.nbLevel - 1];
            p_skipcell prec = temp;
            int i = 1;
            int endList = 0;
            while (temp != NULL && found != 1 && i <= list.nbLevel && endList != 1) {
                p_diary diary = temp->diary;
                // Le contact recherché est trouvé
                if (strcmp(name, diary->person->fullName) == 0) {
                    found = 1;
                    cell = temp;
                // Recherhce si le niveau 0 est atteint
                } else if (i == list.nbLevel) {
                    p_diary precDiary = NULL;
                    if (temp != list.heads[0]) precDiary = prec->diary;
                    p_diary nextDiary = NULL;
                    if (temp->nexts[0] != NULL) nextDiary = temp->nexts[0]->diary;
                    // Vérifie si le nom de la cellule temp contient la chaîne de caractère cherchée
                    if (isStarting(name, diary->person->fullName)) {
                        // Le nom trouvé est le seul correspondant à la recherche
                        if ((nextDiary == NULL || isStarting(name, nextDiary->person->fullName) == 0) && (precDiary == NULL || isStarting(name, precDiary->person->fullName) == 0)) {
                            found = 1;
                            cell = temp;
                        } else {
                            // Affiche la liste des contacts correspondants à la recherche
                            if (firstName == 1) {
                                printf("Liste des noms correspondants a la recherche :\n");
                                firstName = 0;
                            }
                            printf(" - %s\n", diary->person->fullName);
                            prec = temp;
                            temp = temp->nexts[0];
                            if (temp == NULL) endList = 1;
                        }
                    } else if (isStarting(name, precDiary->person->fullName)) {
                        // Si tous les noms correspondants à la chaîne ont été affichées
                        endList = 1;
                    } else if (strcmp(name, diary->person->fullName) > 0) {
                        // Si le nom du contact est supérieur à celui de la chaîne et que le niveau
                        // de la recherche est le niveau 0, met fin à la recherche
                        temp = NULL;
                    } else {
                        // Si le nom du contact de la cellule ne commence pas par la chaîne
                        prec = temp;
                        temp = temp->nexts[0];
                    }
                } else if (isStarting(name, diary->person->fullName)) {
                    // Si le nom du contact de la cellule commence par la chaîne recherchée
                    // mais que le niveau de la liste n'est pas 0
                    i = list.nbLevel;
                } else if (strcmp(name, diary->person->fullName) < 0) {
                    // Si le nom du contact de la cellule est inférieur à la chaîne
                    i++;
                    temp = prec->nexts[list.nbLevel - i];
                } else if (strcmp(name, diary->person->fullName) > 0 && temp->nexts[list.nbLevel - i] == NULL) {
                    // Si le nom du contact de la cellule est supérieur à la chaîne
                    // et que la cellule suivante sur la liste est NULL
                    if (i == list.nbLevel) temp = NULL; // Si le niveau actuel est le niveau 0
                    else {
                        i++;
                        prec = temp;
                    }
                } else if (strcmp(name, diary->person->fullName) > 0) {
                    // Si le nom du contact de la cellule est supérieur à la chaîne
                    prec = temp;
                    temp = temp->nexts[list.nbLevel - i];
                }
            }
            // Si aucune correspondance n'a été trouvé
            if (temp == NULL && endList == 0) {
                printf("Aucun contact correspondant a votre recherche n'est trouve.\n");
            }
        }
        
    } while (!found && !stop);

    return cell;
}
