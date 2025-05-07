#ifndef COMBAT_H
#define COMBAT_H

#define TAILLE_NOM 20
#define MAX_COMBATTANTS 3

//Structure Technique
typedef struct {
    char nom[TAILLE_NOM];
    int valeur;
    char description[100];
    int tours_actifs;
    int tours_rechargement;
} Technique;

//Structure Combattant
typedef struct {
    char nom[TAILLE_NOM];
    int pv_courants;
    int pv_max;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    Technique special;
} Combattant;

//Structure Equipe
typedef struct {
    char nom[TAILLE_NOM];
    Combattant membres[MAX_COMBATTANTS];
} Equipe;

// Déclarations des fonctions
int charger_combattants(const char *nomFichier, Combattant liste[], int max);
void afficher_combattant(const Combattant *c);
int est_ko(const Combattant *c);

#endif
