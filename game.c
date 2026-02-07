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
//This function prints the game state which is the grid for the level selected by the player
    for (int i = 0; i <s.rows; ++i) { //goes through every element stored in variable row
        for (int j = 0; j<s.columns; ++j) { //goes through every element stored in variable column
            printf("%c",s.grid[i][j]); //prints the character at position [i][j]
            }
        printf("\n"); //moves to the next line after each row
    }
}

void print_game(Game game){
    printf("[INFO] Level #%d current score:%d\n",game.level,game.score); //prints current "level" and "score" stored in data structure "game"
    print_state(game.state); //prints the current grid
}

bool is_terminal(State s) {
    // El joc s'acaba quan no queden objectius ('G') ni l'agent sobre un objectiu ('Y')
    for (int i = 0; i < s.rows; i++) {
        for (int j = 0; j < s.columns; j++) {
            if (s.grid[i][j] == 'G' || s.grid[i][j] == 'Y') {
                return false; // Encara falta col·locar alguna caixa
            }
        }
    }
    return true; // Totes les caixes estan al seu lloc
}
State move(State s, Option o) {
    int r, c;
    int dr = 0, dc = 0; // Variables per la direcció: dr (fila), dc (columna)

    // 1. Busquem la posició actual de l'agent ('A' o 'Y')
    for (int i = 0; i < s.rows; i++) {
        for (int j = 0; j < s.columns; j++) {
            if (s.grid[i][j] == 'A' || s.grid[i][j] == 'Y') {
                r = i; c = j;
            }
        }
    }

    // 2. Determinem el moviment segons l'opció triada (Up, Down, Left, Right)
    if (o == MOVE_UP){
        dr = -1;
    }         
    else if (o == MOVE_DOWN){ 
        dr = 1;
    } else if (o == MOVE_LEFT){
        dc = -1;
    } else if (o == MOVE_RIGHT) {
        dc = 1;
    }

    // 3. Calculem on volem anar (next) i on aniria una caixa si l'empenyem (box_next)
    int nr = r + dr;
    int nc = c + dc;
    int nnr = nr + dr;
    int nnc = nc + dc;

    char desti = s.grid[nr][nc];

    // 4. Lògica de col·lisions i moviments
    if (desti == '#') {
        return s; // Si és una paret, no fem res
    }

    // Cas A: La casella de destí és buida o un objectiu
    if (desti == '.' || desti == 'G') {
    // 1. L'AGENT MARXA de la casella on estava (r, c)
    if (s.grid[r][c] == 'Y') {
        s.grid[r][c] = 'G'; // Si l'agent estava sobre un objectiu, hi deixa el punt de l'objectiu [cite: 66]
    } else {
        s.grid[r][c] = '.'; // Si no, deixa la casella buida [cite: 60, 63]
    }

    // 2. L'AGENT ARRIBA a la nova casella (nr, nc)
    if (desti == 'G') {
        s.grid[nr][nc] = 'Y'; // Si on va és un objectiu, l'agent es dibuixa com 'Y' [cite: 66]
    } else {
        s.grid[nr][nc] = 'A'; // Si és un lloc buit, es dibuixa com 'A' [cite: 60]
    }
}
    // Cas B: Hi ha una caixa i mirem si podem empènyer-la
    else if (desti == 'B' || desti == 'X') {
    char darrere = s.grid[nnr][nnc]; // Mirem què hi ha darrere la caixa

    if (darrere == '.' || darrere == 'G') {
        // 1. MOVEM LA CAIXA al lloc de darrere (nnr, nnc)
        if (darrere == 'G') {
            s.grid[nnr][nnc] = 'X'; // Caixa sobre objectiu [cite: 65]
        } else {
            s.grid[nnr][nnc] = 'B'; // Caixa sobre terra [cite: 61]
        }

        // 2. L'AGENT OCUPA EL LLOC DE LA CAIXA (nr, nc)
        if (desti == 'X') {
            s.grid[nr][nc] = 'Y'; // L'agent ara trepitja l'objectiu on hi havia la caixa [cite: 66]
        } else {
            s.grid[nr][nc] = 'A'; // L'agent ara trepitja terra [cite: 60]
        }

        // 3. L'AGENT DEIXA EL SEU LLOC ORIGINAL (r, c)
        if (s.grid[r][c] == 'Y') {
            s.grid[r][c] = 'G';
        } else {
            s.grid[r][c] = '.';
        }
    }
}

    return s;
}


/**** LAB 1 - functions to program (end here) ****/

