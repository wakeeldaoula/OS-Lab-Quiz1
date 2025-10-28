#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h> // For isalpha, isdigit

int main(int argc, char *argv[]) {
    int sum = 0;

    printf("Child: Arguments received:\n");
    for (int i = 1; i < argc; i++) { // Start from argv[1] to skip program name
        char *arg = argv[i];
        printf("  Argument %d: '%s'\n", i, arg);

        // Check if the argument is a single character
        if (strlen(arg) == 1) {
            char c = arg[0]; // Get the character

            if (isalpha(c)) {
                printf("  '%c' is an alphabet.\n", c);
            } else if (isdigit(c)) {
                // Convert character digit to integer value
                sum += (c - '0');
                printf("  '%c' is a digit. Current sum: %d\n", c, sum);
            } else {
                printf("  '%c' is neither an alphabet nor a digit.\n", c);
            }
        } else {
            printf("  '%s' is a string, not a single character. Skipping for sum/alphabet check.\n", arg);
        }
    }

    printf("Child: The sum of the numbers: %d\n", sum);

    return 0;
}
