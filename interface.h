#ifndef INTERFACE_H
#define INTERFACE_H

#include "combat.h"  // Pour utiliser les structures Combattant
#include <stdio.h>
#include <string.h>

// Couleurs ANSI pour l'affichage dans le terminal
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_CYAN   "\033[1;36m"
#define BOLD_GREEN  "\033[1;32m"
#define BOLD_RED    "\033[1;31m"
#define BOLD_WHITE  "\033[1;37m"
#define BOLD_BLUE   "\033[1;34m"

#define LARGEUR_TERMINAL 80

// Fonctions graphiques
void print_centered_color(const char* texte, const char* couleur);
void afficher_lobby();
void afficher_menu();
void affichage_perso(const Combattant *perso);
void afficher_equipes(Joueur *j1, Joueur *j2);

#endif
