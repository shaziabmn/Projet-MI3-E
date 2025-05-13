#include "interface.h"


// Fonction pour afficher un texte centré avec une couleur
void afficher_centre(const char* texte, const char* couleur) {

    int len = strlen(texte); // Longueur du texte
    int spaces = (LARGEUR_TERMINAL - len) / 2; // Calcul du nombre d'espaces pour centrer
    for (int i = 0; i < spaces; i++) printf(" "); // Affichage des espaces
    printf("%s%s%s\n", couleur, texte, RESET); // Affichage du texte coloré suivi de RESET pour revenir à la couleur normale

}


// Fonction pour afficher l'écran d'accueil du jeu
void afficher_jeu() {

    printf("\n\n             ╔══════════════════════════════════════════════════════╗\n");
    printf("             ║                                                      ║\n");
    printf("             ║         %s🎮  BIENVENUE SUR %s" BOLD_YELLOW " CY-FIGHTERS " RESET "  🎮          ║\n", CYAN, YELLOW);
    printf("             ║                                                      ║\n");
    printf("             ╚══════════════════════════════════════════════════════╝\n");
    
    printf(BOLD_CYAN "\n                           🥊 Combat au tour par tour 🥊\n" RESET);
    printf(BOLD_CYAN "                     🌍 Réalisé par Hiba, Shazia et Wahiba 🌍\n\n" RESET);
    

}

// Fonction pour afficher le menu principal
void afficher_menu() {

    printf(BOLD_GREEN "\n📜 MENU PRINCIPAL\n\n" RESET);
    
    printf("1️⃣  Lancer un combat\n");
    printf("2️⃣  Quitter\n");
    
    printf(BOLD_WHITE"\n\n👉 Votre choix : "RESET);

}


// Fonction pour afficher les caractéristiques des combattants
void afficher_perso(const Combattant *perso) {

    char buffer[1000]; // Déclaration d'un tableau de 1000 caractères

    printf("\n");
    sprintf(buffer, "         Nom              : %s", perso->nom); // Formater et stocker le texte dans 'buffer'
    afficher_centre(buffer, YELLOW); // Affiche le texte centré

    sprintf(buffer, "      PV               : %d / %d", perso->pv_courants, perso->pv_max);
    afficher_centre(buffer, GREEN);

    sprintf(buffer, " Attaque          : %d", perso->attaque);
    afficher_centre(buffer, RED);

    sprintf(buffer, "  Défense          : %d", perso->defense);
    afficher_centre(buffer, BLUE);

    sprintf(buffer, " Agilité          : %d", perso->agilite);
    afficher_centre(buffer, WHITE);

    sprintf(buffer, " Vitesse          : %d", perso->vitesse);
    afficher_centre(buffer, WHITE);

    // Affichage des détails de la technique spéciale
    sprintf(buffer, " Technique spéciale : %s", perso->technique.nom);
    afficher_centre(buffer, MAGENTA);

    sprintf(buffer, "%s", perso->technique.description);
    afficher_centre(buffer, MAGENTA);

    sprintf(buffer, " Valeur           : %d", perso->technique.valeur);
    afficher_centre(buffer, MAGENTA);

    sprintf(buffer, " Actif (tours)    : %d", perso->technique.tours_actifs);
    afficher_centre(buffer, WHITE);

    sprintf(buffer, " Recharge (tours) : %d", perso->technique.tours_rechargement);
    afficher_centre(buffer, WHITE);

    printf(CYAN"\n                  ═══════════════════════════════════════════════\n"RESET);

}


// Fonction pour afficher la liste des combattants
void afficher_liste_combattants(Combattant *liste, int n) {
    
    printf(BOLD_WHITE"\n\n\n\n\n                 --- ⚡️  LISTE DES COMBATTANTS DISPONIBLES  ⚡️ ---" RESET);
    printf(CYAN"\n\n                  ═══════════════════════════════════════════════\n"RESET);

    for (int i = 0; i < n; i++) {
        printf("   (%d)", i + 1);
        afficher_perso(&liste[i]);  // Affiche les caractéristiques du combattant
    }
}

// Fonction pour afficher les deux équipes sélectionées
void afficher_equipes(Equipe *e1, Equipe *e2) {

     printf(CYAN "\n\n\n\n\n                  ═══════════════════════════════════════════════\n"RESET);
            printf(BOLD_WHITE"                    🔥 VOS ÉQUIPES SONT PRÊTES À COMBATTRE ! 🔥         "RESET);
            printf(CYAN "\n                  ═══════════════════════════════════════════════\n\n\n\n"RESET);

    char buffer[1000];

    // Équipe 1
    sprintf(buffer, "🟢   Équipe %s ", e1->nom);
    afficher_centre(buffer, BOLD_WHITE);

    afficher_centre("--------------------\n", GREEN);

    for (int i = 0; i < NB_COMBATTANTS; i++) { 
        // Affiche chaque combattant de l'équipe 1
        sprintf(buffer,"   🔹 %s\n", e1->combattant[i].nom);
        afficher_centre(buffer, BOLD_WHITE);
    }
    afficher_centre("--------------------\n\n", GREEN);

    // Équipe 2
    sprintf(buffer, "🔴   Équipe %s ", e2->nom);
    afficher_centre(buffer, BOLD_WHITE);

    afficher_centre("--------------------\n", RED);
    for (int i = 0; i < NB_COMBATTANTS; i++) { 
        // Affiche chaque combattant de l'équipe 2
        sprintf(buffer,"   🔸 %s\n", e2->combattant[i].nom);
        afficher_centre(buffer, BOLD_WHITE);
    }

    afficher_centre("--------------------\n\n\n", RED);
    
}


