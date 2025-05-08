#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fight.h"


//Structure Fighter


 Combattant sakura ={
     .name = "sakura",
  .pv_courants =200,
    .pv_max = 200,
    .attaque = 100,
.defense = 30,
     .agilite = 7,
    .vitesse = 3,
      .nom = "soin ultime" ,
    .valeur = 50,
     .description = "hp",
    .tours_actifs = 1,
     .tours_rechargement = 3,
 };
Combattant sasuke ={
    .name ="sasuke",
  .pv_courants =200,
    .pv_max = 200,
    .attaque = 120,
    .defense = 20,
     .agilite = 10,
    .vitesse = 9,
      .nom = "shidori",
    .valeur = 50,
     .description = "attaque",
    .tours_actifs = 1,
     .tours_rechargement = 3,
 };
 Combattant naruto ={
     .name ="naruto",
  .pv_courants =200,
    .pv_max = 200,
    .attaque = 130,
    .defense = 20,
     .agilite = 10,
    .vitesse = 9,
      .nom = "sage mode" ,
    .valeur = 0,
     .description = "protection",
    .tours_actifs = 2,
     .tours_rechargement = 4,
 };
 Combattant kakashi ={
     .name = "kakshi",
  .pv_courants =200,
    .pv_max = 200,
    .attaque = 120,
    .defense = 15,
     .agilite = 9,
    .vitesse = 9,
      .nom = "bejaia" ,
    .valeur = 0,
     .description = "double",
    .tours_actifs = 1,
     .tours_rechargement = 2,
 };
 Combattant anyr ={
     .name ="anyr",
  .pv_courants =200,
    .pv_max = 200,
    .attaque = 110,
    .defense = 15,
     .agilite = 7,
    .vitesse = 8,
      .nom = "mirroir" ,
    .valeur = 50,
     .description = "reverse",
    .tours_actifs = 1,
     .tours_rechargement = 3,
 };
 Combattant nazarine ={
     .name ="nazarine",
  .pv_courants =200,
    .pv_max = 200,
    .attaque = 90,
    .defense = 10,
     .agilite = 7,
    .vitesse = 7,
      .nom = "nada",
    .valeur = 0,
     .description = "nul",

 };
 void print_centered_color(const char* texte, const char* couleur) {
    int len = strlen(texte);
    int spaces = (LARGEUR_TERMINAL - len) / 2;
    for (int i = 0; i < spaces; i++) printf(" ");
    printf("%s%s%s\n", couleur, texte, RESET);
}
#include <stdio.h>

void afficher_lobby() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║                                                      ║\n");
    printf("║         %s🌀  WELCOME TO %s" BOLD YELLOW " NARUTO STORM " RESET "  🌀         ║\n", CYAN, YELLOW);
    printf("║                                                      ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(BOLD CYAN "               🥷 Ultimate Shinobi Battle 🥷\n" RESET);
    printf("\n");
    printf(BOLD GREEN "  1️⃣  Lancer un combat\n");
    printf("  2️⃣  Voir les règles\n");
    printf("  3️⃣  Quitter le jeu\n");
    printf("\n");
    printf(WHITE "➡️  Fais ton choix (1-3) : " RESET);
}



void affichage_perso(Combattant perso) {
    char buffer[100];

    print_centered_color("=====================================", CYAN);

    sprintf(buffer, " Nom              : %s", perso.name);
    print_centered_color(buffer, BOLD YELLOW);

    sprintf(buffer, " Description      : %s", perso.description);
    print_centered_color(buffer, MAGENTA);

    print_centered_color("-------------------------------------", CYAN);

    sprintf(buffer, " PV               : %d / %d", perso.pv_courants, perso.pv_max);
    print_centered_color(buffer, GREEN);

    sprintf(buffer, " Attaque          : %d", perso.attaque);
    print_centered_color(buffer, RED);

    sprintf(buffer, " Défense          : %d", perso.defense);
    print_centered_color(buffer, BLUE);

    sprintf(buffer, " Agilité          : %d", perso.agilite);
    print_centered_color(buffer, WHITE);

    sprintf(buffer, " Vitesse          : %d", perso.vitesse);
    print_centered_color(buffer, WHITE);

    sprintf(buffer, " Valeur Spéciale  : %d", perso.valeur);
    print_centered_color(buffer, MAGENTA);

    sprintf(buffer, " Tours actifs     : %d", perso.tours_actifs);
    print_centered_color(buffer, WHITE);

    sprintf(buffer, " Recharge (tours) : %d", perso.tours_rechargement);
    print_centered_color(buffer, WHITE);

    print_centered_color("=====================================\n", CYAN);
}
void affichage ()
{

    char next;
       scanf("%c",&next);
    system("cls");
    affichage_perso(sakura);
    scanf("%c",&next);
    system("cls");
    affichage_perso(sasuke);
     scanf("%c",&next);
    system("cls");
    affichage_perso(naruto);
     scanf("%c",&next);
    system("cls");
    affichage_perso(kakashi);
     scanf("%c",&next);
    system("cls");
    affichage_perso(anyr);
     scanf("%c",&next);
    system("cls");
    affichage_perso(nazarine);
     scanf("%c",&next);
    system("cls");
}
void affichage_nom_perso_menu(int numero, Combattant perso) {
    printf(BOLD CYAN "| %d. " RESET, numero);
    printf(BOLD YELLOW "%-12s" RESET, perso.name);
}
void afficher_menu() {
    printf("\n" BOLD CYAN "============ MENU DE SELECTION DES COMBATTANTS ============\n" RESET);
    printf(BOLD CYAN "| %-16s | %-16s |\n" RESET, "Equipe 1", "Equipe 2");
    printf(CYAN "------------------------------------------------------------\n" RESET);

    affichage_nom_perso_menu(1, sakura);
    printf("  ");
    affichage_nom_perso_menu(4, kakashi);
    printf("\n");

    affichage_nom_perso_menu(2, sasuke);
    printf("  ");
    affichage_nom_perso_menu(5, anyr);
    printf("\n");

    affichage_nom_perso_menu(3, naruto);
    printf("  ");
    affichage_nom_perso_menu(6, nazarine);
    printf("\n");

    printf(CYAN "============================================================\n" RESET);
}


void initialiser_persos() {
    tous_les_persos[0] = sakura;
    tous_les_persos[1] = sasuke;
    tous_les_persos[2] = naruto;
    tous_les_persos[3] = kakashi;
    tous_les_persos[4] = anyr;
    tous_les_persos[5] = nazarine;
}
int deja_choisi(int choix,  int selectionne[], int taille) {
    for (int i = 0; i < (taille); i++) {
        if ( selectionne[i] == choix) {
            return 1;
        }
    }
    return 0;
}
void choisir_equipe(Combattant equipe[3] )

{
    int choix,indice =0, selectionne[3];
      printf(BOLD GREEN "\n=== Choisis 3 combattants parmi les 6 ===\n" RESET);
      initialiser_persos();

    while (indice < 3) {
        printf("Choix %d/3 (entre 1 et 6) : ", indice + 1);
        choice:
        scanf("%d", &choix);

        if (choix < 1 || choix > 6) {
            printf(RED "Numéro invalide. Réessaie.\n" RESET);
            goto choice;
        }
        else if (deja_choisi(choix, selectionne ,indice)) {
            printf(YELLOW "Dejà choisi ! Choisis un autre.\n" RESET);
        goto choice ;
        }
        else {
           equipe[indice]= tous_les_persos[choix-1];
           selectionne[indice]=choix;
           indice++;
        }
}
}
void afficher_equipes(Combattant equipe_joueur[3], Combattant equipe_adverse[3]) {
    printf(BOLD CYAN "\n╔════════════════════════════════════╦════════════════════════════════════╗\n");
    printf("║        🟢 Ton Équipe               ║        🔴 Équipe Adverse           ║\n");
    printf("╠════════════════════════════════════╬════════════════════════════════════╣\n" RESET);

    for (int i = 0; i < 3; i++) {
        printf("║ " BOLD GREEN "%d. %-30s" RESET, i + 1, equipe_joueur[i].name);
        printf("║ " BOLD RED "%d. %-30s" RESET, i + 1, equipe_adverse[i].name);
        printf("║\n");
    }

    printf(BOLD CYAN "╚════════════════════════════════════╩════════════════════════════════════╝\n\n" RESET);
}


// Fonction pour vérifier si un combattant est KO
int est_ko( Combattant *c) {
    if (c->pv_courants <= 0){
        return 1;
    }
    return 0;  // Retourne 1 si KO, 0 sinon
}


// PARTIE HIBA


// Fonction pour calculer et infliger des dégâts
void attaquer(Combattant *attaquant, Combattant *cible) {
    int degats = attaquant->attaque - cible->defense;

    cible->pv_courants -= degats;
    if (cible->pv_courants < 0) cible->pv_courants = 0;

    printf("%s attaque %s et inflige %d dégâts !\n", attaquant->name, cible->name, degats);
}


// Fonction pour utiliser une technique spécial
void utiliser_technique(Combattant *c, Combattant *adversaire) {
    if (c->tours_rechargement = 0) {
        printf("%s utilise %s !\n", c->name, c->nom);

        if (strcmp(c->description, "hp") == 0) {
            c->pv_courants += c->valeur;
            if (c->pv_courants > c->pv_max)
                c->pv_courants = c->pv_max;
            printf("%s récupère %d PV !\n", c->name, c->valeur);

        } else if (strcmp(c->description, "attaque") == 0) {
            adversaire->pv_courants -= c->valeur;
            if (adversaire->pv_courants < 0)
                adversaire->pv_courants = 0;
            printf("%s inflige %d dégâts à %s !\n", c->name, c->valeur, adversaire->name);

        } else if (strcmp(c->description, "protection") == 0) {
            c->defense += c->valeur;
            printf("%s augmente sa défense de %d pendant %d tour(s).\n", c->name, c->valeur, c->tours_actifs);

        } else if (strcmp(c->description, "double") == 0) {
            c->attaque *= 2;
            printf("%s double son attaque pendant %d tour(s) !\n", c->name, c->tours_actifs);

        } else if (strcmp(c->description, "reverse") == 0) {
            int temp = c->attaque;
            c->attaque = c->defense;
            c->defense = temp;
            printf("%s inverse attaque et défense pendant %d tour(s) !\n", c->name, c->tours_actifs);

        } else if (strcmp(c->description, "nul") == 0) {
            printf("%s tente un coup spécial… mais il ne se passe rien.\n", c->name);

        } else {
            printf("Technique inconnue.\n");
        }

        c->tours_rechargement = 3;
    } else {
        printf("La technique de %s n’est pas encore rechargée !\n", c->name);
    }
}




void lancer_combat_equipes(Combattant equipe_joueur[3], Combattant equipe_adverse[3]) {
    int indice_joueur = 0, indice_adverse = 0;
    int tour = 1, action_bot = 1 ;

    printf(BOLD GREEN "\n🎮 Début du combat : 1 contre 1 jusqu'à l'élimination complète !\n" RESET);

    while (indice_joueur < 3 && indice_adverse < 3) {
        printf(BOLD CYAN "\n\n  Combat entre %s (Toi) VS %s (Bot)\n" RESET,
               equipe_joueur[indice_joueur].name, equipe_adverse[indice_adverse].name);

        Combattant *j1 = &equipe_joueur[indice_joueur];
        Combattant *j2 = &equipe_adverse[indice_adverse];

 affichage_perso(*j1);
            affichage_perso(*j2);
        int sous_tour = 1;
        while (est_ko(j1) == 0 && est_ko(j2) == 0) {

            printf("\n" BOLD WHITE "===== Tour %d =====\n" RESET, sous_tour);



            if (j1->vitesse >= j2->vitesse) {

                printf(BOLD GREEN "\n🎯 À toi de jouer ! (1: Attaquer, 2: Technique, 3: Soin)\n" RESET);
                int choix;
                scanf(" %d", &choix);
                if (choix == 1) {
                    printf("%s attaque %s !\n", j1->name, j2->name);
                    attaquer(j1, j2);
                } else if (choix == 2) {
                    printf("%s utilise sa technique spéciale sur %s !\n", j1->name, j2->name);
                    utiliser_technique(j1, j2);
                } else if (choix == 3) {
                    printf("%s choisit de se soigner.\n", j1->name);
                    if (j1->pv_courants < j1->pv_max) {
                        j1->pv_courants += 50;
                        if (j1->pv_courants > j1->pv_max) j1->pv_courants = j1->pv_max;
                        printf("%s récupère 50 PV !\n", j1->name);
                    } else {
                        printf("%s a déjà tous ses PV.\n", j1->name);
                    }
                }

                if (!est_ko(j2)) {
                    action_bot = rand() % 3;
                    if (action_bot == 0) {
                        printf("%s (Bot) attaque %s !\n", j2->name, j1->name);
                        attaquer(j2, j1);
                    } else if (action_bot == 1) {
                        printf("%s (Bot) utilise une technique sur %s !\n", j2->name, j1->name);
                        utiliser_technique(j2, j1);
                    } else if (j2->pv_courants < j2->pv_max) {
                        printf("%s (Bot) choisit de se soigner.\n", j2->name);
                        j2->pv_courants += 50;
                        if (j2->pv_courants > j2->pv_max) j2->pv_courants = j2->pv_max;
                        printf("%s se soigne de 50 PV.\n", j2->name);
                    }
                }
            }
            else {

                 action_bot = rand() % 3;
                if (action_bot == 0) {
                    printf("%s (Bot) attaque %s !\n", j2->name, j1->name);
                    attaquer(j2, j1);
                } else if (action_bot == 1) {
                    printf("%s (Bot) utilise une technique sur %s !\n", j2->name, j1->name);
                    utiliser_technique(j2, j1);
                } else  {
                    printf("%s (Bot) choisit de se soigner.\n", j2->name);
                    j2->pv_courants += 50;
                    if (j2->pv_courants > j2->pv_max) j2->pv_courants = j2->pv_max;
                    printf("%s se soigne de 50 PV.\n", j2->name);
                }

                if (!est_ko(j1)) {
                    printf(BOLD GREEN "\n🎯 À toi de jouer ! (1: Attaquer, 2: Technique, 3: Soin)\n" RESET);
                    int choix;
                    scanf("%d", &choix);
                    if (choix == 1) {
                        printf("%s attaque %s !\n", j1->name, j2->name);
                        attaquer(j1, j2);
                    } else if (choix == 2) {
                        printf("%s utilise sa technique spéciale sur %s !\n", j1->name, j2->name);
                        utiliser_technique(j1, j2);
                    } else if (choix == 3) {
                        printf("%s choisit de se soigner.\n", j1->name);
                        if (j1->pv_courants < j1->pv_max) {
                            j1->pv_courants += 50;
                            if (j1->pv_courants > j1->pv_max) j1->pv_courants = j1->pv_max;
                            printf("%s récupère 50 PV !\n", j1->name);
                        } else {
                            printf("%s a déjà tous ses PV.\n", j1->name);
                        }
                    }
                }
            }


            if (j1->tours_rechargement > 0) j1->tours_rechargement--;
            if (j2->tours_rechargement > 0) j2->tours_rechargement--;
             affichage_perso(*j1);
            affichage_perso(*j2);



            sous_tour++;
        }

        if (est_ko(j1)) {
            printf(BOLD RED "\n💀 %s est KO !\n" RESET, j1->name);
            indice_joueur++;
        } else if (est_ko(j2)) {
            printf(BOLD RED "\n💀 %s est KO !\n" RESET, j2->name);
            indice_adverse++;
        }
    }

    if (indice_joueur == 3)
        printf(BOLD RED "\n🔥 Tous tes combattants sont KO. Défaite.\n" RESET);
    else
        printf(BOLD GREEN "\n🏆 Tous les ennemis sont vaincus. Victoire !\n" RESET);
}











