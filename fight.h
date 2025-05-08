#ifndef BIB_H_INCLUDED
#define BIB_H_INCLUDED


#define LARGEUR_TERMINAL 120
#define BOLD    "\033[1m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"
#define ESPACE_GAUCHE 20
#define ESPACE_DROITE 45
void afficher_lobby();
typedef struct {
    char name[50];
    int pv_courants;
    int pv_max;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
      char nom[50];
    int valeur;
    char description[50];
    int tours_actifs;
    int tours_rechargement;


} Combattant;

Combattant nazarine;
Combattant anyr;
Combattant sakura;
Combattant sasuke;
Combattant naruto;
Combattant kakashi;
void print_centered_color(const char* texte, const char* couleur);
void affichage_perso(Combattant perso);
void affichage ();
void afficher_menu();
void afficher_menu();
Combattant tous_les_persos[6];
void choisir_equipe(Combattant equipe[3] );
int deja_choisi(int choix, int selectionne[], int taille);
void afficher_equipes(Combattant equipe_joueur[3], Combattant equipe_adverse[3]);
void lancer_combat_equipes(Combattant *j1, Combattant *j2);
void utiliser_technique(Combattant *c, Combattant *adversaire);
void attaquer(Combattant *attaquant, Combattant *cible);
int est_ko( Combattant *c);




#endif // BIB_H_INCLUDED
