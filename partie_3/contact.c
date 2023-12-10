/*----------------------------------//

            PROJET_C_3
             Partie 3
            contact.c

//----------------------------------*/

//----------------------------------//
// Librairies externes

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//----------------------------------//
// Fichiers internes

#include "contact.h"
#include "meeting.h"

//----------------------------------//
// Corps du fichier

char * createNameContact() {

    /*
    Crée le nom d'un contact en demandant le nom et le prénom
    */

    // Entrée du nom du contact
    int test1 = 1;
    char* lastname = NULL;
    do {
        if (lastname != NULL) free(lastname);
        lastname = (char *) malloc(32 * sizeof(char));
        test1 = 1;
        printf ("Entrez votre nom (ne pas utiliser de caracteres speciaux ou avec accent) : ");
        char* ch1 = scanString();
        int i = 0;

        // Vérifie si le nom est dans le format demandé
        while (ch1[i] != '\0')
        {
            lastname[i] = tolower(ch1[i]);
            if ((lastname[i] < 'a' || lastname[i] > 'z') && lastname[i] != ' ' && lastname[i] != '-' && lastname[i] != '\'')
                test1 = 0;
            i++;
        }
        lastname[i] = '\0';
        lastname = strcat(lastname, "_");
    } while (test1 == 0);

    // Entrée du prénom du contact
    char* firstname = NULL;
    int test2 = 1;
    do
    {
        if (firstname != NULL) free(firstname);
        firstname = (char *) malloc(32 * sizeof(char));
        test2 = 1;
        printf ("Entrez votre prenom (ne pas utiliser de caracteres speciaux ou avec accent) : ");
        char* ch2 = scanString();
        int j = 0;

        // Vérifie si le prénom est dans le format demandé
        while (ch2[j] != '\0')
        {
            firstname[j] = tolower(ch2[j]);
            if ((firstname[j] < 'a' || firstname[j] > 'z') && firstname[j] != ' ' && firstname[j] != '-' && firstname[j] != '\'')
                test2 = 0;
            j++;
        }
        firstname[j] = '\0';
    } while (test2 == 0);

    // Concaténation du nom et du prénom pour le sauvegarder dans un contact
    char* fullName = strcat(lastname, firstname);
    return fullName;
}

p_contact createContact(char * fullName) {

    /*
    Crée un contact
    */

    p_contact person = (p_contact) malloc(sizeof(t_contact));
    person->fullName = (char *) malloc((strlen(fullName) + 1) * sizeof(char));
    strncpy(person->fullName, fullName, strlen(fullName) + 1);

    return person;
}

void deleteContact(p_contact contact) {

    /*
    Supprime un contact
    */

    free(contact);
    contact = NULL;

    return;
}

void displayContact(t_contact contact) {

    /*
    Affiche un contact
    */

    printf ("Contact : %s\n", contact.fullName);

    return;
}

int sameLetterNumber(char * firstName, char * secondName) {

    /*
    Calcule le nombre de lettres identiques entre deux noms
    */

    int cpt = 0;
    int i = 0;
    while (firstName[i] == secondName[i] && cpt < 3) {
        cpt++;
        i++;
    }

    return cpt;
}
