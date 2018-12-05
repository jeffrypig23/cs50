#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{

    // Check if arguments are valid
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover <card.raw>\n");
        return 1;
    }

    // Check if can read file
    FILE *infile = fopen(argv[1], "r");
    if (!infile)
    {
        fprintf(stderr, "Cannot read file!\n");
        return 2;
    }

    unsigned char buffer[512];
    char filename[8];
    int count = 0;
    bool imageOpen = false;

    FILE *outfile;

    while (fread(buffer, 512, 1, infile) == 1)
    {
        // 512 byte buffer

        // Check if this is a new JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] >= 0xe0 && buffer[3] <= 0xef)))
        {
            // The walkthroughs use of buffer[3] & 0xf0 == 0xe0 wasnt correct :/

            // Check if image is already open
            if (imageOpen)
            {
                // Close the current image, and open a new one
                fclose(outfile);
                imageOpen = false;
            }

            // Open an outfile to write to
            sprintf(filename, "%03i.jpg", count);
            outfile = fopen(filename, "w");
            count++;
            imageOpen = true;
        }

        // Write the image if found
        if (imageOpen)
        {
            fwrite(buffer, 512, 1, outfile);
        }
    }

    // Close the outfile
    if (outfile)
    {
        fclose(outfile);
    }

    // Close the infile
    if (infile)
    {
        fclose(infile);
    }
    return 0;
}