#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combat.h"

//Fonction utiliser technique

void utiliser_technique(Fighter *attaquant, Fighter *cible, Technique tech) {
// Exemple par rapport à la description
if (strcmp(tech.description, "attaque") == 0) {
attaquer(attaquant, cible, tech);
}
else if (strcmp(tech.description, "soin") == 0) {
attaquant->pv_currents += tech.value;
if (attaquant->pv_currents > attaquant->pv_max) {
attaquant->pv_currents = attaquant->pv_max;
}
}
else if (strcmp(tech.description, "recharge") == 0) {
// Peut être gérer de l'énergie (dans future version)
printf("%s se recharge\n", attaquant->name);
}

}

//Fonction attaquer

int attaquer(Fighter *attaquant, Fighter *cible, Technique tech) {
// Calcul dégâts
int degats = tech.value + attaquant->attack - cible->defense;

// Empêcher dégâts négatifs
if (degats < 0) degats = 0;

// Appliquer dégâts
cible->pv_currents -= degats;

// Empêcher PV négatifs
if (cible->pv_currents < 0) cible->pv_currents = 0;

// Retour PV restants
return cible->pv_currents;
}
