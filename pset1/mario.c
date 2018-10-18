#include <cs50.h> // Use this library for get_int()
#include <stdio.h>

int main(void) {
    int height = get_int("Height: ");
    if (height != 0) {
        while (height < 1 || height > 23) { // Check heights
            height = get_int("Height: ");
        }
        // printf("Height entered: %i\n",height); // For debugging
        int spaceValue = height-1;
        int hashValue = 1;
        // printf("spaceValue: %i\nhashValue: %i\n", spaceValue, hashValue); // For debugging
        for (int q = 0; q < height; q++) {
            for (int a = 0; a < spaceValue; a++) {
                printf(" ");
            }
            printf("#"); // Use this for the simple version
            for (int b = 0; b < hashValue; b++) {
                printf("#");
            }
            /*
            printf("  ");
            for (int c = 0; c < hashValue; c++) {
                printf("#");
            }
            */ // Disabled for simple mode

            spaceValue--;
            hashValue++;
            printf("\n");
        }
    }
}