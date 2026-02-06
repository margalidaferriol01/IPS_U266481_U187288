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
    // Mirem si queda algun punt de destí ('G') sense caixa [cite: 118]
    for (int i = 0; i < s.rows; i++) {
        for (int j = 0; j < s.columns; j++) {
            // Si hi ha un 'G' (destí buit) o 'Y' (agent sobre destí), no hem acabat 
            if (s.grid[i][j] == 'G' || s.grid[i][j] == 'Y') {
                return false;
            }
        }
    }
    return true; 
}

State move(State s, Option o) {
    int r, c;
    // Busquem on està l'agent ara mateix [cite: 60, 66]
    for (int i = 0; i < s.rows; i++) {
        for (int j = 0; j < s.columns; j++) {
            if (s.grid[i][j] == 'A' || s.grid[i][j] == 'Y') {
                r = i; c = j;
            }
        }
    }

    // Calculem la casella on volem anar (nr, nc) 
    int nr = r, nc = c;
    if (o == MOVE_UP)    nr = r - 1;
    else if (o == MOVE_DOWN)  nr = r + 1;
    else if (o == MOVE_LEFT)  nc = c - 1;
    else if (o == MOVE_RIGHT) nc = c + 1;

    // Què hi ha on volem anar? 
    char desti = s.grid[nr][nc];

    // Cas senzill: Casella buida o objectiu buit 
    if (desti == '.' || desti == 'G') {
        // L'agent marxa: si estava sobre un objectiu, hi deixa la 'G' 
        if (s.grid[r][c] == 'Y') s.grid[r][c] = 'G';
        else s.grid[r][c] = '.';
        
        // L'agent arriba: si el destí era 'G', es converteix en 'Y' 
        if (desti == 'G') s.grid[nr][nc] = 'Y';
        else s.grid[nr][nc] = 'A';
    } 
    // Cas caixa: Volem empènyer 
    else if (desti == 'B' || desti == 'X') {
        // Calculem la casella que hi ha darrere la caixa (nnr, nnc) 
        int nnr = nr + (nr - r);
        int nnc = nc + (nc - c);
        char darrere = s.grid[nnr][nnc];

        // Si darrere la caixa hi ha lloc, empenyem 
        if (darrere == '.' || darrere == 'G') {
            // Movem la caixa al seu nou lloc 
            if (darrere == 'G') s.grid[nnr][nnc] = 'X';
            else s.grid[nnr][nnc] = 'B';

            // L'agent es mou a on estava la caixa
            if (desti == 'X') s.grid[nr][nc] = 'Y';
            else s.grid[nr][nc] = 'A';

            // L'agent marxa del seu lloc original 
            if (s.grid[r][c] == 'Y') s.grid[r][c] = 'G';
            else s.grid[r][c] = '.';
        }
    }
    return s;
}

/**** LAB 1 - functions to program (end here) ****/

