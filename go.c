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

char board[9][9];
char stone = '0'; // 0 = black, O = white

void update_board();
void initialize_board();
void place_stone();

int main() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	initialize_board();
	update_board();
	place_stone();
	
	getch();
}

void place_stone() {
	int x, y;
	
	gotoxy(41, 3);
	printf("| Enter the position of stone to place (x y): ");
	scanf("%d %d", &x, &y);
	
	--x;
	--y;
	
	if (x < 0 || x > 9 || y < 0 || y > 9 || board[x][y] != '+') {
	   	gotoxy(41, 5);
	   	printf("| Invalid move. Press any key to try again.");
	   	
	   	getch();
	   	
	   	update_board();
	}
	
	board[x][y] = stone;
    
    stone = (stone == '0') ? 'O' : '0';
    
	update_board();
}

void initialize_board() {
    int x, y;
    
    for (x = 0; x < 9; x++) {
        for (y = 0; y < 9; y++) {
            board[x][y] = '+';
        }
    }
}

void update_board() {
    int x, y, square_start_y = 2;
    
    system("cls");
    
    for (y = 0; y < 9; y++) {
		int square_start_x = 4;
		
    	for (x = 0; x < 9; x++) {
    		gotoxy(square_start_x, square_start_y);
			printf("%c", board[x][y]);
			
			if (x != 8) {
				printf("---");
			}
			
			if (y != 8) {
				gotoxy(square_start_x, square_start_y + 1);
				printf("|");
			}
			
			square_start_x += 4;
		}
		
		square_start_y += 2;
	}
    
    place_stone();
}
