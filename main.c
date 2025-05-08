//Test des fonctions dans le main

int main() {


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fight.h"

 int main ()

 {
     char answer[10];
     Combattant equipe[3] ,adverse[3] ;
     afficher_lobby();
     affichage();
     start:
     afficher_menu();
     printf(BOLD GREEN "\n╔══════════════════════════════════════════╗\n");
printf("║        🔷 SELECTION DE TON EQUIPE 🔷        ║\n");
     choisir_equipe(equipe);
system("cls");
afficher_menu();
     printf(BOLD RED "\n╔══════════════════════════════════════════╗\n");
printf("║     🔺 SELECTION DE L’EQUIPE ADVERSE 🔺     ║\n");
     choisir_equipe(adverse);
     system("cls");
afficher_equipes(equipe,adverse);
system("cls");
lancer_combat_equipes(equipe,adverse);

printf("\n" BOLD CYAN "🔁 Souhaites-tu lancer une autre partie de " BOLD YELLOW "Naruto Storm" BOLD CYAN " ? (o/n)\n" RESET);
scanf("%d",answer);

if(strcmp(answer ,"yes")== 0)
{
    goto start;
}


return 0;
 }



return 0;
}
