#include <stdio.h>
#include <conio.h>

void draw_board(char board[][8]);

void main()
{
    char board[8][8];
    
    int r, f;
    
    // Initializes space character stored in each square
    for (r = 0; r < 8; r++) {
        for (f = 0; f < 8; f++) {
            board[r][f] = ' ';
        }
    }
    
    board[0][0] = 'K'; // Knight dummy
    
    draw_board(board);
    
    getch();
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
