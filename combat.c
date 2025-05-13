#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "combat.h"
#include "interface.h"


// Fonction pour charger les combattants depuis un fichier texte 
int charger_combattants(const char *nomFichier, Combattant liste[]) {
    FILE *f = fopen(nomFichier, "r");  // Ouvre le fichier en mode lecture

    // Si le fichier ne peut pas être ouvert, afficher une erreur
    if (!f) {                        
        perror("Erreur ouverture fichier"); 
        return 0;                      
    }

    char ligne[1000];  // Pour lire une ligne entière
    int nb_combattants = 0;  // Nombre de combattants chargés

    // Lire les lignes tant qu'on n'a pas atteint la fin du fichier et tant que le nombre de combattants ne dépasse pas la limite MAX_COMBATTANTS
    while (fgets(ligne, sizeof(ligne), f) && nb_combattants < MAX_COMBATTANTS) {

    Combattant *c = &liste[nb_combattants];  /// Récupère un pointeur vers le prochain combattant à remplir

        // Lire et extraire les données formatées depuis la ligne
        sscanf(ligne, "%[^;];%d;%d;%d;%d;%d;%[^;];%d;%[^;];%d;%d", 
            c->nom, &c->pv_max, &c->attaque, &c->defense,
            &c->agilite, &c->vitesse,
            c->technique.nom, &c->technique.valeur, c->technique.description,
            &c->technique.tours_actifs, &c->technique.tours_rechargement);     

        c->pv_courants = c->pv_max;  // Initialise les PV courants au maximum
        nb_combattants++;                        // Passe au combattant suivant

    }

    fclose(f);   // Fermer le fichier
    return nb_combattants;   // Retourne le nombre de combattants chargés

}


// Vérifie si tous les combattants d’une équipe sont K.O.
int equipe_KO(Equipe *e) {
    for (int i = 0; i < NB_COMBATTANTS; i++) {
        if (e->combattant[i].pv_courants > 0) {
            return 0; // L'équipe n'est pas KO
        }
    }
    return 1; // L'équipe est KO
}


// Gestion des tours de recharge
// On ignore t->tours_actifs ici car les effets sont permanents
void gerer_effets_tour(Combattant *c) {
    
    // Si la technique spéciale est encore en rechargement
    if (c->technique.tours_rechargement > 0) { 
        c->technique.tours_rechargement--; // On diminue le nombre de tours restants avant de pouvoir la réutiliser

        // Si la technique est rechargée
        if (c->technique.tours_rechargement == 0) {
            printf(BOLD_GREEN"\nLa technique spéciale %s de %s est prête à être utilisée ! 🧪\n\n"RESET, c->technique.nom, c->nom); // On informe le joueur que la technique spéciale est disponible
        }
    }
}


// Attaquer
void attaquer(Combattant *attaquant, Combattant *defenseur) {
    if (attaquant->pv_courants <= 0) {
        printf(RED"%s est déjà KO ☠️ ! Vous ne pouvez pas attaquer. \n"RESET, attaquant->nom);
        return;
    }

    // Calcul des dégâts
    int degats = attaquant->attaque - defenseur->defense;
    if (degats <= 0) degats = 1; // Inflige toujours au moins 1 dégât

    // On réduit les PV courants du défenseur
    defenseur->pv_courants -= degats;

     // Si les PV deviennent négatifs, on les ramène à 0
    if (defenseur->pv_courants < 0) {
        defenseur->pv_courants = 0;
    }

    printf(BOLD_CYAN"\n\n%s attaque %s pour %d dégâts ! %s a maintenant %d PV ! 🌪️\n\n"RESET, attaquant->nom, defenseur->nom, degats, defenseur->nom, defenseur->pv_courants);
}


// Utiliser la technique spéciale
void utiliser_technique(Combattant *utilisateur, Combattant *cible) {

    // Récupère un pointeur vers la technique spéciale du combattant utilisateur
    Technique *t = &utilisateur->technique;

    // Si la technique est encore en rechargement, on affiche un message et on quitte la fonction
    if (t->tours_rechargement > 0) {
        printf(BOLD_GREEN"\n\nLa technique spéciale %s est encore en recharge. ⏳\n"RESET, t->nom);
        printf(BOLD_GREEN"Il vous reste %d tour(s) avant de pouvoir l’utiliser. ⏱️\n\n"RESET, t->tours_rechargement);
        return;
    }

    // Affiche que la technique est utilisée
    printf(BOLD_WHITE"\n\n%s utilise %s ! 🌟\n\n"RESET, utilisateur->nom, t->nom);

    // Cas : la technique est "Soin"
    if (strcmp(t->nom, "Soin") == 0) {
        int pv_avant = utilisateur->pv_courants; // Sauvegarde des PV avant le soin
        utilisateur->pv_courants += t->valeur; // Ajout des PV selon la valeur de la technique
        if (utilisateur->pv_courants > utilisateur->pv_max)
            utilisateur->pv_courants = utilisateur->pv_max; // Ne pas dépasser les PV max
        printf(BOLD_CYAN"%s récupère %d PV ! %s a maintenant %d PV ! 💎\n"RESET,
            utilisateur->nom, utilisateur->pv_courants - pv_avant, utilisateur->nom, utilisateur->pv_courants);

    } else if (strcmp(t->nom, "Frappe") == 0 || strcmp(t->nom, "Esquive") == 0) {
        cible->pv_courants -= t->valeur;
        if (cible->pv_courants < 0) cible->pv_courants = 0;
        printf(BOLD_CYAN"%s inflige %d dégâts à %s! %s a maintenant %d PV ! 🎯\n"RESET,
            utilisateur->nom, t->valeur, cible->nom, cible->nom, cible->pv_courants);

    } else if (strcmp(t->nom, "Bouclier") == 0) {
        int pv_avant = utilisateur->pv_courants;
        utilisateur->pv_courants += t->valeur;
        if (utilisateur->pv_courants > utilisateur->pv_max)
            utilisateur->pv_courants = utilisateur->pv_max;
        printf(BOLD_CYAN"%s récupère %d PV ! %s a maintenant %d PV ! 🛡️\n"RESET,
            utilisateur->nom, utilisateur->pv_courants - pv_avant, utilisateur->nom, utilisateur->pv_courants);

    } else if (strcmp(t->nom, "Sortilège") == 0) {
        utilisateur->pv_courants *= 2;
        if (utilisateur->pv_courants > utilisateur->pv_max)
            utilisateur->pv_courants = utilisateur->pv_max;
        printf(BOLD_CYAN"%s double ses PV ! %s a maintenant %d PV ! 🔮\n"RESET,
            utilisateur->nom, utilisateur->nom, utilisateur->pv_courants);

    } else if (strcmp(t->nom, "Rapidité") == 0) {
        cible->pv_courants /= 2;
        if (cible->pv_courants < 0) cible->pv_courants = 0;
        printf(BOLD_CYAN"%s divise les PV de %s ! %s a maintenant %d PV ! 🌩️\n"RESET,
            utilisateur->nom, cible->nom, cible->nom, cible->pv_courants);
    }

    t->tours_rechargement = t->tours_actifs;
}




// Tour du joueur avec sélection d’action et de cible
void tour_joueur(Equipe *active, Equipe *adverse, int index) {
    if (index >= NB_COMBATTANTS) return;

    Combattant *c = &active->combattant[index];
    if (c->pv_courants <= 0 || equipe_KO(adverse)) return;

    printf(BOLD_MAGENTA"\n\n\n\n\n--- 🕹️  À VOUS DE JOUER, ÉQUIPE %s ! 🕹️  ---\n\n\n"RESET, active->nom);

    // Affiche les cibles valides (vivantes)
    printf(BOLD_YELLOW"Cibles disponibles 📝 :\n\n"RESET);
    int cibles_valides = 0;
    for (int j = 0; j < NB_COMBATTANTS; j++) {
        if (adverse->combattant[j].pv_courants > 0) {
            printf("%d. %s (%d PV) \n", j + 1, adverse->combattant[j].nom, adverse->combattant[j].pv_courants);
            cibles_valides++;
        } else {
            printf("%d. %s (KO) ☠️\n", j + 1, adverse->combattant[j].nom);
        }
    }

    if (cibles_valides == 0) return;

    // Choix de la cible
    int cible_index, cible_valide = 0;
    while (!cible_valide) {
        printf(BOLD_YELLOW"\n\nChoisissez une cible 🏹 :\n\n> "RESET);
        if (scanf("%d", &cible_index) != 1) {
            while (getchar() != '\n');
            printf(RED"❌ Choix invalide.\n"RESET);
            continue;
        }
        cible_index--;
        if (cible_index >= 0 && cible_index < NB_COMBATTANTS &&
            adverse->combattant[cible_index].pv_courants > 0) {
            cible_valide = 1;
        } else {
            printf(RED"❌ Cible invalide ou déjà KO.\n"RESET);
        }
    }

    // Choix de l'action (attaque ou technique spécial)
    int choix = 0;
    while (choix != 1 && choix != 2) {
        printf(BOLD_BLUE"\n\n\n%s veut agir :\n\n"RESET, c->nom);
        printf("1. Attaquer 👊\n2. Utiliser la technique spéciale 💫\n");
        printf(BOLD_BLUE"\n> "RESET);
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n');
            printf(RED"❌ Choix invalide.\n"RESET);
            choix = 0;
            continue;
        }

        if (choix == 2 && c->technique.tours_rechargement > 0) {
            printf(RED"❌ Technique en recharge. Utilisez l'attaque normale.\n"RESET);
            choix = 0;
        }
    }

    if (choix == 1) {
        attaquer(c, &adverse->combattant[cible_index]);
    } else {
        utiliser_technique(c, &adverse->combattant[cible_index]);
    }

    if (!equipe_KO(active) && !equipe_KO(adverse)) {
        gerer_effets_tour(c);
    }
}

    



// Fonction pour lancer le combat
void lancer_combat(Equipe *e1, Equipe *e2) {
    
    printf(YELLOW "\n\n\n\n\n                  ═══════════════════════════════════════════════\n"RESET);
    printf(BOLD_WHITE"                             ⚔️  LE COMBAT COMMENCE ! ⚔️         "RESET);
    printf(YELLOW "\n                  ═══════════════════════════════════════════════\n"RESET);
    printf("\n\n");

    

    srand(time(NULL));  // Initialise le générateur aléatoire

    int vmax1 = 0, vmax2 = 0;

    // Calcule la vitesse max des deux équipes
    for (int i = 0; i < NB_COMBATTANTS; i++)
        if (e1->combattant[i].vitesse > vmax1) vmax1 = e1->combattant[i].vitesse;
    for (int i = 0; i < NB_COMBATTANTS; i++)
        if (e2->combattant[i].vitesse > vmax2) vmax2 = e2->combattant[i].vitesse;

        int equipe_commence;

        if (vmax1 > vmax2) {
            equipe_commence = 1;
            printf(YELLOW "\n%s possède le combattant le plus rapide et débutera ce combat ! 👀\n" RESET, e1->nom);
            printf("\n\n");
        } else if (vmax2 > vmax1) {
            equipe_commence = 2;
            printf(BOLD_YELLOW "\n%s possède le combattant le plus rapide et débutera ce combat ! 👀\n" RESET, e2->nom);
            printf("\n\n");
        } else {
            equipe_commence = (rand() % 2) + 1;
            printf(BOLD_YELLOW "Les deux équipes ont un combattant aussi rapide ! 🥷\n" RESET);
            printf("\n");
            printf(BOLD_YELLOW "Tirage au sort...🥁 %s COMMENCERA CE COMBAT ! 🚀\n" RESET, equipe_commence == 1 ? e1->nom : e2->nom);
           
        }

        for (int tour = 1; tour < 999; tour++) {
            if (equipe_KO(e1)) {
                printf(BOLD_GREEN"\nVICTOIRE DE %s ! 🏆\n"RESET, e2->nom);
                return;
            }
            if (equipe_KO(e2)) {
                printf(BOLD_GREEN"\nVICTOIRE DE %s ! 🏆\n"RESET, e1->nom);
                return;
            }


        printf(MAGENTA "\n\n\n\n\n                  ═══════════════════════════════════════════════\n"RESET);
        printf(BOLD_WHITE"                             🚨 TOUR %d : PRÉPAREZ VOUS ! 🚨         "RESET, tour);
        printf(MAGENTA "\n                  ═══════════════════════════════════════════════\n"RESET);

        for (int i = 0; i < 3; i++) {
            Equipe *active = (equipe_commence == 1) ? e1 : e2;
            Equipe *adverse = (equipe_commence == 1) ? e2 : e1;

            if (!equipe_KO(active)) tour_joueur(active, adverse, i);
            if (equipe_KO(adverse)) {
                printf(BOLD_GREEN"\nVICTOIRE DE %s ! 🏆\n"RESET, active->nom);
                return;
            }

            // Tour du second joueur
            active = (equipe_commence == 1) ? e2 : e1;
            adverse = (equipe_commence == 1) ? e1 : e2;

            if (!equipe_KO(active)) tour_joueur(active, adverse, i);
            if (equipe_KO(adverse)) {
                printf(BOLD_GREEN"\nVICTOIRE DE %s ! 🏆\n"RESET, active->nom);
                return;
            }
        }
    }
}
