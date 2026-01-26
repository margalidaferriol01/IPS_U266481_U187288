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

void save_game(Session *session){
    // ToDo in Lab 2
}

void load_game(Session *session){
    // ToDo in Lab 2
}

void resume_game(Session *session){
    // ToDo in Lab 2
}

void print_menu(){
    printf("[INFO] Menu options:\n");
    printf("\t1. New game.\n");  // LAB1 - basic lab for playing the game
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
}

int main(){
    Session session;
    init_session(&session);
    run(&session);
}
