// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

typedef struct bin
{
    int sz; // How many words are stored in the bin
    char *words; // The word
} bin;

// Create a global array of bins, based on the first character in the word
struct bin bins[BINNUMBER];

// Create a global variable for cointing total words
long totalSize = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Create a variable that is not read only
    char *lowerWord = malloc(LENGTH);

    // First set the word to lower cased
    for (int lower = 0; lower < strlen(word); lower++)
    {
        lowerWord[lower] = tolower(word[lower]);
    }
    lowerWord[strlen(word)] = '\0';

    // Compare words
    for (int compareWords = 0; compareWords < bins[lowerWord[0] - 'a'].sz; compareWords++)
    {
        // Create a string place holder for getting the word
        char *strCheck = malloc(LENGTH);
        int strCheckNumber = 0;

        // Check if the size of the bin is greater than 0
        if (bins[lowerWord[0] - 'a'].sz > 0)
        {
            // Itterte through the words in the bin
            long length = strlen(bins[lowerWord[0] - 'a'].words);
            for (int newLineHunt = 0; newLineHunt < length + 1; newLineHunt++)
            {
                strCheck[strCheckNumber] = bins[lowerWord[0] - 'a'].words[newLineHunt];

                // Check if its a new line
                if (strCheck[strCheckNumber] == '\n' || strCheck[strCheckNumber] == '\0')
                {
                    // Remove the new line
                    strCheck[strCheckNumber] = '\0';

                    // Compare the 2 strings to see if they are more or less the same
                    if (strcmp(strCheck, lowerWord) == 0)
                    {
                        free(strCheck);
                        free(lowerWord);
                        return true;
                    }
                    else
                    {
                        strCheckNumber = 0;
                        // Reset the word
                        for (int reset = strlen(strCheck) - 1; reset > 0; reset--)
                        {
                            strCheck[reset] = '\0';
                        }
                    }
                }
                else
                {
                    strCheckNumber++;
                }
            }
        }
        free(strCheck);
    }
    free(lowerWord);
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Attempt to load create a FILE representation of the dictionary
    FILE *infile = fopen(dictionary, "r");
    if (infile)
    {
        // Go to the end of the file
        fseek(infile, 0, SEEK_END);

        // Get the end of file posistion to tell how big the file is
        long filesize = ftell(infile);

        // Go back to the start
        rewind(infile);

        // Initalize the bins to nothing for now
        for (int notBin = 0; notBin < BINNUMBER; notBin++)
        {
            bins[notBin].sz = 0;
            bins[notBin].words = malloc(LENGTH);
        }

        // Set aside a variable for storing the word, and initalize it to '\0'
        char word[LENGTH + 1];
        for (int nulify = 0; nulify < LENGTH; nulify++)
        {
            word[nulify] = '\0';

            // Also initialize the bins to nul
            for (int k = 0; k < BINNUMBER; k++)
            {
                bins[k].words[nulify] = '\0';
            }
        }

        // Variable for checking word size
        int wordSize = 0;

        // Variable for storing the character
        char character;

        // Read the file, one character at a time
        for (int f = 0; f < filesize; f++)
        {

            // Save the lower-cased characcter to the character variable
            character = tolower(getc(infile));
            word[wordSize] = character;

            // Check if the character is a new line, ie end of word
            if (word[wordSize] == '\n')
            {

                // Save the word letter by letter to a string, and then put that sting into the respective bin
                char initialC = word[0];

                // Get the lengths of various words
                long wordLength = strlen(word);
                long binLength = strlen(bins[initialC - 'a'].words);
                long newBinStringSize = (wordLength + 1 + binLength + 1 + 2);

                // Create a placeholder for the new string
                char *newBinString = malloc(newBinStringSize + 1);

                // Offset for appending strings, for now, start at one
                int stringOffset = 0;

                // Itterate through the new string, and add the new word
                for (int newStringAdd = 0; newStringAdd < wordLength; newStringAdd++)
                {
                    newBinString[newStringAdd] = word[newStringAdd];
                    stringOffset++;
                }

                // Itterate throug the new string, and add the old words
                for (int oldStringAdd = 0; oldStringAdd < binLength; oldStringAdd++)
                {
                    newBinString[stringOffset] = bins[initialC - 'a'].words[oldStringAdd];
                    stringOffset++;
                }

                // Free the old bin string
                free((char *) bins[initialC - 'a'].words);

                // Add the nul character
                newBinString[stringOffset] = '\0';

                // Check if the 2nd to last character is new line, and set it to nul if it is
                long binStringSize = strlen(newBinString);
                if (newBinString[binStringSize - 1] == '\n')
                {
                    // Go go the end of the character and set it to nul
                    newBinString[binStringSize - 1] = '\0';
                }

                // Recreate the bin and adjust for the new size
                bins[initialC - 'a'].words = malloc(binStringSize + 1);

                // Save the word to the bin
                strcpy(bins[initialC - 'a'].words, newBinString);

                // Reset the word array to '\0', do it backwards so that the pointer doesnt accidentally get overwritten first
                for (int i = wordLength - 1; i >= 0; i--)
                {
                    word[i] = '\0';
                }

                // Increase the size of that bin, and the total size by 1
                bins[initialC - 'a'].sz++;
                totalSize++;

                // Free the bin string
                free(newBinString);

                // Set the word size back to 0
                wordSize = 0;
            }
            else
            {
                // Increase the wordcount size
                wordSize++;
            }
        }
        // Close the file
        fclose(infile);
    }
    else
    {
        printf("An error occoured reading the dictionary\n");
        return false;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Total size is a global variable that is used to track the actual size
    return totalSize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Go throug each bin and free it
    // #freebin
    for (int hashtagFreeBin = 0; hashtagFreeBin < BINNUMBER; hashtagFreeBin++)
    {
        free(bins[hashtagFreeBin].words);
    }
    return true;
}