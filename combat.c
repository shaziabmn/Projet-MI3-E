#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combat.h"
#include "interface.h"

// Fonction pour charger les combattants depuis un fichier texte
int charger_combattants(const char *nomFichier, Combattant liste[], int max) {
    FILE *f = fopen(nomFichier, "r");  // Ouvre le fichier en mode lecture

     // Si le fichier ne peut pas être ouvert, afficher une erreur
    if (!f) {                        
        perror("Erreur ouverture fichier"); 
        return 0;                      
    }

    char ligne[1000];  // Pour lire chaque ligne du fichier
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




// Fonction pour vérifier si un combattant est KO
int est_ko(const Combattant *c){
    printf("%s est KO ☠️ !", c->nom);
    return c->pv_courants <= 0;  // Retourne 1 si KO, 0 sinon
}


// Initialisation des statistiques de base (avant effets)
void initialiser_stats_base(Combattant *c) {
    c->base_attaque = c->attaque;
    c->base_defense = c->defense;
    c->base_agilite = c->agilite;
    c->base_vitesse = c->vitesse;
    c->tours_effet = 0;
}

// Attaque classique avec aléatoire
void attaquer(Combattant *attaquant, Combattant *cible) {
    int degats = attaquant->attaque - (cible->defense / 2);
    if (degats < 0) degats = 0;

    float facteur = 0.8f + (rand() % 41) / 100.0f; // 0.8 à 1.2
    degats = (int)(degats * facteur);

    cible->pv_courants -= degats;
    if (cible->pv_courants < 0) cible->pv_courants = 0;

    printf("%s attaque %s et inflige %d dégâts !\n", attaquant->nom, cible->nom, degats);
}

// Utilisation d'une technique spéciale
void utiliser_technique(Combattant *utilisateur, Combattant *cible) {
    Technique *t = &utilisateur->special;

    if (t->tours_rechargement > 0) {
        printf("Technique en recharge : %d tour(s) restant(s).\n", t->tours_rechargement);
        return;
    }

    printf("%s utilise %s !\n", utilisateur->nom, t->nom);

    if (strcmp(t->nom, "Soin") == 0) {
        utilisateur->pv_courants += t->valeur;
        if (utilisateur->pv_courants > utilisateur->pv_max)
            utilisateur->pv_courants = utilisateur->pv_max;
        printf("%s récupère %d PV !\n", utilisateur->nom, t->valeur);
    } else if (strcmp(t->nom, "Frappe") == 0) {
        cible->pv_courants -= t->valeur;
        if (cible->pv_courants < 0) cible->pv_courants = 0;
        printf("%s inflige %d dégâts bonus à %s !\n", utilisateur->nom, t->valeur, cible->nom);
    } else {
        utilisateur->tours_effet = t->tours_actifs;

        if (strcmp(t->nom, "Bouclier") == 0) {
            utilisateur->defense += t->valeur;
            printf("%s augmente sa défense de %d pour %d tour(s).\n", utilisateur->nom, t->valeur, t->tours_actifs);
        } else if (strcmp(t->nom, "Esquive") == 0) {
            utilisateur->agilite += t->valeur;
            printf("%s augmente son agilité de %d pour %d tour(s).\n", utilisateur->nom, t->valeur, t->tours_actifs);
        } else if (strcmp(t->nom, "Sortilège") == 0) {
            utilisateur->attaque *= 2;
            printf("%s double son attaque pour %d tour(s).\n", utilisateur->nom, t->tours_actifs);
        } else if (strcmp(t->nom, "Rapidité") == 0) {
            utilisateur->vitesse += t->valeur;
            printf("%s augmente sa vitesse de %d pour %d tour(s).\n", utilisateur->nom, t->valeur, t->tours_actifs);
        }
    }

    t->tours_rechargement = 3; // exemple de recharge fixe
}

// Appliquer les effets temporaires à la fin d’un tour
void gerer_effets_tour(Combattant *c) {
    if (c->tours_effet > 0) {
        c->tours_effet--;
        if (c->tours_effet == 0) {
            c->attaque = c->base_attaque;
            c->defense = c->base_defense;
            c->agilite = c->base_agilite;
            c->vitesse = c->base_vitesse;
            printf("%s revient à ses statistiques de base.\n", c->nom);
        }
    }

    if (c->special.tours_rechargement > 0)
        c->special.tours_rechargement--;
}

// Tour du joueur avec sélection d’action et de cible
void tour_joueur(Joueur *joueur, Joueur *adverse) {
    printf("\n== Tour de %s ==\n", joueur->nom);
    for (int i = 0; i < joueur->nb_combattants; i++) {
        Combattant *c = &joueur->equipe[i];
        if (c->pv_courants <= 0) continue;

        printf("\n[%s] Veut agir :\n1. Attaquer\n2. Utiliser technique spéciale\n> ", c->nom);
        int choix;
        scanf("%d", &choix);

        printf("Choisissez une cible :\n");
        for (int j = 0; j < adverse->nb_combattants; j++) {
            if (adverse->equipe[j].pv_courants > 0)
                printf("%d. %s (%d PV)\n", j + 1, adverse->equipe[j].nom, adverse->equipe[j].pv_courants);
        }

        int cible_index;
        scanf("%d", &cible_index);
        cible_index--;

        if (cible_index < 0 || cible_index >= adverse->nb_combattants || adverse->equipe[cible_index].pv_courants <= 0) {
            printf("Cible invalide. Action perdue.\n");
            continue;
        }

        if (choix == 1) attaquer(c, &adverse->equipe[cible_index]);
        else if (choix == 2) utiliser_technique(c, &adverse->equipe[cible_index]);

        gerer_effets_tour(c);
    }
}

// Fonction pour savoir si toute l’équipe est KO
int equipe_KO(Joueur *j) {
    for (int i = 0; i < j->nb_combattants; i++) {
        if (j->equipe[i].pv_courants > 0)
            return 0;
    }
    return 1;
}

// Fonction principale du combat
void lancer_combat(Joueur *j1, Joueur *j2) {
    printf("\n");
    printf(BOLD_YELLOW "\n            === ⚔️  LE COMBAT COMMENCE ! ⚔️  ===\n" RESET);
    printf("\n\n");

    while (1) {
        tour_joueur(j1, j2);
        if (equipe_KO(j2)) {
            printf("\nVictoire de %s !\n", j1->nom);
            break;
        }

        tour_joueur(j2, j1);
        if (equipe_KO(j1)) {
            printf("\nVictoire de %s !\n", j2->nom);
            break;
        }
    }
}


