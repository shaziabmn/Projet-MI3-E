#include <stdio.h>              // Entrées/sorties standard
#include <stdlib.h>             // Fonctions utilitaires (malloc, rand, etc.)
#include <string.h>             // Manipulation de chaînes
#include <time.h>               // Pour initialiser le générateur aléatoire

#include "combat.h"             // Définitions liées au combat
#include "interface.h"          // Fonctions d'affichage

// Charge les combattants depuis un fichier texte
int charger_combattants(const char *nomFichier, Combattant liste[]) {
    FILE *f = fopen(nomFichier, "r");              // Ouvre le fichier en mode lecture
    if (!f) {                                      // Si erreur à l’ouverture
        perror("Erreur ouverture fichier");
        return 0;
    }

    char ligne[1000];                              // Buffer pour lire chaque ligne
    int nb_combattants = 0;                        // Compteur de combattants chargés

    // Lire et extraire les données formatées depuis la ligne (combattants.txt)
    while (fgets(ligne, sizeof(ligne), f) && nb_combattants < MAX_COMBATTANTS) {
        Combattant *c = &liste[nb_combattants];    // Récupère un pointeur vers le prochain combattant à remplir

        // Extraction des données du fichier texte
        sscanf(ligne, "%[^;];%d;%d;%d;%d;%d;%[^;];%d;%[^;];%d;%d",
            c->nom, &c->pv_max, &c->attaque, &c->defense,
            &c->agilite, &c->vitesse,
            c->technique.nom, &c->technique.valeur, c->technique.description,
            &c->technique.tours_actifs, &c->technique.tours_rechargement);

        c->pv_courants = c->pv_max;                // Initialise les PV courants au maximum
        nb_combattants++;                          // Passe au combattant suivant
    }

    fclose(f);                                     // Ferme le fichier
    return nb_combattants;                         // Retourne le nombre total de combattants chargés
}

// Vérifie si tous les combattants d'une équipe sont KO
int equipe_KO(Equipe *e) {
    for (int i = 0; i < NB_COMBATTANTS; i++) {
        if (e->combattant[i].pv_courants > 0) {
            return 0;                              // Au moins un vivant
        }
    }
    return 1;                                      // Tous KO
}

// Gère la recharge de la technique spéciale (si applicable)
void gerer_effets_tour(Combattant *c) {
    if (c->technique.tours_rechargement > 0) {             // Si rechargement en cours
        c->technique.tours_rechargement--;                 // Diminue le nombre de tours restants avant utilisation
        if (c->technique.tours_rechargement == 0) {        // Si technique prête
            printf(BOLD_GREEN"\nLa technique spéciale %s de %s est prête à être utilisée ! 🧪\n\n"RESET,
                   c->technique.nom, c->nom);
        }
    }
}

// Effectue une attaque classique entre 2 combattants
void attaquer(Combattant *attaquant, Combattant *defenseur) {
    if (attaquant->pv_courants <= 0) {                     // Si attaquant KO
        printf(RED"%s est déjà KO ☠️ ! Vous ne pouvez pas attaquer. \n"RESET, attaquant->nom);
        return;
    }

    int degats = attaquant->attaque - defenseur->defense;  // Calcule les dégâts
    if (degats <= 0) degats = 1;                           // Minimum 1 dégât

    defenseur->pv_courants -= degats;                      // Applique les dégâts
    if (defenseur->pv_courants < 0)
        defenseur->pv_courants = 0;                        // Ne descend pas sous 0

    // Affiche le résultat
    printf(BOLD_CYAN"\n\n%s attaque %s pour %d dégâts ! %s a maintenant %d PV ! 🌪️\n\n"RESET,
           attaquant->nom, defenseur->nom, degats, defenseur->nom, defenseur->pv_courants);
}

// Utilise la technique spéciale du combattant
void utiliser_technique(Combattant *utilisateur, Combattant *cible) {
    Technique *t = &utilisateur->technique;                // Récupère un pointeur vers la technique spéciale du combattant utilisateur

    if (t->tours_rechargement > 0) {                       // Si rechargement en cours, message d'erreur et quitte la fonction
        printf(BOLD_GREEN"\n\nLa technique spéciale %s est encore en recharge. ⏳\n"RESET, t->nom);
        printf(BOLD_GREEN"Il vous reste %d tour(s) avant de pouvoir l’utiliser. ⏱️\n\n"RESET, t->tours_rechargement);
        return;
    }
    
    // Affiche que la technique est utilisée
    printf(BOLD_WHITE"\n\n%s utilise %s ! 🌟\n\n"RESET, utilisateur->nom, t->nom); 

    // Différents effets selon le nom de la technique
// Cas : la technique est "Soin"
if (strcmp(t->nom, "Soin") == 0) {
    int pv_avant = utilisateur->pv_courants; // On sauvegarde les PV actuels du combattant pour calculer combien il récupère
    utilisateur->pv_courants += t->valeur;   // On ajoute à ses PV la valeur de soin indiquée dans la technique

    if (utilisateur->pv_courants > utilisateur->pv_max) // Si après soin, les PV dépassent le max autorisé
        utilisateur->pv_courants = utilisateur->pv_max; // On limite les PV au maximum (on ne peut pas dépasser)

    // On affiche un message montrant combien de PV ont été soignés et le total de PV actuels
    printf(BOLD_CYAN"%s récupère %d PV ! %s a maintenant %d PV ! 💎\n"RESET,
           utilisateur->nom, utilisateur->pv_courants - pv_avant, utilisateur->nom, utilisateur->pv_courants);

} 
// Cas : technique offensive simple ("Frappe" ou "Esquive")
else if (strcmp(t->nom, "Frappe") == 0 || strcmp(t->nom, "Esquive") == 0) {
    cible->pv_courants -= t->valeur; // On retire à la cible les PV correspondant à la puissance de la technique
    if (cible->pv_courants < 0) cible->pv_courants = 0; // On empêche les PV de devenir négatifs

    // On affiche un message de dégâts infligés à l’adversaire
    printf(BOLD_CYAN"%s inflige %d dégâts à %s ! %s a maintenant %d PV ! 🎯\n"RESET,
           utilisateur->nom, t->valeur, cible->nom, cible->nom, cible->pv_courants);

} 
// Cas : technique défensive ("Bouclier")
else if (strcmp(t->nom, "Bouclier") == 0) {
    int pv_avant = utilisateur->pv_courants; // On sauvegarde les PV avant d’ajouter la protection
    utilisateur->pv_courants += t->valeur;   // On ajoute les PV fournis par le bouclier

    if (utilisateur->pv_courants > utilisateur->pv_max) // Si les PV dépassent le maximum
        utilisateur->pv_courants = utilisateur->pv_max; // On les limite au maximum autorisé

    // On affiche un message indiquant la récupération de PV par le bouclier
    printf(BOLD_CYAN"%s récupère %d PV ! %s a maintenant %d PV ! 🛡️\n"RESET,
           utilisateur->nom, utilisateur->pv_courants - pv_avant, utilisateur->nom, utilisateur->pv_courants);

} 
// Cas : technique magique puissante ("Sortilège")
else if (strcmp(t->nom, "Sortilège") == 0) {
    utilisateur->pv_courants *= 2; // Double les PV actuels du combattant

    if (utilisateur->pv_courants > utilisateur->pv_max) // Mais sans dépasser les PV max
        utilisateur->pv_courants = utilisateur->pv_max;

    // Affiche que le sortilège a doublé les PV
    printf(BOLD_CYAN"%s double ses PV ! %s a maintenant %d PV ! 🔮\n"RESET,
        utilisateur->nom, utilisateur->nom, utilisateur->pv_courants);
} 

// Cas : attaque stratégique ("Rapidité")
else if (strcmp(t->nom, "Rapidité") == 0) {
    cible->pv_courants /= 2; // Réduit les PV de la cible de moitié

    if (cible->pv_courants < 0) cible->pv_courants = 0; // Par sécurité, on évite les PV négatifs

    // Message indiquant que les PV de l’ennemi sont divisés
    printf(BOLD_CYAN"%s divise les PV de %s ! %s a maintenant %d PV ! 🌩️\n"RESET,
           utilisateur->nom, cible->nom, cible->nom, cible->pv_courants);
}
}


// Fonction appelée quand c'est au tour d'un joueur (équipe active) de jouer
// Le joueur peut attaquer ou utiliser une technique spéciale sur l'équipe adverse
void tour_joueur(Equipe *active, Equipe *adverse, int index) {
    // Si l’index du combattant actif dépasse la taille de l’équipe, on sort immédiatement (sécurité)
    if (index >= NB_COMBATTANTS) return;

    // On récupère un pointeur vers le combattant actif de l’équipe
    Combattant *c = &active->combattant[index];

    // Si ce combattant est KO (0 PV ou moins) OU si tous les ennemis sont déjà KO, on ne fait rien
    if (c->pv_courants <= 0 || equipe_KO(adverse)) return;

    // Affichage du tour de l'équipe active avec un effet visuel
    printf(BOLD_MAGENTA"\n\n\n\n\n--- 🕹️  À VOUS DE JOUER, ÉQUIPE %s ! 🕹️  ---\n\n\n"RESET, active->nom);

    // Affiche toutes les cibles ennemies, avec leurs PV ou "KO" si elles sont éliminées
    printf(BOLD_YELLOW"Cibles disponibles 📝 :\n\n"RESET);
    int cibles_valides = 0; // Compte le nombre de cibles valides

    for (int j = 0; j < NB_COMBATTANTS; j++) {
        // Si le combattant adverse est encore vivant, on affiche ses PV
        if (adverse->combattant[j].pv_courants > 0) {
            printf("%d. %s (%d PV) \n", j + 1, adverse->combattant[j].nom, adverse->combattant[j].pv_courants);
            cibles_valides++; // On note qu’on a une cible possible
        } else {
            // Sinon, on indique que le combattant est KO
            printf("%d. %s (KO) ☠️\n", j + 1, adverse->combattant[j].nom);
        }
    }

    // Si aucune cible n'est disponible, on termine le tour
    if (cibles_valides == 0) return;

    // Boucle pour sélectionner une cible valide
    int cible_index, cible_valide = 0;
    while (!cible_valide) {
        printf(BOLD_YELLOW"\n\nChoisissez une cible 🏹 :\n\n> "RESET);

        // Lecture de l’entrée utilisateur
        if (scanf("%d", &cible_index) != 1) {
            // Si l'entrée n’est pas un nombre, on vide le buffer et affiche un message d’erreur
            while (getchar() != '\n');
            printf(RED"❌ Choix invalide.\n"RESET);
            continue;
        }

        cible_index--; // On ajuste car l'utilisateur entre 1, 2 ou 3 (mais on travaille en 0, 1, 2)

        // On vérifie que l’index est valide et que le combattant n’est pas KO
        if (cible_index >= 0 && cible_index < NB_COMBATTANTS &&
            adverse->combattant[cible_index].pv_courants > 0) {
            cible_valide = 1; // Cible valide : on sortira de la boucle
        } else {
            printf(RED"❌ Cible invalide ou déjà KO.\n"RESET);
        }
    }

    // Boucle pour sélectionner l’action à effectuer (1 = attaquer, 2 = technique)
    int choix = 0;
    while (choix != 1 && choix != 2) {
        // On affiche le menu d'action pour le joueur
        printf(BOLD_BLUE"\n\n\n%s veut agir :\n\n"RESET, c->nom);
        printf("1. Attaquer 👊\n2. Utiliser la technique spéciale 💫\n");
        printf(BOLD_BLUE"\n> "RESET);

        // Lecture du choix
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n'); // Vide le buffer si l'entrée est invalide
            printf(RED"❌ Choix invalide. Veuillez entrer '1' pour attaquer ou '2' pour utiliser la technique spécial.\n\n"RESET);
            choix = 0; // On réinitialise pour que la boucle recommence
            continue;
        } 
        else if (choix != 1 && choix != 2) {
            printf(RED"❌ Choix invalide. Veuillez entrer '1' pour attaquer ou '2' pour utiliser la technique spécial.\n\n"RESET);
        }

        // Si le joueur a choisi la technique, mais qu’elle est en recharge, on affiche un message d’erreur
        if (choix == 2 && c->technique.tours_rechargement > 0) {
            
            printf(BOLD_GREEN"\nLa technique spéciale %s est encore en recharge. ⏱️\n"RESET, c->technique.nom);
            printf(BOLD_GREEN"Il vous reste %d tour(s) avant de pouvoir l’utiliser. ⏳\n"RESET, c->technique.tours_rechargement);
            choix = 0; // On demande à l'utilisateur de choisir à nouveau
            
        }
    }

    // Une fois que l’action est validée :
    // Si choix = 1, on appelle la fonction d’attaque normale
    if (choix == 1)
        attaquer(c, &adverse->combattant[cible_index]);
    else
        // Sinon, on utilise la technique spéciale
        utiliser_technique(c, &adverse->combattant[cible_index]);

    // À la fin du tour, si aucune équipe n’est complètement KO,
    // on gère les effets qui doivent s’appliquer en fin de tour (ex: recharges, bonus temporaires, etc.)
    if (!equipe_KO(active) && !equipe_KO(adverse)) {
        gerer_effets_tour(c);
    }
}

// Lance le combat entre deux équipes
void lancer_combat(Equipe *e1, Equipe *e2) {
    // Message d’introduction
    printf(YELLOW "\n\n\n\n\n                  ═══════════════════════════════════════════════\n"RESET);
    printf(BOLD_WHITE"                             ⚔️  LE COMBAT COMMENCE ! ⚔️         "RESET);
    printf(YELLOW "\n                  ═══════════════════════════════════════════════\n"RESET);
    printf("\n\n");

    srand(time(NULL));                          // Initialise le générateur aléatoire

    int vmax1 = 0, vmax2 = 0;

    // Calcule vitesse max de chaque équipe
    for (int i = 0; i < NB_COMBATTANTS; i++)
        if (e1->combattant[i].vitesse > vmax1) vmax1 = e1->combattant[i].vitesse;
    for (int i = 0; i < NB_COMBATTANTS; i++)
        if (e2->combattant[i].vitesse > vmax2) vmax2 = e2->combattant[i].vitesse;

    int equipe_commence;

    // Détermine l'équipe qui commence
    if (vmax1 > vmax2) {
        equipe_commence = 1;
        printf(YELLOW "\n%s possède le combattant le plus rapide et débutera ce combat ! 👀\n" RESET, e1->nom);
    } else if (vmax2 > vmax1) {
        equipe_commence = 2;
        printf(BOLD_YELLOW "\n%s possède le combattant le plus rapide et débutera ce combat ! 👀\n" RESET, e2->nom);
    } else {
        equipe_commence = (rand() % 2) + 1;
        printf(BOLD_YELLOW "Les deux équipes ont un combattant aussi rapide ! 🥷\n" RESET);
        printf(BOLD_YELLOW "Tirage au sort...🥁 %s COMMENCERA CE COMBAT ! 🚀\n" RESET, equipe_commence == 1 ? e1->nom : e2->nom);
    }

    // Boucle principale de combat entre les deux équipes
for (int tour = 1; tour < 999; tour++) {
    // Si l’équipe 1 est complètement KO, alors l’équipe 2 gagne
    if (equipe_KO(e1)) {
        printf(BOLD_GREEN"\nVICTOIRE DE %s ! 🏆\n"RESET, e2->nom);
        return; // Fin du combat
    }

    // Si l’équipe 2 est complètement KO, alors l’équipe 1 gagne
    if (equipe_KO(e2)) {
        printf(BOLD_GREEN"\nVICTOIRE DE %s ! 🏆\n"RESET, e1->nom);
        return; // Fin du combat
    }

    // Affichage stylisé du numéro de tour
    printf(MAGENTA "\n\n\n\n\n                  ═══════════════════════════════════════════════\n"RESET);
    printf(BOLD_WHITE"                             🚨 TOUR %d : PRÉPAREZ VOUS ! 🚨         "RESET, tour);
    printf(MAGENTA "\n                  ═══════════════════════════════════════════════\n"RESET);

    // Chaque tour est composé de 3 sous-tours (un pour chaque combattant)
    for (int i = 0; i < 3; i++) {
        // On commence par faire jouer une équipe, selon l’ordre déterminé au début
        Equipe *active = (equipe_commence == 1) ? e1 : e2;    // L’équipe qui commence
        Equipe *adverse = (equipe_commence == 1) ? e2 : e1;   // L’équipe adverse

        // Si l’équipe active est encore debout, son combattant i joue
        if (!equipe_KO(active)) tour_joueur(active, adverse, i);

        // On vérifie après chaque action si l’équipe adverse est éliminée
        if (equipe_KO(adverse)) {
            printf(BOLD_GREEN"\nVICTOIRE DE %s ! 🏆\n"RESET, active->nom);
            return; // Fin du combat
        }

        // Puis c’est au tour de l’autre équipe
        active = (equipe_commence == 1) ? e2 : e1;     // Inversion des rôles
        adverse = (equipe_commence == 1) ? e1 : e2;

        // Même chose : si cette équipe est encore en vie, son combattant i joue
        if (!equipe_KO(active)) tour_joueur(active, adverse, i);

        // Vérifie de nouveau si l’équipe adverse est KO après l’action
        if (equipe_KO(adverse)) {
            printf(BOLD_GREEN"\nVICTOIRE DE %s ! 🏆\n"RESET, active->nom);
            return; // Fin du combat
            }
        }
    }
}
