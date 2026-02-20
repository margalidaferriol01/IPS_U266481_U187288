#include "main.h"

void run_game(Session *session){
    Game *game = &session->current_game;

    do{
        print_session(session);

        Option game_option;
        do{
            print_options();
            printf("[INFO] Enter a game option [%d-%d]: ", MOVE_UP, QUIT_GAME);
            game_option = read_int();
        }while(!is_valid_option(game_option));
        
        switch(game_option){
            case MOVE_UP:
            case MOVE_RIGHT:
            case MOVE_DOWN:
            case MOVE_LEFT:
                game->state = move(game->state, game_option);
                game->score++;
                break;
            case SHOW_BEST_MOVE:
                // ToDo in Lab 3
                break;
            case QUIT_GAME:
                printf("[INFO] QUIT GAME!\n");
                return;
        }
        
    }while(!is_terminal(game->state));
    
    new_game_score(session);
    print_session(session);
    printf("[INFO] LEVEL COMPLETED!!!\n");
}

void new_game(Session *session){
    restart_session_game(session);
    choose_level(&(session->current_game));
    run_game(session);
}


/**
 * Guarda la partida actual en un fitxer de text.
 * Segueix el format: Score, Level, State (rows, columns i la graella).
 */
void save_game(Session *session) {
    char filename[MAX_STR_LENGTH];
    
    // Demanem el nom del fitxer a l'usuari
    printf("[INFO] Enter the filename to save: ");
    read_filename(filename);

    // Obrim el fitxer en mode "w" (write/escriptura). 
    // Si el fitxer no existeix, es crea; si existeix, se sobreescriu.
    FILE *f = fopen(filename, "w");
    
    // Comprovem si el fitxer s'ha obert correctament (punter no nul)
    if (f == NULL) {
        printf("[ERROR] Could not open file %s for writing\n", filename);
        return;
    }

    // Escrivim les dades de la sessió amb fprintf (format de sortida a fitxer)
    // Accedim a les dades usant l'operador fletxa -> perquè session és un punter
    fprintf(f, "Score: %d\n", session->current_game.score);
    fprintf(f, "Level: %u\n", session->current_game.level);
    fprintf(f, "State:\n");
    fprintf(f, "rows: %d\n", session->current_game.state.rows);
    fprintf(f, "columns: %d\n", session->current_game.state.columns);

    // Recorrem les files de la graella dinàmica per guardar-les
    for (int i = 0; i < session->current_game.state.rows; i++) {
        // Escrivim cada fila com una cadena de caràcters seguida d'un salt de línia
        fprintf(f, "%s\n", session->current_game.state.grid[i]);
    }

    // Tanquem el fitxer per alliberar el recurs del sistema
    fclose(f);
    printf("[INFO] Game saved in %s\n", filename);
}

/**
 * Carrega una partida des d'un fitxer.
 * Allibera la memòria actual abans de reservar l'espai necessari per al nou mapa.
 */
void load_game(Session *session) {
    char filename[MAX_STR_LENGTH];
    
    printf("[INFO] Enter the filename to load: ");
    read_filename(filename);

    // Obrim el fitxer en mode "r" (read/lectura)
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("[ERROR] File %s not found\n", filename);
        return;
    }

    // Pas 1: Molt important! Alliberem la memòria de la partida actual 
    // per evitar "memory leaks" abans de carregar la nova.
    free_game(&session->current_game);

    // Pas 2: Llegim les dades estructurades amb fscanf
    // El format dins de " " ha de coincidir exactament amb el del fitxer
    int r, c;
    fscanf(f, "Score: %d\n", &session->current_game.score);
    fscanf(f, "Level: %u\n", &session->current_game.level);
    fscanf(f, "State:\n");
    fscanf(f, "rows: %d\n", &r);
    fscanf(f, "columns: %d\n", &c);

    // Pas 3: Actualitzem les dimensions i reservem memòria dinàmica
    // Cridem a make_grid (funció de game.c) que fa el malloc
    session->current_game.state.rows = r;
    session->current_game.state.columns = c;
    session->current_game.state.grid = make_grid(r, c+1); // +1 per al caràcter de final de cadena '\0' en cada fila

    // Pas 4: Llegim la graella caràcter a caràcter o línia a línia
    for (int i = 0; i < r; i++) {
        fscanf(f, "%s\n", session->current_game.state.grid[i]);
    }

    // Tanquem el fitxer
    fclose(f);
    printf("[INFO] Game loaded from %s\n", filename);
}

/**
 * Reprèn la partida que hi ha actualment en memòria.
 * No permet reprendre si el joc ja ha acabat (estat terminal).
 */
void resume_game(Session *session) {
    // Verifiquem si tenim un nivell carregat (level > 0)
    if (session->current_game.level == 0) {
        printf("[ERROR] No game in memory to resume!\n");
        return;
    }

    // Comprovem si l'estat és terminal (totes les caixes a l'objectiu)
    // is_terminal és una funció que rep l'estat per valor
    if (is_terminal(session->current_game.state)) {
        printf("[INFO] The game is already finished. Start a new one!\n");
    } else {
        // Si no ha acabat, cridem al bucle principal del joc
        run_game(session);
    }
}

void print_menu(){
    printf("[INFO] Menu options:\n");
    printf("\t1. New game.\n");  // LAB1 - basic lab for creating grid and moves
    printf("\t2. Save game.\n"); // LAB2 - Writing file
    printf("\t3. Load game.\n"); // LAB2 - Reading file
    printf("\t4. Resume game.\n"); // LAB2 - Continue game after reading file
    printf("\t5. Exit.\n");  // Free all reserved memory!
}


void run(Session *session){
    int option;
    do{
        print_menu();
        do{
            printf("[INFO] Enter an integer [%d-%d]: ", NEW_GAME, EXIT);
            option = read_int();
        }while(option < NEW_GAME || option > EXIT);

        switch (option){
        case NEW_GAME:
            new_game(session);
            break;
        case SAVE_GAME:
            save_game(session);
            break;
        case LOAD_GAME:
            load_game(session);
            break;
        case RESUME_GAME:
            resume_game(session);
            break;
        case EXIT:
            break;
        }
    }while(option != EXIT);
    
    // Lab 2
    free_session(session);
}

int main(){
    Session session;
    init_session(&session);
    run(&session);
}
