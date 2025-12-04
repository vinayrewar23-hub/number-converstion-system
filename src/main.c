#include <stdio.h>
#include <stdlib.h>
#include "../include/converter.h"

int main() {
    int choice;
    do {
        displaymenu();
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            choice = 0;
        } else {
            while (getchar() != '\n');
        }
        switch (choice) {
            case 1: decimaltoall(); break;
            case 2: anybasetodecimal(2); break;
            case 3: anybasetodecimal(8); break;
            case 4: anybasetodecimal(16); break;
            case 5: printf("Number Conversion System. Goodbye!\n"); break;
            default: if (choice != 0) printf("Invalid option. Please choose 1-5.\n"); break;
        }
    } while (choice != 5);
    return 0;
}
