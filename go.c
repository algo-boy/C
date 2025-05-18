#include <stdio.h>
#include <conio.h>
#include <windows.h>

HANDLE hConsole;

void gotoxy(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, coord);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

typedef struct Node {
	int x, y;
	struct Node *next;
} Node;

int board[11][11]; // +2 for off-board spaces
char states[5] = {'+', '0', 'O', '+', 'X'}; // [0] = empty, [1] = black, [2] = white, [3] = liberty, [4] = off-board

int game_running = 1;
int turn = 1; // 1 = black, 2 = white

void update_board();
void initialize_board();
void place_stone();
void detect_group();

int main() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	initialize_board();
	
	while (game_running) {
		update_board();
		place_stone();
	}
	
	getch();
	
	return 0;
}

void place_stone() {
	int x, y;
	
	gotoxy(41, 3);
	printf("| Enter the position of stone to place (x y): ");
	scanf("%d %d", &x, &y);
	
	if (x < 0 || x > 9 || y < 0 || y > 9 || board[x][y] != 0) {
	   	gotoxy(41, 5);
	   	printf("| Invalid move. Press any key to try again.");
	   	
	   	getch();
	   	
	   	return;
	}
	
	board[x][y] = turn;
        
    turn = (turn == 1) ? 2 : 1;
}

void initialize_board() {
    int x, y;
    
    for (x = 0; x < 11; x++) {
        for (y = 0; y < 11; y++) {
			if (x == 0 || x == 10 || y == 0 || y == 10) {
				board[x][y] = 4;
			} else {
				board[x][y] = 0;
			}
        }
    }
}

void update_board() {
    int x, y, square_start_y = 2;
    
    system("cls");
    
    for (y = 1; y < 10; y++) {
		int square_start_x = 4;
		
    	for (x = 1; x < 10; x++) {
    		gotoxy(square_start_x, square_start_y);
			printf("%c", states[board[x][y]]);
			
			if (x != 9) {
				printf("---");
			}
			
			if (y != 9) {
				gotoxy(square_start_x, square_start_y + 1);
				printf("|");
			}
			
			square_start_x += 4;
		}
		
		square_start_y += 2;
	}
}
