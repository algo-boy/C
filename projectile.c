#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <dos.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define TIME_STEP 0.001
#define X_OFFSET 2
#define RAND_MIN 5
#define RAND_MAX 80

#define PI 3.1416
#define G 9.81

#define HIDE_CURSOR gotoxy(SCREEN_WIDTH, SCREEN_HEIGHT)

void display_intro_screen() {
    clrscr();
    
    gotoxy(1, 9);
    printf("                          ________           ________________\n");
    printf("     ___________________________(_)____________  /___(_)__  /____   _______\n");
    printf("     ___  __ \\_  ___/  __ \\____  /_  _ \\  ___/  __/_  /__  /_  _ \\  _  ___/\n");
    printf("     __  /_/ /  /   / /_/ /___  / /  __/ /__ / /_ _  / _  / /  __/__/ /__\n");
    printf("     _  .___//_/    \\____/___  /  \\___/\\___/ \\__/ /_/  /_/  \\___/_(_)___/\n");
    printf("     /_/                  /___/\n");
    
    gotoxy(35, 16);
    
    printf("[ START ]");
    
    HIDE_CURSOR;
    
    getch();
}

int main() {
    float v_0, theta, v_x0, v_y0, T, R, H, t;
    int x, y, target_x, ground_y = SCREEN_HEIGHT - 1;
    
    srand(time(0));
    target_x = (rand() % (RAND_MAX - RAND_MIN + 1)) + RAND_MIN;
    
    target_x = 40; // Test Position
    
    display_intro_screen();
    
    clrscr();
    
    for (x = 1; x <= SCREEN_WIDTH; x++) {
        gotoxy(x, ground_y);
        
        if (x == target_x) {
            printf("O");
        } else {
            printf("_");
        }
    }
    
    gotoxy(1, 1);
    
    printf("Enter initial velocity: ");
    scanf("%f", &v_0);
    
    printf("Enter angle of launch: ");
    scanf("%f", &theta);
    
    theta *= (PI / 180.0);
    
    v_x0 = v_0 * cos(theta);
    v_y0 = v_0 * sin(theta);
    
    T = 2 * v_0 * sin(theta) / G;
    R = v_0 * v_0 * sin(2 * theta) / G;
    H = v_0 * v_0 * (sin(theta)) * (sin(theta)) / (2 * G);
    
    printf("\n| Initial Horizontal Velocity: %0.2f m/s", v_x0);
    printf("\n| Initial Vertical Velocity: %0.2f m/s", v_y0);
    printf("\n| Time of Flight: %0.2f seconds", T);
    printf("\n| Range: %0.2f meters", R);
    printf("\n| Maximum Height: %0.2f meters", H);
    
    for (t = 0; t <= T; t += TIME_STEP) {
        int offset_x, inverted_y;
        
        x = v_x0 * t;
        y = v_y0 * t - 0.5 * G * t * t;
        
        offset_x = x + X_OFFSET;
        inverted_y = ground_y - y;
        
        if (offset_x >= 1 && offset_x <= SCREEN_WIDTH && inverted_y >= 1 && inverted_y <= ground_y) {
            gotoxy(offset_x, inverted_y);
            printf("o");
        } else if (offset_x < 1 || offset_x > SCREEN_WIDTH) {
            gotoxy(43, SCREEN_HEIGHT);
            printf("Trajectory exceeded horizontal bound.");
        }
        
        if (offset_x == target_x && inverted_y == 24) {
            gotoxy(target_x + 2, ground_y - 2);
            printf("You hit the target!");
            
            HIDE_CURSOR;
        }
        
        delay(1);
    }
    
    getch();
    return 0;
}
