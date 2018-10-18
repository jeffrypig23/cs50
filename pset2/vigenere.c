#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int atoi(const char *nptr);
char *strchr(const char *s, int c);

int main(int argc, string argv[])
{
    // This style sucks >.<
    if (argc != 2)
    {
        // This style sucks >.<
        printf("Usage: ./vigenere <string>\n");
        return 1;
    }
    else
    {
        string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int offsets[strlen(argv[1])];
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            // This style sucks >.<
            if (strchr(alphabet, argv[1][i]) != NULL)
            {
                offsets[i] = toupper(argv[1][i]) - (int)'A';
            }
            else
            {
                // This style sucks >.<
                printf("Usage: ./vigenere <string>\n");
                return 1;
            }
        }

        string enteredText = get_string("plaintext: ");
        char cipheredText[strlen(enteredText) + 1];
        for (int i = 0, o = 0; i < strlen(enteredText); i++)
        {
            bool isLetter = (strchr(alphabet, enteredText[i]) != NULL);
            if (isLetter)
            {
                if (o > strlen(argv[1]) - 1)
                {
                    // This style sucks >.<
                    o = 0;
                }
                // This style sucks >.<
                if (isupper(enteredText[i]))
                {
                    // This style sucks >.<
                    int newChar = ((int) enteredText[i] - 'A' + offsets[o]);
                    if (newChar > 26)
                    {
                        // This style sucks >.<
                        newChar = newChar - 26;
                    }
                    cipheredText[i] = (char) newChar + 'A';
                }
                else
                {
                    // This style sucks >.<
                    int newChar = ((int) enteredText[i] - 'a' + offsets[o]);
                    if (newChar > 26)
                    {
                        // This style sucks >.<
                        newChar = newChar - 26;
                    }
                    else if ((char)(newChar + (int) 'a') == '{')
                    {
                        newChar = 0;
                    }
                    cipheredText[i] = (char) newChar + 'a';
                }
                o++;
            }
            else
            {
                // This style sucks >.<
                cipheredText[i] = enteredText[i];
            }
        }
        cipheredText[strlen(enteredText)] = '\0';
        printf("ciphertext: %s\n", cipheredText);
    }
}