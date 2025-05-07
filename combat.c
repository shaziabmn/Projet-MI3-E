//PARTIE SHAZIA 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combat.h"

// Fonction pour charger les combattants depuis un fichier texte
int charger_combattants(const char *nomFichier, Combattant liste[], int max) {
    FILE *f = fopen(nomFichier, "r");  // Ouvre le fichier en mode lecture

     // Si le fichier ne peut pas être ouvert, afficher une erreur
    if (!f) {                        
        perror("Erreur ouverture fichier"); 
        return 0;                      
    }

    char ligne[256];  // Pour lire chaque ligne du fichier
    int nb = 0;       // Compteur de combattants lus

    // Lire les lignes tant qu'on n'a pas atteint la fin
    while (fgets(ligne, sizeof(ligne), f) && nb < max) {

        Combattant *c = &liste[nb];  /// Récupère un pointeur vers le prochain combattant à remplir

        // Lire et extraire les données formatées depuis la ligne
        sscanf(ligne, " %[^;] ; %d ; %d ; %d ; %d ; %d ; %[^;] ; %d ; %[^;] ; %d ; %d",
            c->nom, &c->pv_max, &c->attaque, &c->defense,
            &c->agilite, &c->vitesse,
            c->special.nom, &c->special.valeur, c->special.description,
            &c->special.tours_actifs, &c->special.tours_rechargement);     

        c->pv_courants = c->pv_max;  // Initialiser les PV courants au maximum
        nb++;                        // Passer au prochain combattant

        }
    fclose(f);   // Fermer le fichier
    return nb;   
}


// Fonction pour afficher les caractéristiques d’un combattant
void afficher_combattant(const Combattant *c){
    // Affiche les informations générales
    printf("Nom : %s\n", c->nom);
    printf("PV : %d/%d\n", c->pv_courants, c->pv_max);
    printf("Attaque : %d | Défense : %d | Agilité : %d | Vitesse : %d\n",
           c->attaque, c->defense, c->agilite, c->vitesse);

    // Affiche les détails de la technique spéciale
    printf("Technique spéciale : %s (%s)\n", c->special.nom, c->special.description);
    printf("Valeur : %d | Actif : %d tours | Rechargement : %d tours\n",
           c->special.valeur, c->special.tours_actifs, c->special.tours_rechargement);

    printf("-----------------------------\n");  // Ligne de séparation pour plus de clarté
    }


// Fonction pour vérifier si un combattant est KO
int est_ko(const Combattant *c){
    return c->pv_courants <= 0;  // Retourne 1 si KO, 0 sinon
}








// PARTIE HIBA 

#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include <string.h>
#include <time.h>

// Fonction pour calculer et infliger des dégâts
void attaquer(Combattant *attaquant, Combattant *cible) {
    int degats = attaquant->attaque - cible->defense;
    if (degats < 0) degats = 0;

    cible->pv_courants -= degats;
    if (cible->pv_courants < 0) cible->pv_courants = 0;

    printf("%s attaque %s et inflige %d dégâts !\n", attaquant->nom, cible->nom, degats);
}

// Fonction pour utiliser une technique spéciale
void utiliser_technique(Combattant *c, Combattant *adversaire) {
    if (c->special.tours_rechargement > 0) {
        printf("%s utilise %s !\n", c->nom, c->special.nom);
        const char *nom = c->special.nom;

        if (strcmp(nom, "Soin") == 0) {
            c->pv_courants += c->special.valeur;
            if (c->pv_courants > c->pv_max)
                c->pv_courants = c->pv_max;
            printf("%s récupère %d PV !\n", c->nom, c->special.valeur);

        } else if (strcmp(nom, "Frappe") == 0) {
            adversaire->pv_courants -= c->special.valeur;
            if (adversaire->pv_courants < 0)
                adversaire->pv_courants = 0;
            printf("%s inflige %d dégâts supplémentaires !\n", c->nom, c->special.valeur);

        } else if (strcmp(nom, "Bouclier") == 0) {
            c->defense += c->special.valeur;
            printf("%s augmente sa défense de %d pendant %d tours.\n", c->nom, c->special.valeur, c->special.tours_actifs);

        } else if (strcmp(nom, "Esquive") == 0) {
            c->agilite += c->special.valeur;
            printf("%s augmente son agilité de %d pendant %d tour(s).\n", c->nom, c->special.valeur, c->special.tours_actifs);

        } else if (strcmp(nom, "Sortilège") == 0) {
            c->attaque *= 2;
            printf("%s double son attaque pendant %d tours !\n", c->nom, c->special.tours_actifs);

        } else if (strcmp(nom, "Rapidité") == 0) {
            c->vitesse += c->special.valeur;
            printf("%s augmente sa vitesse de %d pendant %d tour(s).\n", c->nom, c->special.valeur, c->special.tours_actifs);

        } else {
            printf("Technique inconnue.\n");
        }

        c->special.tours_rechargement = 0; // On empêche la réutilisation immédiate
    } else {
        printf("La technique de %s n'est pas encore rechargée.\n", c->nom);
    }
}

// Fonction pour gérer un tour de combat complet
void lancer_combat(Combattant *j1, Combattant *j2) {
    int tour = 1;

    while (!est_ko(j1) && !est_ko(j2)) {
        printf("\n===== Tour %d =====\n", tour);
        printf("État des combattants :\n");
        afficher_combattant(j1);
        afficher_combattant(j2);

        if (j1->vitesse >= j2->vitesse) {
            attaquer(j1, j2);
            if (!est_ko(j2)) attaquer(j2, j1);
        } else {
            attaquer(j2, j1);
            if (!est_ko(j1)) attaquer(j1, j2);
        }

        // Recharge les techniques
        if (j1->special.tours_rechargement < 3) j1->special.tours_rechargement++;
        if (j2->special.tours_rechargement < 3) j2->special.tours_rechargement++;

        tour++;
    }

    printf("\n=== Fin du combat ===\n");
    if (est_ko(j1))
        printf("%s est KO ! Victoire de %s !\n", j1->nom, j2->nom);
    else
        printf("%s est KO ! Victoire de %s !\n", j2->nom, j1->nom);
}
