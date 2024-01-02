#include <cs50.h>
#include <stdio.h

int main(void)
{
    // Prompt for height '#'
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // # Loops
    int i, j, k;
    for (i = 0; i < height; i++)
    {
        for (j = i + 1; j < height; j++)
        {
            printf(" ");
        }
        for (k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
