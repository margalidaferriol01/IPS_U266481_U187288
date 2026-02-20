#include "session.h"

/**** LAB 1 - functions to program (start here) ****/
void restart_session_game(Session *session){
//La funció reinicia els valors de "current game" a els valors per defecte
    //"session" és un punter a una Session (structure) i current_game és el Game (structure) que hi ha dins
    //Passem l'adreça de "session -> current game" perquè init_game el modifiqui
    init_game(&session->current_game);
    // ToDo - Lab 1 & refactor in Lab 2
}

void init_session(Session *session){
//Torna a 0 el "best_score" i reinicia el joc actual amb restart_session_game
    for (int level=0; level<=MAX_LEVELS;++level){ //Recorre els nivells, de 0 a max fixat a les macros
        session -> best_score[level]=0; //Deixa la "best score" de cada nivell a 0, així reinicies el marcador
    }
    restart_session_game(session); //Crida la funció restart_session_game
    // ToDo - Lab 1 & refactor in Lab 2
}

void print_session(Session *session) {
    //Imprimim el millor resultat i cridem a print_game per mostrar l'estat actual del joc
    int lvl = session->current_game.level; //Obtenim el nivell actual del joc
    printf("[INFO] Level #%d best score: %d\n", lvl, session->best_score[lvl]); //Imprimim el millor resultat per al nivell actual
    print_game(session->current_game); //Cridem a print_game per mostrar l'estat actual del joc
}

void new_game_score(Session *session) {
    int lvl = session->current_game.level; //Obtenim el nivell actual del joc
    int actual = session->current_game.score; //Obtenim el resultat actual del joc
    int millor = session->best_score[lvl]; //Obtenim el millor resultat guardat per al nivell actual

    //Si és la primera vegada (0) o hem millorat el rècord, actualitzem el millor resultat
    if (millor == 0 || actual < millor) {
        session->best_score[lvl] = actual;
    }
}
/**** LAB 1 - functions to program (end here) ****/

// LAB 2 - functions
void free_session(Session *s){
	// ToDo - Lab 2
}