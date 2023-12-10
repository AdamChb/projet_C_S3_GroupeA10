/*----------------------------------//

            PROJET_C_3
             Partie 3
              main.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdio.h>
#include <stdlib.h>

//----------------------------------//
// Fichiers internes

#include "cell.h"
#include "list.h"
#include "diary.h"
#include "meeting.h"
#include "research.h"
#include "contact.h"
#include "data.h"
#include "complexity.h"

//----------------------------------//
// Constantes

#define NB_LEVELS 4

//----------------------------------//
// Corps du fichier

int main() {

   int choice;
   t_skiplist list = createSkipList(NB_LEVELS);

   printf("|--------------------------|\n");
   printf("\n");
   printf("         L'AGENDA C\n");
   printf("\n");
   printf("|--------------------------|\n");

    do {

      fflush(stdin);
      choice = -1;

      printf("\nVeuillez choisir une action a effectuer dans l'agenda :\n");
      printf("1-Rechercher un contact\n");
      printf("2-Ajouter un contact\n");
      printf("3-Supprimer un contact\n");
      printf("4-Sauvegarder le fichier de rendez-vous\n");
      printf("5-Charger un fichier de rendez-vous\n");
      printf("6-Tests sur la complexite\n");
      printf("0-Quitter\n");
      printf("--> ");
      scanf("%d", &choice);

      switch (choice) {
         case 1: {

            p_skipcell skipcell = autoCompletion(list);
            if (skipcell == NULL) {
               printf("\nCommande annulée.\n\n");
               int contactChoice;
               printf("Voulez-vous ajouter un rendez-vous à un nouveau contact ?\n1-Oui\n2-Non\n--> ");
               scanf("%d", &contactChoice);

               switch (contactChoice)
               {
                  case 1: {

                     // Création du contact
                     p_contact contact = createContact(createNameContact());
                     p_diary diary = createDiary(contact);
                     p_skipcell newSkipcell = createSkipCell(diary, NB_LEVELS);
                     insertSkipList(&list, newSkipcell);
                     // Création du rendez-vous
                     p_meeting meeting = createMeeting();
                     p_cell cell = createHTCell(meeting);
                     insertHTList(&(diary->event), cell);

                     break;
                  }

                  case 2: {

                     printf("\nCommande annulée.\n\n");

                     break;
                  }

                  default:{

                     printf("\nErreur, veuillez entrer une option valide.\n\n");

                     break;
                  }
               }
            } else {
               int contactChoice;
               p_diary diary = skipcell->diary;
               printf("\nChoissisez une option pour %s:\n", diary->person->fullName);
               printf("1-Afficher la liste des rendez-vous\n");
               printf("2-Créer un nouveau rendez-vous\n");
               printf("3-Supprimer un rendez-vous\n");
               printf("0-Retour au menu principal\n");
               printf("--> ");
               scanf("%d", &contactChoice);

               switch (contactChoice)
               {
                  case 1: {

                     displayMeetings(diary->event);

                     break;
                  }

                  case 2: {

                     p_meeting meeting = createMeeting();
                     p_cell cell = createHTCell(meeting);
                     insertHTList(&(diary->event), cell);
                     break;
                  }

                  case 3: {

                     displayMeetings(diary->event);
                     printf("\nVeuillez choisir le rendez vous que vous voulez supprimer (0 pour annuler): ");
                     int deleteChoice;
                     scanf("%d", &deleteChoice);
                     if (deleteChoice == 0) break;
                     int i = 1;
                     p_cell chosenCell = NULL;
                     p_cell temp = diary->event.head;
                     while (temp != NULL && chosenCell == NULL) {
                        if (i == deleteChoice) chosenCell = temp;
                        i++;
                     }
                     if (chosenCell == NULL) {
                        printf("\nRendez-vous introuvable.\n");
                     } else {
                        deleteCellInHTList(&(diary->event), chosenCell);
                     }

                     break;
                  }

                  case 0: {

                     printf("\nRetour au menu principal.\n\n");

                     break;
                  }

                  default: {

                     printf("\nErreur, veuillez entrer une option valide.\n\n");

                     break;
                  }
               }
            }

            break;
         }

         case 2: {

            // Ajout d'un contact
            p_contact contact = createContact(createNameContact());
            p_diary diary = createDiary(contact);
            p_skipcell cell = createSkipCell(diary, NB_LEVELS);
            int val = insertSkipList(&list, cell);
            if (val) printf("Contact %s ajoute.\n", contact->fullName);

            break;
         }

         case 3: {

            p_skipcell cell = autoCompletion(list);
            if (cell == NULL) {
               printf("\nSupression annulee.\n");
               break;
            }
            p_diary diary = cell->diary;
            printf("\nSuppression du contact %s en cours...\n", diary->person->fullName);
            deleteCellInSkipList(&list, cell);
            printf("Contact supprime.\n");

            break;
         }

         case 4: {

            printf("\nSauvegarde de l'agenda en cours...\n");
            saveData(&list);

            break;
         }

         case 5: {

            printf("\nChargement des donnees en cours...\n");
            loadData(&list);

            break;
         }

         case 6: {

            // Tests de la compléxité
            int complexChoice = -1;
            int endComplexity = 0;
            do {
               printf("Que voulez-vous faire ?\n");
               printf("1-Remplir l'agenda avec 1000 contacts\n");
               printf("2-Tester la complexite du projet\n");
               printf("0-Retour\n");
               printf("--> ");
               fflush(stdin);
               scanf("%d", &complexChoice);

               switch (complexChoice) {
                  case 1: {

                     thousandContactList(&list);
                     endComplexity = 1;

                     break;
                  }

                  case 2: {

                     printf("Tests de la complexite en cours...\n");
                     complexity();
                     printf("Fin des tests, les résultats sont dans des fichiers txt.\n\n");
                     endComplexity = 1;

                     break;
                  }

                  case 0: {

                     printf("\nRetour au menu principal.\n\n");
                     endComplexity = 1;

                     break;
                  }

                  default: {

                     printf("\nErreur, veuillez entrer une option valide.\n\n");

                     break;
                  }
               }
            } while (endComplexity == 0);

            break;
         }

         case 0: {

            int quitChoice;
            do {
               printf("\nVoulez-vous sauvegarder l'agenda avant de quitter ?\n1-Oui\n2-Non\n-->");
               scanf("%d", &quitChoice);

               if (quitChoice == 1) {
                  saveData(&list);
                  printf("\nDonnees sauvegardees.\n");
                  printf("Merci d'avoir utilise l'agenda.\n");
               } else if (quitChoice == 2) {
                  printf("\nDonnees non sauvegardees.\n");
                  printf("Merci d'avoir utilise l'agenda.\n");
               } else {
                  printf("\nErreur, veuillez entrer une option valide.\n\n");
               }
            } while (quitChoice != 1 && quitChoice != 2);

            break;
         }

         default: {

            printf("\nErreur, veuillez entrer une option valide.\n\n");

            break;
         }
      }

   } while (choice != 0);

   return 0;
}