/*----------------------------------//

            PROJET_C_3
             Partie 3
             agenda.h

//----------------------------------*/

#ifndef PROJET_C_S3_AGENDA_H
#define PROJET_C_S3_AGENDA_H

//----------------------------------//
// Fichiers internes

#include "contact.h"
#include "meeting.h"
#include "list.h"

//----------------------------------//
// Corps du fichier

// Structure d'une entrée d'agenda
typedef struct s_diary
{
    p_contact person;
    t_ht_list event;
} t_diary, * p_diary;

/**
 * @brief Crée une entrée d'agenda avec un contact
 * @param contact Contact à ajouter dans la liste de contacts
 * @return Une entrée agenda avec un contact et une liste
   de rendez-vous vide
 */
p_diary createDiary(p_contact);

/**
 * @brief Supprime une entrée d'agenda
 * @param diary Entrée d'agenda à supprimer
 */
void deleteDiary(p_diary);

/**
 * @brief Affiche une entrée d'agenda
 * @param diary Entrée d'agenda à afficher
 */
void displayDiary(t_diary);

/**
 * @brief Ajoute un rendez-vous à une entrée d'agenda
 * @param diary Entrée d'agenda
 * @param meeting Rendez-vous à enregistrer
*/
void addMeetingToDiary(p_diary, p_meeting);

#endif //PROJET_C_S3_AGENDA_H
