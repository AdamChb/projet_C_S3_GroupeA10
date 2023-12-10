/*----------------------------------//

            PROJET_C_3
             Partie 3
              data.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//----------------------------------//
// Fichiers internes

#include "data.h"
#include "diary.h"
#include "meeting.h"
#include "contact.h"

//----------------------------------//
// Constantes

#define DATA_FILE_PATH "data.txt"

//----------------------------------//
// Corps du fichier

void emptyFile() {

    /*
    Vide le fichier de sauvegarde
    */

    FILE * dataFile = fopen(DATA_FILE_PATH, "w");
    fclose(dataFile);

    return;
}

int isEmptyFile() {

    /*
    Vérifie si le fichier de sauvegarde est vide
    */

    FILE * dataFile = fopen(DATA_FILE_PATH, "r");
    char buffer[64];
    if (fgets(buffer, sizeof(buffer), dataFile)) return 0;

    return 1;
}

void saveData(p_skiplist list) {

    /*
    Sauvegarde les données de la skipliste dans un fichier txt
    */

    p_skipcell temp = list->heads[0];
    // Vérifie s'il y a des données à sauvegarder
    if (temp == NULL) {
        printf("Aucune donnée à sauvegarder.\n");
        return;
    }
    emptyFile();  // Vide le fichier
    FILE* dataFile = fopen(DATA_FILE_PATH, "a");
    // Arrêt de la fonction s'il y a une erreur lors du chargement 
    if (dataFile == NULL) {
        printf("Une erreur s'est produite lors de l'ouverture du fichier.\n");
        fclose(dataFile);
        return;
    }
    while (temp != NULL) {
        // Sauvegarde d'un contact
        fprintf(dataFile, "-person-\n");
        p_diary diary = temp->diary;
        fprintf(dataFile, "%s\n", diary->person->fullName);
        // Sauvegarde des rendez-vous d'un contact
        p_cell tempMeeting = diary->event.head;
        while (tempMeeting != NULL) {
            fprintf(dataFile, "-meeting-\n");
            p_meeting meeting = tempMeeting->meeting;
            fprintf(dataFile, "%d %d %d\n",meeting->moment.day, meeting->moment.month, meeting->moment.year);
            fprintf(dataFile, "%d %d\n", meeting->start.hour, meeting->start.minute);
            fprintf(dataFile, "%d %d\n", meeting->duration.hour, meeting->duration.minute);
            fprintf(dataFile, "%s\n", meeting->item);
            tempMeeting = tempMeeting->next;
        }
        temp = temp->nexts[0];
    }
    fprintf(dataFile, "-end-\n");
    printf("\nDonnees sauvegardees.\n\n");
    fclose(dataFile);

    return;
}

void loadData(p_skiplist list) {

    /*
    Charge les données de la sauvegarde dans une skipliste
    */

    // Vérifie s'il y a des données à charger
    if (isEmptyFile()){
        printf("Aucune donnée à charger.\n");
        return;
    }
    // Ouverture du fichier en lecture
    FILE * dataFile = fopen(DATA_FILE_PATH, "r");
    if (dataFile == NULL) {
        printf("Erreur d'acces au fichier.");
        return;
    }
    char buffer[512];
    int test = 1;
    p_diary diary = NULL;
    while (test) {
        fgets(buffer, sizeof(buffer), dataFile);
        // Fin de la sauvegarde
        if (strcmp(buffer, "-end-\n") == 0) {
            printf("Donnees chargees.");
            test = 0;
        // Chargement d'un contact
        } else if (strcmp(buffer, "-person-\n") == 0) {
            char * fullName = fgets(buffer, sizeof(buffer), dataFile);
            fullName[strlen(fullName) - 1] = '\0';
            printf("Chargement de %s...\n", fullName);
            p_contact contact = createContact(fullName);
            diary = createDiary(contact);
            p_skipcell skipcell = createSkipCell(diary, list->nbLevel);
            insertSkipList(list, skipcell);
        // Chargement d'un rendez-vous
        } else if (strcmp(buffer, "-meeting-\n") == 0) {
            int meetingData[7];
            char * momentData = fgets(buffer, sizeof(buffer), dataFile);
            sscanf(momentData, "%d %d %d\n", &meetingData[0], &meetingData[1], &meetingData[2]);
            char * startData = fgets(buffer, sizeof(buffer), dataFile);
            sscanf(startData, "%d %d\n", &meetingData[3], &meetingData[4]);
            char * durationData = fgets(buffer, sizeof(buffer), dataFile);
            sscanf(durationData, "%d %d\n", &meetingData[5], &meetingData[6]);
            char * itemData = fgets(buffer, sizeof(buffer), dataFile);
            itemData[strlen(itemData) - 1] = '\0';
            p_meeting meeting = createMeetingFromData(meetingData, itemData);
            addMeetingToDiary(diary, meeting);
        } else {
            // Erreur si la ligne lu ne correspond pas à une ligen attendue
            printf("Erreur en chargeant les données.");
            test = 0;
        }
    }

    return;
}
