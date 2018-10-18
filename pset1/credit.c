#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool checkLuhn(const long pPurported);
long reverseNumber(long number);

// Make a global array for the number
int array[17];

int main(void) {
    long credit_card_number = get_long_long("Gimme ur credit card info: ");
    if (floor(log10(labs(credit_card_number)))+1 < 13) {
        printf("INVALID\n");
    } else {
        if (checkLuhn(credit_card_number)) {
            if (reverseNumber(reverseNumber(credit_card_number)%10) == 4) {
                printf("VISA\n");
            } else if (reverseNumber(reverseNumber(credit_card_number)%100) == 34
            || reverseNumber(reverseNumber(credit_card_number)%100) == 37) {
                printf("AMEX\n");
            } else if (reverseNumber(reverseNumber(credit_card_number)%100) == 51
            || reverseNumber(reverseNumber(credit_card_number)%100) == 52
            || reverseNumber(reverseNumber(credit_card_number)%100) == 53
            || reverseNumber(reverseNumber(credit_card_number)%100) == 54
            || reverseNumber(reverseNumber(credit_card_number)%100) == 55) {
                printf("MASTERCARD\n");
            } else {
                printf("INVALID\n");
            }
        } else {
            printf("INVALID\n");
        }
    }
}

// https://en.wikipedia.org/wiki/Luhn_algorithm#C
// I did get the Luhn algorithm working, but it was really badly writen, and was too slow, so looking for the algorithm online yeilded this.
// Why reinvent the wheel?
// That being said, I did have to modify it slightly to work with longs...
bool checkLuhn(const long pPurported) {
    int nSum  = 0;
    int nDigits = floor(log10(labs(pPurported))) + 1;
    int nParity = (nDigits-1) % 2;
    char cDigit[2] = "\0";
    char str[256];
    sprintf(str, "%ld", pPurported);
    for (int i = nDigits; i > 0 ; i--) {
        cDigit[0] = str[i-1];
        int nDigit = atoi(cDigit);
        if (nParity == i % 2) {
            nDigit = nDigit * 2;
        }
        nSum += nDigit/10;
        nSum += nDigit%10;
    }
    return 0 == nSum % 10;
}

// Reverses the number
long reverseNumber(long number) {
    int remainder;
    long reversedNumber = 0;
    while(number != 0) {
        remainder = number%10;
        reversedNumber = reversedNumber*10 + remainder;
        number /= 10;
    }
    return reversedNumber;
}