#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "utils.h"

/// LAB 1 - macros
// #define MAX_ROWS 9 // removed in LAB 2
// #define MAX_COLUMNS 9 // removed in LAB 2

/// LAB 1 - data structures
typedef struct{
    int rows;
    int columns;
    //char grid[MAX_ROWS][MAX_COLUMNS]; // removed in LAB 2
    char **grid; // '#' wall; '.' empty; 'G' goal location; 'A' agent; 'Y' agent at goal location;  'B' box;  'X' box at goal location
} State;

typedef struct{    
    int score; // The score in the current game
    unsigned level; // The current level game
    State state; // The current state info (rows x cols, and grid)
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
bool set_level(State *s, unsigned level); // Refactored in Lab 2
void init_game(Game *g);  // Refactored in Lab 2
void choose_level(Game *g);


/**** LAB 1 - functions to program (start here) ****/
void print_state(State s);
void print_game(Game g);
bool is_terminal(State s); // True if all boxes are in goal locations, otherwise false
State move(State b, Option o); // move/push in one of the 4 cardinal directions
/**** LAB 1 - functions to program (end here) ****/


/**** LAB 2 - functions to program (start here) ****/
void free_state(State *s);
void free_game(Game *g);
char** make_grid(int rows, int columns);
/**** LAB 2 - functions to program (end here) ****/


#endif

