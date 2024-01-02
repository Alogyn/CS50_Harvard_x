#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // One command-line condition
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Verify that characters in argv[1] are digits
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert the string argument to an int argument
    int k = atoi(argv[1]);

    // Get input text from the user
    string plaintext = get_string("Plaintext: ");
    printf("Ciphertext: ");

    for (int j = 0; j < strlen(plaintext); j++)
    {
        // Encrypting if uppercase
        if (isupper(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 'A' + k) % 26 + 'A');
        }

        // Encrypting if lowercase
        else if (islower(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 'a' + k) % 26 + 'a');
        }

        // No change for special characters
        else
        {
            printf("%c", plaintext[j]);
        }
    }

    printf("\n");

    return 0;
}
