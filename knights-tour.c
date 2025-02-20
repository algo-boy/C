#include <stdio.h>
#include <conio.h>

char board[8][8];

void draw_board();

void get_starting_pos(int *x, int *y);

void main()
{
    int r, f, pos_x = 0, pos_y = 0, i;
    
    int moves_x[8] = {1, 2, 2, 1, -1, -2, -2, -1}, moves_y[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    
    // Initializes space character stored in each square
    for (r = 0; r < 8; r++) {
        for (f = 0; f < 8; f++) {
            board[r][f] = ' ';
        }
    }
    
    get_starting_pos(&pos_x, &pos_y);
    
    board[pos_x][pos_y] = 'K';
    
    // Mark available moves
    for (i = 0; i < 8; i++) {
        int move_x = pos_x + moves_x[i];
        int move_y = pos_y + moves_y[i];
        
        if (move_x >= 0 && move_y >= 0 && move_x < 8 && move_y < 8) {
            board[move_x][move_y] = 'o';
        }
    }
    
    draw_board();
    
    getch();
}

void get_starting_pos(int *x, int *y) {
    clrscr();
    
    printf("Input starting position of the Knight (x y): ");
    
    scanf("%d %d", x, y);
    
    --*x;
    --*y;
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
            printf("| %c |", board[r][f]);
            
            gotoxy(square_start_x, square_start_y + 2);
            printf("+---+");
            
            square_start_x += 4;
        }
        
        square_start_y += 2;
    }
}
