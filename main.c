//Test des fonctions dans le main

int main() {
Combattant joueur1 = {"Player", 100, 100, 20, 5, 10, 10};
Combattant joueur2 = {"Robot", 80, 80, 15, 3, 8, 8};
Technique poing = {"Coup de poing", 10, "attaque", 0, 0};

utiliser_technique(&joueur1, &joueur2, poing);
printf("PV restants du Robot : %d\n", bot.pv_courants);

return 0;
}
