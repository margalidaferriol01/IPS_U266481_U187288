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
        printf("[INFO]: loading level #%d\n", level);
        s->rows = 3;
        s->columns = 8;
        s->grid = make_grid(s->rows, s->columns+1);
        strcpy(s->grid[0], "########");
        strcpy(s->grid[1], "#.A.B.G#");
        strcpy(s->grid[2], "########");
        break;
    case 2:
        printf("[INFO]: loading level #%d\n", level);
        s->rows = 5;
        s->columns = 8;
        s->grid = make_grid(s->rows, s->columns+1);
        strcpy(s->grid[0], "########");
        strcpy(s->grid[1], "#....###");
        strcpy(s->grid[2], "#.B#.#A#");
        strcpy(s->grid[3], "#..B.GG#");
        strcpy(s->grid[4], "########");
        break;
    case 3:
        printf("[INFO]: loading level #%d\n", level);
        s->rows = 7;
        s->columns = 7;
        s->grid = make_grid(s->rows, s->columns+1);
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
        s->grid = make_grid(s->rows, s->columns+1);
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
    // LAB 1
    /*
    game->state.rows = MAX_ROWS;
    game->state.columns = MAX_COLUMNS;
    for(int i=0; i<MAX_ROWS; ++i)
        for(int j=0; j<MAX_COLUMNS; ++j)
            game->state.grid[i][j] = '.';
    */
    // LAB 2
    game->state.rows = 0;
    game->state.columns = 0;
    game->state.grid = NULL;
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
//Imprimeix l'estat del joc, el "grid" corresponent segons el nivell seleccionat pel jugador
    for (int i = 0; i <s.rows; ++i) { //Recorre totes les files
        for (int j = 0; j<s.columns; ++j) { //Recorre totes les columnes
            printf("%c",s.grid[i][j]); //Imprimeix el caràcter guardat a la posició [i][j]
            }
        printf("\n"); //Passa a la següent línia al final de cada fila 
    }
}

void print_game(Game game){
    //Imprimeix el "level" i "score" guardats a l'estructura de dades "game"
    printf("[INFO] Level #%d current score:%d\n",game.level,game.score); 
    //Imprimeix la taula actual
    print_state(game.state); 
}

bool is_terminal(State s) {
    //El joc s'acaba quan no queden objectius ('G') ni l'agent sobre un objectiu ('Y')
    for (int i = 0; i < s.rows; i++) { //Recorrem cada fila 
        for (int j = 0; j < s.columns; j++) { //Recorrem cada columna
            if (s.grid[i][j] == 'G' || s.grid[i][j] == 'Y') { //Si trobem un objectiu o un agent sobre un objectiu, el joc no ha acabat
                return false; //Encara falta col·locar alguna caixa
            }
        }
    }
    return true; //Totes les caixes estan al seu lloc
}
State move(State s, Option o) {
    int r, c; //Variables per a la posició actual de l'agent: row (fila), column (columna)
    int dr = 0, dc = 0; //Variables per la direcció: drow (fila), dcolumn (columna)

    //1. Cercam la posició actual de l'agent ('A' o 'Y')
    for (int i = 0; i < s.rows; i++) { //Recorrem cada fila
        for (int j = 0; j < s.columns; j++) { //Recorrem cada columna
            if (s.grid[i][j] == 'A' || s.grid[i][j] == 'Y') { //Si trobam l'agent, guardam la seva posició
                r = i; c = j; //Guardam la posició de l'agent
            }
        }
    }

    //2. Determinam el moviment segons l'opció triada (Up, Down, Left, Right)
    if (o == MOVE_UP){
        dr = -1; //Si volem moure cap amunt, la fila disminueix
    }         
    else if (o == MOVE_DOWN){ 
        dr = 1; //Si volem moure cap avall, la fila augmenta
    } 
    else if (o == MOVE_LEFT){
        dc = -1; //Si volem moure cap a l'esquerra, la columna disminueix
    } 
    else if (o == MOVE_RIGHT) {
        dc = 1; //Si volem moure cap a la dreta, la columna augmenta
    }

    //3. Calculam on volem anar (next) i on aniria una caixa si l'empenyem (box_next)
    int nr = r + dr; //La nova fila on volem anar
    int nc = c + dc; //La nova columna on volem anar
    int nnr = nr + dr; //La fila on aniria la caixa si l'empenyem
    int nnc = nc + dc; //La columna on aniria la caixa si l'empenyem

    char desti = s.grid[nr][nc]; //El que hi ha a la casella de destí (on volem anar)

    //4. Lògica de col·lisions i moviments
    if (desti == '#') {
        return s; //Si és una paret, no feim res
    }

    //Cas A: La casella de destí és buida o un objectiu
    if (desti == '.' || desti == 'G') {
    //1. L'agent marxa de la casella on estava (r, c)
    if (s.grid[r][c] == 'Y') { //Si l'agent estava sobre un objectiu, el deixam com a 'G'
        s.grid[r][c] = 'G'; //Si l'agent estava sobre un objectiu, hi deixa el punt de l'objectiu 
    } 
    else {
        s.grid[r][c] = '.'; //Si no, deixa la casella buida
    }

    //2. L'agent arriba a la nova casella (nr, nc)
    if (desti == 'G') { 
        s.grid[nr][nc] = 'Y'; //Si on va és un objectiu, l'agent es dibuixa com 'Y' 
    } 
    else {
        s.grid[nr][nc] = 'A'; //Si és un lloc buit, es dibuixa com 'A' 
    }
}
    //Cas B: Hi ha una caixa i miram si podem empènyer
    else if (desti == 'B' || desti == 'X') { //Si hi ha una caixa, miram què hi ha darrere
    char darrere = s.grid[nnr][nnc]; //El que hi ha a la casella darrere de la caixa (on aniria si l'empenyem)

    if (darrere == '.' || darrere == 'G') {
        //1. Movem la caixa al lloc de darrere (nnr, nnc)
        if (darrere == 'G') {
            s.grid[nnr][nnc] = 'X'; //Caixa sobre objectiu
        } 
        else {
            s.grid[nnr][nnc] = 'B'; //Caixa sobre terra 
        }

        //2. L'agent ocupa el lloc de la caixa (nr, nc)
        if (desti == 'X') {
            s.grid[nr][nc] = 'Y'; //L'agent ara trepitja l'objectiu on hi havia la caixa 
        } 
        else {
            s.grid[nr][nc] = 'A'; //L'agent ara trepitja terra on hi havia la caixa 
        }

        //3. L'agent deixa el seu lloc original (r, c)
        if (s.grid[r][c] == 'Y') { //Si l'agent estava sobre un objectiu, el deixam com a 'G'
            s.grid[r][c] = 'G';
        } 
        else {
            s.grid[r][c] = '.'; //Si no, deixa la casella buida
        }
    }
}

    return s; //Retornam l'estat actualitzat després del moviment o intent de moviment
}


/**** LAB 1 - functions to program (end here) ****/

/**** LAB 2 - functions to program (start here) ****/
/**** LAB 2 - functions to program (start here) ****/
void free_state(State *s){ //s es el punter a State,  amb aquet funcio podem modificar estat original.
    if(s->grid != NULL){// Alliberem la memoria si No es null
        for (int i=0; i < s->rows; i++){ // amb bucle for, recorrem les files.
            free(s->grid[i]);//alliberem fila i 
        }
        free(s->grid);// alliber, l'array principal de punters
        s->grid=NULL;// posem punter a null per evitar els punters penjats
    }
    s->rows=0; // reiniciar fila
    s->columns =0; // reiniciar columna
    
}

void free_game(Game *g){
    g->score =0;// reiniciar dades
    g->level =0;// reiniciar el nivell
    free_state(&g->state); // alliberar el grd cridat la funcio anteriro 
}

char** make_grid(int rows, int columns){
    char **grid=malloc(rows*sizeof(char*));// entrem al punter de la fila i revisar.
    for(int i = 0;i<rows;i++){ //amb for bucle, rerrem cada fila.
        grid[i]=malloc (columns * sizeof (char));// a cada fila revisa memoria de columna
    }
    return grid;// retorna amb la matriu creada
}
/**** LAB 2 - functions to program (end here) ****/

