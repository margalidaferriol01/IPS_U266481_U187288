#include "session.h"

/**** LAB 1 - functions to program (start here) ****/
void restart_session_game(Session *session){
//La funció allibera la memòria dinàmica i reinicia els valors de "current game" a els valors per defecte
    //"session" és un punter a una Session (structure) i current_game és el Game (structure) que hi ha dins
    //Passem l'adreça de "session -> current game" perquè free_game alliberi la memòria de current_game
    //Després, passem l'adreça de "session -> current game" perquè init_game el modifiqui
    free_game(&session->current_game);
    init_game(&session->current_game);
}

void init_session(Session *s) {
    for (int i = 0; i <= MAX_LEVELS; i++) {
        s->best_score[i] = 0;
    }
    s->current_game.state.grid = NULL; 
    s->current_game.state.rows = 0;
    s->current_game.state.columns = 0;
    s->current_game.score = 0;
    s->current_game.level = 0;
}

void print_session(Session *session) {
    // Imprimim el millor resultat i cridem a print_game per mostrar l'estat actual del joc
    int lvl = session->current_game.level;  // Obtenim el nivell actual del joc
    printf("[INFO] Level #%d best score: %d\n", lvl, session->best_score[lvl]); // Imprimim el millor resultat per al nivell actual
    print_game(session->current_game); // Cridem a print_game per mostrar l'estat actual del joc
}

void new_game_score(Session *session) {
    int lvl = session->current_game.level; // Obtenim el nivell actual del joc
    int actual = session->current_game.score; // Obtenim el resultat actual del joc
    int millor = session->best_score[lvl]; // Obtenim el millor resultat guardat per al nivell actual

    // Si és la primera vegada (0) o hem millorat el rècord, actualitzem el millor resultat
    if (millor == 0 || actual < millor) {
        session->best_score[lvl] = actual;
    }
}

// LAB 2 - functions
//Passem l'adreça de s->current_game perquè free_game n'alliberi   
void free_session(Session *s){
	free_game(&s->current_game);
}