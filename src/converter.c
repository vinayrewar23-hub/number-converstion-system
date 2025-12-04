#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/converter.h"

// Implements the Repeated Division algorithm (Decimal to any base)
void decimal_to_base(long long decimal_num, int base, char result[]) {
    if (decimal_num == 0) {
        strcpy(result, "0");
        return;
    }

    int i = 0;
    long long temp_num = decimal_num;

    while (temp_num > 0) {
        long long remainder = temp_num % base;
        char digit;

        if (remainder < 10) {
            digit = remainder + '0';
        } else {
            digit = remainder - 10 + 'A';
        }

        result[i++] = digit;
        temp_num /= base;
    }
    result[i] = '\0';

    int len = strlen(result);
    for (int j = 0; j < len / 2; j++) {
        char temp = result[j];
        result[j] = result[len - 1 - j];
        result[len - 1 - j] = temp;
    }
}

long long base_to_decimal(const char *num_str, int base) {
    long long decimal_num = 0;
    int len = strlen(num_str);
    int power = 0;

    for (int i = len - 1; i >= 0; i--) {
        char digit = num_str[i];
        int value;

        if (digit >= '0' && digit <= '9') {
            value = digit - '0';
        } else if (digit >= 'A' && digit <= 'F') {
            value = digit - 'A' + 10;
        } else if (digit >= 'a' && digit <= 'f') {
            value = digit - 'a' + 10;
        } else {
            return -1;
        }

        if (value >= base) {
            return -2;
        }

        decimal_num += value * (long long)pow(base, power);
        power++;
    }
    return decimal_num;
}

void display_menu() {
    printf("\n--- Number Conversion System Menu ---\n");
    printf("1. Decimal (10) to Other Bases\n");
    printf("2. Binary (2) to Decimal\n");
    printf("3. Octal (8) to Decimal\n");
    printf("4. Hexadecimal (16) to Decimal\n");
    printf("5. Exit\n");
    printf("-------------------------------------\n");
}

void decimal_to_all() {
    long long dec;
    printf("Enter Decimal Number (Base 10): ");
    if (scanf("%lld", &dec) != 1 || dec < 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        while (getchar() != '\n');
        return;
    }

    char binary_res[64];
    char octal_res[64];
    char hex_res[64];

    decimal_to_base(dec, 2, binary_res);
    decimal_to_base(dec, 8, octal_res);
    decimal_to_base(dec, 16, hex_res);

    printf("\nConversion Results for %lld:\n", dec);
    printf("---------------------------------\n");
    printf("Binary (Base 2):       %s\n", binary_res);
    printf("Octal (Base 8):        %s\n", octal_res);
    printf("Hexadecimal (Base 16): %s\n", hex_res);
    printf("---------------------------------\n");
}

void any_base_to_decimal(int base) {
    char input_str[64];
    printf("Enter Number in Base %d: ", base);
    scanf("%63s", input_str);

    for (int i = 0; input_str[i]; i++) {
        if (input_str[i] >= 'a' && input_str[i] <= 'z') {
            input_str[i] = input_str[i] - 32;
        }
    }

    long long dec = base_to_decimal(input_str, base);

    printf("---------------------------------\n");
    if (dec == -1) {
        printf("ERROR: Invalid character detected in the input for Base %d.\n", base);
    } else if (dec == -2) {
        printf("ERROR: Invalid digit detected (e.g., 8 or 9 in Binary/Octal).\n");
    } else {
        printf("Input (%s in Base %d) = Decimal (Base 10): %lld\n", input_str, base, dec);
    }
    printf("---------------------------------\n");
}
