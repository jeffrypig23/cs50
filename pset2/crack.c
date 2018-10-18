#include <cs50.h>
#include <stdio.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <math.h>

string crack(string password_hash, string salt);

char *crypt(const char *key, const char *salt);

int main(int argc, string argv[])
{
    // This style sucks >.<
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    else
    {
        char slt[3];
        strncpy(slt, argv[1], 2);
        // Need to add null terminator
        slt[2] = '\0';
        crack(argv[1], slt);
    }
}

string crack(string password_hash, string salt)
{
    // This style sucks >.<
    string password = "Cannot get password";
    long attempts = 0;
    char guessString[6];
    bool done = false, validated = false;

    for (int i = 0; i < 5; i++)
    {
        // This style sucks >.<
        guessString[i] = '\0';
    }
    guessString[5] = '\0';

    for (int a = (int) 'A'; a < (int) 'z'; a++)
    {
        // This style sucks >.<
        if (a == 91)
        {
            // This style sucks >.<
            a = 97;
        }
        for (int b = (int) 'A'; b < (int) 'z'; b++)
        {
            // This style sucks >.<
            if (b == 91)
            {
                // This style sucks >.<
                b = 97;
            }
            for (int c = (int) 'A'; c < (int) 'z'; c++)
            {
                // This style sucks >.<
                if (c == 91)
                {
                    // This style sucks >.<
                    c = 97;
                }
                for (int d = (int) 'A'; d < (int) 'z'; d++)
                {
                    // This style sucks >.<
                    if (d == 91)
                    {
                        // This style sucks >.<
                        d = 97;
                    }
                    for (int e = (int) 'A'; e < (int) 'z'; e++)
                    {
                        // This style sucks >.<
                        if (e == 91)
                        {
                            // This style sucks >.<
                            e = 97;
                        }
                        attempts++;
                        guessString[0] = (char) e;
                        // Just for testing purposes, lets see what happens when I set the string to ROFL
                        /*
                        guessString[0] = 'R';
                        guessString[1] = 'O';
                        guessString[2] = 'F';
                        guessString[3] = 'L';
                        */

                        //char hash_location = *crypt(guessString, salt);
                        char hash[14], password_hash_char[14];
                        string strHash = crypt(guessString, salt); //&hash_location;
                        for (int k = 0; k < strlen(strHash); k++)
                        {
                            hash[k] = strHash[k];
                            password_hash_char[k] = password_hash[k];
                        }
                        hash[13] = '\0';
                        password_hash_char[13] = '\0';
                        validated = true;
                        for (int v = 0; v < 14; v++)
                        {
                            if (hash[v] != password_hash_char[v])
                            {
                                validated = false;
                            }
                        }
                        // Fun debugging log :D
                        // printf("Trying combo: %s\nGiven hash: %s\n, Hash: %s\nAttempts: %li\n\n", guessString, password_hash, hash, attempts);
                        if (validated) // So strcmp is a thing...
                        {
                            // This style sucks >.<
                            printf("%s\n", guessString);
                            password = guessString;
                            //strncpy(password, guessString, 5);
                            a = 127, b = 127, c = 127, d = 127, e = 127;
                            done = true;
                            //return password;
                        }
                    }
                    if (!done)
                    {
                        guessString[1] = (char) d;
                    }
                }
                if (!done)
                {
                    guessString[2] = (char) c;
                }
            }
            if (!done)
            {
                guessString[3] = (char) b;
            }
        }
        if (!done)
        {
            guessString[4] = (char) a;
        }
    }
    return password;
}