#include <stdio.h>
#include <math.h>
#include <cs50.h>

float get_input()
{
    
    float amount;
    // repeat until valid input entered
    do {
        amount = get_float("How much change: ");
    }
    while (amount < 0.0);
    return amount;
}

int calculate(float amount) 
{
    int coins[4] = {1, 5, 10, 25};
    int cents = round(amount * 100);
    int min_coins = 0;
    for (int i = 3; i >= 0; i--)
    {
        // start at 25, and subtract it from cents until cents < 25
        // repeat for all other coins
        while(cents >= coins[i])
        {
            cents -= coins[i];
            min_coins++;
        }
    }
    return min_coins;
   
}

int main(void)
{
    float amount = get_input();
    int coins = calculate(amount);
    printf("%i\n", coins);
}
