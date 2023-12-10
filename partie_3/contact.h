/*----------------------------------//

            PROJET_C_3
             Partie 3
            contact.h

//----------------------------------*/

#ifndef PROJET_C_S3_CONTACT_H
#define PROJET_C_S3_CONTACT_H

//----------------------------------//
// Fichiers internes


//----------------------------------//
// Corps du fichier

// Structure d'un contact
typedef struct s_contact {
    char * fullName;
} t_contact, * p_contact;

/**
 * @brief Crée le nom d'un contact en demandant le nom et le prénom
 * @return Le nom complet formaté du contact
 */
char * createNameContact();

/**
 * @brief Crée un contact
 * @param fullName Nom et prénom formatés du contact
 * @return Un contact 
 */
p_contact createContact(char *);

/**
 * @brief Supprime un contact
 * @param contact Contact à supprimer
 */
void deleteContact(p_contact);

/**
 * @brief Affiche un contact
 * @param contact Contact à afficher
 */
void displayContact(t_contact);

/**
 * @brief Calcule le nombre de lettres identiques 
 * entre deux noms
 * @param firstName Premier nom
 * @param secondName Second nom
 * @return Nombre de lettres de différence entre deux noms, 
 * maximum 3 lettres
 */
int sameLetterNumber(char *, char *);

#endif //PROJET_C_S3_CONTACT_H
