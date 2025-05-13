# CY-Fighters

**Projet de programmation en langage C** – préING1 MI3-E 2024–2025
- Développé par : Shazia ABDOULRAHIMANE, Hiba FIGUIGUI et Wahiba TALANTIKITE
- Encadrante : Marwa BEN ABDESSALEM

---

## Description

**CY-Fighters** est un jeu de combat tactique au tour par tour, 100 % codé en C, dans lequel deux équipes s'affrontent jusqu’à la dernière attaque !

Chaque joueur compose une équipe de **3 combattants** parmi une sélection personnalisée, et affronte son adversaire dans une bataille rythmée par la **vitesse**, les **statistiques**, et les **techniques spéciales**.

### Votre mission :
**Battre l’équipe adverse en exploitant les faiblesses et les effets des techniques !**

---

## Fonctionnalités

- **Chargement dynamique** des combattants et techniques depuis des fichiers `.txt`
- **Interface terminal** avec menus stylisés, couleurs et emojis
- **Combat en tour par tour** : l’ordre des actions dépend de la **vitesse**
- **Techniques spéciales** : dégâts, soins, buffs, débuffs, recharge
- **Système de tours alternés** : une attaque par tour, selon le combattant le plus rapide
- **Arrêt automatique** du combat dès qu’une équipe est entièrement KO
- **Architecture modulaire** pour un code clair et maintenable

---

## Fichiers du projet

- `main.c` – Menu principal, lancement du jeu, affichage des équipes
- `combat.c` – Moteur de combat : gestion des tours, attaques, techniques, fin de partie
- `interface.c` – Affichage terminal avec couleurs, emojis et menus
- `combat.h` – Déclarations des fonctions et structures liées au combat
- `interface.h` – Déclarations liées à l’affichage et aux menus
- `combattants.txt` – Liste des combattants (stats, techniques associées)
- `makefile` – Compilation automatisée du projet

---

## Compilation et exécution

**Dans un terminal :**

- cd projet 
- make clean 
- make 
- ./jeu

Et que le combat commence !!



**Répartition des rôles**

- Shazia Abdoulrahimane : Structures et chargement des données (Technique, Combattant, Joueur, fichiers .txt, Makefile) + Contribution pour l'interface et la gestion de l'utilisation de la technique spéciale

- Hiba Figuigui : Développement du moteur de combat (fonctions d’attaque, effets, tours) + Contribution dans la logique du jeu 

- Wahiba Talantikite : Interface terminale et logique de jeu (main.c, menus, boucle de jeu)

- Travail commun : gestion des fichiers, relecture du code, corrections, Readme.md et rapport écrit.



**Remerciements**

Merci à notre encadrante Marwa Ben Abdessalem pour son accompagnement, sa bienveillance et ses retours constructifs tout au long du projet !
