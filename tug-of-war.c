#include <stdio.h>
#include <conio.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define SCREEN_CENTER_X SCREEN_WIDTH / 2
#define SCREEN_CENTER_Y SCREEN_HEIGHT / 2 // Integer division

#define HIDE_CURSOR gotoxy(SCREEN_WIDTH, SCREEN_HEIGHT)

void display_title_screen() {
    clrscr();
    
    gotoxy(1, 11);
    printf("                   _                   ___\n");
    printf(" _ ___ ___ ___ ___| |_ _ _ ___ ___ ___|  _|___ _ _ _ ___ ___ ___ ___ ___ ___ __\n");
    printf(" _|___|___|___|___|  _| | | . |___| . |  _|___| | | | .'|  _|___|___|___|___|__\n");
    printf("                  |_| |___|_  |   |___|_|     |_____|__,|_|\n");
    printf("                          |___|\n");
    
    gotoxy(27, 17);
    printf("[ PRESS ANY KEY TO START ]");
    
    HIDE_CURSOR;
    
    getch();
}

void get_settings(char *player1_key, char *player2_key, int *rope_length) {
    clrscr();
    
    gotoxy(25, 11);
    printf("___________SETTINGS___________");
    
    gotoxy(25, 15);
    printf("______________________________");
    
    gotoxy(25, 12);
    printf("Press key for Player 1: ");
    *player1_key = toupper(getche());
    
    // Gets Player 2's control key and compares it to Player 1's
    while (1) {
        int i;
        
        gotoxy(25, 13);
        
        for (i = 1; i <= SCREEN_WIDTH - 1; i++) {
            printf(" ");
        }
        
        gotoxy(25, 13);
        printf("Press key for Player 2: ");
        *player2_key = toupper(getche());
        
        if (*player2_key == *player1_key) {
            gotoxy(15, 16);
            printf("Player 2 key must not be the same as Player 1 key.");
            
            gotoxy(27, 17);
            printf("Press any key to continue.");
            
            getch();
            
            // Clears warning message
            gotoxy(15, 16);
            printf("                                                  ");
            
            gotoxy(27, 17);
            printf("                          ");
        } else break;
    }
    
    // Gets and validates rope length
    while (1) {
        int i;
        
        gotoxy(1, 14);
        
        for (i = 1; i <= SCREEN_WIDTH - 1; i++) {
            printf(" ");
        }
        
        gotoxy(25, 14);
        printf("Enter length of rope: ");
        
        if (scanf("%d", rope_length) != 1 || *rope_length <= 5 || *rope_length >= 39 || *rope_length % 2 == 0) {
            gotoxy(14, 16);
            printf("Rope length must be an odd integer between 5 and 39.");
            
            while (getchar() != '\n');
            
            gotoxy(27, 17);
            printf("Press any key to continue.");
            
            getch();
            
            // Clears warning message
            gotoxy(14, 16);
            printf("                                                    ");
            
            gotoxy(27, 17);
            printf("                          ");
        } else break;
    }
}

void draw_center_line() {
    int y;
    
    clrscr();
    
    for (y = 1; y <= SCREEN_HEIGHT; y++) {
        gotoxy(SCREEN_CENTER_X, y);
        printf("|");
    }
}

void update_rope(int rope_start, int rope_length) {
    int i;
    
    // Clears the previous rope
    gotoxy(1, SCREEN_CENTER_Y);
    
    for (i = 1; i <= SCREEN_WIDTH; i++) {
        printf(" ");
    }
    
    // Draws the new rope
    gotoxy(rope_start, SCREEN_CENTER_Y);
    
    for (i = 1; i <= rope_length; i++) {
        if (i == 1) {
            printf("o");
        } else if (i == rope_length) {
            printf("o");
        } else {
            printf("-");
        }
    }
    
    HIDE_CURSOR;
}

int check_win(int rope_start, int rope_length) {
    if (rope_start == SCREEN_CENTER_X - rope_length + 1) {
        gotoxy(33, SCREEN_CENTER_Y - 1);
        printf("Player 1 wins...");
        
        return 1;
    } else if (rope_start == SCREEN_CENTER_X) {
        gotoxy(33, SCREEN_CENTER_Y - 1);
        printf("Player 2 wins...");
        
        return 2;
    }
    
    return 0;
}

void update_score(int winner, int *player1_score, int *player2_score) {
    if (winner == 1) {
        (*player1_score)++;
    } else if (winner == 2) {
        (*player2_score)++;
    }
    
    gotoxy(4, 2);
    printf("Player 1: %d", *player1_score);
    
    gotoxy(44, 2);
    printf("Player 2: %d", *player2_score);
}

int prompt_play_again() {
    char option;
    
    gotoxy(25, SCREEN_CENTER_Y + 1);
    printf("Would you like to play again?");
    
    gotoxy(35, SCREEN_CENTER_Y + 2);
    printf("[Y]es [N]o");
    
    HIDE_CURSOR;
    
    while (option != 'Y' || option != 'N') {
        option = toupper(getch());
        
        if (option == 'Y') {
            return 1;
        } else if (option == 'N') {
            return 0;
        }
    }
    
    return -1;
}

int main() {
    int rope_length, rope_start, playing = 1, winner, player1_score = 0, player2_score = 0;
    char player1_key, player2_key;
    
    display_title_screen();
    
    get_settings(&player1_key, &player2_key, &rope_length);
    
    // Game loop
    while (playing) {
        draw_center_line();
        
        rope_start = SCREEN_CENTER_X - (rope_length / 2); // Starting rope start position
        
        update_score(0, &player1_score, &player2_score); // Just displays scoreboard
        
        while (1) {
            char input;
            
            update_rope(rope_start, rope_length);
            
            winner = check_win(rope_start, rope_length);
            
            if (winner) {
                update_score(winner, &player1_score, &player2_score);
                
                playing = prompt_play_again();
                
                break;
            }
            
            input = toupper(getch());
            
            if (input == player1_key) {
                rope_start--;
            } else if (input == player2_key) {
                rope_start++;
            }
        }
    }
    
    return 0;
}
