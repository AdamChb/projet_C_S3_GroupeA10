/*----------------------------------//

            PROJET_C_3
             Partie 3
           complexity.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//----------------------------------//
// Fichiers internes

#include "complexity.h"
#include "cell.h"
#include "list.h"
#include "contact.h"
#include "diary.h"
#include "timer.h"

//----------------------------------//
// Constantes

#define FILE_NAME "namesFile.txt"
#define FILE_TIME_INSERT "insertTimes.txt"
#define LIST_LASTNAME_FILE "noms.txt"
#define LIST_FIRSTNAME_FILE "prenoms.txt"

//----------------------------------//
// Corps du fichier

void listContact(int val) {

    /*
    Crée une liste de 1000 contacts aléatoirement
    */

    printf("Chargement d'une liste de %d contact...\n", val);
    srand(time(NULL));
    FILE * data = fopen(FILE_NAME, "w");
    if (data == NULL) return;
    for (int i = 0; i < val; i++) {
        FILE * names = fopen(LIST_LASTNAME_FILE, "r");
        if (names == NULL) return;
        FILE * prenoms = fopen(LIST_FIRSTNAME_FILE, "r");
        if (prenoms == NULL) return;
        int randName = (rand() * 10) % 218900;
        int randPrenom = (rand() * 10) % 36000;
        char fullName[64];
        char buffer1[100];
        char buffer2[100];
        for (int j = 0; j < randName; j++) {
            fgets(buffer1, sizeof(buffer1), names);
        }
        char * name = fgets(buffer1, 100, names);
        name[strlen(name) - 1] = '\0';
        for (int j = 0; j < randPrenom; j++) {
            fgets(buffer2, sizeof(buffer2), prenoms);
        }
        char * prenom = fgets(buffer2, 100, prenoms);
        prenom[strlen(prenom) - 1] = '\0';
        strcpy(fullName, name);
        strcat(fullName, "_");
        strcat(fullName, prenom);
        char oui[200];
        for (int j = 0; j < strlen(fullName); j++) oui[j] = tolower(fullName[j]);
        oui[strlen(fullName)] = '\0';
        fprintf(data, "%s\n", oui);
        fclose(names);
        fclose(prenoms);
    }
    fclose(data);
    printf("Liste chargee.\n");

    return;
}

void insertSkipListSimple(p_skiplist list, p_skipcell newCell) {

    /*
    Insert une cellule dans une skiplist via le niveau 0
    */

    if (list->heads[0] == NULL) list->heads[0] = newCell;
    else
    {
        p_skipcell temp = list->heads[0];
        p_skipcell prev = temp;
        p_diary newDiary = newCell->diary;
        int nameTest = 0;

        while (temp != NULL && nameTest == 0) {
            p_diary oldDiary = temp->diary;
            if (strcmp(newDiary->person->fullName, oldDiary->person->fullName) <= 0) nameTest = 1;
            else {
                prev = temp;
                temp = temp->nexts[0];
            }
        }
        if (temp == NULL) {
            prev->nexts[0] = newCell;
        } else if (temp == list->heads[0]) {
            newCell->nexts[0] = list->heads[0];
            list->heads[0] = newCell;
        } else {
            newCell->nexts[0] = temp;
            prev->nexts[0] = newCell;
        }
    }

    return;
}

void complexity() {

    /*
    Calcule la complexité
    */

    // Crée deux listes qui seront utilisées pour les tests
    t_skiplist listClassic = createSkipList(1);  // Un seul niveau pour les tests sur le niveau 0
    t_skiplist listAdvanced = createSkipList(4);  // 4 niveaux pour les tests sur une skiplist classique
    // Crée un fichier txt avec 10000 contacts
    listContact(10000);
    // Ouverture des fichiers de sauvegarde des données
    FILE * insertFile = fopen(FILE_TIME_INSERT, "w");
    // Tests de la complexité
    char format[] = "%d\t%s\t%s\n";
    for (int i = 1000; i <=10000; i += 1000) {
        t_skiplist listClassic = createSkipList(1);  // Un seul niveau pour les tests sur le niveau 0
        t_skiplist listAdvanced = createSkipList(4);  // 4 niveaux pour les tests sur une skiplist classique
        char * time_insert_classic;
        char * time_insert_advanced;

        // Insertion classique
        FILE * namesFile1 = fopen(FILE_NAME, "r");
        char buffer1[64];
        printf("Insertion classique pour %d contacts.\n", i);
        startTimer();
        for (int j = 0; j < i; j++) {
            char * name = fgets(buffer1, sizeof(buffer1), namesFile1);
            name[strlen(name) - 1] = '\0';
            p_contact contact = createContact(name);
            p_diary diary = createDiary(contact);
            p_skipcell cell = createSkipCell(diary, listClassic.nbLevel);
            insertSkipListSimple(&listClassic, cell);
        }
        stopTimer();
        fclose(namesFile1);
        time_insert_classic = getTimeAsString();

        // Insertion avancée
        FILE * namesFile2 = fopen(FILE_NAME, "r");
        char buffer2[64];
        printf("Insertion avancee pour %d contacts.\n", i);
        startTimer();
        for (int j = 0; j < i; j++) {
            char * name = fgets(buffer2, sizeof(buffer2), namesFile2);
            name[strlen(name) - 1] = '\0';
            p_contact contact = createContact(name);
            p_diary diary = createDiary(contact);
            p_skipcell cell = createSkipCell(diary, listAdvanced.nbLevel);
            insertSkipList(&listAdvanced, cell);
        }
        stopTimer();
        fclose(namesFile2);
        time_insert_advanced = getTimeAsString();

        // Sauvegarde des données
        fprintf(insertFile, format, i, time_insert_classic, time_insert_advanced);
    }
    // Fermeture du fichier de sauvegarde des données
    fclose(insertFile);

    return;
}

void thousandContactList(p_skiplist list) {

    /*
    Remplie une liste avec 1000 contacts
    */

    // Crée un fichier txt avec 1000 contacts
    listContact(1000);

    printf("\nInsertion des contacts dans l'agenda...\n\n");
    FILE * namesFile = fopen(FILE_NAME, "r");
    char buffer[64];
    for (int i = 0; i < 1000; i++) {
        char * name = fgets(buffer, sizeof(buffer), namesFile);
        name[strlen(name) - 1] = '\0';
        p_contact contact = createContact(name);
        p_diary diary = createDiary(contact);
        p_skipcell cell = createSkipCell(diary, list->nbLevel);
        int val = insertSkipList(list, cell);
        if (val) printf("Contact %s ajoute.\n", contact->fullName);
    }
    fclose(namesFile);
    printf("Les contacts ont tous ete inseres.\n\n");

    return;
}
