#ifndef COMBAT_H
#define COMBAT_H

#define NAME_SIZE 20
#define MAX_FIGHTERS 3
#define MAX_TECHNIQUES 3

//Structure Technique
typedef struct {
    char name[NAME_SIZE];
    int value;
    char description;
    int active_turns;
    int reload_turns;
} Technique;

//Structure Fighter
typedef struct {
    char name[NAME_SIZE];
    int currents_hp;
    int max_hp;
    int attack;
    int defense;
    int agility;
    int speed;
    Technique special[MAX_TECHNIQUES];
    int technique_count;
} Fighter;

//Structure Team
typedef struct {
    char name[NAME_SIZE];
    Fighter members[MAX_FIGHTERS];
} Team;

#endif

