#include "session.h"

/**** LAB 1 - functions to program (start here) ****/
void restart_session_game(Session *session){
//we use the function init_game to reset the current game to default values
//"Session" and "Game" are data structures "session" is a pointer that refers to a Session where "current_game" is stored
//"&session -> current game" gets the adress of current_game so that init_game can modify it
    init_game(&session->current_game);
}

void init_session(Session *session){
    for (int level=0; level<=MAX_LEVELS;++level){
        session -> best_score[level]=0;
    }
    restart_session_game(session);
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
/**** LAB 1 - functions to program (end here) ****/
