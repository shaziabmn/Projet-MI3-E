#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "combat.h"
#include "interface.h"


// Fonction pour choisir le nom de l'équipe
void nom_equipe(Equipe *e) {
    // Vider le buffer d'entrée pour s'assurer qu'il n'y a pas de caractères résiduels
    while (getchar() != '\n');

    printf(BOLD_WHITE"\n✨ Nom de l'équipe (15 caractères max) : "RESET);
    fgets(e->nom, TAILLE_NOM, stdin); // lit au maximum (TAILLE_NOM - 1) caractères + \0

    // Supprimer le '\n' si présent à la fin
    size_t len = strlen(e->nom);
    if (len > 0 && e->nom[len - 1] == '\n') {
        e->nom[len - 1] = '\0';  // Remplacer le '\n' par un '\0'
    }

    // Vider à nouveau le buffer pour éviter tout caractère résiduel
    while (getchar() != '\n');
}




// Fonction pour sélectionner une équipe
void selectionner_equipe(Equipe *e, Combattant *c, int total) {

    int choix[NB_COMBATTANTS]; // Tableau pour stocker les choix des combattants de l'équipe
    for (int i = 0; i < NB_COMBATTANTS; i++) { 
        int choix_valide = 0; // Variable pour vérifier si l'entrée de l'utilisateur est valide

        while (!choix_valide) { // Boucle jusqu'à ce qu'un choix valide soit effectué
            
            printf(BOLD_YELLOW"\n\n\n\n                     --- 👤  CHOIX DU COMBATTANT %d/%d  👤 ---\n\n\n" RESET, i + 1, NB_COMBATTANTS);
            printf(BOLD_WHITE"👉 Entrez le numéro du combattant de votre choix : "RESET);

            if (scanf("%d", &choix[i]) != 1 || choix[i] < 1 || choix[i] > total) { // Si l'entrée est invalide, affiche un message d'erreur
                printf(RED "❌ Choix invalide. Veuillez entrer un nombre entre 1 et %d\n" RESET, total);
                while (getchar() != '\n');  // Vider le buffer d'entrée pour éviter des entrées incorrectes
    
            } else {
                choix_valide = 1; // Si l'entrée est valide, sortir de la boucle

            }
        }
        // Sélection du combattant dans l'équipe à partir de 1
        e->combattant[i] = c[choix[i] - 1];
    }

}


// Fonction principale
int main() {
    
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    // Déclaration d'un tableau pour stocker les combattants
    Combattant combattants[MAX_COMBATTANTS];

    // Chargement des combattants depuis le fichier "combattants.txt"
    int nb_combattants = charger_combattants("combattants.txt", combattants);


    // Vérifie s’il y a assez de combattants pour former 2 équipes complètes (sans doublons)
    if (nb_combattants < NB_COMBATTANTS*2) {
        printf("Erreur : pas assez de combattants chargés.\n");
        return 1;
    }

    // Affiche l'écran d'accueil
    afficher_jeu();

    int choix_menu = 0; // Variable pour vérifier si l'entrée de l'utilisateur est valide

    do {
        // Affiche le menu principal
        afficher_menu();

        // Lecture du choix de l'utilisateur et vérification de sa validité
        if (scanf("%d", &choix_menu) != 1 || (choix_menu != 1 && choix_menu != 2)) {
            printf(RED "❌ Choix invalide. Veuillez entrer '1' pour lancer le jeu ou '2' pour quitter\n" RESET);
            while (getchar() != '\n');  // Vider le buffer d'entrée pour éviter des entrées incorrectes
            continue;
        }

        // Si l'utilisateur choisit de lancer le jeu
        if (choix_menu == 1) {
            Equipe e1, e2;
            
            // Equipe 1
            printf("\n\n\n");
            printf(GREEN "\n                  ═══════════════════════════════════════════════\n"RESET);
            printf(BOLD_WHITE"                      🔷 SÉLECTION DE L'ÉQUIPE DU JOUEUR 1 🔷         "RESET);
            printf(GREEN "\n                  ═══════════════════════════════════════════════\n"RESET);
            printf("\n\n");

            // Saisie du nom de l’équipe 1
            nom_equipe(&e1);

            // Affiche la liste de tous les combattants disponibles
            afficher_liste_combattants(combattants, nb_combattants);

            // Permet à l'équipe 1 de choisir ses combattants
            selectionner_equipe(&e1, combattants, nb_combattants);


            // Equipe 2
            printf("\n\n\n\n");
            printf(RED "\n                  ═══════════════════════════════════════════════\n"RESET);
            printf(BOLD_WHITE"                      🔸 SÉLECTION DE L’ÉQUIPE DU JOUEUR 2 🔸         "RESET);
            printf(RED "\n                  ═══════════════════════════════════════════════\n"RESET);
            printf("\n\n");

            // Saisie du nom de l’équipe 2
            nom_equipe(&e2);
            // Affiche la liste de tous les combattants disponibles
            afficher_liste_combattants(combattants, nb_combattants);

            // Permet à l'équipe 2 de choisir ses combattants
            selectionner_equipe(&e2, combattants, nb_combattants);
           
            // Affiche un récapitulatif des deux équipes sélectionnées
            afficher_equipes(&e1, &e2);



            // Demande de confirmation pour lancer le combat
            char reponse;

            do {
            printf(BOLD_CYAN"\n Souhaitez-vous continuer ? 💥 (o/n) : "RESET);
            scanf(" %c", &reponse); // %c avec un espace avant pour ignorer les '\n'

            if (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N') {
                printf(RED "❌ Choix invalide. Veuillez entrer 'o' pour continuer ou 'n' pour quitter.\n\n" RESET);
                while (getchar() != '\n'); // Vider le buffer d'entrée pour éviter des entrées incorrectes
            }

            } while (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N');

            // Si l'utilisateur veut continuer, le combat est lancé
            if (reponse == 'o' || reponse == 'O') {
            lancer_combat(&e1, &e2);

            // Sinon, message de fin 
            } else {
            printf(BOLD_YELLOW "\n MERCI D'AVOIR JOUÉ À CY-FIGHTERS ! À BIENTÔT 👋\n\n" RESET);
            return 0;
            }

            }   

    } while (choix_menu != 2); // Répète tant que l'utilisateur n’a pas choisi de quitter


    // Message final à la fin du jeu
    printf(BOLD_YELLOW "\n MERCI D'AVOIR JOUÉ À CY-FIGHTERS ! À BIENTÔT 👋\n" RESET);
    printf("\n");

    return 0;
}
