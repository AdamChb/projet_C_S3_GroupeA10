/*----------------------------------//

            PROJET_C_3
             Partie 3
             agenda.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdlib.h>

//----------------------------------//
// Fichiers internes

#include "diary.h"

//----------------------------------//
// Corps du fichier

p_diary createDiary(p_contact contact) {

    /*
    Crée une entrée d'agenda avec un contact
    */

    p_diary diary = (p_diary) malloc(sizeof(t_diary));
    diary->person = contact;
    diary->event = createHTList();

    return diary;
}

void deleteDiary(p_diary diary) {

    /*
    Supprime une entrée d'agenda
    */

    deleteContact(diary->person);
    deleteHTList(&(diary->event));
    free(diary);
    diary = NULL;

    return;
}

void displayDiary(t_diary diary) {

    /*
    Affiche une entrée d'agenda
    */

    displayContact(*(diary.person));
    displayMeetings(diary.event);
    
    return;
}

void addMeetingToDiary(p_diary diary, p_meeting meeting) {

    /*
    Ajoute un rendez-vous à une entrée d'agenda
    */

    p_cell cell = createHTCell(meeting);
    insertHTList(&(diary->event), cell);

    return;
}
