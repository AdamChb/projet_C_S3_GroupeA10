/*----------------------------------//

            PROJET_C_3
             Partie 2
            research.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//----------------------------------//
// Fichiers internes

#include "research.h"
#include "timer.h"

//----------------------------------//
// Corps du fichier

p_d_cell researchClassic(t_d_list list, int val){
    
    /*
    Recherche dans une liste une valeur à partir
    de la première ligne uniquement
    */

    p_d_cell temp = list.heads[0];
    while (temp != NULL) {
        if (temp->value == val) {
            return temp;
        }
        temp = temp->nexts[0];
    }
    return NULL;
}


p_d_cell researchAdvanced(t_d_list list, int val){
    
    /*
    Recherche dans une liste list une valeur val à partir 
    du plus haut niveau et descendant de niveau
    */

    p_d_cell temp = NULL;
    int i = 1;
    while (temp == NULL && i < list.nbLevel) {  // Débute au nivea&u le plus haut possible
        temp = list.heads[list.nbLevel - i];
        i++;
    }
    if (temp == NULL) return NULL;
    p_d_cell prec = temp;
    while (temp != NULL && i <= list.nbLevel) {
        if (temp->value == val) {  // La valeur cherchée est trouvée
            return temp;
        } else if (temp->value < val) {  // On avance dans le niveau actuel
            i++;
            temp = prec->nexts[list.nbLevel - i];
        } else if (temp->value > val && temp->nexts[list.nbLevel - i] == NULL){  // On passe au niveau suivant
            i++;
        } else if (temp->value > val) {
            prec = temp;
            temp = temp->nexts[list.nbLevel - i];
        }
    }
    return NULL;
}

void graphics(){
    /*
    Affiche des graphiques de comparaison calculant le temps mis pour faire
    des recherches avancées et classiques pour 1000, 10 000 et 100 000
    valeurs au hasard
    Il faudra avant tout créer un liste classées dans l'ordre croissant
    Ne retourne rien
    */

    int n_max = 15;

    FILE *log_file = fopen("log.txt", "w");
    char format[] = "%d\t%s\t%s\n";
    int level;

    for (int i = 3; i < n_max; i++) {
        int nb_case = pow(2, i) - 1;
        int * tab = (int *) malloc(nb_case * sizeof(int));
        for (int j = 0; j < nb_case; j++) tab[j] = 0;
        for (int j = 1; j < i; j ++) {
            for (int k = -1; k < nb_case; k += pow(2, j)) tab[k] += 1;
        }
        t_d_list list = createList(i);

        for (int j = 0; j < nb_case; j++) {
            insertList(&list, j+1, tab[j]+1);
        }

        level = i;
        char *time_1v10;
        char *time_all_levels;

        startTimer();
        for (int j = 0; j < 10000; j++) {
            researchClassic(list, rand() % nb_case + 1);
        }
        stopTimer();
        time_1v10 = getTimeAsString();

        startTimer();
        for (int j = 0; j < 10000; j++) {
            researchAdvanced(list, rand() % nb_case + 1);
        }
        stopTimer();
        time_all_levels = getTimeAsString();

        fprintf(log_file, format, level, time_1v10, time_all_levels);
        printf(format, level, time_1v10, time_all_levels);

    }

    fclose(log_file);

}