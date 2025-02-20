#include <stdio.h>
#include <conio.h>

void draw_board(char board[][8]);

void get_starting_pos(int *x, int *y);

void main()
{
    char board[8][8];
    int starting_pos_x = 0, starting_pos_y = 0;
    
    int r, f;
    
    // Initializes space character stored in each square
    for (r = 0; r < 8; r++) {
        for (f = 0; f < 8; f++) {
            board[r][f] = ' ';
        }
    }
    
    get_starting_pos(&starting_pos_x, &starting_pos_y);
    
    board[starting_pos_x][starting_pos_y] = 'K';
    
    draw_board(board);
    
    getch();
}

void get_starting_pos(int *x, int *y) {
    clrscr();
    
    printf("Enter starting position of the Knight (x y): ");
    
    scanf("%d %d", x, y);
    
    --*x;
    --*y;
}

void draw_board(char board[][8]) {
    int r, f, square_start_y = 5;
    
    clrscr();
    
    for (r = 0; r < 8; r++) {
        int square_start_x = 25;
        
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
