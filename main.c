#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "combat.h"
#include "interface.h"

#define MAX_TOTAL 10

// Fonction d'affichage des combattants disponibles
void afficher_liste_combattants(Combattant *liste, int n) {
    printf("\n");
    printf("\n");
    printf(BOLD_WHITE"\n                  --- ⚡️  LISTE DES COMBATTANTS DISPONIBLES  ⚡️ ---\n" RESET);

    for (int i = 0; i < n; i++) {
        printf("%d", i + 1);
        affichage_perso(&liste[i]);  // Affiche les détails du combattant
    }
}

// Fonction pour choisir le nom de l'équipe
void nom_equipe(Joueur *j) {
    printf("\n");
    printf("✨ Nom de l'équipe : ");
    scanf("%s", j->nom);
    j->nb_combattants = MAX_COMBATTANTS;
}

// Fonction pour sélectionner une équipe
void selectionner_equipe(Joueur *j, Combattant *disponibles, int total) {
    int choix[MAX_COMBATTANTS];
    for (int i = 0; i < MAX_COMBATTANTS; i++) {
        int choix_valide = 0;
        
        while (!choix_valide) {
            printf("\n\n");
            printf(BOLD_WHITE"\n                  --- 👤  CHOIX DU COMBATTANT %d/%d  👤 ---\n" RESET, i + 1, MAX_COMBATTANTS);
            printf("\n");
            printf("👉 Entrez le numéro du combattant de votre choix : ");

            // Un seul scanf pour récupérer l'entrée
            if (scanf("%d", &choix[i]) != 1 || choix[i] < 1 || choix[i] > total) {
                printf(RED "❌ Choix invalide. Veuillez entrer un nombre entre 1 et %d\n" RESET, total);
                while (getchar() != '\n');  // Vider le buffer d'entrée
            } else {
                choix_valide = 1;
            }
        }

        // Sélection du combattant dans l'équipe
        j->equipe[i] = disponibles[choix[i] - 1];
        initialiser_stats_base(&j->equipe[i]);
    }
}


int main() {
    srand(time(NULL));

    Combattant combattants_disponibles[MAX_TOTAL];
    int nb_total = charger_combattants("combattants.txt", combattants_disponibles, MAX_TOTAL);

    if (nb_total < 2) {
        printf("Erreur : pas assez de combattants chargés.\n");
        return 1;
    }

    int choix_menu;
    afficher_lobby();

    do {
        afficher_menu();

        if (scanf("%d", &choix_menu) != 1 || (choix_menu != 1 && choix_menu != 2)) {
            printf(RED "❌ Choix invalide. Veuillez entrer '1' pour lancer le jeu ou '2' pour quitter\n" RESET);
            while (getchar() != '\n');  
            continue;
        }

        if (choix_menu == 1) {
            Joueur joueur1, joueur2;

            printf("\n");
            printf(GREEN "\n                  ═══════════════════════════════════════════════\n"RESET);
            printf(BOLD_WHITE"                      🔷 SÉLECTION DE L'ÉQUIPE DU JOUEUR 1 🔷         "RESET);
            printf(GREEN "\n                  ═══════════════════════════════════════════════\n"RESET);

            nom_equipe(&joueur1);
            afficher_liste_combattants(combattants_disponibles, nb_total);
            selectionner_equipe(&joueur1, combattants_disponibles, nb_total);

            printf("\n");
            printf("\n");
            printf(RED "\n                  ═══════════════════════════════════════════════\n"RESET);
            printf(BOLD_WHITE"                      🔸 SÉLECTION DE L’ÉQUIPE DU JOUEUR 2 🔸         "RESET);
            printf(RED "\n                  ═══════════════════════════════════════════════\n"RESET);

            nom_equipe(&joueur2);
            afficher_liste_combattants(combattants_disponibles, nb_total);
            selectionner_equipe(&joueur2, combattants_disponibles, nb_total);
           

            afficher_equipes(&joueur1, &joueur2);

            printf("\n");

    // Demander si on veut continuer
    
    char reponse;
    do {
    printf("\n");
    printf(BOLD_CYAN "Souhaitez-vous continuer ? 💥 (o/n) : " RESET);
    scanf(" %c", &reponse);

    if (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N') {
        printf(RED "❌ Choix invalide. Veuillez entrer 'o' pour continuer ou 'n' pour quitter.\n" RESET);
        while (getchar() != '\n'); // vide le buffer en cas d'entrée invalide
        printf("\n");
    }
    } while (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N');

    if (reponse == 'o' || reponse == 'O') {
    lancer_combat(&joueur1, &joueur2);
    } else {
    printf(BOLD_YELLOW "MERCI D'AVOIR JOUÉ À CY-FIGHTERS ! À BIENTÔT 👋\n" RESET);
    printf("\n");

    return 0;
    }
        }

    } while (choix_menu != 2);

    printf("\n");
    printf(BOLD_YELLOW "MERCI D'AVOIR JOUÉ À CY-FIGHTERS ! À BIENTÔT 👋\n" RESET);
    printf("\n");

    return 0;
}
