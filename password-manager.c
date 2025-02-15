#include <stdio.h>
#include <conio.h>
#include <ctype.h>

typedef struct {
    char domain[20];
    char name[50];
    char password[128];
} Account;

void display_menu(char *option) {
    clrscr();
    
    printf("[A]DD ACCOUNT\n");
    printf("[R]ETRIEVE ACCOUNT\n");
    printf("[E]XIT\n");
    
    *option = toupper(getch());
    
}

void add_account(Account *account) {
    clrscr();
    
    printf("Enter domain: ");
    scanf("%s", account->domain);
    
    printf("Enter name: ");
    scanf("%s", account->name);
    
    printf("Enter password: ");
    scanf("%s", account->password);
}

int main() {
    Account accounts[128];
    
    char option;
    int i = 0;
    
    while (1) {
        display_menu(&option);
        
        switch (option) {
            case 'A':
                add_account(&accounts[i]);
                
                printf("Account stored successfully.");
                
                i++;
                
                break;
                
            case 'R':
                
                // Account retrieval goes here
                
                break;
                
            case 'E':
                printf("\nExiting...\n");
                return 0;
                
            default:
                continue;
        }
        
        getch();
    }
    
    // return 0;
}
