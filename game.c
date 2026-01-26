#include "game.h"


/**** LAB 1 - given functions ****/
void print_options(){
    printf("Options:\n");
    printf("\t%d. Up | %d. Right | %d. Down | %d. Left |\n", MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT);
    printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
    printf("\t%d. Quit game\n", QUIT_GAME);
}

bool is_valid_option(Option o){
    return ((MOVE_UP <= o) && (o<=QUIT_GAME));
}

bool set_level(State *s, unsigned level){
   switch(level){
    case 1:
        s->rows = 3;
        s->columns = 8;
        strcpy(s->grid[0], "########");
        strcpy(s->grid[1], "#.A.B.G#");
        strcpy(s->grid[2], "########");
        break;
    case 2:
        s->rows = 5;
        s->columns = 8;
        strcpy(s->grid[0], "########");
        strcpy(s->grid[1], "#....###");
        strcpy(s->grid[2], "#.B#.#A#");
        strcpy(s->grid[3], "#..B.GG#");
        strcpy(s->grid[4], "########");
        break;
    case 3:
        s->rows = 7;
        s->columns = 7;
        strcpy(s->grid[0], "#######");
        strcpy(s->grid[1], "###G###");
        strcpy(s->grid[2], "###B###");
        strcpy(s->grid[3], "#GBABG#");
        strcpy(s->grid[4], "###B###");
        strcpy(s->grid[5], "###G###");;
        strcpy(s->grid[6], "#######");
        break;
    case 4:
        printf("[INFO]: loading level #%d\n", level);
        s->rows = 6;
        s->columns = 8;
        strcpy(s->grid[0], "#######.");
        strcpy(s->grid[1], "#.B.AG##");
        strcpy(s->grid[2], "#.XXG..#");
        strcpy(s->grid[3], "#....B.#");
        strcpy(s->grid[4], "#..#####");
        strcpy(s->grid[5], "####....");
        break;
    default:
        printf("[ERROR]: level not found!\n");
        return false;
   };
   
   return true;
}

void init_game(Game *game){
    game->score = 0;
    game->level = 0;
    game->state.rows = MAX_ROWS;
    game->state.columns = MAX_COLUMNS;
    for(int i=0; i<MAX_ROWS; ++i)
        for(int j=0; j<MAX_COLUMNS; ++j)
            game->state.grid[i][j] = '.';
}

void choose_level(Game *game){
    game->score = 0;    
    do{
        printf("[INFO] Choose the level [1-4]: ");
        game->level = read_int();
    }while(!set_level(&game->state, game->level));
}


/**** LAB 1 - functions to program (start here) ****/
void print_state(State s){
    // ToDo
}

void print_game(Game game){
    // ToDo
}


bool is_terminal(State s){
    // ToDo
    return false;
}

State move(State s, Option o){
    // ToDo
    return s;
}

/**** LAB 1 - functions to program (end here) ****/

