#ifndef _SESSION_H_
#define _SESSION_H_ 

#include "game.h"

#define MAX_LEVELS 4

/// LAB 1 - data structure
typedef struct{
    int best_score[MAX_LEVELS+1];
    Game current_game; // LAB 1
} Session;

// LAB 1 - functions 
void restart_session_game(Session *s); // Lab 2 - refactor
void init_session(Session *s); // Lab 2 - refactor
void print_session(Session *s);
void new_game_score(Session *s);

// LAB 2 - functions
void free_session(Session *s);

#endif
