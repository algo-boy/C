// Header Files
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <ctype.h>

// Screen Dimensions
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Physical Constants
#define TIME_STEP 0.01
#define GROUND_Y 24
#define INITIAL_X 2
#define TARGET_X 40

// Mathematical Constants
#define PI 3.1416
#define G 9.81

// Macro Definition
#define HIDE_CURSOR gotoxy(SCREEN_WIDTH, SCREEN_HEIGHT) // Moves cursor to the bottom-right corner of the screen

void clear_line(int y) {
    int i;
    
    gotoxy(1, y);
    
    for (i = 1; i <= SCREEN_WIDTH - 1; i++) { // SCREEN_WIDTH - 1 to prevent overflow into the next line
        putchar(' ');
    }
}

void display_title_screen() {
    clrscr();
    
    gotoxy(1, 9);
    printf("                          ________           ________________\n");
    printf("     ___________________________(_)____________  /___(_)__  /____   _______\n");
    printf("     ___  __ \\_  ___/  __ \\____  /_  _ \\  ___/  __/_  /__  /_  _ \\  _  ___/\n");
    printf("     __  /_/ /  /   / /_/ /___  / /  __/ /__ / /_ _  / _  / /  __/__/ /__\n");
    printf("     _  .___//_/    \\____/___  /  \\___/\\___/ \\__/ /_/  /_/  \\___/_(_)___/\n");
    printf("     /_/                  /___/\n");
    
    gotoxy(27, 16);
    printf("[ PRESS ANY KEY TO START ]");
    
    HIDE_CURSOR;
    
    getch();
}

void draw_environment() {
    int x;
    
    clrscr();
    
    for (x = 1; x <= SCREEN_WIDTH; x++) {
        gotoxy(x, GROUND_Y);
        
        if (x == TARGET_X) {
            printf("O");
        } else if (x == INITIAL_X) {
            printf("o");
        } else {
            printf("_");
        }
    }
}

void get_initial_conditions(float *v_0, float *theta) {
    gotoxy(2, 2);
    printf("____________INPUTS____________");
    
    gotoxy(2, 5);
    printf("______________________________");
    
    // Gets and validates v_0
    while (1) {
        gotoxy(2, 3);
        printf("Enter initial velocity: ");
        
        if (scanf("%f", v_0) != 1 || *v_0 <= 0) {
            gotoxy(10, SCREEN_HEIGHT);
            printf("Initial velocity must be a positive number. Press any key to continue.");
            
            getch();
            
            clear_line(3);
            clear_line(SCREEN_HEIGHT);
            
            fflush(stdin); // Flush recent input from the buffer
        } else break;
    }
    
    // Gets and validates theta
    while (1) {
        gotoxy(2, 4);
        printf("Enter launch angle: ");
        
        if (scanf("%f", theta) != 1 || *theta < 1 || *theta > 180) {
            gotoxy(6, SCREEN_HEIGHT);
            printf("Launch angle must be between 1 and 180 degrees. Press any key to continue.");
            
            getch();
            
            clear_line(4);
            clear_line(SCREEN_HEIGHT);
            
            fflush(stdin);
        } else break;
    }
}

void compute_results(float v_0, float theta, float *v_x0, float *v_y0, float *T, float *R, float *H) {
    float cos_theta, sin_theta;
    
    theta *= PI / 180.0; // Converts degrees into radians
    
    // Caches values for efficiency
    cos_theta = cos(theta);
    sin_theta = sin(theta);
    
    *v_x0 = v_0 * cos_theta;
    *v_y0 = v_0 * sin_theta;
    
    *T = 2 * v_0 * sin_theta / G;
    *R = v_0 * v_0 * sin(2 * theta) / G;
    *H = v_0 * v_0 * (sin_theta) * (sin_theta) / (2 * G);
}

void display_results(float v_x0, float v_y0, float T, float R, float H) {
    gotoxy(35, 2);
    printf("___________________RESULTS___________________");
    
    gotoxy(35, 3);
    printf("Initial Horizontal Velocity:\t%0.2f m/s", v_x0);
    
    gotoxy(35, 4);
    printf("Initial Vertical Velocity:\t%0.2f m/s", v_y0);
    
    gotoxy(35, 5);
    printf("Time of Flight:\t\t%0.2f seconds", T);
    
    gotoxy(35, 6);
    printf("Range:\t\t\t%0.2f meters", R);
    
    gotoxy(35, 7);
    printf("Maximum Height:\t\t%0.2f meters", H);
    
    gotoxy(35, 8);
    printf("_____________________________________________");
    
    gotoxy(22, GROUND_Y / 2);
    printf("[ PRESS ANY KEY TO PLAY TRAJECTORY ]");
    
    HIDE_CURSOR;
    
    getch();
}

void draw_trajectory(float T, float v_x0, float v_y0) {
    float t;
    int x, y;
    
    clear_line(GROUND_Y / 2);
    
    // Animates projectile trajectory
    for (t = 0; t <= T; t += TIME_STEP) {
        int offset_x, inverted_y;
        
        x = v_x0 * t;
        y = v_y0 * t - 0.5 * G * t * t;
        
        offset_x = x + INITIAL_X; // Offsets x by INITIAL_X for correct screen display
        inverted_y = GROUND_Y - y; // Inverts y for correct screen display
        
        // Plots trajectory point in bounds
        if (offset_x >= 1 && offset_x <= SCREEN_WIDTH && inverted_y >= 1 && inverted_y <= GROUND_Y) {
            gotoxy(offset_x, inverted_y);
            printf("o");
        } else if (offset_x < 1 || offset_x > SCREEN_WIDTH) {
            gotoxy(23, SCREEN_HEIGHT);
            printf("Trajectory exceeded horizontal bounds.");
            
            break;
        }
        
        // Detects target hit
        if (offset_x == TARGET_X && inverted_y == GROUND_Y) {
            gotoxy(TARGET_X + 2, GROUND_Y - 2);
            printf("You hit the target!");
        }
        
        delay(10);
    }
}

int get_retry_option() {
    char option;
    
    while (option != 'R' && option != 'X') {
        gotoxy(62, SCREEN_HEIGHT);
        printf("[R] Retry [X] Quit");
        
        option = toupper(getch());
        
        if (option == 'R') {
            return 1;
        } else if (option == 'X') {
            return 0;
        } else {
            clear_line(SCREEN_HEIGHT);
            
            gotoxy(47, SCREEN_HEIGHT);
            printf("Invalid input.");
        }
    }
    
    return -1; // Does nothing but fulfill compiler's wish
}

int main() {
    float v_0, theta, v_x0, v_y0, T, R, H;
    int will_repeat = 1;
    
    display_title_screen();
    
    while (will_repeat) {
        draw_environment();
        
        get_initial_conditions(&v_0, &theta);
        
        compute_results(v_0, theta, &v_x0, &v_y0, &T, &R, &H);
        
        display_results(v_x0, v_y0, T, R, H);
        
        draw_trajectory(T, v_x0, v_y0);
        
        will_repeat = get_retry_option();
    }
    
    return 0;
}
