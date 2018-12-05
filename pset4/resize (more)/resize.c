#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Check if the correct number of arguments were entered
    if (argc != 4)
    {
        printf("Usage: ./resize <scale> <infile> <outfile>\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // Get the amount to scale the image to
    float scale = atof(argv[1]);

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (!outptr)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 4;
    }

    // Create a a variable for padding, and the new padding
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4,
        newPadding = fmod(4 - (fmod(round(bi.biWidth * scale) * sizeof(RGBTRIPLE), 4)), 4);

    // Update and write the outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER nbi;
    nbi.biSize = bi.biSize;
    nbi.biWidth = round(bi.biWidth * scale);
    nbi.biHeight = round(bi.biHeight * scale);
    nbi.biPlanes = bi.biPlanes;
    nbi.biBitCount = bi.biBitCount;
    nbi.biCompression = bi.biCompression;
    nbi.biSizeImage = ((sizeof(RGBTRIPLE) * (nbi.biWidth) + newPadding) * abs(nbi.biHeight));
    nbi.biXPelsPerMeter = bi.biXPelsPerMeter;
    nbi.biYPelsPerMeter = bi.biYPelsPerMeter;
    nbi.biClrUsed = bi.biClrUsed;
    nbi.biClrImportant = bi.biClrImportant;

    // Update and write the outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER nbf;
    nbf.bfType = bf.bfType;
    nbf.bfSize = nbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    nbf.bfReserved1 = bf.bfReserved1;
    nbf.bfReserved2 = bf.bfReserved2;
    nbf.bfOffBits = bf.bfOffBits;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write the outfile's BITMAPINFOHEADER
    fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Go down the height of the image
    for (int i = 0, height = abs(bi.biHeight); i < height; i++)
    {

        // Scale vertically as well as horizontally
        for (int _ = 0; _ < ceil(scale); _++)
        {
            // Seek to the beginning of the file, but be sure to skip over the padding
            fseek(inptr, bf.bfOffBits + (bi.biWidth * 3 + padding) * i, SEEK_SET);

            // Check if certain lines need to be skipped
            bool skip = scale < 1;
            if (skip)
            {
                i++;
            }

            // Read over the width of the image
            for (int j = 0; j < (bi.biWidth); j++)
            {
                // Store each pixel as a RGBTRIPLE
                RGBTRIPLE pixel;

                // Read the current pixel
                fread(&pixel, sizeof(RGBTRIPLE), 1, inptr);

                // Skip check
                if (scale < 1)
                {
                    skip = !skip;
                }

                // Write the scaled data to the file
                if (!skip)
                {
                    for (int __ = 0; __ < round(scale); __++)
                    {
                        fwrite(&pixel, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
            }

            // Write the padding
            fseek(inptr, padding, SEEK_CUR);
            for (int __ = 0; __ < newPadding; __++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // Close the files
    fclose(inptr);
    fclose(outptr);

    return 0;
}