#include <stdio.h>
#include <conio.h>
#include <math.h>

#define HIDE_CURSOR gotoxy(80, 25)

char board[8][8];
int first_x, first_y, last_x, last_y, moves = 0, solving = 0;

void draw_board(int available_moves);
void clear_board();
void get_position();
void display_intro_screen();
void play_solution();

void main()
{
    int r, f;
    
    display_intro_screen();
    
    getch();
    
    clear_board();
    
    draw_board(-1); // Dummy argument
    
    getch();
}

void play_solution() {
    int current_x, current_y;
    
    if (!moves) {
        board[first_x][first_y] = 'K';
        
        current_x = first_x;
        current_y = first_y;
    } else if (moves < 64) {
        int i, j, best_x, best_y, fewest_moves = 9;
        
        board[last_x][last_y] = 'x';
        
        current_x = last_x;
        current_y = last_y;
        
        // Traverse through all current valid knight moves
        for (i = -2; i <= 2; i++) {
            for (j = -2; j <= 2; j++) {
                int move_x = current_x + i;
                int move_y = current_y + j;
                int available_moves = 0;
                
                if ((abs(i) != abs(j)) && (i != 0 && j != 0)
                    && (move_x >= 0 && move_x < 8 && move_y >= 0 && move_y < 8)
                    && (board[move_x][move_y] != 'x')) {
                    int k, l;
                    
                    // Traverse through all next valid knight moves
                    for (k = -2; k <= 2; k++) {
                        for (l = -2; l <= 2; l++) {
                            int next_x = move_x + k;
                            int next_y = move_y + l;
                            
                            if ((abs(k) != abs(l)) && (k != 0 && l != 0)
                                && (next_x >= 0 && next_x < 8 && next_y >= 0 && next_y < 8)
                                && (board[next_x][next_y] != 'x')) {
                                available_moves++;
                            }
                        }
                    }
                    
                    if (available_moves < fewest_moves) {
                        fewest_moves = available_moves;
                        
                        best_x = move_x;
                        best_y = move_y;
                    }
                }
            }
        }
        
        current_x = best_x;
        current_y = best_y;
        
        board[best_x][best_y] = 'K';
    } else {
        solving = 0;
        
        gotoxy(2, 2);
        printf("| The Knight's tour has been completed.");
        
        HIDE_CURSOR;
        
        getch();
        
        return;
    }
    
    moves++;
    
    last_x = current_x;
    last_y = current_y;
    
    delay(500);
    
    draw_board(-1); // Dummy argument, not necessary to pass anything
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
    
    if (moves) {
        board[last_x][last_y] = 'x';
        
        if (moves == 1) { // Save first move coordinates
            first_x = last_x;
            first_y = last_y;
        }
    }
    
    while (1) {
        gotoxy(2, 2);
        
        if (moves) {
            printf("| Input next position of the knight (x y): ");
        } else {
            printf("| Input starting position of the knight (x y): ");
        }
        
        scanf("%d %d", &x, &y);
        
        --x;
        --y;
        
        if ((abs(last_x - x) + abs(last_y - y) != 3) && moves) {
            gotoxy(2, 2);
            printf("| Invalid knight move. ");
        } else if (x < 0 || y < 0 || x >= 8 || y >= 8) {
            gotoxy(2, 2);
            printf("| Position out of bounds. ");
        } else if ((board[x][y] == 'x')) {
            gotoxy(2, 2);
            printf("| Square has been visited. ");
        } else {
            moves++;
            
            break;
        }
        
        printf("Press any key to try again.");
        
        HIDE_CURSOR;
        
        getch();
        
        gotoxy(2, 2);
        printf("                                                                                ");
    }
    
    board[x][y] = 'K';
    
    for (i = -2; i <= 2; i++) {
        for (j = -2; j <= 2; j++) {
            int move_x = x + i;
            int move_y = y + j;
            
            if ((abs(i) != abs(j)) && (i != 0 && j != 0)
                && (move_x >= 0 && move_x < 8 && move_y >= 0 && move_y < 8)
                && (board[move_x][move_y] != 'x')) {
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
    
    HIDE_CURSOR;
    
    if (!available_moves) {
        gotoxy(2, 2);
        
        if (moves == 64) {
            printf("| You have successfully completed the knight's tour. Congratulations!");
            
            HIDE_CURSOR;
        } else {
            char option;
            
            printf("| No available moves left. Better luck next time.");
            
            gotoxy(25, 23);
            printf("[1] Play Solution\t [0] Exit");
            
            HIDE_CURSOR;
            
            while (option != '1' && option != '0') {
                option = getch();
            }
            
            switch (option) {
                case '1':
                    clear_board();
                    
                    moves = 0; // Repurpose of variable
                    
                    solving = 1;
                    
                    break;
                case '0':
                    return;
            }
        }
    }
    
    if (!solving) {
        get_position();
    } else {
        play_solution();
    }
}
