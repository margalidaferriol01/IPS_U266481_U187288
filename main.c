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


// Guarda la partida actual en un fitxer de text i segueix el format: Score, Level, State (rows, columns i la graella).
void save_game(Session *session) {
    char filename[50]; // Creem un espai per guardar el nom que li posaràs al fitxer
    
    printf("Escriu el nom del fitxer per guardar la partida: ");
    read_filename(filename); // Llegim el nom que has escrit (ex: "partida1.txt")

    // Intentem obrir el fitxer per escriure-hi ("w" de write)
    FILE *f = fopen(filename, "w");
    
    // Si per algun motiu no es pot obrir, sortim
    if (f == NULL) {
        printf("Error: No s'ha pogut crear el fitxer.\n");
        return;
    }

    // Comencem a escriure les dades tal com diu l'enunciat:
    //Fem servir fprintf, que és igual que el printf però envia el text al fitxer 'f'
    fprintf(f, "Score: %d\n", session->current_game.score);
    fprintf(f, "Level: %u\n", session->current_game.level);
    fprintf(f, "State:\n");
    fprintf(f, "rows: %d\n", session->current_game.state.rows);
    fprintf(f, "columns: %d\n", session->current_game.state.columns);

    // Ara hem d'escriure el mapa (la graella) fila per fila
    for (int i = 0; i < session->current_game.state.rows; i++) {
        // Escrivim cada fila com una paraula completa i fem un salt de línia
        fprintf(f, "%s\n", session->current_game.state.grid[i]);
    }

    // Tanquem el fitxer en acabar per guardar els canvis
    fclose(f);
    printf("Partida guardada correctament!\n");
}

// Carrega una partida des d'un fitxer i allibera la memòria actual abans de reservar l'espai necessari per al nou mapa.
void load_game(Session *session) {
    // Definim una cadena de caràcters per guardar el nom del fitxer
    char filename[50]; 
    
    // Mostrem un missatge per pantalla demanant el nom a l'usuari
    printf("Quin fitxer vols carregar?: "); 
    
    // Utilitzem la funció per llegir el text que escrigui l'usuari
    read_filename(filename); 

    // Intentem obrir el fitxer indicat en mode lectura ("r" de read)
    FILE *f = fopen(filename, "r"); 
    
    // Comprovem si el fitxer existeix; si fopen retorna NULL, és que no s'ha pogut obrir
    if (f == NULL) { 
        // Avisem de l'error i sortim de la funció per evitar que el programa peti
        printf("Error: No s'ha trobat el fitxer.\n"); 
        return; 
    }

    // Abans de carregar res, "netegem" la memòria de la partida d'abans
    // Així evitem que el programa s' o es quedi sense espai si carreguem un mapa més gran que l'anterior
    free_game(&session->current_game);

    // Llegim les dades del fitxer fent servir fscanf. Aquest funciona igual que el scanf però llegeix des del fitxer 'f' en lloc de des de la consola.
    int r, c;
    fscanf(f, "Score: %d\n", &session->current_game.score);
    fscanf(f, "Level: %u\n", &session->current_game.level);
    fscanf(f, "State:\n");
    fscanf(f, "rows: %d\n", &r);
    fscanf(f, "columns: %d\n", &c);

    // Ara que sabem quantes files (r) i columnes (c) té el mapa nou, demanem memòria dinàmica per a la nova graella
    session->current_game.state.rows = r;
    session->current_game.state.columns = c;
    
    // Fem servir el "make_grid" per reservar l'espai. 
    // Posem c+1 per deixar un forat extra pel caràcter invisible que marca el final de la línia.
    session->current_game.state.grid = make_grid(r, c + 1);

    // Finalment, llegim el mapa del fitxer i el posem a la memòria
    for (int i = 0; i < r; i++) {
        fscanf(f, "%s\n", session->current_game.state.grid[i]);
    }

    fclose(f); // Tanquem el fitxer
    printf("Partida carregada! Ja pots continuar jugant.\n");
}

// Reprèn la partida que hi ha actualment en memòria i no permet reprendre si el joc ja ha acabat (estat terminal).
void resume_game(Session *session) {
    // Si el nivell és 0, vol dir que no hem carregat res encara
    if (session->current_game.level == 0) {
        printf("Error: No hi ha cap partida per continuar.\n");
        return;
    }

    // Si ja hem guanyat (totes les caixes a lloc), no deixem reprendre
    if (is_terminal(session->current_game.state)) {
        printf("Aquesta partida ja ha acabat!\n");
    } 
    else {
        // Si tot està bé, cridem a run_game per tornar a jugar
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
