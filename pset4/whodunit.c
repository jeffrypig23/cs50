#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit <infile> <outfile>\n");
        return 1;
    }

    char *in = argv[1], *out = argv[2];

    // Why are there no try catch blocks in c? ;_;

    FILE *infile = fopen(in, "r");
    if (!infile)
    {
        fprintf(stderr, "Could not open %s.\n", in);
        return 2;
    }

    FILE *outfile = fopen(out, "w");
    if (!outfile)
    {
        fclose(infile);
        fprintf(stderr, "Could not create %s.\n", out);
        return 3;
    }

    BITMAPFILEHEADER bfh;
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, infile);

    BITMAPINFOHEADER bih;
    fread(&bih, sizeof(BITMAPINFOHEADER), 1, infile);

    if (bfh.bfType != 0x4d42 || bfh.bfOffBits != 54 || bih.biSize != 40 ||
        bih.biBitCount != 24 || bih.biCompression != 0)
    {
        fclose(outfile);
        fclose(infile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, outfile);
    fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, outfile);

    int padding = (4 - (bih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0, biHeight = abs(bih.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bih.biWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, infile);
            //printf("triple: %c\n", &triple);
            triple.rgbtBlue = 0;
            triple.rgbtGreen = 0;
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outfile);
        }
        fseek(infile, padding, SEEK_CUR);
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outfile);
        }
    }

    fclose(infile);
    fclose(outfile);
    return 0;

}