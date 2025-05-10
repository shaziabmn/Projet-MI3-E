#ifndef COMBAT_H
#define COMBAT_H

#define TAILLE_NOM 16
#define MAX_COMBATTANTS 3

// Structure des techniques
typedef struct {
    char nom[TAILLE_NOM];
    int valeur;
    char description[100];
    int tours_actifs;
    int tours_rechargement;
} Technique;

// Structure des combattants
typedef struct {
    char nom[TAILLE_NOM];
    int pv_courants, pv_max;
    int attaque, defense, agilite, vitesse;

    // Sauvegarde des statistiques originales
    int base_attaque, base_defense, base_agilite, base_vitesse;

    int tours_effet; // durée restante de l’effet actif

    Technique special;
} Combattant;

// Structure des joueurs
typedef struct {
    char nom[TAILLE_NOM];
    Combattant equipe[MAX_COMBATTANTS];
    int nb_combattants;
} Joueur;

// Déclaration fonctions
void initialiser_stats_base(Combattant *c);
void attaquer(Combattant *attaquant, Combattant *cible);
void utiliser_technique(Combattant *utilisateur, Combattant *cible);
void gerer_effets_tour(Combattant *c);
void tour_joueur(Joueur *joueur, Joueur *adverse);
void lancer_combat(Joueur *j1, Joueur *j2);
int equipe_KO(Joueur *j);
int charger_combattants(const char *nomFichier, Combattant liste[], int max);

#endif
