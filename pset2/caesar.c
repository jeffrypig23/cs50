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
        printf("Usage: ./caesar <positive number>\n");
        return 1;
    }
    else
    {
        int offset = atoi(argv[1]);
        // check offset
        while (offset > 26)
        {
            offset = offset - 26;
        }
        string enteredText = get_string("plaintext: ");
        char cipheredText[strlen(enteredText)];
        string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < strlen(enteredText); i++)
        {
            // This style sucks >.<
            bool isLetter = (strchr(alphabet, enteredText[i]) != NULL);
            if (isLetter)
            {
                // This style sucks >.<
                if (isupper(enteredText[i]))
                {
                    // This style sucks >.<
                    int newChar = ((int) enteredText[i] - 'A' + offset);
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
                    int newChar = ((int) enteredText[i] - 'a' + offset);
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
            }
            else
            {
                // This style sucks >.<
                cipheredText[i] = enteredText[i];
            }
        }
        printf("ciphertext: %s\n", cipheredText);
    }
}