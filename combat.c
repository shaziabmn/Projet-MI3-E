#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combat.h"

//Fonction utiliser technique

void utiliser_technique(Combattant *attaquant, Combattant *cible, Technique tech) {
// Exemple par rapport à la description
if (strcmp(tech.description, "attaque") == 0) {
attaquer(attaquant, cible, tech);
}
else if (strcmp(tech.description, "soin") == 0) {
attaquant->pv_courants += tech.valeur;
if (attaquant->pv_courants > attaquant->pv_max) {
attaquant->pv_courants = attaquant->pv_max;
}
}
else if (strcmp(tech.description, "recharge") == 0) {
// Peut être gérer de l'énergie (dans future version)
printf("%s se recharge\n", attaquant->nom);
}

}

//Fonction attaquer

int attaquer(Fighter *attaquant, Fighter *cible, Technique tech) {
// Calcul dégâts
int degats = tech.valeur + attaquant->attaque - cible->defense;

// Empêcher dégâts négatifs
if (degats < 0) degats = 0;

// Appliquer dégâts
cible->pv_courants -= degats;

// Empêcher HP négatifs
if (cible->pv_courants < 0) cible->pv_courants = 0;

// Retour HP restants
return cible->pv_courants;
}

else if (strcmp(tech.description, "boost_attaque") == 0) {
    attaquant->attaque += tech.valeur;
    printf("%s augmente son attaque de %d !\n", attaquant->nom, tech.valeur);
}
else if (strcmp(tech.description, "reduction_defense") == 0) {
    cible->defense -= tech.valeur;
    if (cible->defense < 0) cible->defense = 0;
    printf("%s perd %d de défense !\n", cible->nom, tech.valeur);
}
int est_mort(Fighter *f) {
    return f->pv_courants <= 0;
}

void combat(Fighter *f1, Fighter *f2) {
    int tour = 1;
    while (!est_mort(f1) && !est_mort(f2)) {
        printf("Tour %d :\n", tour);

        if (tour % 2 == 1) {
            Technique attaque_joueur = {"Coup de poing", 10, "attaque", 0, 0};
            utiliser_technique(f1, f2, attaque_joueur);
        } else {
            Technique attaque_bot = {"Frappe", 8, "attaque", 0, 0};
            utiliser_technique(f2, f1, attaque_bot);
        }

        printf("%s : %d PV | %s : %d PV\n\n", f1->name, f1->pv_courants, f2->nom, f2->pv_courants);
        tour++;
    }

    if (est_mort(f1)) printf("%s a perdu !\n", f1->name);
    else printf("%s a perdu !\n", f2->name);
}
