/*----------------------------------//

            PROJET_C_3
             Partie 2
              main.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdio.h>

//----------------------------------//
// Fichiers internes

#include "cell.h"
#include "list.h"
#include "research.h"

//----------------------------------//
// Corps du fichier

int main(){

    //--------------PARTIE 1--------------//

    int choice;
    do {

        // Choix de la fonction à tester

        printf("Choisi une fonction à tester :\n");
        printf("1-createCell()\n");
        printf("2-createList()\n");
        printf("3-insertHeadList()\n");
        printf("4-displayListLevel()\n");
        printf("5-displayList()\n");
        printf("6-displayAlignedList()\n");
        printf("7-insertList()\n");
        printf("8-Recherche dans la liste\n");
        printf("9-Complexité\n");
        printf("0-Mettre fin aux tests\n");
        scanf("%d", &choice);

        printf("\n");

        // Exécution du test choisi

        switch (choice) {
            case 1: {  // createCell()

                // printf("Création d'une cellule...\n");
                // p_d_cell cell = createCell(5, 4);  // Création d'une cellule
                // printf("Cellule créée !\n\n");

                break;
            }

            case 2: {  // createList()

                // printf("Création d'une liste vide...\n");
                // t_d_list list = createList(4); // Création d'une liste vide
                // printf("Liste créée !\n\n");

                break;
            }

            case 3: {  // insertHeadList()

                printf("Insertion en tête d'une cellule dans la liste...\n");
                t_d_list list = createList(5); // Création d'une liste à 5 niveaux
                p_d_cell cell1 = createCell(9, 3);
                insertHeadList(&list, cell1); // Test pour une liste vide
                p_d_cell cell2 = createCell(7, 2);
                insertHeadList(&list, cell2); // Test pour une liste non vide
                printf("Cellule insérée !\n\n");

                break;
            }
            
            case 4: {  // displayListLevel()

                t_d_list list = createList(5); // Création d'une liste à 5 niveaux

                printf("Affichage du niveau 1 de la liste vide...\n");
                displayListLevel(list, 1); // Affichage du niveau 1 vide
                printf("Niveau 1 de la liste vide affiché !\n\n");

                p_d_cell cell1 = createCell(9, 3); // Insertion de 2 maillons
                insertHeadList(&list, cell1);
                p_d_cell cell2 = createCell(7, 2);
                insertHeadList(&list, cell2);

                printf("Affichage du niveau 1 d'une liste non vide...\n");
                displayListLevel(list, 1); // Affichage du niveau 1 non vide
                printf("Niveau 1 de la liste non vide affiché !\n\n");

                break;
            }

            case 5: {  // displayList()

                t_d_list list = createList(5); // Création d'une liste à 5 niveaux

                printf("Affichage de la liste vide...\n");
                displayList(list); // Affichage de la liste vide
                printf("Liste vide affiché !\n\n");

                p_d_cell cell1 = createCell(9, 3); // Insertion de 2 maillons
                insertHeadList(&list, cell1);
                p_d_cell cell2 = createCell(7, 2);
                insertHeadList(&list, cell2);

                printf("Affichage d'une liste non vide...\n");
                displayList(list); // Affichage de la liste non vide
                printf("Liste non vide affiché !\n\n");

                break;
            }

            case 6: {  // displayAlignedList()

                t_d_list list = createList(5); // Création d'une liste à 5 niveaux

                printf("Affichage de la liste vide alignée...\n");
                displayAlignedList(list); // Affichage de la liste vide alignée
                printf("Liste vide alignée affiché !\n\n");

                p_d_cell cell1 = createCell(9, 3); // Insertion de 2 maillons
                insertHeadList(&list, cell1);
                p_d_cell cell2 = createCell(7, 2);
                insertHeadList(&list, cell2);

                printf("Affichage d'une liste non vide alignée...\n");
                displayAlignedList(list); // Affichage de la liste non vide alignée
                printf("Liste non vide alignée affiché !\n\n");

                break;
            }

            case 7: {  // insertList()

                t_d_list list = createList(5); // Création d'une liste à 5 niveaux
                p_d_cell cell1 = createCell(9, 3); // Insertion de 2 maillons
                insertHeadList(&list, cell1);
                p_d_cell cell2 = createCell(7, 2);
                insertHeadList(&list, cell2);

                printf("Insertion en fin de liste...\n");
                insertList(&list, 11, 5); // Insertion en fin de liste
                displayAlignedList(list);
                printf("Fait !\n\n");

                printf("Insertion en milieu de liste...\n");
                insertList(&list, -8, 4); // Insertion en milieu de liste
                displayAlignedList(list);
                printf("Fait !\n\n");
                
                printf("Insertion au début de la liste...\n");
                insertList(&list, 5, 1); // Insertion en début de liste
                displayAlignedList(list);
                printf("Fait !\n\n");

                break;
            }

            case 8: {  // researchClassic() & researchAdvanced()

                printf("Création d'une liste...\n");
                t_d_list list = createList(4); // Création d'une liste
                insertList(&list, 83, 1);
                insertList(&list, 1, 4);
                insertList(&list, 35, 3);
                insertList(&list, 17, 2);
                insertList(&list, 4, 1);
                insertList(&list, 9, 4);
                insertList(&list, 21, 3);
                insertList(&list, 100, 2);
                displayAlignedList(list);

                printf("Résultats : \n"); // Affichage des résulats
                printf("researchClassic() avec correspondance : %p\n", researchClassic(list, 17));
                printf("researchClassic() sans correspondance : %p\n", researchClassic(list, 20));
                printf("researchAdvanced() avec correspondance: %p\n", researchAdvanced(list, 17));
                printf("researchAdvanced() sans correspondance : %p\n", researchClassic(list, 20));
                printf("\n");
                
                break;
            }

            case 9: {
                graphics();
                printf("\n");
            }

            case 0: {  // Fin du programme
                break;
            }

            default: {  // Erreur dans l'entrée
                printf("Choix invalide :/\n\n");
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
