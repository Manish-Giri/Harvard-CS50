#include <cs50.h>
#include <stdio.h>
int get_input(void);
void build_pyramid(int height);
void print_backward(int height, int level);
void print_forward(int height, int level);
int main(void)
{
    // get a positive number between 1 and 8
    int height = get_input();
    // printf("User entered: %i\n", height);
    build_pyramid(height);
    printf("\n");
}

int get_input(void)
{
    int input;
    // check for positive input
    do 
    {
        input = get_int("Enter a positive integer between 1 and 8: ");
    } 
    while (input < 1 || input > 8);
    return input;    
}

void build_pyramid(int height) 
{
    int width = 2;
    for (int level = 1; level <= height; level++)
    {
        print_backward(height, level);
        printf("  ");
        print_forward(height, level);
        if (level < height)
        {
            printf("\n");
        }
       
    }
}

void print_backward(int height, int level)
{
    // spaces = height - level 
    // hashes = level
    int spaces = height - level;
    int hashes = level;
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < level; i++)
    {
        printf("#");
    }
}

void print_forward(int height, int level)
{
    for (int i = 0; i < level; i++)
    {
        printf("#");
    }
}
