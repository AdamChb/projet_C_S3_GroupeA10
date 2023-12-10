/*----------------------------------//

            PROJET_C_3
             Partie 3
           rendez-vous.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------//
// Fichiers internes

#include "meeting.h"

//----------------------------------//
// Corps du fichier

char * scanString()
{

    /*
    Sécurise la saisie de chaînes de caractère
    */

    fflush(stdin);
    char chaine[256];
    char * string = fgets(chaine, sizeof(chaine), stdin);
    string[strlen(string) - 1] = '\0';
    return string;

}

p_meeting createMeeting() {

    /*
    Crée un rendez-vous
    */

    p_meeting appointment = (p_meeting) malloc(sizeof(t_meeting));
    appointment->item = (char *) malloc(256 * sizeof(char));

    int month_31[] = {1, 3, 5, 7, 8, 10, 12};
    int month_30[] = {4, 6, 9, 11};

    int DateExist = 0;
    int WhichMonth = 0;

    do {
        fflush(stdin);
        printf ("\nQuelle est la date de votre rendez-vous ? JJ/MM/AAAA\n-->");
        scanf("%d/%d/%d", &(appointment->moment.day), &(appointment->moment.month), &(appointment->moment.year));

        for (int i = 0; i < 7;i++)
        {
            if (month_31[i] == appointment->moment.month)
            {
                WhichMonth = 31;
                break;
            }
        }
        for (int i = 0; i < 4;i++)
        {
            if (month_30[i] == appointment->moment.month)
            {
                WhichMonth = 30;
                break;
            }
        }

        if (appointment->moment.month == 2)
            WhichMonth = 2;

        if ((WhichMonth == 31 && appointment->moment.day >= 0 && appointment->moment.day <= 31)
            || (WhichMonth == 30 && appointment->moment.day >= 0 && appointment->moment.day <= 30)
            || (WhichMonth == 2 && appointment->moment.day >= 0 && appointment->moment.day <= 29 && ((appointment->moment.year%4 == 0 && appointment->moment.year%100 != 0) || (appointment->moment.year%400 == 0)))
            || (WhichMonth == 2 && appointment->moment.day >= 0 && appointment->moment.day <= 28 && appointment->moment.year%4 != 0))
            DateExist = 1;

    } while (DateExist == 0 || WhichMonth == 0);

    do {
        fflush(stdin);
        printf("\nA quelle heure commence votre rendez-vous ? HHhMM\n-->");
        scanf ("%dh%d", &(appointment->start.hour), &(appointment->start.minute));
    } while (appointment->start.hour < 0 || appointment->start.hour >= 24 || appointment->start.minute < 0 || appointment->start.minute >= 60);

    do {
        fflush(stdin);
        printf ("\nCombien de temps dure votre rendez-vous ? HHhMM\n-->");
        scanf("%dh%d", &(appointment->duration.hour), &(appointment->duration.minute));
    } while (appointment->duration.hour < 0 || appointment->duration.hour >= 24 || appointment->duration.minute < 0 || appointment->duration.minute >= 60);

    do {
        printf ("\nQuelle est l'objet de votre rendez-vous ?\n-->");
        const char* chaine = scanString();
        if (appointment->item != NULL)
        {
            strncpy(appointment->item, chaine, strlen(chaine) + 1);
            appointment->item[strlen(appointment->item)] = '\0';
        }
    } while (*(appointment->item) == '\0' || strlen(appointment->item) > 256);

    return appointment;
}

p_meeting createMeetingFromData(int * tab, char * item) {

    /*
    Crée un rendez-vous depuis la sauvegarde
    */

    p_meeting meeting = (p_meeting) malloc(sizeof(t_meeting));
    meeting->item = (char *) malloc(256 * sizeof(char));
    meeting->moment.day = tab[0];
    meeting->moment.month = tab[1];
    meeting->moment.year = tab[2];
    meeting->start.hour = tab[3];
    meeting->start.minute = tab[4];
    meeting->duration.hour = tab[5];
    meeting->duration.minute = tab[6];
    strncpy(meeting->item, item, strlen(item) + 1);

    return meeting;
}

void deleteMeeting(p_meeting meeting) {
    
    /*
    Supprime un rendez-vous
    */

    free(meeting);
    meeting = NULL;
    return;
}

void displayMeeting(t_meeting meeting) {

    /*
    Affiche un seul rendez-vous
    */
   
    printf ("Objet du rendez-vous : %s du %d/%d/%d a %dh%d de %dh%d minutes\n", meeting.item, meeting.moment.day, meeting.moment.month, meeting.moment.year, meeting.start.hour, meeting.start.minute, meeting.duration.hour, meeting.duration.minute);

}

void displayMeetings(t_ht_list list) {

    /*
    Affiche une liste de rendez-vous
    */

    p_cell temp = list.head;
    int i = 1;
    while (temp != NULL) 
    {
        p_meeting appointement = temp->meeting;
        printf("%d-", i);
        displayMeeting(*appointement);
        temp = temp->next;
        i++;
    }
    return;
}
