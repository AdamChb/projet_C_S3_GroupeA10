/*----------------------------------//

            PROJET_C_3
             Partie 3
           rendez-vous.h

//----------------------------------*/

#ifndef PROJET_C_S3_RENDEZ_VOUS_H
#define PROJET_C_S3_RENDEZ_VOUS_H

//----------------------------------//
// Fichiers internes

#include "list.h"

//----------------------------------//
// Corps du fichier

//Structure d'une date
typedef struct date {
    int day;
    int month;
    int year;
} date;

//Structure d'une heure/durée
typedef struct hour {
    int hour;
    int minute;
} hour;

//Structure d'un rendez-vous
typedef struct s_meeting {
    date moment;
    hour start;
    hour duration;
    char* item;
} t_meeting, * p_meeting;

/**
 * @brief Sécuride la saisie de chaînes de caractères
 * @return Une chaîne de caractère
*/
char * scanString();

/**
 * @brief Crée un rendez-vous
 * @return Un rendez-vous
 */
p_meeting createMeeting();

/**
 * @brief Crée un rendez-vous depuis la sauvegarde
 * @param tab Tableau des données du rendez-vous
 * @param item Description du rendes-vous
 * @return Un rendez-vous
*/
p_meeting createMeetingFromData(int *, char *);

/**
 * @brief Supprime un rendez-vous
 * @param meeting Rendez-vous à supprimer
 */
void deleteMeeting(p_meeting);

/**
 * @brief Affiche un seul rendez-vous
 * @param meeting Rendez-vous à afficher
 */
void displayMeeting(t_meeting);

/**
 * @brief Affiche une liste de rendez-vous
 * @param list Liste des rendez-vous
 */
void displayMeetings(t_ht_list);

#endif //PROJET_C_S3_RENDEZ_VOUS_H