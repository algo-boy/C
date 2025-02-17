#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

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

void retrieve_account(Account accounts[], int accounts_size) {
    int i;
    char domain[20];
    
    clrscr();
    
    printf("Enter domain: ");
    scanf("%s", domain);
    
    for (i = 0; i < accounts_size; i++) {
        if (strcmp(domain, accounts[i].domain) == 0) {
            printf("Account found:\n");
            printf("Domain: %s\n", accounts[i].domain);
            printf("Name: %s\n", accounts[i].name);
            printf("Password: %s\n", accounts[i].password);
            return;
        }
    }
    
    printf("Account not found.\n");
}

int main() {
    Account accounts[128];
    
    char option;
    int i = 0;
    
    while (1) {
        display_menu(&option);
        
        switch (option) {
            case 'A':
                if (i < 128) {
                    add_account(&accounts[i]);
                    i++;
                } else {
                    printf("Account limit reached.\n");
                }
                
                break;
                
            case 'R':
                retrieve_account(accounts, i);
                break;
                
            case 'E':
                return 0;
                
            default:
                continue;
        }
        
        getch();
    }
}
