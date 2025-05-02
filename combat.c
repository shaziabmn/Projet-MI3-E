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
attaquant->currents_hp += tech.value;
if (attaquant->currents_hp > attaquant->max_hp) {
attaquant->currents_hp = attaquant->max_hp;
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
cible->currents_hp -= degats;

// Empêcher HP négatifs
if (cible->currents_hp < 0) cible->currents_hp = 0;

// Retour HP restants
return cible->currents_hp;
}
