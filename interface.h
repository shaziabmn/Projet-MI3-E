#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <string.h>

#include "combat.h"  


// Définition des codes de couleurs ANSI pour l'affichage dans le terminal
#define RESET       "\033[0m" // Réinitialise la couleur à la valeur par défaut
#define BOLD        "\033[1m" // Met le texte en gras
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Met le texte en couleurs et en gras
#define BOLD_RED    "\033[1;31m"
#define BOLD_GREEN  "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE   "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN   "\033[1;36m"
#define BOLD_WHITE  "\033[1;37m"


// Définition de la largeur du terminal pour centrer des éléments à l'écran
#define LARGEUR_TERMINAL 80


// Déclarations des fonctions
void afficher_centre(const char* texte, const char* couleur); // Afficher un texte centré avec une couleur
void afficher_jeu(); // Afficher l'écran d'accueil du jeu
void afficher_menu(); // Afficher le menu principal
void afficher_perso(const Combattant *perso); // Afficher les caractéristiques des combattants
void afficher_liste_combattants(Combattant *liste, int n); // Afficher la liste des combattants
void afficher_equipes(Equipe *e1, Equipe *e2); // Afficher les deux équipes sélectionées


#endif
