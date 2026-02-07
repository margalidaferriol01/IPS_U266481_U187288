#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "utils.h"

/// LAB 1 - macros
#define MAX_ROWS 9
#define MAX_COLUMNS 9

/// LAB 1 - data structures
typedef struct{
    int rows;
    int columns;
    char grid[MAX_ROWS][MAX_COLUMNS]; // '#' wall; '.' empty; 'G' goal location; 'A' agent; 'Y' agent at goal location;  'B' box;  'X' box at goal location
} State;

typedef struct{
    // Current score
    int score;
    // Current level;
    unsigned level;
    // State status
    State state;
} Game;

typedef enum{
    MOVE_UP = 1,
    MOVE_RIGHT = 2,
    MOVE_DOWN = 3,
    MOVE_LEFT = 4,
    SHOW_BEST_MOVE = 5,
    QUIT_GAME = 6
} Option;

/// LAB 1 - given functions
void print_options();
bool is_valid_option(Option o);
bool set_level(State *s, unsigned level);
void init_game(Game *g);
void choose_level(Game *g);

/**** LAB 1 - functions to program (start here) ****/
void print_state(State s);
void print_game(Game g);
bool is_terminal(State s); // True if all boxes are in goal locations, otherwise false
State move(State b, Option o); // move/push in one of the 4 cardinal directions
/**** LAB 1 - functions to program (end here) ****/


#endif

