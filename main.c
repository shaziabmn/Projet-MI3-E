//Test des fonctions dans le main

int main() {
Fighter Player = {"Player", 100, 100, 20, 5, 10, 10};
Fighter bot2 = {"Robot", 80, 80, 15, 3, 8, 8};
Technique poing = {"Coup de poing", 10, "attaque", 0, 0};

utiliser_technique(&Player, &bot2, poing);
printf("PV restants du Robot : %d\n", bot.pv_currents);

return 0;
}
