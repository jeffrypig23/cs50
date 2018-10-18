#include <stdio.h>
#include <cs50.h>
#include <math.h>

int amount = 0, roundValue;

void subtractValue(int currentAmount);

int main(void) {

    float valueOwed = get_float("How much do I owe? ");
    if (valueOwed < 0) {
        valueOwed = get_float("How much do I owe? ");
    }
    roundValue = roundf(valueOwed * 100);
    subtractValue(25);
    subtractValue(10);
    subtractValue(5);
    subtractValue(1);
   printf("%i\n", amount);
}

void subtractValue(int currentAmount) {
    while (roundValue - currentAmount >= 0) {
        amount++;
        //printf("Subtracting %i...\nNew value: %i\n", currentAmount, roundValue);
        roundValue = roundValue - currentAmount;
    }
}