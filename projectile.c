#include <stdio.h>
#include <conio.h>
#include <math.h>

#define HIDE_CURSOR gotoxy(80, 25)

char board[8][8];
int last_x, last_y;
int started = 0;

void draw_board(int available_moves);
void clear_board();
void get_position();
void display_intro_screen();

void main()
{
    int r, f;
    
    display_intro_screen();
    
    getch();
    
    clear_board();
    
    draw_board(1); // Dummy argument
    
    getch();
}

void display_intro_screen() {
    clrscr();
    
    gotoxy(35, 7);
    printf("   (\\=,\n");
    
    gotoxy(35, 8);
    printf("  //  .\\\n");
    
    gotoxy(35, 9);
    printf(" (( \\_  \\\n");
    
    gotoxy(35, 10);
    printf("  ))  `\\_)\n");
    
    gotoxy(35, 11);
    printf(" (/     |\n");
    
    gotoxy(35, 12);
    printf("  \\_.- /\n");
    
    gotoxy(35, 13);
    printf("  )___(\n");
    
    gotoxy(35, 14);
    printf(" (=====)\n");
    
    gotoxy(35, 15);
    printf(" }====={\n");
    
    gotoxy(35, 16);
    printf("(_______)\n");
    
    gotoxy(33, 18);
    printf("Knight's Tour");
    
    gotoxy(27, 20);
    printf("[ PRESS ANY KEY TO START ]");
    
    HIDE_CURSOR;
}

void get_position() {
    int x, y, i, j, available_moves = 0;
    
    if (started) {
        board[last_x][last_y] = 'x';
    }
    
    while (1) {
        gotoxy(2, 2);
        
        if (started) {
            printf("| Input next position of the knight (x y): ");
        } else {
            printf("| Input starting position of the knight (x y): ");
        }
        
        scanf("%d %d", &x, &y);
        
        --x;
        --y;
        
        if ((abs(last_x - x) + abs(last_y - y) != 3) && started) {
            gotoxy(2, 2);
            printf("| Invalid knight move. ");
        } else if (x < 0 || y < 0 || x >= 8 || y >= 8) {
            gotoxy(2, 2);
            printf("| Position out of bounds. ");
        } else if ((board[x][y] == 'x')) {
            gotoxy(2, 2);
            printf("| Square has been visited. ");
        } else {
            started = 1;
            
            break;
        }
        
        printf("Press any key to try again.");
        
        getch();
        
        gotoxy(2, 2);
        printf("                                                                                ");
    }
    
    board[x][y] = 'K';
    
    for (i = -2; i <= 2; i++) {
        for (j = -2; j <= 2; j++) {
            if ((abs(i) != abs(j)) && (i != 0 && j != 0)
                && (x + i >= 0 && x + i < 8 && y + j >= 0 && y + j < 8)
                && (board[x + i][y + j] != 'x')) {
                available_moves++;
            }
        }
    }
    
    last_x = x;
    last_y = y;
    
    draw_board(available_moves);
}

void clear_board() {
    int r, f;
    
    for (r = 0; r < 8; r++) {
        for (f = 0; f < 8; f++) {
            board[r][f] = ' ';
        }
    }
}

void draw_board(int available_moves) {
    int r, f, square_start_y = 5;
    
    clrscr();
    
    // Displays file labels
    gotoxy(27, 4);
    printf("1   2   3   4   5   6   7   8");
    
    for (r = 0; r < 8; r++) {
        int square_start_x = 25;
        
        // Displays rank labels
        gotoxy(square_start_x - 2, square_start_y + 1);
        printf("%d", r + 1);
        
        for (f = 0; f < 8; f++) {
            gotoxy(square_start_x, square_start_y);
            printf("+---+");
            
            gotoxy(square_start_x, square_start_y + 1);
            printf("| %c |", board[f][r]);
            
            gotoxy(square_start_x, square_start_y + 2);
            printf("+---+");
            
            square_start_x += 4;
        }
        
        square_start_y += 2;
    }
    
    if (!available_moves) {
        gotoxy(2, 2);
        printf("| No available moves left. Better luck next time.");
        
        HIDE_CURSOR;
        
        return;
    }
    
    get_position();
}
