#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------
// Convert Decimal → Any Base (2, 8, 16)
//------------------------------------------------------
void decimal_to_base(long long decimal_num, int base, char result[]) {
    if (decimal_num == 0) {
        strcpy(result, "0");
        return;
    }

    int index = 0;
    long long temp = decimal_num;

    while (temp > 0) {
        int rem = temp % base;

        if (rem < 10)
            result[index++] = rem + '0';
        else
            result[index++] = (rem - 10) + 'A';

        temp /= base;
    }

    result[index] = '\0';

    // Reverse the string
    int len = index;
    for (int i = 0; i < len / 2; i++) {
        char t = result[i];
        result[i] = result[len - 1 - i];
        result[len - 1 - i] = t;
    }
}

//------------------------------------------------------
// Convert Any Base → Decimal (avoid pow() floating bug)
//------------------------------------------------------
long long base_to_decimal(const char *num_str, int base) {
    long long decimal = 0;
    long long multiplier = 1;
    int len = strlen(num_str);

    for (int i = len - 1; i >= 0; i--) {
        char d = num_str[i];
        int val;

        if (d >= '0' && d <= '9')
            val = d - '0';
        else if (d >= 'A' && d <= 'F')
            val = d - 'A' + 10;
        else
            return -1; // invalid char

        if (val >= base)
            return -2; // digit cannot exist in that base

        decimal += val * multiplier;
        multiplier *= base;
    }

    return decimal;
}

//------------------------------------------------------
// Menu Display
//------------------------------------------------------
void display_menu() {
    printf("\n--- Number Conversion System Menu ---\n");
    printf("1. Decimal (10) to Binary/Octal/Hex\n");
    printf("2. Binary (2) to Decimal\n");
    printf("3. Octal (8) to Decimal\n");
    printf("4. Hexadecimal (16) to Decimal\n");
    printf("5. Exit\n");
    printf("-------------------------------------\n");
}

//------------------------------------------------------
// Decimal → All Bases
//------------------------------------------------------
void decimal_to_all() {
    long long dec;

    printf("Enter Decimal Number: ");
    if (scanf("%lld", &dec) != 1 || dec < 0) {
        printf("Invalid input. Please enter a positive number.\n");
        while (getchar() != '\n');
        return;
    }

    char bin[64], oct[64], hex[64];

    decimal_to_base(dec, 2, bin);
    decimal_to_base(dec, 8, oct);
    decimal_to_base(dec, 16, hex);

    printf("\nResults:\n");
    printf("Binary      : %s\n", bin);
    printf("Octal       : %s\n", oct);
    printf("Hexadecimal : %s\n", hex);
}

//------------------------------------------------------
// Any Base → Decimal
//------------------------------------------------------
void any_base_to_decimal(int base) {
    char input[64];
    printf("Enter Number in Base %d: ", base);
    scanf("%63s", input);

    // Convert lowercase hex to uppercase
    for (int i = 0; input[i]; i++)
        if (input[i] >= 'a' && input[i] <= 'f')
            input[i] -= 32;

    long long result = base_to_decimal(input, base);

    if (result == -1) {
        printf("ERROR: Invalid character for base %d.\n", base);
        return;
    }
    if (result == -2) {
        printf("ERROR: Digit out of range for base %d.\n", base);
        return;
    }

    printf("Decimal Value: %lld\n", result);
}

//------------------------------------------------------
// MAIN PROGRAM
//------------------------------------------------------
int main() {
    int choice;

    while (1) {
        display_menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: decimal_to_all(); break;
            case 2: any_base_to_decimal(2); break;
            case 3: any_base_to_decimal(8); break;
            case 4: any_base_to_decimal(16); break;
            case 5: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

