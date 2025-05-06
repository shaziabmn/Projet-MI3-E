#ifndef COMBAT_H
#define COMBAT_H

#define TAILLE_NOM 20
#define MAX_COMBATTANTS 3
#define MAX_TECHNIQUES 3

//Structure Technique
typedef struct {
    char nom[TAILLE_NOM];
    int valeur;
    char description;
    int tours_actifs;
    int tours_rechargement;
} Technique;

//Structure Fighter
typedef struct {
    char name[TAILLE_NOM];
    int pv_courants;
    int pv_max;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    Technique special[MAX_TECHNIQUES];
    int nb_technique;
} Combattant;

//Structure Team
typedef struct {
    char nom[TAILLE_NOM];
    Combattant membres[MAX_COMBATTANTS];
} Equipe;

#endif

