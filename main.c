//Test des fonctions dans le main

int main() {
Fighter hiba = {"Hiba", 100, 100, 20, 5, 10, 10};
Fighter bot = {"Robot", 80, 80, 15, 3, 8, 8};
Technique poing = {"Coup de poing", 10, "attaque", 0, 0};

utiliser_technique(&hiba, &bot, poing);
printf("PV restants du Robot : %d\n", bot.pv_currents);

return 0;
}
