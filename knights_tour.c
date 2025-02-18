#include <stdio.h>
#include <conio.h>

void draw_board(char board[][8]);

void main()
{
    char board[8][8];
    
    board[2][2] = 'K';
    
    draw_board(board);
}

void draw_board(char board[][8]) {
    int r, f, square_start_y = 1;
    
    clrscr();
    
    for (r = 0; r < 8; r++) {
        int square_start_x = 1;
        
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
