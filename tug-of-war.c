#include <stdio.h>
#include <conio.h>

#define SCREEN_X 80
#define SCREEN_Y 25
#define SCREEN_CENTER_X SCREEN_X / 2
#define SCREEN_CENTER_Y SCREEN_Y / 2 // Integer division

#define ROPE_LENGTH 11 // Best to be an odd integer

#define HIDE_CURSOR gotoxy(SCREEN_X, SCREEN_Y)

void draw_center_line() {
    int y;
    
    clrscr();
    
    for (y = 1; y <= SCREEN_Y; y++) {
        gotoxy(SCREEN_CENTER_X, y);
        printf("|");
    }
}

void update_rope(int rope_start) {
    int i;
    
    // Clears the previous rope
    gotoxy(1, SCREEN_CENTER_Y);
    
    for (i = 1; i <= SCREEN_X; i++) {
        printf(" ");
    }
    
    // Draws the new rope
    gotoxy(rope_start, SCREEN_CENTER_Y);
    
    for (i = 1; i <= ROPE_LENGTH; i++) {
        if (i == 1) {
            printf("o");
        } else if (i == ROPE_LENGTH) {
            printf("o");
        } else {
            printf("-");
        }
    }
    
    HIDE_CURSOR;
}

int main() {
    int rope_start = SCREEN_CENTER_X - (ROPE_LENGTH / 2);
    char input;
    
    draw_center_line();
    
    while (1) {
        update_rope(rope_start);
        
        if (rope_start == SCREEN_CENTER_X - ROPE_LENGTH + 1) {
            gotoxy(33, SCREEN_CENTER_Y - 1);
            printf("Player 1 wins...");
            
            break;
        } else if (rope_start == SCREEN_CENTER_X) {
            gotoxy(33, SCREEN_CENTER_Y - 1);
            printf("Player 2 wins...");
            
            break;
        }
        
        input = toupper(getch());
        
        if (input == 'F') {
            rope_start--;
        } else if (input == 'J') {
            rope_start++;
        } else if (input == '0') {
            break;
        }
    }
    
    getch();
    
    return 0;
}
