#include <stdio.h>
#include <conio.h>
#include <math.h>

char board[8][8];
int last_x, last_y;

void draw_board();
void clear_board();
void get_starting_pos();
void get_move();

void main()
{
    int r, f;
    
    clear_board();
    
    get_starting_pos();
    
    getch();
}

void get_move() {
    int x, y;
    
    board[last_x][last_y] = 'x';
    
    while ((abs(last_x - x) + abs(last_y - y) != 3) || (x < 0 || y < 0 || x >= 8 || y >= 8) || (board[x][y] == 'x')) {
        gotoxy(1, 1);
        
        printf("Input next position of the Knight (x y): ");
        scanf("%d %d", &x, &y);
        
        --x;
        --y;
    }
    
    board[x][y] = 'K';
    
    last_x = x;
    last_y = y;
    
    draw_board();
}

void get_starting_pos() {
    int x, y;
    
    clrscr();
    
    printf("Input starting position of the Knight (x y): ");
    scanf("%d %d", &x, &y);
    
    --x;
    --y;
    
    board[x][y] = 'K';
    
    last_x = x;
    last_y = y;
    
    draw_board();
}

void clear_board() {
    int r, f;
    
    for (r = 0; r < 8; r++) {
        for (f = 0; f < 8; f++) {
            board[r][f] = ' ';
        }
    }
}

void draw_board() {
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
    
    get_move();
}
