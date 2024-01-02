#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Get input text from user
    string text = get_string("Text: ");

    // Declarition of calculation variables
    int letters = 0, words = 1, sentences = 0;

    // Text Caracters calculation loops
    for (int i = 0; i < strlen(text); i++)
    {
        // Count letters
        if (isalpha(text[i]))
        {
            letters++;
        }

        // Count words
        if (isspace(text[i]))
        {
            words++;
        }

        // Count Sentences
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    // Count Index
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Get output Grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }
}