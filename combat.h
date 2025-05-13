#ifndef COMBAT_H
#define COMBAT_H

#define TAILLE_NOM 16
#define NB_COMBATTANTS 3 // Nombre de combattants par équipe
#define MAX_COMBATTANTS 10 // Nombre maximal de combattants autorisés dans le fichier


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
    int pv_courants; 
    int pv_max;
    int attaque;
    int defense;
    int agilite; 
    int vitesse;
    Technique technique;

} Combattant;


// Structure des équipes

typedef struct {

    char nom[TAILLE_NOM];
    Combattant combattant[NB_COMBATTANTS];

} Equipe;


// Déclaration fonctions
int charger_combattants(const char *nomFichier, Combattant liste[]);
int equipe_KO(Equipe *e);
void gerer_effets_tour(Combattant *c);
void attaquer(Combattant *attaquant, Combattant *defenseur);
void utiliser_technique(Combattant *utilisateur, Combattant *cible);
void tour_joueur(Equipe *active, Equipe *adverse, int index);
void lancer_combat(Equipe *e1, Equipe *e2);


#endif
