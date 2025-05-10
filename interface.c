#include "interface.h"

void print_centered_color(const char* texte, const char* couleur) {
    int len = strlen(texte);
    int spaces = (LARGEUR_TERMINAL - len) / 2;
    for (int i = 0; i < spaces; i++) printf(" ");
    printf("%s%s%s\n", couleur, texte, RESET);
}

void afficher_lobby() {
    printf("\n");
    printf("\n");
    printf("             ╔══════════════════════════════════════════════════════╗\n");
    printf("             ║                                                      ║\n");
    printf("             ║         %s🎮  BIENVENUE SUR %s" BOLD_YELLOW " CY-FIGHTERS " RESET "  🎮          ║\n", CYAN, YELLOW);
    printf("             ║                                                      ║\n");
    printf("             ╚══════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(BOLD_CYAN "                           🥊 Combat au tour par tour 🥊\n" RESET);
    printf(BOLD_CYAN "                     🌍 Réalisé par Hiba, Shazia et Wahiba 🌍\n" RESET);
    printf("\n");
}

void afficher_menu() {
    printf(BOLD_GREEN "\n📜 MENU PRINCIPAL\n" RESET);
    printf("\n");
    printf("1️⃣  Lancer un combat\n");
    printf("2️⃣  Quitter\n");
    printf("\n");
    printf("\n👉 Votre choix : ");
}

void affichage_perso(const Combattant *perso) {
    char buffer[1000];

    print_centered_color("=======================================================", CYAN);
    printf("\n");

    sprintf(buffer, "         Nom              : %s", perso->nom);
    print_centered_color(buffer, YELLOW);

    sprintf(buffer, "      PV               : %d / %d", perso->pv_courants, perso->pv_max);
    print_centered_color(buffer, GREEN);

    sprintf(buffer, " Attaque          : %d", perso->attaque);
    print_centered_color(buffer, RED);

    sprintf(buffer, "  Défense          : %d", perso->defense);
    print_centered_color(buffer, BLUE);

    sprintf(buffer, " Agilité          : %d", perso->agilite);
    print_centered_color(buffer, WHITE);

    sprintf(buffer, " Vitesse          : %d", perso->vitesse);
    print_centered_color(buffer, WHITE);

    sprintf(buffer, " Technique spéciale : %s", perso->special.nom);
    print_centered_color(buffer, MAGENTA);

    sprintf(buffer, " Effet : %s", perso->special.description);
    print_centered_color(buffer, MAGENTA);

    sprintf(buffer, " Valeur           : %d", perso->special.valeur);
    print_centered_color(buffer, MAGENTA);

    sprintf(buffer, " Actif (tours)    : %d", perso->special.tours_actifs);
    print_centered_color(buffer, WHITE);

    sprintf(buffer, " Recharge (tours) : %d", perso->special.tours_rechargement);
    print_centered_color(buffer, WHITE);

    printf("\n");
    print_centered_color(" =======================================================", CYAN);
}

void afficher_equipes(Joueur *j1, Joueur *j2) {
    printf("\n\n\n");
    printf(BOLD_CYAN "           === 🔥 VOS ÉQUIPES SONT PRÊTES À COMBATTRE ! 🔥 ===\n" RESET);
    printf("\n\n");

    // Équipe 1
    printf(" 🟢 " BOLD_GREEN "Équipe %s" RESET "\n", j1->nom);
    printf("--------------------\n");
    for (int i = 0; i < MAX_COMBATTANTS; i++) {
        printf("   🔹 %s\n", j1->equipe[i].nom);
    }
    printf("--------------------\n");
    printf("\n");

    // Équipe 2
    printf(" 🔴 " BOLD_RED "Équipe %s" RESET "\n", j2->nom);
    printf("--------------------\n");
    for (int i = 0; i < MAX_COMBATTANTS; i++) {
        printf("   🔸 %s\n", j2->equipe[i].nom);
    }
    printf("--------------------\n");
    
}

